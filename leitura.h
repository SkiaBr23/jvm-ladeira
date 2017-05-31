/*
Universidade de Brasília - 01/2017
Software Básico - Turma A
Projeto Leitor/Exibidor de arquivo .class

Alunos: Maximillian Fan Xavier - 12/0153271
				Rafael Dias da Costa - 12/0133253
				Murilo Cerqueira Medeiros - 12/0130637
				Eduardo Sousa da Silva - 13/0108405
				Eduardo Schuabb Duarte - 11/0010876

*/

/*Macro para verificação de inclusão de arquivos de estrutura,
bibliotecas de leitura/escrita de dados e manipulação de arquivos
*/
#ifndef LEITURA_H
#define LEITURA_H

/*Inclusão de bibliotecas para leitura/escrita de dados,
manipualão de arquivos e definição de estruturas*/
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "classFileStruct.h"

/*Assinatura de métodos para leitura de dados*/
u1 u1Read(FILE *fp);
u2 u2Read(FILE *fp);
u4 u4Read(FILE *fp);
ClassFile * lerArquivo (char *);
cp_info * lerConstantPool (FILE * fp, u2 constant_pool_count);
method_info * lerMethod (FILE * fp, u2 methods_count, cp_info *cp);
code_attribute * lerCode (FILE * fp, u2 name_index, u2 size, cp_info *cp);
line_number_table * lerLineNumberTable(FILE * fp, u2 attr_name_index, u2 size);
exception_table * lerExceptionTable (FILE * fp, u2 size);
attribute_info * lerAttributes (FILE * fp, u2 attributes_count, cp_info *cp);
source_file_attribute * lerSourceFile (FILE * fp);
char* buscaNomeTag(u1 tag);
char* decodificaStringUTF8(cp_info *cp);
char* decodificaNIeNT(cp_info *cp, u2 index,u1 tipo);
char* decodificaAccessFlags(u2 flag);
void imprimirClassFile (ClassFile *);

#endif
