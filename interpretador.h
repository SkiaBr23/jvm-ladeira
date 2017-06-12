#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "instrucoes.h"

void iload_impl(u1 index, frame *f);
void aconst_null_impl(frame *f);
void iconst_m1_impl(u1 constant, frame *f);
void iconst_0_impl(u1 constant, frame *f);
void iconst_1_impl(u1 constant, frame *f);
void iconst_2_impl(u1 constant, frame *f);
void iconst_3_impl(u1 constant, frame *f);
void iconst_4_impl(u1 constant, frame *f);
void iconst_5_impl(u1 constant, frame *f);
void lconst_0_impl(u1 constant, frame *f);
void lconst_1_impl(u1 constant, frame *f);
void fconst_0_impl(u1 constant, frame *f);
void fconst_1_impl(u1 constant, frame *f);
void fconst_2_impl(u1 constant, frame *f);
void dconst_0_impl(u1 constant, frame *f);
void dconst_1_impl(u1 constant, frame *f);
void bipush_impl(u1 byte, frame *f);
void sipush_impl(u1 byte1, u1 byte2, frame *f);

#endif