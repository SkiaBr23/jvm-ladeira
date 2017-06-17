#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "instrucoes.h"

/* Ficamos na dúvida entre u1 e u4, não sabemos qual valor deve ser mandado para o argumento das funções */
void nop_impl(void); // Não implementado
void aconst_null_impl(frame *f);
void iconst_m1_impl(frame *f);
void iconst_0_impl(frame *f);
void iconst_1_impl(frame *f);
void iconst_2_impl(frame *f);
void iconst_3_impl(frame *f);
void iconst_4_impl(frame *f);
void iconst_5_impl(frame *f);
void lconst_0_impl(frame *f);
void lconst_1_impl(frame *f);
void fconst_0_impl(frame *f);
void fconst_1_impl(frame *f);
void fconst_2_impl(frame *f);
void dconst_0_impl(frame *f);
void dconst_1_impl(frame *f);
void bipush_impl(u1 byte, frame *f);
void sipush_impl(u1 byte1, u1 byte2, frame *f);
void ldc_impl(void); // Não implementado
void ldc_w_impl(void); // Não implementado
void ldc2_w_impl(void); // Não implementado
void iload_impl(u1 index, frame *f);
void lload_impl(u1 index, frame *f); // Não implementado
void fload_impl(u1 index, frame *f);
void dload_impl(void); // Não implementado
void aload_impl(u1 index, frame *f);
void iload_0_impl(frame *f);
void iload_1_impl(frame *f);
void iload_2_impl(frame *f);
void iload_3_impl(frame *f);
void lload_0_impl(frame *f); // Não implementado
void lload_1_impl(frame *f); // Não implementado
void lload_2_impl(frame *f); // Não implementado
void lload_3_impl(frame *f); // Não implementado
void fload_0_impl(frame *f);
void fload_1_impl(frame *f);
void fload_2_impl(frame *f);
void fload_3_impl(frame *f);
void dload_0_impl(frame *f); // Não implementado
void dload_1_impl(frame *f); // Não implementado
void dload_2_impl(frame *f); // Não implementado
void dload_3_impl(frame *f); // Não implementado
void aload_0_impl(frame *f);
void aload_1_impl(frame *f);
void aload_2_impl(frame *f);
void aload_3_impl(frame *f);
/* Verificar iaload até saload, tem que ajustar a lógica de acesso ao array no índice x. */
void iaload_impl(frame *f);
void laload_impl(frame *f); // Não implementado
void faload_impl(frame *f);
void daload_impl(frame *f); // Não implementado
void aaload_impl(frame *f);
void baload_impl(frame *f);
void caload_impl(frame *f);
void saload_impl(frame *f);
void istore_impl(u1 index, frame *f);
void lstore_impl(u1 index, frame *f); // Não implementado
void fstore_impl(u1 index, frame *f);

#endif