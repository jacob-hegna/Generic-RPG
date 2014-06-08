BUILDDIR    = bin/
INCLUDEDIR  = include/
SOURCEDIR   = src/

DEFINES     = STATIC_MEDIA

SDIRS       = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(SDIRS):$(foreach dir, $(SDIRS), $(wildcard $(dir)*/))

IFILES     := $(shell find $(SOURCEDIR) -name '*.cpp')
OFILES     := $(subst $(SOURCEDIR),  $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR)  -name '*.cpp'))))


CC          = g++
CCFLAGS     = -c -w -O3 -std=c++0x -I$(INCLUDEDIR)
LINKFLAGS   = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpng

OBJC        = objcopy
OBJCFLAGS   = --input-target binary --output-target elf32-i386 --binary-architecture i386

TARGET = Generic-RPG

all: $(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(foreach file, $^, $(BUILDDIR)$(file)) $(LINKFLAGS) -o $@ $(DYNLINK)

%.cpp.o: %.cpp
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $(BUILDDIR)$@

.PHONY: clean
clean:
	rm $(BUILDDIR)*
	rm $(TARGET)