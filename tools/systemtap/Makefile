SHELL := bash
MYROOT := ${PWD}/myroot
MODULE = heca
KERNEL_REL := $(shell uname -r)
MODULE_FILE = /lib/modules/$(KERNEL_REL)/kernel/drivers/$(MODULE)/$(MODULE).ko

all: stap

ELF_PKG = elfutils-0.153
ELF_TGZ := $(ELF_PKG).tar.bz2
ELF_URL := http://pkgs.fedoraproject.org/repo/pkgs/elfutils/$(ELF_TGZ)/289a146182bc29f0236eaa15d8ebdf98/$(ELF_TGZ)

elfutils:
	rm -rf $(ELF_PKG) $(ELF_TGZ)
	wget $(ELF_URL)
	tar xvfj $(ELF_TGZ)

CLEAN += $(ELF_PKG) $(ELF_TGZ)

STAP_PKG = systemtap-1.8
STAP_TGZ := $(STAP_PKG).tar.gz
STAP_URL := http://sourceware.org/systemtap/ftp/releases/$(STAP_TGZ)

systemtap:
	rm -rf $(STAP_PKG) $(STAP_TGZ) $(MYROOT)
	wget $(STAP_URL)
	tar xvfz $(STAP_TGZ)
	cd $(STAP_PKG) && \
		./configure --with-elfutils=${PWD}/$(ELF_PKG) --prefix=$(MYROOT)
	cd $(STAP_PKG) && patch -p1 < ${PWD}/systemtap.patch
	cd $(STAP_PKG) && make
	cd $(STAP_PKG) && make install
	chmod a+x $(MYROOT)/bin/*

CEAN += $(STAP_PKG) $(STAP_TGZ) $(MYROOT)

ldd:
	install `ldd $(MYROOT)/bin/stap | awk '{print $$3}' | grep x86` \
		$(MYROOT)/lib

build: elfutils systemtap ldd

.PHONY: build

clean:
	rm -rf $(CLEAN)

.PHONY: clean

export PATH := $(MYROOT)/bin:${PATH}
export LD_LIBRARY_PATH := $(MYROOT)/lib/
export SYSTEMTAP_TAPSET := $(MYROOT)/share/systemtap/tapset/
export SYSTEMTAP_RUNTIME := $(MYROOT)/share/systemtap/runtime/

pre:
	[ -f $(MODULE_FILE) ]
	if [ -f /usr/share/systemtap ]; then \
		mv -f /usr/share/systemtap /usr/share/systemtap.orig; \
	fi

.PHONY: pre

TARGET_DIR := `mktemp -d /tmp/systemtap.XXXX`

STAP := \
	cd $(TARGET_DIR); \
	$(MYROOT)/bin/stap -vvv -g -v -k --vp 0001

help: pre
	$(STAP) --help 2>&1

heca: pre
	$(STAP) -d $(MODULE_FILE) ${PWD}/probe.stp

.PHONY: stap

kernel: pre
	$(STAP) -e 'probe kernel.function("*") {}' -p4 2>&1

.PHONY: kernel

modules: pre
	$(STAP) -e 'probe module("*").function("ioctl").inline {printf("hi")}' -p4 2>&1

.PHONY: modules

funcion: pre
	$(STAP) -e 'probe module("$(MODULE)").function("*") {}' -p4 2>&1

.PHONY: function

statement: pre
	$(STAP) -e 'probe module("$(MODULE)").statement("*@drivers/dsm/dsm_ctl.c:*") {}' -p4 2>&1

.PHONY: stataement

printk: pre
	$(STAP) -e 'probe kernel.function("printk") { print_stack(backtrace()) }' -p4 2>&1

.PHONY: printk

