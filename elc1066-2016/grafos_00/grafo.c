#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

#define NUM_VERTICES 10


/*composição de um grafo*/
struct grafo{
    int matriz[NUM_VERTICES][NUM_VERTICES];
};


void grafo_imprime_tab_ (Grafo * grafo, int vertice1, int vertice2, int prof);

Grafo * grafo_cria()
{
    Grafo * grafo = (Grafo *) malloc(sizeof(Grafo));
    int i = 0;
    for (i=0;i<NUM_VERTICES;i++){
        int j = 0;
        for (j=0;j<NUM_VERTICES;j++){
            grafo->matriz[i][j]=-1;
            }

    }
    return grafo;
}

void grafo_libera (Grafo * grafo){
    free(grafo);
}

int grafo_qtd_vertices (Grafo * grafo){
    return NUM_VERTICES;
}

int * grafo_busca_vertices_saida(Grafo * grafo, int vertice, int * cont){
    int j = 0;
    int num_vertices =0;
    for (j=0;j<NUM_VERTICES;j++){
        if (grafo->matriz[vertice][j]!=-1){
            num_vertices++;
        }

    }

    int * vertices = (int *)malloc(sizeof(int) * num_vertices);
    int num_vertice = 0;
    for (j=0;j<NUM_VERTICES;j++){
        if (grafo->matriz[vertice][j]!=-1){
            vertices[num_vertice] = j;
            num_vertice++;
        }

    }
    *cont = num_vertices;
    return vertices;

}

int * grafo_busca_vertices_entrada(Grafo * grafo, int vertice, int * cont){
    int i = 0;
    int num_vertices =0;
    for (i=0;i<NUM_VERTICES;i++){
        if (grafo->matriz[i][vertice]!=-1){
            num_vertices++;
        }

    }

    int * vertices = (int *)malloc(sizeof(int) * num_vertices);
    int num_vertice = 0;
    for (i=0;i<NUM_VERTICES;i++){
        if (grafo->matriz[i][vertice]!=-1){
            vertices[num_vertice] = i;
            num_vertice++;
        }

    }
    *cont = num_vertices;
    return vertices;

}

void grafo_insere_aresta (Grafo * grafo, int vertice1, int vertice2, int custo){
    grafo->matriz[vertice1][vertice2] = custo;
}

int grafo_busca_aresta(Grafo * grafo, int vertice1, int vertice2){
    return grafo->matriz[vertice1][vertice2];
}


void grafo_imprime_tab (Grafo * grafo, int vertice)
{
   grafo_imprime_tab_(grafo, vertice, -1, 0);
}


void grafo_imprime_tab_ (Grafo * grafo, int vertice1, int vertice2, int prof)
{
   static int tab = 0;
   int x;
   for(x=0;x<tab;x++)
       printf("   ");
   if (vertice2!=-1)
        printf("%d -- %d (%d)\n", vertice2,vertice1, grafo->matriz[vertice2][vertice1]);

   if (prof==3) return;

   tab+=1;
   int num_vertices = 0;
   int * vertices = grafo_busca_vertices_saida(grafo, vertice1, &num_vertices);
   int i = 0;
   for (i=0;i<num_vertices;i++){
       grafo_imprime_tab_(grafo, vertices[i], vertice1, prof + 1);
   }

   tab-=1;
}




