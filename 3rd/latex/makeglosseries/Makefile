include ../../Makefile.conf

MKGLS_FILE := makeglossaries
MKGLS_URL := http://ftp.gwdg.de/pub/ctan/macros/latex/contrib/glossaries/$(MKGLS_FILE)

all:
	wget $(MKGLS_URL)
	install $(MKGLS_FILE) $(BIN_DIR) 

.PHONY: all

clean:
	rm -rf $(BIN_DIR)/$(MKGLS_FILE)

.PHONY: clean
