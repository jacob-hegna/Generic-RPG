BUILDDIR    = bin/
INCLUDEDIR  = include/
SOURCEDIR   = src/

DEFINES     = 

SDIRS       = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(SDIRS):$(foreach dir, $(SDIRS), $(wildcard $(dir)*/))

IFILES     := $(shell find $(SOURCEDIR) -name '*.cpp')
OFILES     := $(subst $(SOURCEDIR),  $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR)  -name '*.cpp'))))


CC          = g++
CCFLAGS     = -c -w -O3 -std=c++0x -I$(INCLUDEDIR)
LINKFLAGS   = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpng

TARGET = Generic-RPG

all: $(TARGET)

$(TARGET): $(foreach file, $(OFILES), $(BUILDDIR)$(file))
	$(CC) $^ $(LINKFLAGS) -o $@ $(DYNLINK)

$(BUILDDIR)%.cpp.o: %.cpp
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(BUILDDIR)*
	rm $(TARGET)