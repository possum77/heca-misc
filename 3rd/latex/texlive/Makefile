include ../Makefile.conf

TLV_VER := 2012
TLV_DIR := texlive$(TLV_VER)
TLV_ISO := $(TLV_DIR).iso

all: download mount-$(UNAME) install umount-$(UNAME)

download: 
	[ -f $(TLV_VER) ]
	wget http://ftp.gwdg.de/pub/ctan/systems/texlive/Images/$(TLV_ISO)

mount-linux:
	rm -rf $(TLV_DIR)
	mkdir -p $(TLV_DIR)
	mount -t iso9660 -o loop $(TLV_ISO) $(TLV_DIR)

mount-cygwin:
	echo "Extract $(TLV_ISO) into $(PATH)/$(TLV_DIR)"
	WinRAR unrar x $(TLV_ISO) $(TLV_DIR)

install:
	cd $(TLV_DIR) && ./install-tl -gui text
	cp .bash_texlive ~/.
	echo "source ~/.bash_texlive" >> ~/.bash_profile
	cat README

umount-linux:
	umount $(TLV_DIR)

umount-cygwin:
	echo "Safe to remove $(PATH)/$(TLV_DIR)"

uninstall:
	rm -rf /usr/local/texlive/$(TLV_VER)

