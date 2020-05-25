PROGRAM_NAME := print
SOURCE_DIRS := src/
OBJECT_DIRS := bin/

MKDIR := mkdir -p
RM := rm -rf

INCLUDE :=-I./$(SOURCE_DIRS)

DWARF_DEBUG_FLAGS := -gdwarf-2
GDB_DEBUG_FLAGS := -ggdb

ASFLAGS = --64 -c $(INCLUDE)
LDFLAGS = -static

SEARCH_WILDCARDS := $(addsuffix *.s, $(SOURCE_DIRS))
SOURCES := $(wildcard $(SEARCH_WILDCARDS))
OBJECTS := $(join $(OBJECT_DIRS), $(notdir $(patsubst %.s,%.o, $(SOURCES))))

.PHONY : all debug dgdb $(OBJECT_DIRS) clean

all: $(PROGRAM_NAME)

debug: ASFLAGS += $(DWARF_DEBUG_FLAGS)
debug: $(PROGRAM_NAME)

dgdb: ASFLAGS += $(GDB_DEBUG_FLAGS)
dgdb: $(PROGRAM_NAME)

clean:
	$(RM) $(PROGRAM_NAME) $(OBJECT_DIRS)

$(PROGRAM_NAME): $(OBJECTS) 
	$(LD) $(LDFLAGS) -o $@ $^  

$(OBJECTS): $(OBJECT_DIRS) $(SOURCES)
	$(AS) $(ASFLAGS) -o $@ $(SOURCES)

$(OBJECT_DIRS):
	$(MKDIR) $(OBJECT_DIRS)
