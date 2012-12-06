include ../../Makefile.conf

TARGET_DIR := /usr/local/texlive/proposal

all: macros prop

.PHONY: all

macros: macros_download macros_install

.PHONY: macros

prop: prop_download prop_install

.PHONY: prop

clean: macros_clean prop_clean

.PHONY: clean

MACROS_FILES := \
	forCTAN/ed/ed.sty \
	forCTAN/proposal/etc/workaddress.sty \
	forCTAN/proposal/etc/sref.sty \
	forCTAN/proposal/etc/metakeys.sty \
	fromCTAN/etoolbox/etoolbox.sty \
	fromCTAN/hyperref/kvoptions.sty \
	fromCTAN/logreq/logreq.sty \
	fromCTAN/logreq/logreq.def \
	fromCTAN/svninfo.sty \
	fromCTAN/xkeyval.sty \
	forCTAN/proposal/eu/eupdata.sty \

EXTRA_FILES := \
	forCTAN/proposal/eu/euproposal.cls \
	forCTAN/proposal/base/proposal.cls \
	forCTAN/proposal/base/pdata.sty \

macros_download: macros_clean
	svn checkout https://svn.kwarc.info/repos/kwarc/doc/macros

.PHONY: macros_download

macros_clean:
	rm -rf macros

.PHONY: macros_clean

macros_install: uninstall
	mkdir -p $(TEXMF)
	cd macros && install $(MACROS_FILES) $(TEXMF)
	mkdir -p $(TARGET_DIR)
	cp -ar macros/forCTAN/proposal $(TARGET_DIR)

.PHONY: macros_install

PROP_DIR := proposal
PROP_ZIP := $(PROP_DIR).zip
PROP_URL := http://www.tex.ac.uk/CTAN/macros/latex/contrib/$(PROP_ZIP)

prop_download: prop_clean
	$(WGET) $(PROP_URL)
	unzip $(PROP_ZIP)

.PHONY: prop_download

prop_clean:
	rm -rf $(PROP_DIR) $(PROP_ZIP)

.PHONY: prop_clean

PROP_FILES := \
	eu/euproposal.cls \
	base/proposal.cls \
	base/pdata.sty \

prop_install:
	mkdir -p $(TEXMF)
	mkdir -p $(TARGET_DIR)
	for i in $(PROP_FILES); do \
		install $(PROP_DIR)/$$i $(TEXMF); \
		DIR=`dirname $$i`; \
		mkdir -p $(TARGET_DIR)/$$DIR; \
		cp -ar $(PROP_DIR)/$$i $(TARGET_DIR)/$$i; \
	done

.PHONY: prop_install

uninstall:
	rm -rf $(TARGET_DIR)

.PHONY: uninstall

