#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"

void imprime_tab (No* no, char * lado)
{
	static int tab = 0;

	if (no==NULL) return;

	int x;
	for(x=0;x<tab;x++)
		printf("	");
	printf("%d (%s)\n", arv_busca_valor(no), lado);

	tab+=1;
	imprime_tab(arv_busca_filho(no,0), "ESQ");
	imprime_tab(arv_busca_filho(no,1), "DIR");
	tab-=1;
}


int conta_nos_maiores(No * no, int v){
	int aux = 0;
	if(no != NULL){
		if(arv_busca_valor(no) > v)
			aux++;
		aux += (conta_nos_maiores(arv_busca_filho(no,0), v) + conta_nos_maiores(arv_busca_filho(no,1),v));
	}
	return aux;
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

	arv_insere_final(no1, no2, 0);
	arv_insere_final(no1, no3, 1);
	arv_insere_final(no3, no4, 0);
	arv_insere_final(no3, no5, 1);
	arv_insere_final(no3, no6, 1);
	arv_seta_raiz (arv, no1);

	printf("\n");
	imprime_tab(arv_busca_raiz(arv), "RAIZ");
	printf("\n");

	int valor = 50;
	//No * rem = arv_remover_no(arv_busca_raiz(arv), valor);
	int rem = arv_remover_no2(arv_busca_raiz(arv), valor);
	if (rem)
		printf("\nNo removido: %d", valor);
	else
		printf("\nNo nao removido: %d", valor);


	printf("\n");
	imprime_tab(arv_busca_raiz(arv), "RAIZ");
	printf("\n");

	int valor2 = 40;
	No * no = arv_busca_no(arv_busca_raiz(arv), valor2);
	if (no==NULL)
		printf("\nNo nao encontrado: %d", valor2);
	else
		printf("\nNo encontrado: %d", valor2);

	printf("\n");
	int valor3 = 30;
	int cont = conta_nos_maiores(arv_busca_raiz(arv), valor3);
	printf("Nos maiores que %d: %d ", valor3, cont);

	return 0;
}
