/**
 * @file interpretador.c
 * @brief Arquivo fonte que contém a implementação das instruções e funções auxiliares.
 */

 #ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "instrucoes.h"
#include "classFileStruct.h"
#include "jvm.h"
#include <stdbool.h>

/** Macro para normalizar índice do pool de constantes */
#define normaliza_indice(x,y) (x << 8) | y


ClassFile* resolverClasse(char *nome_classe);
bool resolverMetodo(cp_info *cp, u2 indice_cp, u1 interface);
char* obterNomeMetodo(cp_info *cp, u2 indice_cp, u1 interface);
char* obterDescriptorMetodo(cp_info *cp, u2 indice_cp, u1 interface);
int descriptorFieldValidate (char * descriptor);
char* obterClasseDoMetodo(cp_info *cp, u2 indice_cp);
frame* transferePilhaVetor(frame *anterior, frame *novo, int *parametros_cont);
double decodificaDoubleValor(u4 high, u4 low);
float decodificaFloatValor(u4 valor);
long decodificaLongValor (u4 high, u4 low);
int getParametrosNaoStatic (ClassFile * classe);
Lista_Objetos * InsereObjeto (Lista_Objetos * lis, ClassFile * classe, int parametrosNaoStatic);
bool buscaStaticFlags (char * accessFlags);
int getParametrosCount (char * descriptor);
Lista_Objetos * buscaObjetoViaReferencia (ClassFile * p);
int getPositionField (ClassFile * obj, char * nomeField);
ClassFile * instanciarClasse (char * nomeClasse);
int getTipoOperandoSaida(char * descriptorRetorno);
int getTipoRetorno (char * descriptor);


/**
 * @brief Não executa nada =)
 * 
 * @param par0 -
 * @param par1 -
 * @param par2 -
 */
void nop_impl(frame *par0,u1 par1, u1 par2);
/**
 * @brief Faz o push de um valor nulo para a pilha de operandos 
 * @param f Ponteiro para o frame]
 * @param par1 -
 * @param par2 -
 */
void aconst_null_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param f [description]
 * @param par1 [description]
 * @param par2 [description]
 */
