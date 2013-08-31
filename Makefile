COMPILER=gcc

PROJECTFLAGS:=-ljansson
FLAGS:=$(PROJECTFLAGS) -I. -ggdb -std=c11

COMPILEFLAGS=$(FLAGS) -fPIC
LINKFLAGS=$(FLAGS)

HEADERS=$(wildcard src/*.h) $(wildcard src/*/*.h) $(wildcard lib/*.h)
PROGRAMOBJECTS=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c)) $(patsubst src/%.c,obj/%.o,$(wildcard src/*/*.c))

PROGRAMFILE=bin/$(notdir $(shell pwd)).$(shell arch)

all: $(PROGRAMFILE)

obj/%.o: src/%.c $(HEADERS)
	$(COMPILER) -c -o $@ $< $(COMPILEFLAGS) -fPIC

$(PROGRAMFILE): $(PROGRAMOBJECTS)
	$(COMPILER) -o $(PROGRAMFILE) $(PROGRAMOBJECTS) $(LINKFLAGS)

clean:
	/bin/bash -c 'if [ -e bin/* ]; then rm bin/*; fi'
	/bin/bash -c 'if [ -e obj/* ]; then rm obj/*; fi'
