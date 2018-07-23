#include "stdlib.h"
#include "stdio.h"
#include "grafo.h"

void imprime_tab (Grafo * grafo, int vertice);
void imprime_tab_ (Grafo * grafo, int vertice1, int vertice2, int prof);
void encontra_mais_popular(Grafo * grafo);

void imprime_tab (Grafo * grafo, int vertice)
{
   imprime_tab_(grafo, vertice, -1, 0);
}


void imprime_tab_ (Grafo * grafo, int vertice1, int vertice2, int prof)
{
   static int tab = 0;

   int x;
   for(x=0;x<tab;x++)
       printf("   ");
   if (vertice2!=-1)
        printf("%d -- %d (%d)\n", vertice2,vertice1, grafo_busca_aresta(grafo, vertice2,vertice1));

   if (prof==3) return;

   tab+=1;
   int num_filhos = 0;
   int * filhos = grafo_busca_vertices_saida(grafo, vertice1, &num_filhos);
   int i = 0;
   for (i=0;i<num_filhos;i++){
       imprime_tab_(grafo, filhos[i], vertice1, prof + 1);
   }

   tab-=1;
}

void encontra_mais_popular(Grafo * grafo){

    int vertice;
    int maior_escore = -1;
    int vertice_escolhido = -1;
    for (vertice=0;vertice<grafo_qtd_vertices(grafo);vertice++){
        int cont = 0;
        int * vertices_entrada = grafo_busca_vertices_entrada(grafo, vertice, &cont);
        int j = 0;
        int escore_total = 0;
        for (j=0;j<cont;j++){
            int escore = grafo_busca_aresta(grafo, vertices_entrada[j], vertice);
            if (escore!=-1){
                escore_total += escore;
            }
        }
        if (escore_total > maior_escore){
            maior_escore = escore_total;
            vertice_escolhido = vertice;

        }
    }
    printf("Vertice mais popular: %d com %d pontos.", vertice_escolhido, maior_escore);

}


int main()
{
   Grafo * grafo = grafo_cria();

   grafo_insere_aresta(grafo, 1, 2, 1);
   grafo_insere_aresta(grafo, 1, 3, 1);
   grafo_insere_aresta(grafo, 1, 4, 1);

   grafo_insere_aresta(grafo, 2, 3, 1);
   grafo_insere_aresta(grafo, 2, 4, 1);
   grafo_insere_aresta(grafo, 3, 4, 1);

   grafo_insere_aresta(grafo, 4, 8, 10);

   grafo_imprime_tab(grafo, 1);

   //imprime_tab(grafo, 1);

    int cont = 0;
    int vertice = 1;
    int * vertices = grafo_busca_vertices_saida(grafo, vertice, &cont);
    int i;
    printf("Os vertices de saida do vertice %d sao:\n", vertice );
    for (i=0;i<cont;i++){
        printf("%d\n", vertices[i]);

    }


   encontra_mais_popular(grafo);

   grafo_libera(grafo);

   return 0;
}
