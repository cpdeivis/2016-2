#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"

static int nivel = 0;
void arv_tab_imprime(No* pai, char* lado)
{
	if (pai==NULL){
		return;
	}
	printf("\n");
	nivel++;
	for (int i = 0; i < nivel; i++)
		printf("---");
	printf("%d(%s)", arv_busca_valor(pai), lado);
	arv_tab_imprime(arv_busca_filho(pai, 0), "esq");
	arv_tab_imprime(arv_busca_filho(pai, 1), "dir");
	nivel--;
}

int main()
{
	Arvore * arv = arv_cria();
	No * no1 = arv_cria_no(10);
	No * no2 = arv_cria_no(20);
	No * no3 = arv_cria_no(30);
	No * no4 = arv_cria_no(40);
	No * no5 = arv_cria_no(50);

	No * no6 = arv_cria_no(60);

	arv_insere(no1, no2, 0);
	arv_insere(no1, no3, 1);
	arv_insere(no3, no4, 0);
	arv_insere_final(no3, no5, 1);
	arv_insere_final(no3, no6, 1);
	arv_seta_raiz (arv, no1);

	arv_imprime(arv_busca_raiz(arv));
	arv_imprime_tab(arv_busca_raiz(arv), "raiz");
	arv_tab_imprime(arv_busca_raiz(arv), "raiz");

	printf("\n");
	return 0;
}
