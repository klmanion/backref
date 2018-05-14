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
	
void
encode(
	const int nm,
	const char *const sep)
{
	char in[BUF_SZ];
	char fmt[80];
	char enc[BUF_SZ];

	snprintf(fmt, 79, "%%%d[^%s]", BUF_SZ-1, sep);

	while (!feof(stdin))
	{
		scanf(fmt, in);

#ifdef DEBUG
		printf("reading in: %s\n", in);
#endif
		for (size_t i=0,k=0,sz=strlen(in); i<sz; ++i)
		{
			char *pattern,*match;
			int p,n;
			backref_t *br = NULL;
			size_t offset;

			pattern = &in[i];
#ifdef DEBUG
			printf("pattern[0]: %c\n", pattern[0]);
#endif

			//look for beginning of pattern
			for (int j=i-1; j>0; --j)
			{
				if (in[j] == pattern[0]) {
					p = i-1 - j;
					n = 1;
					for (; in[j+n]==pattern[n]; ++n) { }

					if (!br || n > br->n) {
						match = (char *)malloc(CHAR_BIT*(n+1));
						if (!match)
							errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);
						memcpy(match, &in[j], n);
						match[n] = '\0';
						if (br)
							br = backref_free(br);
						br = backref_make(p, n, match);
					}
				}
			}
			if (br && br->n >= nm) {
				k += add_backref(enc, br);
				i += br->n-1;
				br = backref_free(br);
			} else {
				enc[k] = in[i];
				enc[++k] = '\0';
			}
#ifdef DEBUG
			printf("->%s\n", enc);
#endif
		}
		printf("%s", enc);
	}
}
		
/* vim: set ts=4 sw=4 noexpandtab tw=79: */
