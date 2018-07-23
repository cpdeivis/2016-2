#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"


/*composi��o de um no*/
struct no{
	int info;
	int contagem;
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

static void arv_remove_no3(No * filho);
static int arv_remove_no2(No * no, int v);

static No * encontra_maior(No * no);
static No * encontra_menor(No * no);


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
	no->contagem = 1;
	no->info = v;
	no->esq = NULL;
	no->dir = NULL;
	no->pai = NULL;
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
	else if (v > no->info){
		if (no->dir==NULL){
			No * filho = arv_cria_no (v);
			arv_insere(no, filho, 1);
			return;
		}

		arv_insere_no2(no->dir, v);
	}
	else
		no->contagem++;

}


int arv_remove_no(Arvore * arv, int v){
	if (arv->raiz==NULL) return 0;

	return arv_remove_no2(arv->raiz, v);
}


static int arv_remove_no2(No * no, int v){
	if (no==NULL) return 0;

	if (no->info==v)
	{
		if(no->contagem == 1){
			arv_remove_no3(no);
			return 1;
		}
		no->contagem--;
	}

	if (v < no->info)
		return arv_remove_no2(no->esq, v);
	else return arv_remove_no2(no->dir, v);

}

static void arv_remove_no3(No * filho){

	if (filho->esq==NULL && filho->dir == NULL)
	{
		if (filho->pai->esq==filho)
			filho->pai->esq = NULL;
		else filho->pai->dir = NULL;
		free(filho);
		return;
	}
	if (filho->esq!=NULL) {

		No * maior = encontra_maior(filho->esq);
		filho->info = maior->info;

		arv_remove_no3(maior);
		return;
	}
	else{

		No * menor = encontra_menor(filho->dir);
		filho->info = menor->info;

		arv_remove_no3(menor);
		return;
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

static No * encontra_maior(No * no)
{
	if (no->dir==NULL) return no;
	return encontra_maior(no->dir);
}

static No * encontra_menor(No * no)
{
	if (no->esq==NULL) return no;
	return encontra_menor(no->esq);
}



/* inser��o de um no filho abaixo de um no pai */
static void arv_insere (No* pai, No* filho, int dir)
{
	if (dir)
		pai->dir = filho;
	else
	  pai->esq = filho;

	filho->pai = pai;

}
