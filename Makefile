BUILDDIR    = bin/
INCLUDEDIR  = include/
SOURCEDIR   = src/

DIRS        = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(DIRS):$(foreach dir, $(DIRS), $(wildcard $(dir)*/))

IFILES     := $(shell find $(SOURCEDIR) -name '*.cpp')
OFILES     := $(subst $(SOURCEDIR), $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR) -name '*.cpp'))))

CC          = g++
CCFLAGS     = -c -g -w -O3 -std=c++0x -I$(INCLUDEDIR)
LINKFLAGS   = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

TARGET = Generic-RPG

all: $(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(foreach file, $^, $(BUILDDIR)$(file)) $(LINKFLAGS) -o $@ $(DYNLINK)

%.cpp.o: %.cpp
	$(CC) $(CCFLAGS) $< -o $(BUILDDIR)$@

.PHONY: clean
clean:
	rm $(BUILDDIR)*
	rm $(TARGET)