CFLAGS := -g -O0
LIBS := -lpthread -lrt
PROG := appmembench
OUT := /tmp/$(PROG).out

all: build
	./$(PROG).bin 2>&1 | tee $(OUT)

gdb: build
	gdb ./$(PROG).bin

ntp:
	apt-get install ntp
	service ntp stop
	while [ true ]; do ntpdate -t 0.1 datime.wdf.sap.corp; done

build:
	gcc $(CFLAGS) -o $(PROG).bin main.c $(LIBS)

clean:
	rm -rf *.bin

log:
	tail $(OUT)

