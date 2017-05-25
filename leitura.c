#include "leitura.h"

u1* u1Read(FILE *fp,int num){
	int lidos;
	u1 *destino = malloc(sizeof(u1)*num);
	lidos = fread(destino,sizeof(u1),num,fp);
	if(ferror(fp)){
		return NULL;
	}
	
	return destino;
}

u2* u2Read(FILE *fp,int num){
	int lidos;
	u2 *destino = malloc(sizeof(u2)*num);
	lidos = fread(destino,sizeof(u2),num,fp);
	if(ferror(fp)){
		return NULL;
	}
	
	return destino;
}

u4* u4Read(FILE *fp,int num){
	int lidos;
	u4 *destino = malloc(sizeof(u4)*num);
	lidos = fread(destino,sizeof(u4),num,fp);
	if(ferror(fp)){
		return NULL;
	}
	
	return destino;
}