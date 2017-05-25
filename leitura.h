#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

u1* u1Read(FILE *fp, int num);
u2* u2Read(FILE *fp, int num);
u4* u4Read(FILE *fp, int num);

#endif