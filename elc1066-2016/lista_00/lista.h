typedef struct no No;

void lst_cria (No ** inicio);
int lst_vazia (No* inicio);
void lst_insere (No** inicio, int i);
void insere_lista(No** inicio, int v, No * ant);

void lst_insere_ordenado (No** inicio, int v);
void lst_insere_final (No** inicio, int v);
void lst_imprime (No* inicio);
