DEBUGFS = /sys/kernel/debug
TRACING = $(DEBUGFS)/tracing
CONFIG = /usr/src/linux/.config
LOG = ${PWD}/trace.log

mount:
	mount -t debugfs nodev $(DEBUGFS) || true

umount:
	umount $(DEBUGFS)

trace:
	grep CONFIG_FUNCTION_TRACER=y $(CONFIG)
	cd $(TRACING) && echo function > current_tracer
	cd $(TRACING) && echo 1 > tracing_enabled
	cd $(TRACING) && echo 1 > tracing_on
	cd $(TRACING) && echo 0 > trace

untrace:
	cd $(TRACING) && cat trace > $(LOG)
	cd $(TRACING) && echo 0 > tracing_on
	cd $(TRACING) && echo 0 > tracing_enabled

show: 
	cat $(TRACING)/trace

log:
	tail -f $(TRACING)/trace | tee $(LOG)

CLEAN += $(LOG)

prof:
	grep CONFIG_FUNCTION_PROFILER=y $(CONFIG)
	echo 1 > $(TRACING)/function_profile_enabled

unprof:
	echo 0 > $(TRACING)/function_profile_enabled
	echo "prfiling files found here:"
	ls -l $(TRACING)/trace_stat/

clean:
	rm -rf $(CLEAN)

