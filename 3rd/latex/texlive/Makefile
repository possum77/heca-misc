include ../../Makefile.conf

TLV_VER := 2012
TLV_DIR := texlive$(TLV_VER)
TLV_ISO := $(TLV_DIR).iso

all: download extract install

.PHONY: all

download: 
	[ -f $(TLV_VER) ] || \
		wget http://ftp.gwdg.de/pub/ctan/systems/texlive/Images/$(TLV_ISO)

.PHONY: download

extract: clean
	rm -rf $(TLV_DIR)
	mkdir -p $(TLV_DIR)
	7z x -o$(TLV_DIR) $(TLV_ISO)

.PHONY: extract

clean:
	rm -rf $(TLV_DIR)

.PHONY: clean

install: uninstall
	cd $(TLV_DIR) && ./install-tl -gui text
	cp .bash_texlive ~/.
	echo "source ~/.bash_texlive" >> ~/.bash_profile
	cat README

.PHONY: install

uninstall:
	rm -rf /usr/local/texlive/$(TLV_VER)

.PHONY: uninstall

