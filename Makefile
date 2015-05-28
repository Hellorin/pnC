all:
	mkdir -p bin
	gcc -dNDEBUG src/pnc.c -o bin/pnc.o 

testypoo:
	mkdir -p tests/bin
	gcc -l cmocka tests/tests.c -o tests/bin/tests.o

debug:
	mkdir -p bin
	gcc src/pnc.c -o bin/pnc.o

clean:
	rm -r -f bin
	rm -f pnc.o