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
	@printf "\033[32mCOMPILE\033[0m %8s\033[31m\n" "$<"
	@$(COMPILER) -c -o $@ $< $(COMPILEFLAGS) -fPIC
	@printf "\033[0m"
$(PROGRAMFILE): $(PROGRAMOBJECTS)
	@printf "\033[34mLINK_TO\033[0m %8s\033[31m\n" "$@"
	@$(COMPILER) -o $(PROGRAMFILE) $(PROGRAMOBJECTS) $(LINKFLAGS)
	@printf "\033[0m"

clean:
	@rm -f obj/*
	@rm -f bin/*
	@rm -f src/TAGS
	@printf "\033[31mCLEANED\033[0m\n"

tags: src/TAGS

src/TAGS: $(wildcard src/*.c) $(HEADERS)
	@printf "\033[33mTAGGIFY\033[0m %s\n" "$(wildcard src/*.c) $(HEADERS)"
	@etags src/*.c src/*.h -o src/TAGS
