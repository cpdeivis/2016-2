typedef struct no No;

void lst_cria (No ** inicio);
void lst_libera (No** inicio);
int lst_vazia (No* inicio);

void lst_insere_comeco (No** inicio, int i);
void lst_insere_ordenado (No** inicio, int v);
void lst_insere_final (No** inicio, int v);

No* lst_busca (No* inicio, int v);
No* lst_busca_rec (No* inicio, int v);

int lst_conta_menores (No* inicio, int v);
void lst_conta_menores_rec (No* inicio, int v, int * cont);

No * lst_localiza_ultimo_menor_rec (No* ant, No * inicio, int v);
//No * lst_localiza_ultimo_rec (No* ant, No * inicio);

void lst_retira (No** inicio, int v);
void lst_retira_rec (No** no, int v);

void lst_imprime (No* inicio);
void lst_imprime_rec (No* no);

int lst_igual (No* n1, No* n2);
int lst_igual_rec (No* n1, No* n2);
