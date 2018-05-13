//encode.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "encode.h"

#include <stdio.h>
#include <limits.h>
#include <err.h>
#include <string.h>
#include <stdint.h>
#include "defs.h"


extern	uint8_t	v_flg;
extern	uint8_t	s_flg;


int*
match_pattern(
	const char **const restrict	enc,
	const size_t				enc_curi,
	const char *const restrict	pattern,
	size_t						nm)
{
	int *offsets;
	size_t dex;

	offsets = (int *)malloc(sizeof(int)*1024);
	if (!offsets)
		errx(1,"malloc error, %s:%d", __FILE__, __LINE__);

	dex = 0;
	offsets[dex] = -1;

	//for each line of the encoding
	for (size_t i=0,k=0; i<=enc_curi; ++i) {
		for (size_t j=0,sz=strlen(enc[i]); j<sz; ++j,++k) {
			if (strncmp(&enc[i][j], pattern, nm)==0) {
				offsets[dex] = k;
				offsets[++dex] = -1;
			}
		}
	}

	return offsets[0] == -1 ? NULL : offsets;
}
	


void
encode(
	const int nm,
	const char *const sep)
{
	char *in,**enc;
	lookup_t *lookup_table = NULL;
	char fmt[80];

	enc = (char **)malloc(sizeof(char *)*BUF_SZ);
	if (!enc)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	snprintf(fmt, 79, "%%%d[^%s]", BUF_SZ-1, sep);

	for (size_t i=0; !feof(stdin) && i<BUF_SZ; ++i)
	{
		in = (char *)malloc(CHAR_BIT*BUF_SZ);
		if (!in)
			errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

		scanf(fmt, in);

#ifdef DEBUG
		printf("reading in: %s\n", in);
#endif

		enc[i] = (char *)malloc(CHAR_BIT*BUF_SZ);
		if (!enc[i])
			errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);
		enc[i+1] = NULL;

		memcpy(enc[i], in, nm);
		enc[i][nm] = '\0';
		lookup_table = lookup_init(&lookup_table);
		for (size_t j=nm,k=nm,sz=strlen(in); j<sz; ++j,++k)
		{
			backref_t *br;
			int *offsets;
			int *ptr,*offset;
			int ni,n;
			char *s;
			//check if the pattern starting at in[j] reoccurs previously
			//first, in the lookup table
			offsets = lookup_pattern(lookup_table, in, j, nm);
			//second, in the encoded string
			if (!offsets)
				offsets = match_pattern(enc, i, &in[j], nm);

			if (offsets) {
				//find the longest pattern matched
				ptr = offsets;
				n = -1;
				while (*(++ptr) != -1)
				{
					for (ni = nm; strncmp(&in[j], enc[*ptr], ni)==0; ++ni) { }
					if (ni >= n) {
						n = ni;
						offset = ptr;
					}
				}
				br = make_backref(j-*offset, n);
				add_backref(enc[i], &k, br);
				lookup_add_backref(lookup_table, br, 0); //FIXME
				free(offsets);
			} else {
				enc[i][k] = in[j];
				enc[i][k+1] = '\0';
			}
		}
		printf("%s", enc[i]);
	}
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
