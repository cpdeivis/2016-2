/*tipos exportados*/
typedef struct no No;

typedef struct arvore Arvore;

Arvore * arv_cria ();
No * arv_cria_no (int v);

int arv_vazia (Arvore * arvore);
int arv_no_vazio (No * no);

No * arv_busca_raiz (Arvore * arvore);
void arv_seta_raiz (Arvore * arvore, No * raiz);

void arv_insere (No* pai, No* filho, int dir);
void arv_insere_final (No* pai, No* filho, int dir);

No* arv_busca_filho(No * no, int dir);
int arv_busca_valor(No * no);

No * arv_busca_no(No * no, int v);

void arv_libera_arvore(Arvore * arv);


No * arv_remover_no(No * no, int v);
int arv_remover_no1(No * no, int v);
int arv_remover_no2 (No * no, int v);
