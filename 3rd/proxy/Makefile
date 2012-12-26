include ../Makefile.conf

ifneq ($(UNAME),Cygwin)
MYHOME=/home/$(USER)
else
MYHOME=${HOME}
endif

BINDIR=${HOME}/bin

help:
	echo "type make [all|clean|proxy|ooo]"

.PHONY: help

all:
	rm -rf connect.c
	mkdir -p $(BINDIR)
	wget http://savannah.gnu.org/maintenance/connect.c
	gcc -o connect connect.c
	install connect $(BINDIR)

.PHONY: all

CLEAN += connect connect.c

proxy: proxy_ssh proxy_bash proxy_svn
	@echo "Use GIT URL: ssh://git@ssh.github.com/hecatonchire/orbit"

ooo: ooo_ssh ooo_bash ooo_svn
	@echo "Use GIT URL: ssh://git@github.com/hecatonchire/orbit"

proxy_ssh:
	mkdir -p $(MYHOME)/.ssh
	cp .ssh/config $(MYHOME)/.ssh/config

.PHONY: proxy_ssh

ooo_ssh:
	rm -rf $(MYHOME)/.ssh/config

.PHONY: ooo_ssh

proxy_svn:
	mkdir -p $(MYHOME)/.subversion
	cp .subversion/servers $(MYHOME)/.subversion/servers

.PHONY: proxy_svn

ooo_svn:
	rm -rf $(MYHOME)/.subversion/servers

.PHONY: ooo_svn

proxy_bash: 
	cp .bash_proxy $(MYHOME)/
	echo "source ~/.bash_proxy" >> $(MYHOME)/.bash_profile
	@echo "** Please type 'source $(MYHOME)/.bash_proxy' **"

.PHONY: proxy_bash

ooo_bash:
	rm -rf $(MYHOME)/.bash_proxy
	touch $(MYHOME)/.bash_proxy

.PHONY: ooo_bash

clean:
	rm -rf $(CLEAN)

.PHONY: clean

