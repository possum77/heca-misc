include ../Makefile.conf

PKGS := \
	subversion \
	p7zip-full \

all: env-$(UNAME)
	for s in $(SUBDIRS); do \
		make -C $$s; \
	done

.PHONY: all

env-ubuntu:
	apt-get install $(PKGS)

.PHONY: ubuntu-env

env-Cygwin:
	echo do nothing

.PHONY: Cygwin-env

SUBDIRS := \
	texlive \
	proposal \
	gnuplot \
	sigplanconf \

clean:
	for s in $(SUBDIRS); do
		make -C $$s;
	done

.PHONY: clean

