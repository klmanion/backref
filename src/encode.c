//encode.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "encode.h"

#include <stdio.h>
#include <limits.h>
#include <err.h>
#include <string.h>
#include "defs.h"


extern int	v_flg;
extern int	s_flg;


int*
match_pattern(
	const char **const restrict	enc,
	const size_t				enc_sz,
	const char *const restrict	pattern,
	size_t						nm)
{
	int offsets[1024];
	size_t dex;

	dex = 0;
	offsets[dex] = -1;

	//for each line of the encoding
	for (size_t i=0,k=0; i<enc_sz; ++i) {
		for (size_t j=0,sz=strlen(enc[i]); j<sz; ++j,++k) {
			if (strncmp(&enc[i][j], pattern, nm)==0) {
				offsets[dex++] = k;
				offsets[dex] = -1;
			}
		}
	}

	return offsets;
}
	


void
encode(
	const int nm,
	const char *const sep)
{
	char *in,**enc;
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
		for (size_t j=nm,k=nm,sz=strlen(in); j<sz; ++j,++k)
		{
			backref_t *br;
			int *offsets;
			int *ptr,*offset;
			int n,nM;
			char *s;
			//check if the pattern starting at in[j] reoccurs previously
			//first, in the lookup table
			br = lookup_pattern(lookup_table, in, j, nm);
			if (br) {
				s = backref_to_str(br);
				add_backref(enc[i], &k, s);
				free(s);
				continue;
			}
			//second, in the encoded string
			offsets = match_pattern(enc, i, &in[j], nm);

			//find the longest pattern matched
			ptr = offsets;
			nM = -1;
			while (*(++ptr) != -1)
			{
				for (n = nm; strncmp(&in[j], enc[*ptr], n)==0; ++n) { }
				if (n >= nM) {
					nM = n;
					offset = ptr;
				}
			}
			add_backref_raw(enc[i], &k, j-offset, nM);
		}
		printf("%s", enc[i]);
	}
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
