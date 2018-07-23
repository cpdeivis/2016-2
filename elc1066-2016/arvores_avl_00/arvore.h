/*tipos exportados*/
typedef struct no No;

typedef struct arvore Arvore;

Arvore * arv_cria ();
No * arv_cria_no (int v);

int arv_vazia (Arvore * arvore);
int arv_no_vazio (No * no);

No * arv_busca_raiz (Arvore * arvore);

No* arv_busca_filho(No * no, int dir);
int arv_busca_valor(No * no);

No * arv_busca_no(No * no, int v);

void arv_libera_arvore(Arvore * arv);

void arv_insere_no(Arvore * arv, int v);

int arv_remove_no(Arvore * arv, int v);
