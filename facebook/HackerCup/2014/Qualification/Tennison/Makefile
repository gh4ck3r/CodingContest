CURDIR:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
INCDIR:=$(abspath $(CURDIR)/../../../../../include)

SRC := src.cc
SRC := $(addprefix $(CURDIR)/,$(SRC))

CXX := g++

CFLAGS := -W -Wall
CFLAGS += -MMD
CFLAGS += -I$(INCDIR)
CFLAGS += -g3

CXXFLAGS := -std=gnu++11

TARGET := play
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@

clean:
	@rm -f $(TARGET)
	@rm -f *.d

-include $(SRCS:%.cc=%.d)
