typedef struct grafo Grafo;
typedef struct vertice Vertice;

Grafo * grafo_cria (int num_vertices_max);
void grafo_libera (Grafo * grafo);

int grafo_qtd_vertices (Grafo * grafo);

Vertice * grafo_cria_vertice(Grafo * grafo, const char nome[]);
Vertice * grafo_retorna_vertice(Grafo * grafo, int indice);

char * grafo_retorna_nome(Vertice * vertice);
int grafo_retorna_indice(Vertice * vertice);

void grafo_insere_aresta (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int peso);
int grafo_busca_aresta(Grafo * grafo, Vertice * vertice1, Vertice * vertice2);

Vertice ** grafo_busca_vertices_saida(Grafo * grafo, Vertice * vertice, int * cont);
Vertice ** grafo_busca_vertices_entrada(Grafo * grafo, Vertice * vertice, int * cont);

void grafo_imprime_tab (Grafo * grafo, Vertice * vertice);
