#include "leitura.h"

u1* u1Read(FILE *fp,int num){
	u1 *destino = malloc(sizeof(u1)*num);
	fread(destino,sizeof(u1),num,fp);
	if(ferror(fp)){
		return NULL;
	}

	return destino;
}

u2* u2Read(FILE *fp,int num){
	u2 *destino = malloc(sizeof(u2)*num);
	fread(destino,sizeof(u2),num,fp);
	if(ferror(fp)){
		return NULL;
	}

	return destino;
}

u4* u4Read(FILE *fp,int num){
	u4 *destino = malloc(sizeof(u4)*num);
	fread(destino,sizeof(u4),num,fp);
	if(ferror(fp)){
		return NULL;
	}

	return destino;
}
