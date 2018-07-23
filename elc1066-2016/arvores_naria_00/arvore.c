#include <stdlib.h>
#include "arvore.h"


static No * ultimo_filho(No* prim);

typedef struct no{
	int valor;
	struct no * esq;
	struct no * viz;
} No;

typedef struct arvore{
	No * raiz;
} Arvore;

Arvore * arv_cria_arvore()
{
	Arvore * arv = (Arvore*)malloc(sizeof(Arvore));
	arv->raiz = NULL;
	return arv;
}

No * arv_cria_no(int valor){
	No * no = (No*)malloc(sizeof(No));
	no->esq = NULL;
	no->viz = NULL;
	no->valor = valor;
	return no;
}

void arv_seta_raiz(Arvore * arv, No * raiz)
{
	arv->raiz = raiz;
}

No* arv_pega_raiz(Arvore * arv)
{
	return arv->raiz;
}

int arv_busca_valor_no(No* no){

	return no->valor;
}

void arv_seta_valor_no(No * no, int valor)
{
	no->valor = valor;
}

void arv_insere_no(No * pai, No * filho)
{
	No * ultimo = ultimo_filho(pai);

	if (ultimo==NULL)
		pai->esq = filho;
	else ultimo->viz = filho;

}

static No * ultimo_filho(No* no)
{
	No * filho = no->esq;
	No * ant = NULL;
	while (filho!=NULL){
		ant = filho;
		filho = filho->viz;
	}

	return ant;
}

No* arv_busca_filho(No * no)
{
	return no->esq;
}

No* arv_busca_irmao(No * no)
{
	return no->viz;
}
