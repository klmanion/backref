//backref.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "backref.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

backref_t* __pure2
backref_make(
	const ptrdiff_t	p,
	const size_t	n,
	char 			*const pattern)
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

backref_t* __pure
backref_free(
	backref_t *br)
{
	if (br) {
		if (br->pattern)
			free(br->pattern);
		free(br);
	}

	return br = NULL;
}

char* __pure
backref_to_str(
	const backref_t *const br)
{
	char *s;

	s = (char *)malloc(CHAR_BIT*80);
	if (!s)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	snprintf(s, 79, "<%td,%zu>", br->p, br->n);

	return s;
}

backref_t* __pure
str_to_backref(
	char *const brs)
{
	ptrdiff_t p;
	size_t n;

	sscanf(brs, "<%td,%zu>", &p, &n);

	return backref_make(p, n, NULL);
}

char* __pure2
make_backref_str(
	const ptrdiff_t	p,
	const size_t	n)
{
	backref_t br;

	br.p = p;
	br.n = n;

	return backref_to_str(&br);
}

size_t __pure
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
