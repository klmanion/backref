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
backref_make(
	const int p,
	const int n,
	char *pattern)
{
	backref_t *br;

	br = (backref_t *)malloc(backref_sz);
	if (!br)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	br->p = p;
	br->n = n;
	br->pattern = pattern;

	return br;
}

backref_t*
backref_free(
	backref_t *br)
{
	free(br->pattern);
	free(br);

	return br = NULL;
}

char*
backref_to_str(
	const backref_t *const br)
{
	char *s;

	s = (char *)malloc(CHAR_BIT*80);
	if (!s)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	snprintf(s, 79, "<%d,%d>%c", br->p, br->n, '\0');

	return s;
}

backref_t*
str_to_backref(
	char *const brs)
{
	int p,n;

	sscanf(brs, "<%d,%d>", &p, &n);

	return backref_make(p, n, NULL);
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

size_t
add_backref(
	char *const s,
	const backref_t *const br)
{
	char *brs;
	size_t sz;

	brs = backref_to_str(br);
	sz = strlen(brs);

	memcpy(strchr(s, '\0'), brs, sz+1);

	free(brs);

	return sz;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
