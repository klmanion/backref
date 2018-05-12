//main.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

int
main(
	int argc,
	char *const argv[])
{
	printf("version: %s\n", VERSION);

	return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
