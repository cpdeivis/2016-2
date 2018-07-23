#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

static No * lst_localiza_ultimo_menor(No * inicio, int v);
static No * lst_localiza_ultimo(No * inicio);
static void insere_lista(No** inicio, int v, No * ant);

struct no{
	int info;
	struct no* prox;
};

/* fun��o de cria��o */
void lst_cria (No ** inicio)
{
	 *inicio = NULL;
}

void lst_libera (No** inicio)
{
	No* p = *inicio;
	while (p != NULL) {
		No* t = p->prox;
		free(p);
		p = t;
	}
 *inicio = NULL;
}

/* retorna 1 se vazia ou 0 se n�o vazia */
int lst_vazia (No* inicio)
{
	return (inicio == NULL);
}

/* inser��o no in�cio */
void lst_insere_comeco (No** inicio, int i)
{
	No* novo = (No*) malloc(sizeof (No));
	novo->info = i;
	novo->prox = *inicio;
	*inicio = novo;
}

void lst_insere_ordenado (No** inicio, int v)
{
	No* ant = lst_localiza_ultimo_menor(*inicio, v);	/* ponteiro para elemento anterior	*/
	insere_lista(inicio, v, ant);
}

void lst_insere_final (No** inicio, int v)
{
	No* ant = lst_localiza_ultimo(*inicio);	/* ponteiro para o �ltimo elemento	*/
	insere_lista(inicio, v, ant);
}

static void insere_lista(No** inicio, int v, No * ant)
{
	 /* cria novo elemento */
	No* novo = (No*) malloc(sizeof (No));
	novo->info = v;
	/* encadeia elemento */
	if (ant == NULL){			/* insere elemento no in�cio	*/
		novo->prox = *inicio;
		*inicio = novo;
	}
	else {			/* insere elemento no meio da lista */
		novo->prox = ant->prox;
		ant->prox = novo;
	}

}

static No * lst_localiza_ultimo_menor(No * inicio, int v)
{
	No* p = inicio;	/* ponteiro para percorrer a lista	*/
	No* ant = NULL;	/* ponteiro para elemento anterior	*/
	/* procura posi��o de inser��o */
	while (p != NULL && p->info < v){
		ant = p;
		p = p->prox;
	}
	return ant;

}

static No * lst_localiza_ultimo(No * inicio)
{
	No* p = inicio;	/* ponteiro para percorrer a lista	*/
	No* ant = NULL;	/* ponteiro para elemento anterior	*/
	/* procura posi��o de inser��o */
	while (p != NULL){
		ant = p;
		p = p->prox;
	}
	return ant;

}

No* lst_busca (No* inicio, int v)
{
	No* p = inicio;
	while (p!=NULL)
	{
		if (p->info ==  v)
			return  p;
		p = p->prox;
	}
	return NULL;
}

No* lst_busca_rec (No* inicio, int v){
	if(!lst_vazia(inicio))
	{
		if(inicio->info == v)
			return inicio;
		else
			return lst_busca_rec(inicio->prox, v);
	}
	else{
		printf("O inicio informado é nulo | não encontrado\n");
		return inicio;
	}
}

void lst_imprime (No* inicio)
{
	No* p = inicio;
	while (p != NULL) {
		printf("info = %d\n", p->info);
		p = p->prox;
	}
}

void lst_imprime_rec (No* no)
{
	if (!lst_vazia(no)){
		printf("info: %d\n",  no->info);

		lst_imprime_rec (no->prox);
	}
}

int lst_conta_menores (No* inicio, int v)
{
	No* p = inicio;
	int cont = 0;
	while (p!=NULL)
	{
		  if (p->info <  v)
	cont++;
		  p = p->prox;
	}
	return cont;
}

void lst_conta_menores_rec (No* inicio, int v, int* cont){
	if(!lst_vazia(inicio)){
		if(inicio->info < v)
			(*cont)++;

		lst_conta_menores_rec(inicio->prox, v, cont);
	}
}

No* lst_localiza_ultimo_menor_rec (No* ant, No* inicio, int v){
	if(!lst_vazia(inicio)){
		if(inicio->info < v && inicio->info > ant->info){
			ant = inicio;
			//ant->prox = NULL;
		}
		return !lst_vazia(inicio->prox) ? lst_localiza_ultimo_menor_rec(ant, inicio->prox, v) : ant;
	}
	else{
		printf("O inicio informado é nulo | não encontrado\n");
		return inicio;
	}
}

/*No * lst_localiza_ultimo_rec (No* ant, No * inicio){
	if(!lst_vazia(inicio)){
		if(lst_vazia(inicio->prox))
			return ant;
		else
		{

		}
	}
	else{
		printf("O inicio informado é nulo | não encontrado\n");
		return inicio;
	}
}*/

void lst_retira (No** inicio, int v)
{
	No* ant = NULL;
	No* p = *inicio;

	while (p != NULL && p->info != v){
		ant = p;
		p = p->prox;
	}

	if (p == NULL)	return;

	if (ant == NULL)
		*inicio = p->prox;
	else
		ant->prox = p->prox;

	free(p);
}

/* Fun��o retira recursiva */
void lst_retira_rec (No** no, int v)
{
	if (!lst_vazia(*no)) {
		/* verifica se esse � o elemento a retirar */
		if ((*no)->info == v) {
			No* t = *no;		/* tempor�rio para poder liberar */
			*no = (*no)->prox;
			free(t);
			}
		else {	/* necess�rio procurar no pr�ximo elemento*/
			lst_retira_rec (&(*no)->prox,v);
		}
	}
}

int lst_igual (No* n1, No* n2)
{
	No* p1;	/* ponteiro para percorrer n1 */
	No* p2;	/* ponteiro para percorrer n2 */
	p1=n1, p2=n2;
	while (p1 != NULL && p2 != NULL) {
		 if (p1->info != p2->info)
	return 0;
		 p1 = p1->prox;
		 p2 = p2->prox;
	}
	return p1==p2;
}

int lst_igual_rec (No* n1, No* n2)
{
	if (n1 == NULL && n2 == NULL)
		return 1;
	else if (n1 == NULL || n2 == NULL)
		return 0;
	else
		return n1->info == n2->info && lst_igual (n1->prox, n2->prox);
}
