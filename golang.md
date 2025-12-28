# notes on using Go in Plan 9

## Installation

`27 dec 2025` -- Instructions on this stuff is kinda contradictory so here's how I,
personally, got Go working in 9front. **YMMV**

### Bootstrap from another OS

Go is written in Go, and it cannot be built with super old versions of Go. Additionally,
the last version of Go to be written in C was **1.4.3**. This means, as I understand it,
if you don't cross-compile from another machine, you'll be compiling like 10 previous
versions of Go in sequence. Don't do that.

You can cross-compile Go from a Linux machine with Go already installed:

```
wget https://go.dev/dl/go1.25.5.src.gz
tar xf go1.25.5.src.tar.gz
cd go/src
GOOS=plan9 GOARCH=amd64 ./bootstrap.bash
```

My PC's fans had a lot of fun with this.

You'll get a file somewhere like `../../go-plan9-amd64-bootstrap.tbz` after.

Get this file on your plan 9 machine. If you can stick it on a web server you can do:

```
hget http(s)://www.example.com/wherever/go-plan9-amd64-bootstrap.tbz | bunzip2 -c | tar x
mkdir /sys/lib/go
mv go-plan9-amd64-bootstrap /sys/lib/go/amd64
```

Try invoking `/sys/lib/go/amd64/bin/go` with no arguments and see if it works.
If it does, go ahead and run `mkdir -p $home/go/bin` and add this stuff
somewhere in your `$home/lib/profile`:

```
bind -a /sys/lib/go/amd64/bin /bin
bind -a $home/go/bin /bin
GOPROXY=https://proxy.golang.org
GOROOT=/sys/lib/go/amd64
```

Now `reboot` and you should be good to go. Try building something!

![](https://files.catbox.moe/imolnf.png)