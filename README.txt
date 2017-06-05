==============================
Para compilar os arquivos, é possivel executar o makefile com o comando

> make

Ou via compilação manual rodando o comando

> gcc -std=c99 -Wall structures.h classFileStruct.h instrucoes.h leitura.h instrucoes.c leitura.c main.c -lm

Será gerado um arquivo executável (a.out em Linux, a.exe em Windows) que deve ser rodado passando um arquivo 
".class" como no exemplo:

./a.out Main.class

O usuario deve inserir o nome do arquivo de saida quando requisitado pelo programa. 
O programa imprime a saida na tela e neste arquivo.
