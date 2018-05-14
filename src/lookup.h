//lookup.h
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#ifndef __LOOKUP_H__
#define __LOOKUP_H__

#include <stdlib.h>
#include <stdbool.h>
#include "backref.h"
#include "defs.h"

/* TODO */
typedef
struct _entry {
	backref_t	*br;
	char		*pattern;
	size_t		dex;
} entry_t;
#define entry_sz sizeof(entry_t)

typedef
struct _lookup {
	entry_t	*entry_lst;
	entry_t	*head;
	entry_t	*tail;
} lookup_t;
#define lookup_sz sizeof(lookup_t)

__BEGIN_DECLS
lookup_t*	lookup_init	__P((lookup_t **));
lookup_t*	lookup_free __P((lookup_t *));

bool		lookup_empty __P((const lookup_t *const));

void		lookup_add_backref __P((const lookup_t *,const backref_t *const,
										const size_t));

int*		lookup_pattern __P((const lookup_t *const,const char *const,
									const size_t,const size_t));
__END_DECLS

#endif /* !__LOOKUP_H__ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
