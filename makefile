#-------------------------------------------------------------------------------
# General makefile for C/C++ projects using SFML on linux
#-------------------------------------------------------------------------------

TARGET		:=	$(shell basename $(CURDIR))
SOURCES		:=	source/main source/state source/entity source/util
INCLUDES	:=	source
BUILD		:=	build

#-------------------------------------------------------------------------------
SYSTEM		:=	$(shell uname -s)
CFILES		:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
OFILES		:=	$(addprefix $(BUILD)/,$(CFILES:%.c=%.o)\
			$(CPPFILES:%.cpp=%.o))
DEPENDFILES	:=	$(OFILES:%.o=%.d)
CC		:=	gcc
CXX		:=	g++
INCLUDEFILES	:=	$(foreach dir,$(INCLUDES),$(wildcard $(dir)/*.h))
INCLUDE		:=	$(addprefix -I,$(INCLUDES))
DEPENDFLAGS	:=	-MMD -MP
CFLAGS		:=	$(INCLUDE) -g -Wall -O2
CXXFLAGS	:=	$(CFLAGS) -std=c++11
LIBS		:=	sfml-network sfml-audio sfml-graphics sfml-window sfml-system GL GLU
LDFLAGS		:=	$(addprefix -l,$(LIBS))

all: setup $(TARGET)

$(TARGET): $(OFILES)
	$(CXX) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

.PHONY: setup clean

setup:
	$(foreach source,$(SOURCES),$(shell echo \
	$(shell [ -d $(BUILD)/$(source) ] || ( mkdir -p $(BUILD)/$(source)) )))

clean:
	-rm -fr $(TARGET) $(BUILD)

-include $(DEPENDFILES)

#-------------------------------------------------------------------------------
$(BUILD)/%.o: %.c
	@echo $(notdir $<)
	$(CC) $(DEPENDFLAGS) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
	@echo

$(BUILD)/%.o: %.cpp
	@echo $(notdir $<)
	$(CXX) $(DEPENDFLAGS) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
	@echo
