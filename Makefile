COMPILER=gcc
EXTRAFLAGS:=

PROJECTFLAGS:=-ljansson
FLAGS:=$(PROJECTFLAGS) -I. -ggdb -std=c11 $(EXTRAFLAGS)

COMPILEFLAGS=$(FLAGS) -fPIC
LINKFLAGS=$(FLAGS)

HEADERS=$(wildcard src/*.h) $(wildcard src/*/*.h) $(wildcard lib/*.h)
PROGRAMOBJECTS=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c)) $(patsubst src/%.c,obj/%.o,$(wildcard src/*/*.c))

PROGRAMFILE=scoutify-merger.$(shell arch)

all: tags $(PROGRAMFILE)

obj/%.o: src/%.c $(HEADERS)
	$(COMPILER) -c -o $@ $< $(COMPILEFLAGS)
$(PROGRAMFILE): $(PROGRAMOBJECTS)
	$(COMPILER) -o $(PROGRAMFILE) $(PROGRAMOBJECTS) $(LINKFLAGS)

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f src/TAGS

tags: src/TAGS

src/TAGS: $(wildcard src/*.c) $(HEADERS)
	etags $^ -o src/TAGS
