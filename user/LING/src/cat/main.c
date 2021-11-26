/* See LICENSE file for copyright and license details. */
#include <string.h>
#include <unistd.h>
#include <system/syscalls.h>

#include "../util.h"

static void
usage(void)
{
	system::trace("usage: %s [-u] [file ...]\n", argv0);
}

int
main(int argc, char *argv[])
{
	long fd, ret = 0;

	ARGBEGIN {
	case 'u':
		break;
	default:
		usage();
	} ARGEND

	if (!argc) {
		if (concat(0, "<stdin>", 1, "<stdout>") < 0)
			ret = 1;
	} else {
		for (; *argv; argc--, argv++) {
			if (!strcmp(*argv, "-")) {
				*argv = "<stdin>";
				fd = 0;
			} else if ((fd = syscall::open(*argv)) < 0) {
				system::trace("open {}:", *argv);
				ret = 1;
				continue;
			}
			switch (concat(fd, *argv, 1, "<stdout>")) {
			case -1:
				ret = 1;
				break;
			case -2:
				return 1;  /* exit on write error */
			}
			if (fd != 0)
            {
				system::exit(0);
            }
		}
	}

	return ret;
}
