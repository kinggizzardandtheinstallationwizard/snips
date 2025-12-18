void
iconinit(void)
{
	/*
	 * stolen code from https://wiki.xxiivv.com/site/rio.html
	 * download an appropriate size picture i.e. whatever.jpg to /usr/glenda/lib/
	 * and do something like: jpg -9t whatev.jpg > wallpaper
	 * this should fall back to the grey background if there's no /usr/glenda/lib/wallpaper
	 * this replaces the iconinit() function in:
	 * 					/sys/src/cmd/rio/data.c
	 */
	int fd;
	Image *bimg = nil;
	fd = open("/usr/glenda/lib/wallpaper", OREAD);
	if(fd >= 0) {
		bimg = readimage(display, fd, 0);
		close(fd);
	}
	if(bimg) {
		background = allocimage(display, Rect(0, 0, Dx(bimg->r), Dy(bimg->r)), RGB24, 1, 0x000000FF);
		draw(background, background->r, bimg, 0, bimg->r.min);
		goto skipbgfallback;
	} else {
		fprint(2, "iconinit: %r\n");
	}

	background = allocimage(display, Rect(0,0,1,1), screen->chan, 1, 0x777777FF);

skipbgfallback:
	/* greys are multiples of 0x11111100+0xFF, 14* being palest */
	cols[BACK] = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0xFFFFFFFF^reverse);
	cols[BORD] = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0x999999FF^reverse);
	cols[TEXT] = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0x000000FF^reverse);
	cols[HTEXT] = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0x000000FF);
	if(!reverse) {
		cols[HIGH] = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0xCCCCCCFF);
		titlecol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DGreygreen);
		lighttitlecol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DPalegreygreen);
	} else {
		cols[HIGH] = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DPurpleblue);
		titlecol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DPurpleblue);
		lighttitlecol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0x222222FF);
	}
	dholdcol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DMedblue);
	lightholdcol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DGreyblue);
	paleholdcol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DPalegreyblue);
	paletextcol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, 0x666666FF^reverse);
	sizecol = allocimage(display, Rect(0,0,1,1), CMAP8, 1, DRed);

	if(reverse == 0)
		holdcol = dholdcol;
	else
		holdcol = paleholdcol;
}
