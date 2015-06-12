# pnC

## Description & Goal
A simple C library for black and white Petri nets. In order to represent Petri nets in term of FMU, a simple C library for Petri nets was required. Unfortunately, it seemed that none exist. Therefore, *pnC* was developed.

## Understanding the tree structure
- **bin**: folder for compilation purposes
- **example**: simple example on how to use the library
- **lib**: folder that contains the pnC library
    - **inc**: folder for headers
    - **src**
        - *dynarray.c*: C code to have dynamic signed int arrays
        - *pnc.c*: C code to represent a black and white Petri nets
- **tests**: folders with cmocka tests

## How to tests the library
This library has been tested using the [cmocka unit testint library](https://cmocka.org/). Therefore, the latter must be installed.

Once, it is installed, one must only called the following line:
> make test

## How to execute the example
> make
> ./example/bin/example.o

