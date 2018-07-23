#include "stdlib.h"
#include "stdio.h"
#include "grafo.h"
#include "limits.h"

struct item{
	Vertice * vertice;
	struct item  * prox_item;
};

typedef struct item Item;

typedef struct lista{
	Item * primeiro_item;
	Item * ultimo_item;
} Lista;

void dfs(Grafo * grafo, Vertice * vertice);

void detecta_ciclos (Grafo * grafo);
int detecta_ciclos_(Grafo * grafo, Vertice * vertice, Lista * lista_branca, Lista * lista_cinza, Lista * lista_negra, int * mapa);

int * inicializa_mapa(Grafo * grafo);
void imprime_ciclo(Grafo * grafo, int * mapa, int inicio);
void detecta_ciclos_em_vertice (Grafo * grafo, Vertice * origem);

Lista * cria_lista();
Item * adiciona_item(Lista * lista, Vertice * vertice);
Item * busca_item(Lista * lista, Vertice * vertice);

int lista_vazia(Lista * lista);
void alimenta_lista(Grafo * grafo, Lista * lista);
void remove_item(Lista * lista, Vertice * vertice);

int * inicializa_mapa(Grafo * grafo){
	if(grafo == NULL)
		return NULL;
	int qtd = grafo_qtd_vertices(grafo), i;
	int * vetor = (int *)malloc(sizeof(int) * qtd);
	for(i = 0; i < qtd; i++){
		vetor[i] = -1;
	}
	return vetor;
}

void detecta_ciclos (Grafo * grafo){
	printf("\nVerificacao de amizades\n");

	int ok = 1;
	Lista * lista_branca = cria_lista();
	Lista * lista_cinza = cria_lista();
	Lista * lista_negra = cria_lista();

	int * mapa = inicializa_mapa(grafo);
	alimenta_lista(grafo, lista_branca);

	while (!lista_vazia(lista_branca)){
		Item * item = lista_branca->primeiro_item;
		int resp = detecta_ciclos_(grafo, item->vertice,lista_branca, lista_cinza, lista_negra, mapa);
		if (resp!=-1){
			printf("Encontrada amizade reciproca (que pode ser indireta) : ");
			imprime_ciclo(grafo, mapa, resp);
			ok = 1;
			//return;
		}
	}
	if (!ok)
		printf("Nao existe amizade reciproca");
	return;
}

void detecta_ciclos_em_vertice (Grafo * grafo, Vertice * origem){
	printf("\nVerificacao de amizades reciprocas com %s\n", grafo_retorna_nome(origem));

	int ok = 0;
	Lista * lista_branca = cria_lista();
	Lista * lista_cinza = cria_lista();
	Lista * lista_negra = cria_lista();
	int * mapa = inicializa_mapa(grafo);
	//alimenta_lista(grafo, lista_branca);
	adiciona_item(lista_branca, origem);
	while (!lista_vazia(lista_branca)){
		Item * item = lista_branca->primeiro_item;
		int resp = detecta_ciclos_(grafo, item->vertice,lista_branca, lista_cinza, lista_negra, mapa);
		if (resp!=-1){
			printf("Encontrada amizade reciproca (que pode ser indireta) : ");
			imprime_ciclo(grafo, mapa, resp);
			ok = 1;
			//return;
		}
	}
	if (!ok)
		printf("Nao existe amizade reciproca");

	printf("\n");
	return;
}

int detecta_ciclos_(Grafo * grafo, Vertice * vertice, Lista * lista_branca, Lista * lista_cinza, Lista * lista_negra, int * mapa){
	if (busca_item(lista_negra, vertice)!=NULL)
		return -1;

	if (busca_item(lista_cinza, vertice)!=NULL)
		return grafo_retorna_indice(vertice);

	adiciona_item(lista_cinza, vertice);
	remove_item(lista_branca, vertice);

	int cont = 0;
	Vertice ** vertices_destino = grafo_busca_vertices_saida(grafo, vertice, &cont);
	int i = 0;
	for (i=0;i<cont;i++){
		mapa[ grafo_retorna_indice(vertices_destino[i])] = grafo_retorna_indice(vertice);
		int resp = detecta_ciclos_(grafo, vertices_destino[i], lista_branca, lista_cinza, lista_negra, mapa);
		if (resp != -1)
			return resp;
	}
	remove_item(lista_cinza, vertice);
	adiciona_item(lista_negra, vertice);

	return -1;
}

