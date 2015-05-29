COMPILER = gcc

DEBUG = -DNDEBUG

HEADER_FOLDER = src
SRC_FOLDER = src
BIN_FOLDER = bin

TESTS_SRC_FOLDER = tests
TESTS_BIN_FOLDER = tests/bin

PNC_SRCS = $(SRC_FOLDER)/pnc.c
UTIL_SRCS = $(SRC_FOLDER)/dynarray.c

PNC_INCLUDE = src

INCLUDES = -I $(PNC_INCLUDE)

SRCS = $(PNC_SRCS) $()
TESTS = $(TESTS_SRC_FOLDER)/pnC_tests.c $(TESTS_SRC_FOLDER)/dynarray_tests.c
SRC_MAIN_TEST = $(TESTS_SRC_FOLDER)/alltests.c
BIN_MAIN_TEST = $(TESTS_BIN_FOLDER)/alltests.o

LIBS = -l cmocka

all: $(SRCS)
	mkdir -p $(BIN_FOLDER)
	gcc $(DEBUG) src/pnc.c -o bin/pnc.o 

array:
	mkdir -p $(BIN_FOLDER)
	gcc $(DEBUG) src/dynarray.c -o bin/dynarray.o 

test: $(SRCS)
	mkdir -p $(TESTS_BIN_FOLDER)
	$(COMPILER) $(DEBUG) $(LIBS) $(INCLUDES) $(UTIL_SRCS) $(SRCS) $(TESTS) $(SRC_MAIN_TEST) -o $(BIN_MAIN_TEST)
	$(BIN_MAIN_TEST)

debug: $(SRCS)
	mkdir -p bin
	gcc src/pnc.c -o bin/pnc.o

clean:
	rm -r -f $(BIN_FOLDER)
	rm -f pnc.o
	rm -r -f $(TESTS_BIN_FOLDER)