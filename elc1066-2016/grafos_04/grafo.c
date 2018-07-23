#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"

struct vertice{
	char nome[50];
	int index;
};

/*composi��o de um grafo*/
struct grafo{
	int num_vertices_max;
	int ** matriz;
	int ultimo_ocupado;
	Vertice ** vertices;
};

void grafo_imprime_tab_ (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int prof);
void grafo_libera_matriz (Grafo * grafo);
void grafo_libera_vertices (Grafo * grafo);

Grafo * grafo_cria(int num_vertices_max){
	Grafo * grafo = (Grafo *) malloc(sizeof(Grafo));
	grafo->num_vertices_max = num_vertices_max;
	grafo->matriz = (int**)malloc(sizeof(int *) * num_vertices_max);
	int i = 0;
	for (i=0;i<num_vertices_max;i++){
		int j = 0;
		grafo->matriz[i] = (int*)malloc(sizeof(int) * num_vertices_max);
		for (j=0;j<num_vertices_max;j++){
			grafo->matriz[i][j]=-1;
			}
	}
	grafo->ultimo_ocupado = 0;
	grafo->vertices = (Vertice **) malloc(sizeof (Vertice*) * num_vertices_max);
	return grafo;
}

void grafo_libera (Grafo * grafo){
	grafo_libera_matriz(grafo);
	grafo_libera_vertices(grafo);
	free(grafo);
}

void grafo_libera_matriz (Grafo * grafo){
	int i;
	for (i=0;i<grafo->num_vertices_max;i++){
		free(grafo->matriz[i]);
	}
	free(grafo->matriz);
}

void grafo_libera_vertices (Grafo * grafo){
	int i;
	for (i=0;i<grafo->ultimo_ocupado;i++){
		free(grafo->vertices[i]);
	}
	free(grafo->vertices);
}

int grafo_qtd_vertices (Grafo * grafo){
	return grafo->ultimo_ocupado;
}

Vertice * grafo_cria_vertice(Grafo * grafo, const char nome[]){
	if (grafo->ultimo_ocupado == grafo->num_vertices_max)
		return NULL;

	Vertice * v = (Vertice *)malloc(sizeof(Vertice));
	strcpy(v->nome, nome);

	grafo->vertices[grafo->ultimo_ocupado] = v;
	v->index = grafo->ultimo_ocupado;
	grafo->ultimo_ocupado++;
	return v;
}

Vertice * grafo_retorna_vertice(Grafo * grafo, int indice){
	if (grafo->ultimo_ocupado <= indice)
		return NULL;
	return grafo->vertices[indice];
}

char * grafo_retorna_nome(Vertice * vertice){
	return vertice->nome;
}

int grafo_retorna_indice(Vertice * vertice){
	return vertice->index;
}

void grafo_insere_aresta (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int peso){
	grafo->matriz[vertice1->index][vertice2->index] = peso;
}

int grafo_busca_aresta(Grafo * grafo, Vertice * vertice1, Vertice * vertice2){
	return grafo->matriz[vertice1->index][vertice2->index];
}

Vertice ** grafo_busca_vertices_saida(Grafo * grafo, Vertice * vertice, int * cont){
	int j = 0;
	int num_vertices =0;
	for (j=0;j<grafo->num_vertices_max;j++){
		if (grafo->matriz[vertice->index][j]!=-1){
			num_vertices++;
		}

	}
	Vertice ** vertices = (Vertice **)malloc(sizeof(Vertice * ) * num_vertices);
	int num_vertice = 0;
	for (j=0;j<grafo->num_vertices_max;j++){
		if (grafo->matriz[vertice->index][j]!=-1){
			vertices[num_vertice] = grafo->vertices[j];
			num_vertice++;
		}

	}
	*cont = num_vertices;
	return vertices;
}

Vertice ** grafo_busca_vertices_entrada(Grafo * grafo, Vertice * vertice, int * cont){
	int i = 0;
	int num_vertices =0;
	for (i=0;i<grafo->num_vertices_max;i++){
		if (grafo->matriz[i][vertice->index]!=-1){
			num_vertices++;
		}
	}
	Vertice ** vertices = (Vertice **)malloc(sizeof(Vertice * ) * num_vertices);
	int num_vertice = 0;
	for (i=0;i<grafo->num_vertices_max;i++){
		if (grafo->matriz[i][vertice->index]!=-1){
			vertices[num_vertice] = grafo->vertices[i];
			num_vertice++;
		}

	}
	*cont = num_vertices;
	return vertices;
}

void grafo_imprime_tab (Grafo * grafo, Vertice * vertice){
	grafo_imprime_tab_(grafo, vertice, NULL, 0);
}

void grafo_imprime_tab_ (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int prof){
	static int tab = 0;
	int x;
	for(x=0;x<tab;x++)
		printf(" ");
	if (vertice2!=NULL)
		printf("%s -- %s (%d)\n", vertice2->nome,vertice1->nome, grafo->matriz[vertice2->index][vertice1->index]);

	if (prof==3) return;

	tab+=1;
	int num_vertices = 0;
	Vertice ** vertices = grafo_busca_vertices_saida(grafo, vertice1, &num_vertices);
	int i = 0;
	for (i=0;i<num_vertices;i++){
		grafo_imprime_tab_(grafo, vertices[i], vertice1, prof + 1);
	}
	tab-=1;
}
