all:
	gcc -std=c99 -Wall structures.h classFileStruct.h instrucoes.h leitura.h instrucoes.c leitura.c main.c -lm

debug:
	gcc -g -std=c99 -Wall structures.h classFileStruct.h instrucoes.h leitura.h instrucoes.c leitura.c main.c -lm

clean:
	rm a.out
	rm *.gch
