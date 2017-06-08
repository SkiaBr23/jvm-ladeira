#include <stdio.h>

/* Essa lista foi implementada utilizando strings. Substituir a string pelo elemento que será utilizado */
struct lista{
	char *string;
	struct lista *prox,*ant;
};
typedef struct lista Lista;

Lista* CriarLista();
Lista* InserirInicio(Lista *lis, char *string); 
Lista* InserirFim(Lista *lis, char *string);
Lista* RemoverInicio(Lista *lis);
Lista* RemoverFim(Lista *lis);
Lista* RemoverElemento(Lista *lis, char *string);
Lista* BuscarElemento(Lista *lis, char *string);
Lista* BuscarPosicao(Lista *lis, int posicao);
Lista* InserirPosicao(Lista *lis, char *string, int posicao);
Lista* RemoverPosicao(Lista *lis, int posicao);
void ImprimirLista(Lista *lis);
void LiberarLista(Lista *lis);