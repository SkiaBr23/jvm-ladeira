all:
	gcc -std=c99 -Wall structures.h classFileStruct.h instrucoes.h leitura.h instrucoes.c leitura.c main.c

clean:
	rm a.out
	rm *.gch
