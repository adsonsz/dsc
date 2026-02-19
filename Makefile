GXX = gcc
INCLUDE = -Iinclude
FLAGS = -Wall -Wextra -pedantic

REPONAME = dsc
LIB_NAME = build/$(REPO_NAME).so

INC = $(shell find include -type f -name '*.h')
SRC = $(shell find src -type f -name '*.c')
OBJ = $(patsubst src/%.c, build/obj/%.o, $(SRC))

TEST_SRC = $(shell find test/ -type f -name '*.c' ! -path 'test/main.c')
TEST_OBJ = $(patsubst test/%.c, build/test_obj/%.o, $(TEST_SRC))
TEST_BIN = $(patsubst test/%.c, build/test_bin/%, $(TEST_SRC))

EXAMPLES_SRC = $(shell find examples -type f -name '*.c')
EXAMPLES_BIN = $(patsubst examples/%.c, build/examples/%, $(EXAMPLES_SRC))

.PHONY: display loc clear external test
.PRECIOUS: $(TEST_OBJ)

all: $(OBJ) $(EXAMPLES_BIN) $(TEST_BIN)

test: $(TEST_BIN)
	@python run_tests.py
    
build/obj/%.o: src/%.c
	@mkdir -p "$(@D)"
	@echo Compiling "$<"...
	@$(GXX) $(INCLUDE) -c "$<" -o "$@" $(FLAGS)

build/examples/%: examples/%.c $(OBJ)
	@mkdir -p "$(@D)"
	@echo Compiling "$<"...
	@$(GXX) $(INCLUDE) $(OBJ) "$<" -o "$@" $(FLAGS)

build/test_obj/%.o: test/%.c
	@mkdir -p "$(@D)"
	@echo Compiling "$<"...
	@$(GXX) $(INCLUDE) -c "$<" -o "$@" $(FLAGS)

build/test_bin/%: build/test_obj/%.o $(OBJ)
	@mkdir -p "$(@D)"
	@echo Compiling "$<"...
	@$(GXX) $(INCLUDE) $(OBJ) "$<" -o "$@" $(FLAGS)

loc: 
	@find . -type f \( -iname \*.c -o -iname \*.h \) -exec wc -l {} +

clear:
	@rm -rf build

display:
	@echo INC=$(INC)
	@echo SRC=$(SRC)
	@echo OBJ=$(OBJ)
	@echo TEST_SRC=$(TEST_SRC)
	@echo TEST_OBJ=$(TEST_OBJ)
	@echo TEST_BIN=$(TEST_BIN)
	@echo EXAMPLES_SRC=$(EXAMPLES_SRC)
	@echo EXAMPLES_BIN=$(EXAMPLES_BIN)
	@echo LIB_NAME=$(LIB_NAME)


