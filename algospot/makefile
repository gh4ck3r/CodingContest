TARGET := $(notdir $(PWD))
INPUT := input
OUTPUT := output

DEBUG 	:= no
PROFILE := no

CFLAGS   := -W -Wall
ifneq ($(DEBUG), no)
CFLAGS += -g
endif
ifneq ($(PROFILE), no)
CFLAGS += -pg
endif
CCFLAGS  := -std=c11
CXXFLAGS := -std=c++11

PROFILE_FILE := gmon.out

$(TARGET):

%: %.cc
	@$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@

.PHONY: clean run verify profile

clean:
	@rm -f $(TARGET)
	@rm -f $(PROFILE_FILE)

run: $(TARGET) $(INPUT)
	@$(realpath $<) < $(INPUT)

profile: $(TARGET) $(PROFILE_FILE)
	@gprof -l -x $^

verify: $(TARGET) $(INPUT) $(OUTPUT)
	@output=$$($(realpath $<) < $(INPUT) | diff -y -W30 - $(OUTPUT)) \
		&& echo "Pass!!" \
		|| (echo "Fail!"; echo "$$output")

define REMOVE_UNPROFILED_TARGET
[ -x $(TARGET) ] && \
		!(readelf -s $(TARGET) | grep '\<mcount\>' 2>&1 >/dev/null) && \
		rm -f $(TARGET)
endef
ifneq ($(PROFILE), no)
$(shell $(REMOVE_UNPROFILED_TARGET))

$(PROFILE_FILE): $(TARGET) run
else
$(PROFILE_FILE):
	@$(REMOVE_UNPROFILED_TARGET);
	@$(MAKE) PROFILE= $@
endif


