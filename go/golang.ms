\" troff -ms -mpictures golang.ms | page

.TL
.ft HB
Notes on Using the Go Programming Language in Plan 9 from Bell Labs
.AU
kinggizzardandtheinstallationwizard

.SH
.ft HB
Installation

.PP
.ft H
Note, 2025 December 27: Instructions on this stuff is kinda contradictory.
This is how I, personally, got Go working in 9front.
.ft HB
YMMV\fH.

.SH
.ft HB
Bootstrap from another OS

.PP
.ft H
Go is written in Go, and it cannot be built with super old versions of Go. Additionally,
the last version of Go to be written in C was
.ft HB
1.4.3
.ft H
. This means, as I understand it,
if you don't cross-compile from another machine, you'll be compiling like 10 previous
versions of Go in sequence. Don't do that.

You can cross-compile Go from a Linux machine with Go already installed:

.DS
.ft C
wget https://go.dev/dl/go1.25.5.src.gz
tar xf go1.25.5.src.tar.gz
cd go/src
GOOS=plan9 GOARCH=amd64 ./bootstrap.bash
.DE

.PP
.ft H
My PC's fans had a lot of fun with this.

You'll get a file somewhere like \fC../../go-plan9-amd64-bootstrap.tbz\fH after.

Get this file on your plan 9 machine. If you can stick it on a web server you can do:

.DS
.ft C
hget http(s)://wherever.com/go-plan9-amd64-bootstrap.tbz | bunzip2 -c | tar x
mkdir /sys/lib/go
mv go-plan9-amd64-bootstrap /sys/lib/go/amd64
.DE

.bp

.PP
.ft H
Try invoking \fC/sys/lib/go/amd64/bin/go\fH with no arguments and see if it works.
If it does, go ahead and run \fCmkdir -p $home/go/bin\fH and add this stuff
somewhere in your \fC$home/lib/profile\fH:

.DS
.ft C
bind -a /sys/lib/go/amd64/bin /bin
bind -a $home/go/bin /bin
GOPROXY=https://proxy.golang.org
GOROOT=/sys/lib/go/amd64
.DE

.PP
.ft H
Now \fCreboot\fH and you should be good to go. Try building something!

.BP sc.ps 6i 6i c "It works!"
