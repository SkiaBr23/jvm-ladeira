all:
	gcc structures.h classFileStruct.h leitura.h leitura.c main.c -std=c99

clean:
	rm a.out
	rm *.gch