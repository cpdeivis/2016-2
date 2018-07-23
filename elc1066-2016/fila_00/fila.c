#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fila.h"

/* n� da lista para armazenar valores */
struct no {
	int info;
	struct no* prox;
};
typedef struct no No;

/* estrutura da fila */
struct fila {
	No* ini;
	No* fim;
};

Fila* fila_cria (void)
{
	Fila* f = (Fila*) malloc(sizeof(Fila));
	f->ini = NULL;
	f->fim = NULL;
	return f;
}

int fila_vazia (Fila* f)
{
	 return (f->ini==NULL);
}

void fila_insere (Fila* f, int v)
{
	No* n = (No*) malloc(sizeof (No));
	n->info = v;					/* armazena informa��o				*/
	n->prox = NULL;		/* novo n� passa a ser o �ltimo		*/
	if (f->fim != NULL)	 /* verifica se lista n�o estava vazia */
		f->fim->prox = n;
	else	 /* fila estava vazia */
		f->ini = n;
	f->fim = n;	/* fila aponta para novo elemento	  */
}

int fila_retira (Fila* f)
{
	if (fila_vazia(f)) {
		printf("Fila vazia.\n");
		exit(1);/* aborta programa */
	 }

	No* t = f->ini;
	int v = t->info;
	f->ini = t->prox;
	if (f->ini == NULL)	/* verifica se fila ficou vazia */
		f->fim = NULL;
	free(t);
	return v;
}

void fila_libera (Fila* f)
{
	No* q = f->ini;
	while (q!=NULL) {
		No* t = q->prox;
		free(q);
		q = t;
	}
	free(f);
}

int fila_tamanho (Fila* f){
	int size = 0;
	if(!fila_vazia(f)){
		No* aux = f->ini;
		do {
			aux = aux->prox;
			size++;
		} while(aux != f->fim);
	}
	return size;
}
