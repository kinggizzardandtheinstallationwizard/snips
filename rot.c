/* 
 * This is a slightly less crappy caesar cipher for Plan 9.
 * Not recommended for pregnant/nursing persons, or persons
 * who are sensitive to caffeine.
 */
#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <bio.h>

char caesar(int r, char c);

void
main(int argc, char *argv[])
{
	/* for line by line input */
	Biobuf inbuf;
	char *ln;
	int lnlen;

	int rots;
	char cur;

	if (Binit(&inbuf, 0, OREAD) == Beof)
		sysfatal("oh the humanity! %r");

	rots = 13; /* default */
	if (argc > 1)
		rots = atoi(argv[1]);

	/* read until EOF */
	while ((ln = Brdline(&inbuf, '\n')) != nil) {
		lnlen = Blinelen(&inbuf);
		for (int i = 0; i < lnlen; i++) {
			cur = caesar(rots, ln[i]);
			putchar(cur);
		}
	}
	Bterm(&inbuf);

	putchar('\n');

	exits(nil);
}

char
caesar(int r, char c)
{
	/* assume lowercase */
	if ((c > 122) || (c < 97))
		goto notlower;

	c -= 97;
	c = (c + r) % 26;
	c += 97;

	return c;

notlower:
	if ((c > 90) || (c < 65))
		return c;

	c -= 65;
	c = (c + r) % 26;
	c += 65;

	return c;
}
