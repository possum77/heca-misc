VG_PKG := valgrind-3.8.1
VG_ZIP := $(VG_PKG).tar.bz2
VG_URL := http://www.valgrind.org/downloads/$(VG_ZIP)
RM = rm -rf

all: download build

.PHONY: all

download: clean
	wget $(VG_URL)
	tar xvfj $(VG_ZIP)

.PHONY: download

build:
	cd $(VG_PKG) && make distclean || true
	cd $(VG_PKG) && ./configure
	cd $(VG_PKG) && make -j `nproc`
	cd $(VG_PKG) && chmod -R a+r .
	cd $(VG_PKG) && chmod -R a+w .

.PHONY: build

install:
	cd $(VG_PKG) && make install

.PHONY: install

clean:
	$(RM) $(VG_PKG) $(VG_ZIP)

.PHONY: clean

