#include "leitura.h"

u1 * u1Read(FILE *fp){
	u1 * destino = malloc(sizeof(u1));
	if (fread(destino,sizeof(u1),1,fp) != 1) {
		return NULL;
	} else {
		return destino;
	}
}

u2 * u2Read(FILE *fp){
	u2 * destino = malloc(sizeof(u2));
	u2 * lowByte, * highByte;
	highByte = u1Read(fp);
	lowByte = u1Read(fp);

	if(highByte != NULL && lowByte != NULL) {
		*destino = ((*highByte)<<8) | ((*lowByte));
		return destino;
	} else {
		return NULL;
	}
}

u4 * u4Read(FILE *fp){
	u4 * destino = malloc(sizeof(u4));
	u4 * byteZero, * byteUm, * byteDois, * byteTres;
	byteTres = u1Read(fp);
	byteDois = u1Read(fp);
	byteUm = u1Read(fp);
	byteZero = u1Read(fp);
	if(byteTres != NULL && byteDois != NULL && byteUm != NULL && byteZero != NULL){
		*destino = ((*byteTres)<<24) | ((*byteDois)<<16) | ((*byteUm)<<8) | ((*byteZero));
		return destino;
	} else {
		return NULL;
	}
}

ClassFile * lerArquivo (char * nomeArquivo) {
	ClassFile * arquivoClass = NULL;
	FILE * fp = fopen(nomeArquivo,"rb");
	if (fp == NULL) {
		printf("Ocorreu um problema ao abrir o arquivo, finalizando programa!\n");
		exit(1);
	} else {
		return arquivoClass;
	}
}
