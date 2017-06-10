all:
	gcc -std=c99 -Wall structures.h lista_operandos.h pilha_operandos.h classFileStruct.h instrucoes.h leitura.h instrucoes.c leitura.c main.c -lm

debug:
	gcc -g -std=c99 -Wall structures.h lista_operandos.h pilha_operandos.h classFileStruct.h instrucoes.h leitura.h instrucoes.c leitura.c main.c -lm

clean:
	rm a.out
	rm *.gch
