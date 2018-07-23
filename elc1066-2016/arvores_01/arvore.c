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

static void arv_libera_no(No * no);

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

void arv_insere_final (No* pai, No* filho, int dir)
{
	if (dir){
		if (pai->dir==NULL)
			pai->dir = filho;
		else arv_insere_final(pai->dir, filho, dir);
	}

	else{
		if (pai->esq==NULL)
			pai->esq = filho;
		else arv_insere_final(pai->esq, filho, dir);
	}

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

No * arv_busca_no(No * no, int v){

	if (no==NULL)
		return NULL;

	if (no->info == v)
		return no;

	No * aux = arv_busca_no(no->esq, v);
	if (aux!=NULL)
		return aux;
	aux = arv_busca_no(no->dir, v);
	if (aux!=NULL)
		return aux;

	return NULL;
}

No * arv_remover_no(No * no, int v){

	if (no==NULL)  return NULL;

	if (no->info == v)  {
		return no;
	}

	No * aux = arv_remover_no(no->esq, v);
	if (aux!=NULL)  {

		if (no->esq->info == v)
			no->esq = NULL;
		return aux;
	}

	aux = arv_remover_no(no->dir, v);
	if (aux!=NULL)  {

		if (no->dir->info == v)
			no->dir = NULL;
		return aux;
	}
	return NULL;
}

int arv_remover_no1(No * no, int v){

	if (no==NULL)  return 0;

	if (no->info == v)  {
		return 1;
	}

	int aux = arv_remover_no1(no->esq, v);
	if (aux==1)  {
		if (no->esq->info == v)
		{
			arv_libera_no(no->esq);
			no->esq = NULL;
		}
		return 1;
	}

	aux = arv_remover_no1(no->dir, v);
	if (aux==1)  {
		if (no->dir->info == v)
		{
				arv_libera_no(no->dir);
				no->dir = NULL;
		}
		return 1;
	}
	return 0;
}

int arv_remover_no2 (No * no, int v){
	if (no==NULL)  return 0;

	if (no->info == v)  {
		return 1;
	}

	int aux = arv_remover_no2(no->esq, v);
	if (aux==1)  {
		if (no->esq->info == v)
		{
			No* cortando = no->esq;
			//verifica se o nó NÃO TEM exatamente 2 filhos
			if(!(cortando->esq != NULL && cortando->dir != NULL)){
				//atribui o valor do filho a variavel
				//caso tenha algum filho;
				cortando = (cortando->esq != NULL) ? cortando->esq : cortando->dir;
				if(cortando == NULL)
					arv_libera_no(no->esq);
				else
					no->esq = cortando;

				return 1;
			}
			return 0;
		}
		return 1;
	}

	aux = arv_remover_no2(no->dir, v);
	if (aux==1)  {
		if (no->dir->info == v)
		{
			No* cortando = no->dir;
			//verifica se o nó NÃO TEM exatamente 2 filhos
			if(!(cortando->esq != NULL && cortando->dir != NULL)){
				//atribui o valor do filho a variavel
				//caso tenha algum filho;
				cortando = (cortando->esq != NULL) ? cortando->esq : cortando->dir;
				if(cortando == NULL)
					arv_libera_no(no->dir);
				else
					no->dir = cortando;

				return 1;
			}
			return 0;
		}
		return 1;
	}
	return 0;
}
