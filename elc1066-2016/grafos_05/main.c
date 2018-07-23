#include "stdlib.h"
#include "stdio.h"
#include "grafo.h"
#include "limits.h"

struct item{
	Vertice * vertice;
	int aberto;
	int custo;
	struct item  * precedente;
	struct item  * prox_item;
};

typedef struct item Item;

typedef struct lista{
	Item * primeiro_item;
	Item * ultimo_item;
} Lista;

void dijkstra (Grafo * grafo, Vertice * origem);
Lista * inicializa_lista(Grafo * grafo, Vertice * origem);
void atualiza_custo(Grafo * grafo, Lista * lista, Item * item_origem, Vertice * vertice_destino, int custo);
Item * item_menor_custo(Grafo * grafo, Lista * lista);
void exibe_menores_custos(Grafo * grafo, Lista * lista, Vertice * origem);

Lista * cria_lista();
Item * adiciona_item(Lista * lista, Vertice * vertice);

void dijkstra (Grafo * grafo, Vertice * origem){
	Lista * lista = inicializa_lista(grafo, origem);
	Item * it_menor_custo = NULL;
	while (1){
		it_menor_custo = item_menor_custo(grafo, lista);
		if (it_menor_custo==NULL)
			break;
		int cont = 0;
		Vertice ** vertices_destino = grafo_busca_vertices_saida(grafo, it_menor_custo->vertice, &cont);
		int i = 0;
		for (i=0;i<cont;i++){
			int custo = grafo_busca_aresta(grafo, it_menor_custo->vertice,vertices_destino[i]);
			atualiza_custo(grafo, lista,it_menor_custo, vertices_destino[i], custo + it_menor_custo->custo);
		}
	}
	exibe_menores_custos(grafo, lista, origem);
}

Lista * inicializa_lista(Grafo * grafo, Vertice * origem){
	Lista * lista = cria_lista();
	int indice_vertice = 0;
	for (indice_vertice=0;indice_vertice<grafo_qtd_vertices(grafo);indice_vertice++){
		Vertice * v = grafo_retorna_vertice(grafo, indice_vertice);
		Item * item = adiciona_item(lista, v);
		item->aberto = 1;
		if (v == origem)
			item->custo = 0;
		else item->custo = INT_MAX ;
	}
	return lista;
}

Item * item_menor_custo(Grafo * grafo, Lista * lista){
	Item * it_menor_custo = NULL;
	int menor_custo = INT_MAX;
	Item * item = lista->primeiro_item;
	while (item!=NULL){
		if (item->aberto && item->custo< menor_custo){
			it_menor_custo = item;
			menor_custo = item->custo;
		}
		item = item->prox_item;
	}
	if (it_menor_custo!=NULL)
		it_menor_custo->aberto = 0;
	return it_menor_custo;
}

void atualiza_custo(Grafo * grafo, Lista * lista, Item * item_origem, Vertice * vertice_destino, int custo){
	Item * item_destino = lista->primeiro_item;
	while (item_destino!=NULL){
		if (item_destino->vertice == vertice_destino && item_destino->custo>custo){
			item_destino->custo = custo;
			item_destino->precedente = item_origem;
		}
		item_destino = item_destino->prox_item;
	}

}

void exibe_menores_custos(Grafo * grafo, Lista * lista, Vertice * origem){
	printf("Menores Custos\n");
	Item * inicial = lista->primeiro_item;
	while(inicial != NULL){
		printf("De %s para %s o menor custo é %d\n", grafo_retorna_nome(origem), grafo_retorna_nome(inicial->vertice), inicial->custo);
		inicial = inicial->prox_item;
	}
}

Lista * cria_lista(){
	Lista * lista = (Lista*) malloc(sizeof(Lista));
	lista->primeiro_item = NULL;
	lista->ultimo_item = NULL;
	return lista;
}

Item * adiciona_item(Lista * lista, Vertice * vertice){
	Item * item = (Item *)malloc(sizeof(Item));
	item->vertice = vertice;
	item->prox_item = NULL;
	item->precedente = NULL;

	if (lista->primeiro_item==NULL){
		lista->primeiro_item = item;
		lista->ultimo_item = item;
	}
	else{
		lista->ultimo_item->prox_item = item;
		lista->ultimo_item = item;
	}
	return item;

}

int main(int argc, char **argv){
	Grafo * grafo = grafo_cria(10);

	Vertice * vSantaMaria = grafo_cria_vertice(grafo, "Santa Maria");
	Vertice * vRosario = grafo_cria_vertice(grafo, "Rosario do Sul");
	Vertice * vSaoSepe = grafo_cria_vertice(grafo, "Sao Sepe");
	Vertice * vSaoVicente = grafo_cria_vertice(grafo, "Sao Vicente");
	Vertice * vSaoPedro = grafo_cria_vertice(grafo, "Sao Pedro");
	Vertice * vSaoGabriel = grafo_cria_vertice(grafo, "Sao Gabriel");

	grafo_insere_aresta(grafo, vSantaMaria, vRosario, 430); //230
	grafo_insere_aresta(grafo, vSantaMaria, vSaoPedro, 60);
	grafo_insere_aresta(grafo, vSaoPedro, vSaoVicente, 50);
	grafo_insere_aresta(grafo, vSaoVicente, vRosario, 130);
	grafo_insere_aresta(grafo, vSantaMaria, vSaoSepe, 80);
	grafo_insere_aresta(grafo, vSaoSepe, vSaoGabriel, 140);
	grafo_insere_aresta(grafo, vSaoGabriel, vRosario, 60);

	dijkstra(grafo, vSantaMaria);

	Grafo * grafo2 = grafo_cria(10);

	Vertice * vA = grafo_cria_vertice(grafo2, "A");
	Vertice * vB = grafo_cria_vertice(grafo2, "B");
	Vertice * vC = grafo_cria_vertice(grafo2, "C");
	Vertice * vD = grafo_cria_vertice(grafo2, "D");
	Vertice * vE = grafo_cria_vertice(grafo2, "E");
	Vertice * vF = grafo_cria_vertice(grafo2, "F");

	grafo_insere_aresta(grafo2, vA, vB, 2);
	grafo_insere_aresta(grafo2, vA, vC, 6);
	grafo_insere_aresta(grafo2, vA, vD, 5);
	grafo_insere_aresta(grafo2, vB, vC, 2);
	grafo_insere_aresta(grafo2, vC, vE, 1);
	grafo_insere_aresta(grafo2, vD, vE, 3);
	grafo_insere_aresta(grafo2, vD, vF, 5);
	grafo_insere_aresta(grafo2, vE, vF, 2);

	dijkstra(grafo2, vA);

	grafo_libera(grafo);
	return 0;
}
