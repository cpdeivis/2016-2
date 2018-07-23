#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

No * lst_localiza_ultimo_menor(No * inicio, int v);
No * lst_localiza_ultimo(No * inicio);

struct no{
	int info;
	struct no* prox;
};

/* fun��o de cria��o */
void lst_cria (No ** inicio){
	*inicio = NULL;
}

/* retorna 1 se vazia ou 0 se n�o vazia */
int lst_vazia (No* inicio){
	return (inicio == NULL);
}

/* inser��o no in�cio */
void lst_insere (No** inicio, int i){
	No* novo = (No*) malloc(sizeof (No));
	novo->info = i;
	novo->prox = *inicio;
	*inicio = novo;
}

No* lst_localiza_ultimo_menor(No* inicio, int v){
	No* ant = NULL;
	while(inicio != NULL){
		if(inicio->info < v){
			ant = inicio;
		}
		inicio = inicio->prox;
	}
	return ant;
}

void insere_lista(No** inicio, int v, No *ant){
	No* novo = (No*) malloc(sizeof (No));
	novo->info = v;
	/* encadeia elemento */
	if (ant == NULL){		 /* insere elemento no in�cio	*/
		novo->prox = *inicio;
		*inicio = novo;
	}
	else {/* insere elemento no meio da lista */
		novo->prox = ant->prox;
		ant->prox = novo;
	}
}

void lst_insere_ordenado(No** inicio, int v){
	No* ant = lst_localiza_ultimo_menor(*inicio, v);/* ponteiro para elemento anterior	*/

	/* cria novo elemento */
	insere_lista(inicio, v, ant);
}

No* lst_localiza_ultimo(No * inicio){
	No* ult = inicio;
	while(ult->prox != NULL)
		ult = ult->prox;

	return ult;
}

void lst_insere_final (No** inicio, int v){
	No* ant = lst_localiza_ultimo(*inicio);	/* ponteiro para o �ltimo elemento	*/

	/* cria novo elemento */
	insere_lista(inicio, v, ant);
}

void lst_imprime (No* inicio){
	No* p = inicio;
	while (p != NULL) {
		printf("info = %d\n", p->info);
		p = p->prox;
	}
}
