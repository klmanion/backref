//backref.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "backref.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

char*
backref_to_str(
	const backref_t *const br)
{
	char *s;

	s = (char *)malloc(CHAR_BIT*80);
	if (!s)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	snprintf(s, 79, "<%d,%d>", br->p, br->n);

	return s;
}

char*
make_backref_str(
	const int p,
	const int n)
{
	backref_t br;

	br.p = p;
	br.n = n;

	return backref_to_str(br);
}

char*
add_backref_str(
	char *s,
	int *dex,
	const char *const brs)
{
	int sz = strlen(brs);

	strcpy(s[dex], brs, sz);
	*k += sz;

	return s;
}

char*
add_backref(
	char *s;
	int *dex;
	const backref_t *const br)
{
	char *brs,*r;

	brs = backref_to_str(br);
	r = add_backref_str(s, dex, brs);
	free(brs);

	return r;
}


/* vim: set ts=4 sw=4 noexpandtab tw=79: */
