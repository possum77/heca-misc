SCRIPT_URL = http://gnuplot.sourceforge.net/demo
DAT_URL = http://amrl.uakron.edu/win_prog/gnuplot/demo

define doplot
	mkdir -p tmp
	##wget -N -nd $(SCRIPT_URL)/$1
	rm -rf $2
	wget -N -nd $(DAT_URL)/$2
	echo 'set title "$3"' > $1.tmp
	echo 'set output "$3"' >> tmp/$1
	echo 'set terminal png nocrop enhanced font arial 8 size 420,320 ' >> tmp/$1
	cat $1 >> tmp/$1
	gnuplot tmp/$1
endef

all:
	$(call doplot,histo1.gnu,immigration.dat,histo1.png)
	$(call doplot,histo2.gnu,immigration.dat,histo2.png)
	$(call doplot,histo6.gnu,immigration.dat,histo6.png)

CLEAN += immigration.dat histo1.png histo2.png histo6.png

GP_DIR = gnuplot-4.6.0
GP_TAR = $(GP_DIR).tar.gz

CLEAN += $(GP_DIR)*

build:
	wget http://fossies.org/unix/misc/$(GP_TAR)
	tar xvfz $(GP_TAR)
	cd $(GP_DIR) && ./configure
	cd $(GP_DIR) && make
	cd $(GP_DIR) && make install

clean:
	rm -rf $(CLEAN) tmp

