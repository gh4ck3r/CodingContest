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

ifeq ($(TARGET), algospot)
URL_PREFIX := https://algospot.com/judge/problem/read
PARSE_SAMPLE = xmllint --html --nowarning --xpath "//section[@class='problem_sample_$(1)']/pre/text()" - 2>/dev/null > $(1)
%: SHELL := /bin/bash
#curl -s https://algospot.com/judge/problem/read/BRUTEFORCE | xmllint --html --nowarning --xpath "//section[@class='problem_sample_input']/pre/text()" - 2>/dev/null
%:
	@TARGET=$@                                     && \
	content=$$(curl -s $(URL_PREFIX)/$${TARGET^^}) && \
	echo "Making $${TARGET,,}"                     && \
	mkdir $${TARGET,,} && cd $${TARGET,,}          && \
	$(call PARSE_SAMPLE,input) <<< "$$content"     && \
	$(call PARSE_SAMPLE,output) <<< "$$content"    && \
	touch $${TARGET,,}.cc                          && \
	echo $${TARGET,,} > .gitignore				   && \
	ln -s ../makefile
endif

