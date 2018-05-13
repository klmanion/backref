//lookup.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include "lookup.h"

#include <err.h>

lookup_t*
lookup_init(
	lookup_t **p)
{
	*p = (lookup_t *)malloc(lookup_sz);
	if (!*p)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	*p->entry_lst = (entry_t *)malloc(entry_sz*BUF_SZ);
	if (!*p->entry_lst)
		errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	*p->head = NULL;
	*p->tail = NULL;

	return *p;
}

bool
lookup_empty(
	const lookup_t *const l)
{
	return l->head == NULL;
}

backref_t*
lookup_pattern(
	const lookup_t *const	tab,
	const char *const		s,
	const size_t			dex,
	const size_t			nm)
{
	return NULL;
}


void
lookup_add_backref(
	const lookup_t *l,
	const backref_t *const br,
	const size_t dex)
{
	return;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
