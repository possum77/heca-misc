include ../Makefile.conf

all: llncs2e typeinst

llncs2e:
	mkdir -p $(TEXMF)
	rm -rf llncs2e*
	wget ftp://ftp.springer.de/pub/tex/latex/llncs/latex2e/llncs2e.zip
	unzip -d llncs2e llncs2e.zip
	cd llncs2e && install *.cls *.sty $(TEXMF)

.PHONY: llncs2e

CLEAN += llncs2e*

typeinst:
	wget ftp://ftp.springer.de/pub/tex/latex/llncs/latex2e/instruct/authors/typeinst.zip
	unzip -d typeinst typeinst.zip
	cd typeinst && pdflatex typeinst.tex

.PHONY: typeinst

CLEAN += typeinst*

clean:
	rm -rf $(CLEAN)
