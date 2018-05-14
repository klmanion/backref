//backref.h
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#ifndef __BACKREF_H__
#define __BACKREF_H__

#include <stdlib.h>

typedef
struct _backref {
	int	p;
	int	n;
	char *pattern;
} backref_t;
#define backref_sz sizeof(backref_t)

__BEGIN_DECLS
backref_t*	backref_make __P((const int,const int,char *));
backref_t*	backref_free __P((backref_t *));

char*	backref_to_str __P((const backref_t *const));
char*	make_backref_str __P((const int,const int));

size_t	add_backref __P((char *const,const backref_t *const));
__END_DECLS

#endif /* !__BACK_REF_H__ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