void iconst_m1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 2 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 3 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 4 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_4_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 5 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_5_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 2 \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fconst_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dconst_1_impl(frame *f, u1 par1, u1 par2);
void bipush_impl(frame *f, u1 byte, u1 par1);
void sipush_impl(frame *f,u1 byte1, u1 byte2);
void ldc_impl(frame *f,u1 indexbyte1,u1 par2);
void ldc_w_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void ldc2_w_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void iload_impl(frame *f, u1 index, u1 par1);
void lload_impl(frame *f, u1 index, u1 par1);
void fload_impl(frame *f, u1 index, u1 par1);
void dload_impl(frame *par0, u1 par1,u1 par2);
void aload_impl(frame *f, u1 index, u1 par1);
void iload_0_impl(frame *f, u1 par1, u1 par2);
void iload_1_impl(frame *f, u1 par1, u1 par2);
void iload_2_impl(frame *f, u1 par1, u1 par2);
void iload_3_impl(frame *f, u1 par1, u1 par2);
void lload_0_impl(frame *f, u1 par1, u1 par2);
void lload_1_impl(frame *f, u1 par1, u1 par2);
void lload_2_impl(frame *f, u1 par1, u1 par2);
void lload_3_impl(frame *f, u1 par1, u1 par2);
void fload_0_impl(frame *f, u1 par1, u1 par2);
void fload_1_impl(frame *f, u1 par1, u1 par2);
void fload_2_impl(frame *f, u1 par1, u1 par2);
void fload_3_impl(frame *f, u1 par1, u1 par2);
void dload_0_impl(frame *f, u1 par1, u1 par2);
void dload_1_impl(frame *f, u1 par1, u1 par2);
void dload_2_impl(frame *f, u1 par1, u1 par2);
void dload_3_impl(frame *f, u1 par1, u1 par2);
void aload_0_impl(frame *f, u1 par1, u1 par2);
void aload_1_impl(frame *f, u1 par1, u1 par2);
void aload_2_impl(frame *f, u1 par1, u1 par2);
void aload_3_impl(frame *f, u1 par1, u1 par2);
/* Verificar iaload até saload, tem que ajustar a lógica de acesso ao array no índice x. */
void iaload_impl(frame *f, u1 par1, u1 par2);
void laload_impl(frame *f, u1 par1, u1 par2);
void faload_impl(frame *f, u1 par1, u1 par2);
void daload_impl(frame *f, u1 par1, u1 par2);
void aaload_impl(frame *f, u1 par1, u1 par2);
void baload_impl(frame *f, u1 par1, u1 par2);
void caload_impl(frame *f, u1 par1, u1 par2);
void saload_impl(frame *f, u1 par1, u1 par2);
void istore_impl(frame *f, u1 index, u1 par1);
void lstore_impl(frame *f, u1 index, u1 par1);
void fstore_impl(frame *f, u1 index, u1 par1);
void dstore_impl(frame *f, u1 index, u1 par1);
void astore_impl(frame *f,u1 index, u1 par1);
void istore_0_impl(frame *f, u1 par1, u1 par2);
void istore_1_impl(frame *f, u1 par1, u1 par2);
void istore_2_impl(frame *f, u1 par1, u1 par2);
void istore_3_impl(frame *f, u1 par1, u1 par2);
void lstore_0_impl(frame *f, u1 par1, u1 par2);
void lstore_1_impl(frame *f, u1 par1, u1 par2);
void lstore_2_impl(frame *f, u1 par1, u1 par2);
void lstore_3_impl(frame *f, u1 par1, u1 par2);
void fstore_0_impl(frame *f, u1 par1, u1 par2);
void fstore_1_impl(frame *f, u1 par1, u1 par2);
void fstore_2_impl(frame *f, u1 par1, u1 par2);
void fstore_3_impl(frame *f, u1 par1, u1 par2);
void dstore_0_impl(frame *f, u1 par1, u1 par2);
void dstore_1_impl(frame *f, u1 par1, u1 par2);
void dstore_2_impl(frame *f, u1 par1, u1 par2);
void dstore_3_impl(frame *f, u1 par1, u1 par2);
void astore_0_impl(frame *f, u1 par1, u1 par2);
void astore_1_impl(frame *f, u1 par1, u1 par2);
void astore_2_impl(frame *f, u1 par1, u1 par2);
void astore_3_impl(frame *f, u1 par1, u1 par2);
void iastore_impl(frame *f, u1 par1, u1 par2);
void lastore_impl(frame *f, u1 par1, u1 par2);
void fastore_impl(frame *f, u1 par1, u1 par2);
void dastore_impl(frame *f, u1 par1, u1 par2);
void aastore_impl(frame *f, u1 par1, u1 par2); // Não implementado - FODINHA essa
void bastore_impl(frame *f, u1 par1, u1 par2);
void castore_impl(frame *f, u1 par1, u1 par2);
void sastore_impl(frame *f, u1 par1, u1 par2);
pilha_operandos* pop_impl(frame *f);
pilha_operandos** pop2_impl(frame *f);
void pop_fantasma(frame *par0, u1 par1, u1 par2);
void pop2_fantasma(frame *par0, u1 par1, u1 par2);
void dup_impl(frame *f, u1 par1, u1 par2);
void dup_x1_impl(frame *f, u1 par1, u1 par2);
void dup_x2_impl(frame *f, u1 par1, u1 par2);
void dup2_impl(frame *f, u1 par1, u1 par2);
void dup2_x1_impl(frame *f, u1 par1, u1 par2);
void dup2_x2_impl(frame *f, u1 par1, u1 par2);
void swap_impl(frame *f, u1 par1, u1 par2);
void iadd_impl(frame *f, u1 par1, u1 par2);
void ladd_impl(frame *f, u1 par1, u1 par2);
void fadd_impl(frame *f, u1 par1, u1 par2);
void dadd_impl(frame *f, u1 par1, u1 par2);
void isub_impl(frame *f, u1 par1, u1 par2);
void lsub_impl(frame *f, u1 par1, u1 par2);
void fsub_impl(frame *f, u1 par1, u1 par2);
void dsub_impl(frame *f, u1 par1, u1 par2);
void imul_impl(frame *f, u1 par1, u1 par2);
void lmul_impl(frame *f, u1 par1, u1 par2);
void fmul_impl(frame *f, u1 par1, u1 par2);
void dmul_impl(frame *f, u1 par1, u1 par2);
void idiv_impl(frame *f, u1 par1, u1 par2);
void ldiv_impl(frame *f, u1 par1, u1 par2);
void fdiv_impl(frame *f, u1 par1, u1 par2);
void ddiv_impl(frame *f, u1 par1, u1 par2);
void irem_impl(frame *f, u1 par1, u1 par2);
void lrem_impl(frame *f, u1 par1, u1 par2);
void frem_impl(frame *f, u1 par1, u1 par2);
void drem_impl(frame *f, u1 par1, u1 par2);
void ineg_impl(frame *f, u1 par1, u1 par2);
void lneg_impl(frame *f, u1 par1, u1 par2);
void fneg_impl(frame *f, u1 par1, u1 par2);
void dneg_impl(frame *f, u1 par1, u1 par2);
void ishl_impl(frame *f, u1 par1, u1 par2);
void lshl_impl(frame *f, u1 par1, u1 par2);
void ishr_impl(frame *f, u1 par1, u1 par2);
void lshr_impl(frame *f, u1 par1, u1 par2);
void iushr_impl(frame *f, u1 par1, u1 par2);
void lushr_impl(frame *f, u1 par1, u1 par2);
void iand_impl(frame *f, u1 par1, u1 par2);
void land_impl(frame *f, u1 par1, u1 par2);
void ior_impl(frame *f, u1 par1, u1 par2);
void lor_impl(frame *f, u1 par1, u1 par2);
void ixor_impl(frame *f, u1 par1, u1 par2);
void lxor_impl(frame *f, u1 par1, u1 par2);
void iinc_fantasma(frame *par0, u1 par1, u1 par2);
void iinc_impl(frame *f, u1 index, i1 constante);
void iinc_wide_fantasma(frame *f, u1 indexbyte1, u1 indexbyte2, u1 constbyte1, u1 constbyte2);
void iinc_wide(frame *f, u2 indexbyte, i2 constbyte);
void i2l_impl(frame *f, u1 par1, u1 par2);
void i2f_impl(frame *f, u1 par1, u1 par2);
void i2d_impl(frame *f, u1 par1, u1 par2);
void l2i_impl(frame *f, u1 par1, u1 par2);
void l2f_impl(frame *f, u1 par1, u1 par2);
void l2d_impl(frame *f, u1 par1, u1 par2);
void f2i_impl(frame *f, u1 par1, u1 par2);
void f2l_impl(frame *f, u1 par1, u1 par2);
void f2d_impl(frame *f, u1 par1, u1 par2);
void d2i_impl(frame *f, u1 par1, u1 par2);
void d2l_impl(frame *f, u1 par1, u1 par2);
void d2f_impl(frame *f, u1 par1, u1 par2);
void i2b_impl(frame *f, u1 par1, u1 par2);
void i2c_impl(frame *f, u1 par1, u1 par2);
void i2s_impl(frame *f, u1 par1, u1 par2);
void lcmp_impl(frame *f, u1 par1, u1 par2);
void fcmpl_impl(frame *f, u1 par1, u1 par2);
void fcmpg_impl(frame *f, u1 par1, u1 par2);
void dcmpl_impl(frame *f, u1 par1, u1 par2);
void dcmpg_impl(frame *f, u1 par1, u1 par2);
void ifeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void iflt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for maior ou igual ao valor zero
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void ifge_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for maior do que o valor zero
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void ifgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for menor do que o valor zero
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void ifle_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for igual ao próximo inteiro na pilha
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void if_icmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for diferente do próximo inteiro na pilha
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void if_icmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for maior do que o próximo inteiro na pilha
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void if_icmplt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for menor do que o próximo inteiro na pilha
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void if_icmpge_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for menor do que o próximo inteiro na pilha
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void if_icmpgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se o inteiro no topo da pilha for maior do que o próximo inteiro na pilha
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void if_icmple_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se as referências na pilha forem iguais
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void acmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Branch será efetuado se as referências na pilha não forem iguais
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o índice do branch
 * @param branchbyte2 Byte que será concatenado para montar o índice do branch
 */
void acmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief A instrução sempre efetuará um branch
 * 
 * @param f Frame corrente
 * @param branchbyte1 Parâmetro que será concatenado para montar o índice do branch
 * @param branchbyte2 Parâmetro que será concatenado para montar o índice do branch
 */
void inst_goto_impl(frame *f,u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Instrução para efetuar um branch para um offset, dentro do código do mesmo método sendo executado
 * 
 * @param f Frame corrente
 * @param branchbyte1 Parâmetro que será concatenado para montar o índice do branch
 * @param branchbyte2 Parâmetro que será concatenado para montar o índice do branch
 */
void jsr_impl(frame *f,u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Instrução para retornar de uma subrotina
 * 
 * @param f Frame corrente
 * @param index Índice no vetor de variáveis locais do frame corrente
 * @param par1 Esse parâmetro não será utilizado na prática
 */
void ret_impl(frame *f, u1 index, u1 par1);

/**
 * @brief Instrução utilizada como placeholder, para ocupar a posição no array de instruções, para não prejudicar o mapeamento direto
 * 
 * @param par0 Esse parâmetro não será utilizado na prática
 * @param par1 Esse parâmetro não será utilizado na prática
 * @param par2 Esse parâmetro não será utilizado na prática
 */
void tableswitch_fantasma(frame *par0, u1 par1, u1 par2);

/**
 * @brief Instrução utilizada como placeholder, para ocupar a posição no array de instruções, para não prejudicar o mapeamento direto
 * 
 * @param par0 Esse parâmetro não será utilizado na prática
 * @param par1 Esse parâmetro não será utilizado na prática
 * @param par2 Esse parâmetro não será utilizado na prática
 */
void lookupswitch_fantasma(frame *par0, u1 par1, u1 par2);

/**
 * @brief Instrução para acessar uma jump table por index e efetuar um jump
 * 
 * @param f Frame corrente
 */
void tableswitch_impl(frame *f);

/**
 * @brief Instrução para acessar uma chave em um jump table e efetuar um jump
 * 
 * @param f Frame corrente
 */
void lookupswitch_impl(frame *f);

/**
 * @brief Instrução para retornar um inteiro de um método
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void ireturn_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para retornar um long de um método
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void lreturn_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para retornar um float de um método
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void freturn_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para retornar um double de um método
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void dreturn_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para retornar uma referência de um método
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void areturn_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para retornar void de um método
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro não utilizado
 * @param par2 Parâmetro não utilizado
 */
void inst_return_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para obter um field estático de uma classe
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void getstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução para setar um field estático em uma classe
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void putstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução para obter o field de um objeto
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void getfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução para setar um field em um objeto
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void putfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Função para invocar um método de instância, geralmente utilizada para impressão em tela
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void invokevirtual_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução para invocar um método de instância
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void invokespecial_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução para invocar um método estático (método de classe)
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void invokestatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução utilizada como placeholder, para ocupar a posição no array de instruções, para não prejudicar o mapeamento direto
 * 
 * @param f Esse parâmetro não será utilizado na prática
 * @param par1 Esse parâmetro não será utilizado na prática
 * @param par2 Esse parâmetro não será utilizado na prática
 */
void invokeinterface_fantasma(frame *par0, u1 par1, u1 par2);

/**
 * @brief Instrução para invocar um método de interface
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 * @param count Um byte que não pode ser zero
 */
void invokeinterface_impl(frame *f, u1 indexbyte1, u1 indexbyte2, u1 count);

/**
 * @brief Instrução para invocar um método dinâmico. Essa instrução só existe para criar uma posição "falsa" no vetor de ponteiros de função
 * @details [long description]
 * 
 * @param par0 Parâmetro não utilizado
 * @param par1 Parâmetro não utilizado
 * @param par2 Parâmetro não utilizado
 */
void invokedynamic_fantasma(frame *par0, u1 par1, u1 par2);

/**
 * @brief Instrução para criar um novo objeto
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param indexbyte2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void inst_new_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Função para criar um novo array de um dado tipo
 * 
 * @param f Frame corrente
 * @param atype Tipo do array que deve ser criado
 * @param par1 Parâmetro não utilizado
 */
void newarray_impl(frame *f ,u1 atype, u1 par1);

/**
 * @brief Criar um novo array do tipo referência
 * @details [long description]
 * 
 * @param f Frame corrente
 * @param par1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param par2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void anewarray_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para obter o tamanho de um array
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro não utilizado
 * @param par2 Parâmetro não utilizado
 */
void arraylength_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para lançar uma exceção ou erro
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro não utilizado
 * @param par2 Parâmetro não utilizado
 */
void athrow_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para verificar se um objeto é de um determinado tipo
 * 
 * @param f Frame corrente
 * @param par1 Byte que será concatenado para acessar uma entrada na constant pool
 * @param par2 Byte que será concatenado para acessar uma entrada na constant pool
 */
void checkcast_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para determinar se um objeto é de um eterminado tipo
 * 
 * @param f Frame corrente
 * @param par1 Byte que será concatenado para acessar uma entrada na constant pool
 *
 * @param par2 Byte que será concatenado para acessar uma entrada na constant pool
 *
 */
void instanceof_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para entrar no monitor de um objeto
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro não utilizado
 * @param par2 Parâmetro não utilizado
 */
void monitorenter_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para sair de um monitor de um objeto
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro não utilizado
 * @param par2 Parâmetro não utilizado
 */
void monitorexit_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para estender a próxima instrução para ter o dobro de bytes de índice. 
 * 
 * @param f Parâmetro não utilizado
 * @param indexbyte1 Parâmetro não utilizado
 * @param indexbyte2 Parâmetro não utilizado
 */
void wide_impl(frame *f, u1 indexbyte1, u1 indexbyte2);

/**
 * @brief Instrução que irá criar um array multidimensional
 * 
 * @param f Frame corrente
 * @param indexbyte1 Byte que será concatenado para montar um índice para a constant pool da classe corrente
 * @param indexbyte2 Byte que será concatenado para montar um índice para a constant pool da classe corrente
 * @param dimensions Número de dimensões do array
 */
void multianewarray_impl(frame *f, u1 indexbyte1, u1 indexbyte2, u1 dimensions);

/**
 * @brief Instrução utilizada como placeholder, para ocupar a posição no array de instruções, para não prejudicar o mapeamento direto
 * 
 * @param f Esse parâmetro não será utilizado na prática
 * @param par1 Esse parâmetro não será utilizado na prática
 * @param par2 Esse parâmetro não será utilizado na prática
 */
void multianewarray_fantasma(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução que irá efetuar um branch caso a referência no topo da pilha seja nula
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o offset do branch
 * @param branchbyte2 Byte que será concatenado para montar o offset do branch
 */
void ifnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief Instrução que irá efetuar um branch caso a referência no topo da pilha não seja nula
 * 
 * @param f Frame corrente
 * @param branchbyte1 Byte que será concatenado para montar o offset do branch
 * @param branchbyte2 Byte que será concatenado para montar o offset do branch
 */
void ifnonnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2);

/**
 * @brief A instrução sempre efetuará um branch, para um offset wide
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro que será concatenado para montar o índice do branch
 * @param par2 Parâmetro que será concatenado para montar o índice do branch
 */
void goto_w_impl(frame *f, u1 par1, u1 par2);

/**
 * @brief Instrução para efetuar um branch para um offset wide, de 32 bits, dentro do código do mesmo método sendo executado
 * 
 * @param f Frame corrente
 * @param par1 Parâmetro que será concatenado para montar o índice do branch
 * @param par2 Parâmetro que será concatenado para montar o índice do branch
 */
void jsr_w_impl(frame *f, u1 par1, u1 par2);

extern void (*func_ptr[202])(frame *,u1,u1);

#endif