void dfs(Grafo * grafo, Vertice * vertice){

	int cont = 0;
	Vertice ** vertices_destino = grafo_busca_vertices_saida(grafo, vertice, &cont);
	int i = 0;
	for (i=0;i<cont;i++){
		printf("fui de %s para %s\n",grafo_retorna_nome(vertice), grafo_retorna_nome(vertices_destino[i]));
		dfs(grafo, vertices_destino[i]);
	}
	if (cont==0)
		printf("em %s eu fiquei\n",grafo_retorna_nome(vertice));
}

void imprime_ciclo(Grafo * grafo, int * mapa, int inicio){
	int aux = inicio;
	Vertice * vertice = NULL;
	do {
		vertice = grafo_retorna_vertice(grafo, aux);
		printf("%s - ", grafo_retorna_nome(vertice));
		aux = mapa[aux];
	} while(aux != inicio);
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

Item * busca_item(Lista * lista, Vertice * vertice){
	Item * item = lista->primeiro_item;
	while (item!=NULL){
		if (item->vertice == vertice)
			return item;
		item = item->prox_item;
	}
	return NULL;
}

int lista_vazia(Lista * lista){
	return (lista->primeiro_item==NULL);
}

void alimenta_lista(Grafo * grafo, Lista * lista){
	int indice_vertice = 0;
	for (indice_vertice=0;indice_vertice<grafo_qtd_vertices(grafo);indice_vertice++){
		Vertice * v = grafo_retorna_vertice(grafo, indice_vertice);

		adiciona_item(lista, v);
	}
}

void remove_item(Lista * lista, Vertice * vertice){
	Item * item = lista->primeiro_item;
	Item * anterior = NULL;
	while (item!=NULL){
		if (item->vertice == vertice)
		{
			if (anterior==NULL){ //primeiro item
				lista->primeiro_item = item->prox_item;
			}
			else{
				anterior->prox_item = item->prox_item;
			}
			if (item->prox_item==NULL){ //ultimo item
				lista->ultimo_item = anterior;
			}
			return;
		}
		anterior = item;
		item = item->prox_item;
	}

}

int main(){
	Grafo * grafo = grafo_cria(10);
	Vertice * vMauro = grafo_cria_vertice(grafo, "Mauro");
	Vertice * vAna = grafo_cria_vertice(grafo, "Ana");
	Vertice * vPedro = grafo_cria_vertice(grafo, "Pedro");
	Vertice * vPaulo = grafo_cria_vertice(grafo, "Paulo");
	Vertice * vLuisa = grafo_cria_vertice(grafo, "Luisa");
	Vertice * vGabriel = grafo_cria_vertice(grafo, "Gabriel");


	grafo_insere_aresta(grafo, vMauro, vAna, 0);
	grafo_insere_aresta(grafo, vMauro, vLuisa, 0);
	grafo_insere_aresta(grafo, vLuisa, vPaulo, 0);
	grafo_insere_aresta(grafo, vPaulo, vAna, 0);
	grafo_insere_aresta(grafo, vMauro, vPedro, 0);
	grafo_insere_aresta(grafo, vPedro, vGabriel, 0);
	grafo_insere_aresta(grafo, vGabriel, vAna, 0);

	grafo_insere_aresta(grafo, vPaulo, vMauro, 0);//ciclo

	detecta_ciclos(grafo);

	detecta_ciclos_em_vertice(grafo, vAna);
	//dfs(grafo, vMauro);

	grafo_libera(grafo);

	return 0;
}
