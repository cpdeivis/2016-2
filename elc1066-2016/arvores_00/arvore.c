#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"


/*composi��o de um no*/
struct no{
	int info;
	struct no* esq;
	struct no* dir;
};

/*composi��o de uma arvore*/
struct arvore{
	No * raiz;
};


/* fun��o de cria��o */
Arvore * arv_cria ()
{
	Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
	arv->raiz = NULL;
	return arv;
}


/* fun��o de cria��o */
No * arv_cria_no (int v)
{
	No * no = (No *) malloc(sizeof(No));
	no->info = v;
	no->esq = NULL;
	no->dir = NULL;
	return no;
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_vazia (Arvore * arvore)
{
	return (arvore->raiz == NULL);
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_no_vazio (No * no)
{
	//supondo que no n�o seja nulo
	return (no->esq==NULL && no->dir == NULL);
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
No * arv_busca_raiz (Arvore * arvore)
{
	return (arvore->raiz);
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
void arv_seta_raiz (Arvore * arvore, No * raiz)
{
	arvore->raiz = raiz;
}


/* inser��o de um no filho abaixo de um no pai */
void arv_insere (No* pai, No* filho, int dir)
{
	if (dir)
		pai->dir = filho;
	else
		pai->esq = filho;
}

void arv_insere_final (No* pai, No* filho, int dir){
	if(dir)
		if(pai->dir != NULL)
			arv_insere_final(pai->dir, filho, dir);
		else
			pai->dir = filho;
	else
		if(pai->esq != NULL)
			arv_insere_final(pai->esq, filho, dir);
		else
			pai->esq = filho;
}

void arv_imprime (No* pai)
{
	if (pai==NULL)
		return;

	printf("\n%d", pai->info);
	arv_imprime(pai->esq);
	arv_imprime(pai->dir);

}

static int nivel = 0;
void arv_imprime_tab(No* pai, char* lado){
	if (pai==NULL){
		return;
	}
	printf("\n");
	nivel++;
	for (int i = 0; i < nivel; i++)
		printf("---");
	printf("%d(%s)", pai->info, lado);
	arv_imprime_tab(pai->esq, "esq");
	arv_imprime_tab(pai->dir, "dir");
	nivel--;
}

No* arv_busca_filho(No* no, int dir){
	if(no != NULL){
		if(dir == 0)
			return no->esq;
		else
			return no->dir;
	}
	return NULL;
}
int arv_busca_valor(No* no){
	if(no != NULL){
		return no->info;
	}
	return -1;
}
