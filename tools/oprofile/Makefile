WGET := 'wget -N -nd'

all:
	echo "do nothing"

install: gprof xdot distro binutils bfd libiberty popt oprofile

GPROF_PROG := gprof2dot.py
GPROF_URL := http://gprof2dot.jrfonseca.googlecode.com/git/$(GPROF_PROG)

gprof:
	wget $(GPROF_URL)
	install $(GPROF_PROG) /sbin

XDOT_PROG := xdot.py
XDOT_URL := http://xdot.jrfonseca.googlecode.com/git/$(XDOT_PROG)

xdot:
	wget $(XDOT_URL)
	install $(XDOT_PROG) /sbin

distro:
	zypper install python-gtk

BINUTILS_PKG := binutils-2.22
BINUTILS_TGZ := $(BFD_PKG).tar.gz
BINUTILS_URL := http://ftp.gnu.org/gnu/binutils/$(BFD_TGZ)

binutils:
	$(WGET) $(BFD_URL)
	tar xvfz $(BFD_TGZ)

define binutils_sub
	cd $(BINUTILS_PKG)/$1 && ./configure 'CFLAGS=-g -O2 -fPIC'
	cd $(BINUTILS_PKG)/$1 && make
	cd $(BINUTILS_PKG)/$1 && make install
endef

bfd:
	$(call binutils_sub,bfd)

libib:
	$(call binutils_sub,libiberty)

POPT_PKG := popt-1.16
POPT_TGZ := $(POPT_PKG).tar.gz
POPT_URL := http://rpm5.org/files/popt/$(POPT_TGZ)

popt:
	$(WGET) $(POPT_URL)
	tar xvfz $(POPT_TGZ)
	cd $(POPT_PKG) && ./configure
	cd $(POPT_PKG) && make
	cd $(POPT_PKG) && make install

OP_VER := 0.9.7
OP_PKG := oprofile-$(OP_VER)
OP_TGZ := $(OP_PKG).tar.gz
OP_URL := http://prdownloads.sourceforge.net/oprofile/$(OP_TGZ)

oprofile:
	ln -sf /lib64/libpopt.so.0 /lib64/libpopt.so
	$(WGET) $(OP_URL)
	tar xvfz $(OP_TGZ)
	cd $(OP_PKG) && ./configure --with-kernel-support
	cd $(OP_PKG) && make
	cd $(OP_PKG) && make install

config:
	opcontrol --deinit
	opcontrol --event=CPU_CLK_UNHALTED:1000000:0x0:0:1 \
          --callgraph=16 \
          --separate=thread,library \
		  --vmlinux=/usr/src/linux/vmlinux
	opcontrol --init

start:
	opcontrol --stop
	opcontrol --reset
	opcontrol --start

test:
	echo "Stop using <ctrl>-C after some time ..."
	while [ true ]; do export >/dev/null; done

stop:
	opcontrol --stop
	opcontrol --dump

OUT := ${PWD}/output
GPROF := $(OUT).gprof
DOT := $(OUT).dot
XDOT := $(OUT).xdot

CLEAN += $(OUT).*

process:
	zypper install XFree86
	zypper install graphviz
	#ls /etc/X11/xorg.conf
	opreport -cgf -o $(GPROF) --merge tgid
	gprof2dot.py -f oprofile -o $(DOT) $(GPROF)
	dot -T xdot $(DOT) > $(XDOT)

show:
	echo "*** Best viewed with Xming on Windows ***"
	xrandr -q
	xdot.py $(XDOT)

clean:
	rm -rf $(CLEAN)

