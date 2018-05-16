//decode.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "decode.h"

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>
#include <err.h>
#include <math.h>
#define NDEBUG /* turn off assertions */
#include <assert.h>
#include "defs.h"

backref_t*
read_backref(
	char *const s,	//encoded string
	size_t dex)
{
	char *c;
	char *brs;
	backref_t *br;
	ptrdiff_t d;

	c = strchr(&s[dex], '>');
	d = c - &s[dex];

	brs = (char *)malloc(CHAR_BIT*(d+2));
	if (!brs)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	memcpy(brs, &s[dex], (size_t)(d+1));
	brs[d+1] = '\0';

	br = str_to_backref(brs);
	free(brs);

	return br;
}

char*
expand_backref(
	char *const s,	//decoded string
	size_t dex,
	backref_t *br)
{
	char *c0,*c;
	char *exp;
	size_t sz;

	c0 = &s[(dex-1)-br->p]; //first index of pattern

	exp = (char *)malloc(CHAR_BIT*(br->n+1));
	if (!exp)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	assert(s[dex] == '\0');
	memcpy(exp, c0, br->n);
	exp[br->n] = '\0';

	/* self-referential back-reference */
	for (ptrdiff_t d=br->n - br->p - 1; d > 0; d-=sz) {
		sz = fmin(strlen(exp), d);
		*(char *)(memmove(strchr(exp, '\0'), exp, sz)+sz) = '\0';
	}

	return exp;
}

void
decode(void)
{
	char enc[BUF_SZ];
	char dec[BUF_SZ];
	char fmt[80];
	char *exp;
	size_t exp_sz;
	backref_t *br;

	snprintf(fmt, 79, "%%%d[^%c]", BUF_SZ, '\0');

	while (!feof(stdin))
	{
		scanf(fmt, enc);

		for (size_t i=0,j=0,sz=strlen(enc); i<sz; ++i)
		{
			if (enc[i] == '<') {
				br = read_backref(enc, i);
				exp = expand_backref(dec, j, br);
				backref_free(br);
				exp_sz = strlen(exp);
				memcpy(&dec[j], exp, exp_sz);
				free(exp);
				dec[j+=exp_sz] = '\0';
				i += strchr(&enc[i], '>')-&enc[i];
			} else {
				dec[j] = enc[i];
				dec[++j] = '\0';
			}
		}
		printf("%s", dec);
	}
}


/* vim: set ts=4 sw=4 noexpandtab tw=79: */
