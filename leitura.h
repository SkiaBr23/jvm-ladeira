#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "classFileStruct.h"

u1 * u1Read(FILE *fp);
u2 * u2Read(FILE *fp);
u4 * u4Read(FILE *fp);

ClassFile * lerArquivo (char *);

#endif
