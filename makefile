flags = -std=c99 -Wall
program = myavl

all: $(program)

$(program): myavl.o avl.o
	gcc -o $(program) myavl.o avl.o $(flags)

myavl.o: myavl.c
	gcc -c myavl.c $(flags)

avl.o: avl.h avl.c
	gcc -c avl.c $(flags)

clean:
	rm -f *.o *.gch $(program)

purge:
	rm -f *.o *.gch $(program)
	clear