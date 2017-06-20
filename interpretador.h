#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "instrucoes.h"

/* Observar todas as instruções, pois a maioria delas está parcialmente implementada */
/* Observar todas as intruções quanto ao lançamento de exceções */
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
void lload_impl(u1 index, frame *f);
void fload_impl(u1 index, frame *f);
void dload_impl(u1 index, frame *f);
void aload_impl(u1 index, frame *f);
void iload_0_impl(frame *f);
void iload_1_impl(frame *f);
void iload_2_impl(frame *f);
void iload_3_impl(frame *f);
void lload_0_impl(frame *f);
void lload_1_impl(frame *f);
void lload_2_impl(frame *f);
void lload_3_impl(frame *f);
void fload_0_impl(frame *f);
void fload_1_impl(frame *f);
void fload_2_impl(frame *f);
void fload_3_impl(frame *f);
void dload_0_impl(frame *f);
void dload_1_impl(frame *f);
void dload_2_impl(frame *f);
void dload_3_impl(frame *f);
void aload_0_impl(frame *f);
void aload_1_impl(frame *f);
void aload_2_impl(frame *f);
void aload_3_impl(frame *f);
/* Verificar iaload até saload, tem que ajustar a lógica de acesso ao array no índice x. */
void iaload_impl(frame *f);
void laload_impl(frame *f);
void faload_impl(frame *f);
void daload_impl(frame *f);
void aaload_impl(frame *f);
void baload_impl(frame *f);
void caload_impl(frame *f);
void saload_impl(frame *f);
void istore_impl(u1 index, frame *f);
void lstore_impl(u1 index, frame *f);
void fstore_impl(u1 index, frame *f);
void dstore_impl(u1 index, frame *f);
void astore_impl(u1 index, frame *f);
void istore_0_impl(frame *f);
void istore_1_impl(frame *f);
void istore_2_impl(frame *f);
void istore_3_impl(frame *f);
void lstore_0_impl(frame *f);
void lstore_1_impl(frame *f);
void lstore_2_impl(frame *f);
void lstore_3_impl(frame *f);
void fstore_0_impl(frame *f);
void fstore_1_impl(frame *f);
void fstore_2_impl(frame *f);
void fstore_3_impl(frame *f);
void dstore_0_impl(frame *f);
void dstore_1_impl(frame *f);
void dstore_2_impl(frame *f);
void dstore_3_impl(frame *f);
void astore_0_impl(frame *f);
void astore_1_impl(frame *f);
void astore_2_impl(frame *f);
void astore_3_impl(frame *f);
void iastore_impl(frame *f);
void lastore_impl(frame *f);
void fastore_impl(frame *f);
void dastore_impl(frame *f);
void aastore_impl(frame *f); // Não implementado - BEM FODA
void bastore_impl(frame *f);
void castore_impl(frame *f);
void sastore_impl(frame *f);
pilha_operandos* pop_impl(frame *f);
pilha_operandos** pop2_impl(frame *f);
void dup_impl(frame *f);
void dup_x1_impl(frame *f);
void dup_x2_impl(frame *f);
void dup2_impl(frame *f);
void dup2_x1_impl(frame *f);
void dup2_x2_impl(frame *f);
void swap_impl(frame *f);
void iadd_impl(frame *f);
void ladd_impl(frame *f); // Não implementado
void fadd_impl(frame *f); // Não implementado
void dadd_impl(frame *f); // Não implementado
void isub_impl(frame *f);
void lsub_impl(frame *f); // Não implementado
void fsub_impl(frame *f); // Não implementado
void dsub_impl(frame *f); // Não implementado
void imul_impl(frame *f);
void lmul_impl(frame *f); // Não implementado
void fmul_impl(frame *f); // Não implementado
void dmul_impl(frame *f); // Não implementado
void idiv_impl(frame *f);
void ldiv_impl(frame *f); // Não implementado
void fdiv_impl(frame *f); // Não implementado
void ddiv_impl(frame *f); // Não implementado
void irem_impl(frame *f);
void lrem_impl(frame *f); // Não implementado
void frem_impl(frame *f); // Não implementado
void drem_impl(frame *f); // Não implementado
void ineg_impl(frame *f);
void lneg_impl(frame *f); // Não implementado
void fneg_impl(frame *f); // Não implementado
void dneg_impl(frame *f); // Não implementado
void ishl_impl(frame *f);
void lshl_impl(frame *f); // Não implementado
void ishr_impl(frame *f);
void lshr_impl(frame *f); // Não implementado
void iushr_impl(frame *f);
void lushr_impl(frame *f); // Não implementado
void iand_impl(frame *f);
void land_impl(frame *f); // Não implementado
void ior_impl(frame *f);
void lor_impl(frame *f); // Não implementado
void ixor_impl(frame *f);
void lxor_impl(frame *f); // Não implementado
void iinc_impl(frame *f, u1 index, i1 constante);
void i2l_impl(frame *f); // Não implementado
void i2f_impl(frame *f); // Não implementado
void i2d_impl(frame *f); // Não implementado
void l2i_impl(frame *f); // Não implementado
void l2f_impl(frame *f); // Não implementado
void l2d_impl(frame *f); // Não implementado
void f2i_impl(frame *f); // Não implementado
void f2l_impl(frame *f); // Não implementado
void f2d_impl(frame *f); // Não implementado
void d2i_impl(frame *f); // Não implementado
void d2l_impl(frame *f); // Não implementado
void d2f_impl(frame *f); // Não implementado
void i2b_impl(frame *f);
void i2c_impl(frame *f);
void i2d_impl(frame *f); // Não implementado 
void i2s_impl(frame *f);
void lcmp_impl(frame *f); // Não implementado
void fcmpl_impl(frame *f); // Não implementado
void fcmpg_impl(frame *f); // Não implementado
void dcmpl_impl(frame *f); // Não implementado
void dcmpg_impl(frame *f); // Não implementado
void ifeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void iflt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifge_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifle_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void icmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void icmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void icmplt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void icmpgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void icmple_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void acmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void acmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void inst_goto_impl(frame *f,u1 branchbyte1, u1 branchbyte2);
void jsr_impl(frame *f,u1 branchbyte1, u1 branchbyte2);
void ret_impl(frame *f, u1 index);
void tableswitch_impl(frame *f);
void lookupswitch_impl(frame *f);
void ireturn_impl(frame *f);
void lreturn_impl(frame *f); // Não implementado
void freturn_impl(frame *f); // Não implementado
void dreturn_impl(frame *f); // Não implementado
void areturn_impl(frame *f);
void inst_return_impl(frame *f);
void getstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void putstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void getfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void putfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void invokevirtual_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
// Pulei várias instruções
void invokespecial_impl(frame *f); // Não implementado
/* Próximo objetivo: implementar invokestatic */
void invokestatic_impl(frame *f); // Não implementado
void invokeinterface_impl(frame *f); // Não implementado
void inst_new_impl(frame *f, u1 indexbyte1, u1 indexbyte2); // Não implementado
void newarray_impl(frame *f ,u1 atype); // Observação do -INT_MAX
void anewarray_impl(frame *f); // Não implementado
void arraylength_impl(frame *f);
void athrow_impl(frame *f); // Não implementado
void checkcast_impl(frame *f); // Não implementado
void instanceof_impl(frame *f); // Não implementado
void monitorenter_impl(frame *f); // Não implementado
void monitorexit_impl(frame *f); // Não implementado
void wide_impl(frame *f); // Não implementado
void multianewarray_impl(frame *f); // Não implementado
void ifnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifnonnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void goto_w_impl(frame *f);
void jsr_w_impl(frame *f);
#endif