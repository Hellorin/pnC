all:
	mkdir -p bin
	gcc src/pnc.c -o bin/pnc.o
	
debug:
	mkdir -p bin
	gcc src/pnc.c -o bin/pnc.o

normal:
	mkdir -p bin
	gcc src/pnc.c -o bin/pnc.o

clean:
	rm -r -f bin
	rm -f pnc.o