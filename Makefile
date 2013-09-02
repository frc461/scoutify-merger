COMPILER=gcc

PROJECTFLAGS:=-ljansson
FLAGS:=$(PROJECTFLAGS) -I. -ggdb -std=c11

COMPILEFLAGS=$(FLAGS) -fPIC
LINKFLAGS=$(FLAGS)

HEADERS=$(wildcard src/*.h) $(wildcard src/*/*.h) $(wildcard lib/*.h)
PROGRAMOBJECTS=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c)) $(patsubst src/%.c,obj/%.o,$(wildcard src/*/*.c))

PROGRAMFILE=bin/$(notdir $(shell pwd)).$(shell arch)

all: $(PROGRAMFILE) tags

obj/%.o: src/%.c $(HEADERS)
	@printf "\033[32mCOMPILE\033[0m %8s\n" "$<"
	@$(COMPILER) -c -o $@ $< $(COMPILEFLAGS) -fPIC

$(PROGRAMFILE): $(PROGRAMOBJECTS)
	@printf "\033[34mLINK TO\033[0m %8s\n" "$@"
	@$(COMPILER) -o $(PROGRAMFILE) $(PROGRAMOBJECTS) $(LINKFLAGS)

clean:
	rm obj/*
	rm bin/*

tags: src/TAGS

src/TAGS: $(wildcard src/*.c) $(HEADERS)
	etags src/*.c src/*.h -o src/TAGS
