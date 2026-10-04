#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <bio.h>

void
main(int argc, char *argv[])
{
	Biobuf b;
	char *ln;
	int lnlen;

	if(Binit(&b,0,OREAD) == Beof)
		sysfatal("uh oh! %r");

	while ((ln = Brdline(&b, '\n')) != nil) {
		lnlen = Blinelen(&b);
		for (int i = 0; i < lnlen; i++) {
			putchar(ln[i]);
		}
	}

	Bterm(&b);

	exits(nil);
}
