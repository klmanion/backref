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
} backref_t;

__BEGIN_DECLS
char*	backref_to_str __P((const backref_t *const));
char*	make_backref_str __P((const int,const int));

char*	add_backref_str __P((char *,int *,const char *const));
char*	add_backref __P((char *,int *,const backref_t *const));
char*	add_backref_raw __P((char *,int *,const int,const int));
__END_DECLS

#endif /* !__BACK_REF_H__ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
