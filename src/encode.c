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
	char **const restrict		enc,
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
	char **enc,*in;
	char fmt[80];
	backref_t brl[BUF_SZ/2];
	size_t brl_sz;

	enc = (char **)malloc(sizeof(char *)*BUF_SZ);
	if (!enc)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	snprintf(fmt, 79, "%%%d[^%s]", BUF_SZ-1, sep);

	brl_sz = 0;

	for (size_t i=0,j=0; !feof(stdin) && i<BUF_SZ; ++i)
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

		if (i == 0) {
			memcpy(enc[i], in, nm);
			j = nm;
			enc[i][j] = '\0';
		}
		for (size_t k=i==0?nm:0,sz=strlen(in); k<sz; ++k)
		{
			char *pattern,*match;
			char *saved_head,*saved_pattern;
			size_t ct;

			pattern = &in[k];
			ct = 0;
			//search back through enc for pattern
			for (char *head=&enc[i][j],*c0=&enc[0][0]; head!=c0-1;)
			{
				switch (mode) {
				case searching:
					switch (*head) {
					case pattern[0]:
						mode = check_match;
						saved_head = head;
						saved_pattern = pattern;
						break;;

					case '>':
						mode = read_backref;
						saved_head = head;
						saved_pattern = pattern;
						break;;

					default:
						--head;
						break;;
					}
					break;;

				case check_match:
					/* TODO */
					break;;

				case pattern_match: /* FIXME */
					for (n=nm+1; strncmp(*head, pattern, n)==0; ++n) { }
					full_pattern = (char *)malloc(CHAR_BIT*(n+1));
					if (!full_pattern)
						errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);
					memcpy(match, pattern, n);
					br = make_backref(&enc[i][j]-*head, n, match);
					brl[brl_sz] = br;
					++brl_sz;
					break;;

				case read_backref:
					if (strncmp(brl[brl_sz-ct].pattern, pattern, nm)==0) {
						for (size_t n=nm+1;
								brl[brl_sz-ct].pattern[n]==pattern[n];
								++n) { }
						--n;
						for (; *head!='<'; --head) { }
					}
					++ct;
					for (; *head!='<'; --head) { }
					
			}

			//no match found
			enc[i][j] = in[k];
			enc[i][++j] = '\0';
		}
#ifdef DEBUG
		printf("enc[i]: %s\n", enc[i]);
#endif
	}
}
			



				/*
			{
				switch (mode) {
				case searching:
					switch (*head) {
					case pattern[0]:
						mode = check_match;
						break;;
					case '>':
						mode = read_backref;
						--head;
						break;;
					case default:
						--head;
						break;;
					}

				case check_match:
					if (strncmp(*head, pattern, nm)==0)
						mode = pattern_match;
					else
						mode = searching;
					break;;

				case pattern_match:
					for (n=nm+1; strncmp(*head, pattern, n)==0; ++n) { }
					br = make_backref(dex-_dex, n);
					
					*/







void
old_encode(
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
#ifdef DEBUG
				printf("adding backref p:%d n:%d\n", br->p, br->n);
#endif
				add_backref(enc[i], &k, br);
				lookup_add_backref(lookup_table, br, 0); //FIXME
				free(offsets);
			} else {
				enc[i][k] = in[j];
				enc[i][k+1] = '\0';
			}
		}
		lookup_table = lookup_free(lookup_table);
		printf("%s", enc[i]);
	}
	putchar('\n');
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
