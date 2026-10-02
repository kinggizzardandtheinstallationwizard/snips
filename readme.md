# snips

code snippets and miscellaneous notes related to plan 9. everything is public domain. who caaares

files:

* rot.c - caesar cipher
* go/ - notes on using go and related stuff
* iconinit.c - set wallpaper
* mam - shortcut, open a manpage in `sam`
* shub - shortcut script for downloading from [shithub.us](https://shithub.us)

## Notes
don't forget to set your clocks, kids

### notes on taking notes

As far as I'm aware, there's no built-in markdown command on Plan 9, but a [C implementation of Markdown](https://www.pell.portland.or.us/~orc/Code/discount/) is available, and it compiles on Plan 9 just fine.


```
hget https://www.pell.portland.or.us/~orc/Code/discount/discount-3.0.1.2.tar.bz2 | bunzip2 | tar x
cd discount-3.0.1.2/Plan9
mk
../markdown # type some stuff to test it out and then hit ^D
mk install
```

Since **page(1)** can read HTML, you can read Markdown files right in a terminal after this by typing `markdown file.md|page`.

Note that it doesn't quite read the language the same as something like GitHub, and some formatting may look weird.
For example you need to type `markdown -f fencedcode` instead of just `markdown` for any Markdown document that has code blocks in it, like this one does.

For any *real* writing I highly recommend learning **troff(1)** and using that instead.
