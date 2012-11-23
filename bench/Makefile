all:
	@echo "You must build/run individual tests"

#
# pgbench - PostGres database benchmark
# - runs several tests scaling size, clients
# - gnuplot output
# - not useful as a memory test
#

PGBENCH_URL = http://www.westnet.com/~gsmith/content/postgresql/
PGBENCH_DIR = pgbench-tools-0.4
PGBENCH_PKG = $(PGBENCH_DIR).tar.gz

pgbench-install:
	apt-get install postgresql
	apt-get install postgresql-doc
	apt-get install gnuplot
	wget $(PGBENCH_URL)$(PGBENCH_PKG)
	tar xvfz $(PGBENCH_PKG)
	@echo "Follow instructions for user/password setup" 

pgbench:
	sudo -u postgres psql -f $(PGBENCH_DIR)/init/resultdb.sql
	cd $(PGBENCH_DIR) && ./runset
	cd $(PGBENCH_DIR) && mkdir -p results
	cd $(PGBENCH_DIR) && ./webreport

.PHONY: pgbench
CLEAN += pgbench*

#
# LMBench - a simple portable ANSI/C microbenchmarks for UNIX/POSIX
# - zero's and copies large amount of memory
# - check check cpu-memory read and write speeds
# - does not represent a SAP like applicaiton
#

LMBENCH_URL = http://www.bitmover.com/lmbench/
LMBENCH_PKG = lmbench3.tar.gz

lmbench-install:
	wget $(LMBENCH_URL)$(LMBENCH_PKG)
	tar xvfz $(LMBENCH_PKG)
	cd lmbench3 && mkdir -p SCCS
	cd lmbench3 && touch SCCS/s.ChangeSet
	cd lmbench3/src && make

.PHONY: lmbench-install

lmbench:
	cd lmbench3/ && bin/*/bw_mem -P 16 -W 16 -N 16 100M rdwr

.PHONY: lmbench
CLEAN += lmbench*

#
# SAT (Stress Application Test)
# - high performance memory write
# - seems very uniform
# - may be effectecd by XBZRLE but not by PRIO
#

SAT_URL = http://stressapptest.googlecode.com/files/
SAT_DIR = stressapptest-1.0.4_autoconf
SAT_PKG = $(SAT_DIR).tar.gz

sat-install:
	apt-get install make g++ gcc
	apt-get install libaio-dev htop
	wget $(SAT_URL)$(SAT_PKG)
	tar xvfz $(SAT_PKG)
	cd $(SAT_DIR) && ./configure
	cd $(SAT_DIR) && make

sat:
	cd $(SAT_DIR)/src && ./stressapptest -s 200 -M 256 -m 8 -C 8 -W
	#cd $(SAT_DIR)/src && ./stressapptest -f /tmp/file1 -f /tmpfile2

.PHONY: sat
CLEAN += stressapptest*

#
# Graph500
#
G500_URL = http://www.graph500.org/
G500_DIR = graph500-2.1.4
G500_PKG = $(G500_DIR).tar.bz2

g500-install:
	wget $(G500_URL)$(G500_PKG)
	tar xvfj $(G500_PKG)
	cd $(G500_DIR) && cp make-incs/make.inc-gcc make.inc
	cd $(G500_DIR) && echo "CPPFLAGS =" >> make.inc
	cd $(G500_DIR) && make
	cd $(G500_DIR)/generator && make -f Makefile.omp

G500_SCALE = 20
G500_OPTS = -V -s $(G500_SCALE)

g500:
	#@echo "-- Sequential list-based implementation --"
	#cd $(G500_DIR) && seq-list/seq-list $(G500_OPTS)
	#@echo "-- Sequential compressed-sparse-row implementation --"
	#cd $(G500_DIR) && seq-csr/seq-csr $(G500_OPTS)
	#@echo "-- OpenMP compressed-sparse-row implementation --"
	#cd $(G500_DIR) && omp-csr/omp-csr $(G500_OPTS)
	@echo "-- OpenMP compressed-sparse-row generator --"
	cd $(G500_DIR)/generator && ./generator_test_omp $(G500_SCALE)

.PHONY: g500
CLEAN += graph500*

#
# phoronix - a general test suite
#

PHORONIX_URL = http://www.phoronix-test-suite.com/download.php?file=
PHORONIX_PKG = phoronix-test-suite-3.6.1

phoronix:
	wget $(PHORONIX_URL)$(PHORONIX_PKG)

.PHONY: phoronix
CLEAN += phoronix*

#
# clean
#
clean:
	rm -rf $(CLEAN)
