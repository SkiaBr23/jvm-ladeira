#include "leitura.h"

u1 u1Read(FILE *fp){
	u1 destino;
	if (fread(&destino,sizeof(u1),1,fp) != 1) {
		return MAXU1;
	} else {
		return destino;
	}
}

u2 u2Read(FILE *fp){
	u2 destino;
	u1 lowByte, highByte;
	highByte = u1Read(fp);
	lowByte = u1Read(fp);

	if(highByte != MAXU1 && lowByte != MAXU1) {
		destino = ((highByte)<<8) | ((lowByte));
		return destino;
	} else {
		return MAXU2;
	}
}

u4 u4Read(FILE *fp){
	u4 destino;
	u1 byteZero, byteUm, byteDois, byteTres;
	byteTres = u1Read(fp);
	byteDois = u1Read(fp);
	byteUm = u1Read(fp);
	byteZero = u1Read(fp);
	if(byteTres != MAXU1 && byteDois != MAXU1 && byteUm != MAXU1 && byteZero != MAXU1){
		destino = ((byteTres)<<24) | ((byteDois)<<16) | ((byteUm)<<8) | ((byteZero));
		return destino;
	} else {
		return MAXU4;
	}
}

ClassFile* lerArquivo (char * nomeArquivo) {
	ClassFile *arquivoClass = NULL;
	FILE * fp = fopen(nomeArquivo,"rb");
	// Se o ponteiro do arquivo for nulo, encerrar o programa e dar erro
	if (fp == NULL) {
		printf("Ocorreu um problema ao abrir o arquivo, finalizando programa!\n");
		exit(1);
	} else {
		arquivoClass = (ClassFile*) malloc(sizeof(ClassFile));

		arquivoClass->magic = u4Read(fp); 
		arquivoClass->minor_version = u2Read(fp);
		arquivoClass->major_version = u2Read(fp);
		arquivoClass->constant_pool_count = u2Read(fp); 

		printf("%x\n",arquivoClass->magic);
		printf("%x\n",arquivoClass->minor_version);
		printf("%x\n",arquivoClass->major_version);
		printf("%x\n",arquivoClass->constant_pool_count);

		fclose(fp);

		return arquivoClass;
	}
}
