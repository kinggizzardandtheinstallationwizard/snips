\" % troff -ms -mpictures golang.ms | page

.TL
.ft HB
Notes on Using the Go Programming Language in Plan 9 from Bell Labs
.AU
kinggizzardandtheinstallationwizard

.SH
.ft HB
Installation

.PP
.ft HB
ACHTUNG! (2025 December 27)\fH Instructions on this stuff is kinda contradictory.
This is how I, personally, got Go working in 9front. Much like others' notes on this,
the instructions could be outdated or just plain
.ft HI
wrong\fH. Use your brain!
.ft HB
Your mileage may vary\fH.

.PP
.ft HB
ACHTUNG! (2026 January 19)\fH ARM64 users: there is not yet an official port of Go to \fCplan9/arm64\fH.
There is, however, a working (albeit slightly outdated) community branch available:

.DS
.ft C
https://github.com/psilva261/go-arm64.plan9
.DE

.SH
.ft HB
Prerequisite

.PP
.ft H
Before we start, I recommend running this totally unrelated command if you haven't already.
You'll thank me later.

.DS
.ft C
hget https://curl.haxx.se/ca/cacert.pem > /sys/lib/tls/ca.pem
.DE

.PP
.ft H
I am mentioning this first so you may easily ignore it if you've already done this.
Since Go is designed specifically with modern internet connections in mind, you'll obviously
want a working CA certificate, which Plan 9(front) does not ship with.

.SH
.ft HB
Bootstrap from another OS

.PP
.ft H
Go is written in Go, and it cannot be built with super old versions of Go. Considering this,
and that the last version of Go to be written in C was
.ft HB
1.4.3\fH, starting without an already working, current version of Go is infeasible.

You can cross-compile Go from a Linux machine with Go already installed:

.DS
.ft C
wget https://go.dev/dl/go1.25.5.src.gz
tar xf go1.25.5.src.tar.gz
cd go/src
GOOS=plan9 GOARCH=amd64 ./bootstrap.bash
.DE

Change the value of \fCGOARCH\fH to that of \fC$objtype\H on your target Plan 9 system.

.PP
.ft H
My PC's fans had a lot of fun with this.

You'll get a file somewhere like \fC../../go-plan9-amd64-bootstrap.tbz\fH after.

Get this file on your plan 9 machine. If you can stick it on a web server you can do:

.DS
.ft C
hget http(s)://wherever.com/go-plan9-$objtype-bootstrap.tbz | bunzip2 -c | tar x
mkdir /sys/lib/go
mv go-plan9-$objtype-bootstrap /sys/lib/go/$objtype
.DE

.PP
.ft H
If you are using your Plan 9 machine through
.ft HB
drawterm\fH,
you can copy the file without such hassle.

.DS
.ft C
mkdir /sys/lib/go && cd /sys/lib/go
cp /mnt/term/path/to/local/go-plan9-$objtype-bootstrap.tbz .
bunzip -c go-plan9-$objtype-bootstrap.tbz | tar x
mv go-plan9-$objtype-bootstrap $objtype
.DE

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

.BP sc.ps 4i 4i c "It works!"
