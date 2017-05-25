all:
	gcc -std=c99 -Wall structures.h classFileStruct.h leitura.h leitura.c main.c

clean:
	rm a.out
	rm *.gch
