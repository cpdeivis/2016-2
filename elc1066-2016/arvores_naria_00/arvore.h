typedef struct no No;


typedef struct arvore Arvore;

Arvore * arv_cria_arvore();
No * arv_cria_no(int valor);

void arv_seta_raiz(Arvore * arv, No * raiz);
No* arv_pega_raiz(Arvore * arv);

int arv_busca_valor_no(No* no);
void arv_seta_valor_no(No * no, int valor);


void arv_insere_no(No * pai, No * filho);

No* arv_busca_filho(No * no);
No* arv_busca_irmao(No * no);

