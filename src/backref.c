//backref.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "backref.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

backref_t*
make_backref(
	const int p,
	const int n)
{
	backref_t *br;

	br = (backref_t *)malloc(backref_sz);
	if (!br)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	br->p = p;
	br->n = n;

	return br;
}

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

	return backref_to_str(&br);
}

char*
add_backref(
	char *s,
	size_t *dexptr,
	const backref_t *const br,
	const lookup_t *l)
{
	char *brs;
	size_t sz;

	brs = backref_to_str(br);
	sz = strlen(brs);

	memcpy(&s[*dexptr], brs, sz);
	free(brs);

	lookup_add_backref(l, br, *dexptr);

	*dexptr += sz;

	return s;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
