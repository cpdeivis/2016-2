typedef struct no No;

void lst_cria(No ** inicio);
No* lst_busca (No* inicio, int v);
void lst_insere (No** inicio, int v);
void lst_insere_final (No** inicio, int v);
void lst_retira (No** inicio, int v);
void lst_imprime(No * inicio);
void lst_imprime_para_tras(No * inicio);
