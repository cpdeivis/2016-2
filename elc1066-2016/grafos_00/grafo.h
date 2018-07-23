typedef struct grafo Grafo;

/*funções para criação/remoção de um grafo*/
Grafo * grafo_cria ();
void grafo_libera (Grafo * grafo);

/*funções para manipulação dos vértices de um grafo*/
int grafo_qtd_vertices (Grafo * grafo);
int * grafo_busca_vertices_saida(Grafo * grafo, int vertice, int * cont);
int * grafo_busca_vertices_entrada(Grafo * grafo, int vertice, int * cont);

/*funções para manipulação das arestas do grafo*/
void grafo_insere_aresta (Grafo * grafo, int vertice1, int vertice2, int custo);
int grafo_busca_aresta(Grafo * grafo, int vertice1, int vertice2);

/*função para impressão tabulada a partir de um vértice*/
void grafo_imprime_tab (Grafo * grafo, int vertice);
