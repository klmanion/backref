//backref.h
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#ifndef __BACKREF_H__
#define __BACKREF_H__

#include <stdlib.h>
#include <stddef.h>

typedef
struct _backref {
	ptrdiff_t	p;
	size_t		n;
	char 		*pattern;
} backref_t;
#define backref_sz sizeof(backref_t)

__BEGIN_DECLS
backref_t*	backref_make __P((const ptrdiff_t,const size_t,char *const)) __pure2;
backref_t*	backref_free __P((backref_t *)) __pure;

char*		backref_to_str __P((const backref_t *const)) __pure;
backref_t*	str_to_backref __P((char *const)) __pure;

char*	make_backref_str __P((const ptrdiff_t,const size_t)) __pure2;

size_t	add_backref __P((char *const,const backref_t *const)) __pure;
__END_DECLS

#endif /* !__BACK_REF_H__ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
