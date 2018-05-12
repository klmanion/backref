//lookup.h
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#ifndef __LOOKUP_H__
#define __LOOKUP_H__

#include <stdlib.h>
#include "defs.h"

typedef
struct _lookup {
	void *foo;
} lookup_t;

__BEGIN_DECLS
backref_t*	lookup_pattern __P((const lookup_t *const,const char *const,
									const size_t,const size_t));
__END_DECLS

#endif /* !__LOOKUP_H__ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
