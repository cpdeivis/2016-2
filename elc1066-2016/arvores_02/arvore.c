#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

/*composi��o de um no*/
struct no{
	int info;
	struct no* pai;
	struct no* esq;
	struct no* dir;
};

/*composi��o de uma arvore*/
struct arvore{
	No * raiz;
};

static void arv_libera_no(No * no);
static void arv_insere_no2(No * no, int v);
static void arv_insere (No* pai, No* filho, int dir);

/* fun��o de cria��o */
Arvore * arv_cria (){
	Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
	arv->raiz = NULL;
	return arv;
}

/* fun��o de cria��o */
No * arv_cria_no (int v){
	No * no = (No *) malloc(sizeof(No));
	no->info = v;
	no->esq = NULL;
	no->dir = NULL;
	no->pai = NULL;
	return no;
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_vazia (Arvore * arvore){
	return (arvore->raiz == NULL);
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_no_vazio (No * no){
	//supondo que no n�o seja nulo
	return (no->esq==NULL && no->dir == NULL);
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
No * arv_busca_raiz (Arvore * arvore){
	return (arvore->raiz);
}

No* arv_busca_filho(No * no, int dir){
	if (dir)
		return no->dir;
	else return no->esq;
}

int arv_busca_valor(No * no){
	return no->info;
}

void arv_libera_arvore(Arvore * arv){
	arv_libera_no(arv->raiz);
	free(arv);
}

static void arv_libera_no(No * no){
	if (no==NULL)
		return;
	arv_libera_no(no->esq);
	arv_libera_no(no->dir);
	free(no);
}

void arv_insere_no(Arvore * arv, int v){
	if (arv->raiz==NULL){
		No * filho = arv_cria_no (v);
		arv->raiz = filho;
		return;
	}
	arv_insere_no2(arv->raiz, v);
}

static void arv_insere_no2(No * no, int v){
	if (no==NULL) return;

	if (v < no->info)
	{
		if (no->esq==NULL){
			No * filho = arv_cria_no (v);
			arv_insere(no, filho, 0);
			return;
		}
		arv_insere_no2(no->esq, v);
	}
	else {
		if (no->dir==NULL){
			No * filho = arv_cria_no (v);
			arv_insere(no, filho, 1);
			return;
		}
		arv_insere_no2(no->dir, v);
	}
}

No * arv_busca_no(No * no, int v){
	if (no==NULL)
		return NULL;

	if (no->info==v)
		return no;
	if (v<no->info)
		return arv_busca_no(no->esq, v);

	return arv_busca_no(no->dir, v);
}

/* inser��o de um no filho abaixo de um no pai */
static void arv_insere (No* pai, No* filho, int dir){
	if (dir)
		pai->dir = filho;
	else
		pai->esq = filho;

	filho->pai = pai;
}
