/* 
 * This is a crappy caesar cipher for Plan 9.
 * Not recommended for pregnant/nursing persons, or persons
 * who are sensitive to caffeine.
 */
#include <u.h>
#include <libc.h>
#include <stdio.h>

char caesar(int r, char c);

/*
 * rot: no. of rotations
 * one: first arg to read
 * cur: current char to manipulate
 */
void
main(int argc, char *argv[])
{
	int rot;
	int one;
	char cur;

	if (argc < 2) {
		fprint(2, "usage: %s [+/-][ROTATIONS] Your Message\n", argv[0]);
		exits("usage");
	}

	rot = atoi(argv[1]);
	one = 2;

	/* default is rot13 */
	if (rot == 0) {
		rot = 13;
		one = 1;
	}

	/* wrap negative */
	if (rot < 0)
		rot = 26 - (-1 * (rot % 26));

	for (int i = one; i < argc; i++) {
		for (int j = 0; argv[i][j] != '\0'; j++) {
			cur = caesar(rot, argv[i][j]);
			putchar(cur);
		}
		if (i < argc - 1)
			putchar(' ');
	}

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
