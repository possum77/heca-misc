include Makefile.conf

PKGS := \
	subversion \

env-ubuntu:
	apt-get install $(PKGS)

.PHONY: ubuntu-env

env-cygwin:
	echo do nothing

.PHONY: cygwin-env

SUBDIRS := \
	texlive \
	proposal \
	gnuplot \
	sigplanconf \
	springer \

all: env-$(UNAME)
	for s in $(SUBDIRS); do
		make -C $$s;
	done

.PHONY: all

clean:
	for s in $(SUBDIRS); do
		make -C $$s;
	done

.PHONY: clean

