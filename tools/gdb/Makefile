GDB_PKG := gdb-7.6.50.20130318
GDB_DIR := $(GDB_PKG)
GDB_ZIP := $(GDB_PKG).tar.bz2
GDB_URL := http://mirrors.kernel.org/sources.redhat.com/gdb/snapshots/current/$(GDB_ZIP)

EXP_PKG := expat-2.0.1
EXP_DIR := $(EXP_PKG)
EXP_ZIP := $(EXP_DIR).tar.gz
EXP_URL := http://downloads.sourceforge.net/expat/$(EXP_ZIP)

RM = rm -rf

all: download build

.PHONY: all

download: clean
	wget $(EXP_URL)
	tar xvfz $(EXP_ZIP)
	wget $(GDB_URL)
	tar xvfj $(GDB_ZIP)

.PHONY: download

build:
	cd $(EXP_DIR) && ./configure && make
	cd $(GDB_DIR) && make distclean || true
	cd $(GDB_DIR) && ./configure --enable-werror
	cd $(GDB_DIR) && make -j `nproc`
	cd $(GDB_DIR) && chmod -R a+rw .

.PHONY: build

install:
	cd $(EXP_DIR) && make install
	cd $(GDB_DIR) && make -j `nproc` install

.PHONY: install

clean:
	$(RM) -rf gdb-* expat-*

.PHONY: clean

