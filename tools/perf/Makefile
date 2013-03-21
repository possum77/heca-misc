DATA = perf.data
SVG = output.svg

install:
	zypper install perf

record:
	rm -rf $(DATA)
	echo "type <ctrl>-D to stop data collection"
	perf record -a -g

CLEAN += $(DATA)

report:
	perf report

top:
	perf top -a

clean:
	rm -rf $(CLEAN)

