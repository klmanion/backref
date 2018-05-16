//main.c
// created by: Kurt L. Manion
// on: Sat., 12 May 2018
//

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <err.h>
#include <sysexits.h>
#include <stdint.h>

#ifdef HAVE_CONFIG_H
# include <config.h>
#else /* !HAVE_CONFIG_H */
# error "no config.h"
#endif /* HAVE_CONFIG_H */

#include "encode.h"
#include "decode.h"

const char *const opts = ":edm:s::hvV";
const struct option longopts[] = {
	{ "encode",		no_argument,		NULL,	'e' },
	{ "decode",		no_argument,		NULL,	'd' },
	{ "min-width",	required_argument,	NULL,	'm' },
	{ "separator",	optional_argument,	NULL,	's' },
	{ "help",		no_argument,		NULL,	'h' },
	{ "verbose",	no_argument,		NULL,	'v' },
	{ "version",	no_argument,		NULL,	'V' },
	{ NULL, 0, NULL, 0 }
};

void __dead2
usage(
	const char *const basename)
{
	fprintf(stderr, "usage:\n"
		"\t%s [-e | -d] [-m min_width] [-s seperator]\n", basename);
	exit(EX_USAGE);
}

void __dead2
version(
	const char *const basename)
{
	fprintf(stderr, "%s version %s\n", basename, VERSION);
	exit(EX_OK);
}

static	uint8_t	e_flg;
static	uint8_t	d_flg;
		uint8_t	v_flg;

int
main(
	int argc,
	char *const argv[])
{
	extern int optind;
	extern char *optarg;
	extern int optopt;
	extern int opterr;
	char flg;
	const char *const basename = argv[0];
	int mn;
	char *sep;

	opterr = 0;

	d_flg = v_flg = 0;
	e_flg = 1;

	mn = 4;
	sep = "\0";

	while ((flg = getopt_long(argc,argv, opts, longopts, NULL)) != -1) {
		switch (flg) {
		case 'e':
			d_flg = 0;
			e_flg = 1;
			break;;

		case 'd':
			e_flg = 0;
			d_flg = 1;
			break;;

		case 'm':
			if ((mn=atoi(optarg)) <= 0)
				warnx("minimum width must be positive"),usage(basename);;
			break;;

		case 's':
			sep = optarg ? optarg : "\n";
			break;;

		case 'h':
			usage(basename);;

		case 'v':
			++v_flg;
			break;;

		case 'V':
			version(basename);;

		case '?':
			if (isprint(optopt))
				warnx("unknown option flag `%c'", (char)optopt);
			else
				warnx("unknown option code `%#x'", optopt);
			usage(basename);;

		case ':':
			warnx("option flag `%c' requires an argument", (char)optopt);
			usage(basename);;

		default: /* this will never happen */
			abort();;
		}
	}
	argc -= optind;
	argv += optind;

	if (argc > 0) {
		warnx("extraneous arguments");
		usage(basename);
	}

	if (e_flg)
		encode(mn, sep);
	else if (d_flg)
		decode();
	else {
		warnx("either the e or d option must be specified");
		usage(basename);
	}

	return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
