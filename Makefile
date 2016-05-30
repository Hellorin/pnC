COMPILER = gcc

DEBUG = -DNDEBUG

HEADER_FOLDER = src
SRC_FOLDER = lib/src
INC_FOLDER = inc
BIN_FOLDER = bin
BUILD_FOLDER = build
EXAMPLE_FOLDER = example
EXAMPLE_INC_FOLDER = $(EXAMPLE_FOLDER)/include
EXAMPLE_SRC_FOLDER = $(EXAMPLE_FOLDER)
EXAMPLE_BIN_FOLDER = $(EXAMPLE_FOLDER)/bin

EXAMPLE_SRCS = $(EXAMPLE_SRC_FOLDER)/example.c

TESTS_SRC_FOLDER = tests
TESTS_BIN_FOLDER = tests/bin

PNC_SRCS = $(SRC_FOLDER)/pnc.c
UTIL_SRCS = $(SRC_FOLDER)/dynarray.c

PNC_INCLUDE = lib/inc

INCLUDES = -I $(PNC_INCLUDE) -I deps/cmocka-1.0.0/build/include

SRCS = $(PNC_SRCS) $()
TESTS = $(TESTS_SRC_FOLDER)/pnC_tests.c $(TESTS_SRC_FOLDER)/dynarray_tests.c
SRC_MAIN_TEST = $(TESTS_SRC_FOLDER)/alltests.c
BIN_MAIN_TEST = $(TESTS_BIN_FOLDER)/alltests.o

LIBS = -l cmockery

all: $(SRCS) $(UTIL_SRCS) $(EXAMPLE_SRCS)
	mkdir -p $(EXAMPLE_BIN_FOLDER)
	$(COMPILER) -std=c99 -DVERBOSE $(INCLUDES) $(UTIL_SRCS) $(SRCS) $(EXAMPLE_SRCS) -o $(EXAMPLE_BIN_FOLDER)/example.o

dev: $(SRCS) $(UTIL_SRCS) $(EXAMPLE_SRCS)
	mkdir -p $(EXAMPLE_BIN_FOLDER)
	$(COMPILER) -std=c99 $(DEBUG) -DVERBOSE $(INCLUDES) $(UTIL_SRCS) $(SRCS) $(EXAMPLE_SRCS) -o $(EXAMPLE_BIN_FOLDER)/example.o

test: $(SRCS) $(UTIL_SRCS)
	mkdir -p $(TESTS_BIN_FOLDER)
	$(COMPILER) -std=c99 $(DEBUG) $(LIBS) $(INCLUDES) $(UTIL_SRCS) $(SRCS) $(TESTS) $(SRC_MAIN_TEST) -o $(BIN_MAIN_TEST)
	$(BIN_MAIN_TEST)

configure:
	mkdir deps
	cd deps && curl -O https://cmocka.org/files/1.0/cmocka-1.0.0.tar.xz
	cd deps && xz -d cmocka-1.0.0.tar.xz
	cd deps && tar vxf cmocka-1.0.0.tar
	cd deps/cmocka-1.0.0 && mkdir build
	cd deps/cmocka-1.0.0/build && cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug .. && make

clean:
	rm -r -f $(BIN_FOLDER)
	rm -f pnc.o
	rm -r -f $(TESTS_BIN_FOLDER)
	rm -r -f $(BUILD_FOLDER)
	rm -r -f cmocka*
	rm -r -f deps
	