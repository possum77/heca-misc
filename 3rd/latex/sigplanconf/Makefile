include ../../Makefile.conf

all:
	wget http://www.sigplan.org/sigplanconf.cls
	cp sigplanconf.cls $(TEXMF)/
	wget http://www.sigplan.org/sigplanconf-template.tex
	pdflatex sigplanconf-template.tex

clean:
	rm -rf sigplan*
	rm -rf $(TEXMF)/sigplanconf.cls
