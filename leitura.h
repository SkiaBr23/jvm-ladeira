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
#include "instrucoes.h"

/*Assinatura de métodos para leitura de dados*/
u1 u1Read(FILE *fp);
u2 u2Read(FILE *fp);
u4 u4Read(FILE *fp);
ClassFile * lerArquivo (char *);
cp_info * lerConstantPool (FILE * fp, u2 constant_pool_count);
method_info * lerMethod (FILE * fp, u2 methods_count, cp_info *cp);
char* decodificarOperandoInstrucao(cp_info *cp, u2 index, u2 sizeCP);
char* decodificarCode(cp_info *cp,u2 sizeCP,u1 *code, u4 length,instrucao *instrucoes);
field_info * lerField (FILE * fp, u2 fields_count, cp_info * cp);
u2 * lerInterfaces (FILE * fp, u2 size);
innerClasses_attribute * lerInnerClasses (FILE * fp, cp_info * cp);
exceptions_attribute * lerExceptionsAttribute (FILE * fp);
classes * lerClasses (FILE * fp);
constantValue_attribute * lerConstantValue (FILE * fp);
double decodificaDoubleInfo (cp_info * cp);
uint64_t decodificaLongInfo (cp_info * cp);
float decodificaFloatInfo (cp_info * cp);
int decodificaIntegerInfo (cp_info * cp);
signature_attribute * lerSignature (FILE * fp);
char* organizandoFlags(char* flagsOrdemInversa);
stackMapTable_attribute * lerStackMapTable (FILE * fp);
stack_map_frame * lerStackMapFrame (FILE * fp);
int setaOffsetImpressao (int posicao, u1 offset);
verification_type_info * lerVerificationTypeInfo (FILE * fp);
code_attribute * lerCode (FILE * fp, cp_info *cp);
line_number_table * lerLineNumberTable(FILE * fp, cp_info *cp);
exception_table * lerExceptionTable (FILE * fp, u2 size);
attribute_info * lerAttributes (FILE * fp, cp_info *cp);
source_file_attribute * lerSourceFile (FILE * fp);
char* buscaNomeTag(u1 tag);
char* decodificaStringUTF8(cp_info *cp);
char* decodificaNIeNT(cp_info *cp, u2 index,u1 tipo);
char* decodificaAccessFlags(u2 flag);
void imprimirClassFile (ClassFile *, FILE *);

#endif
