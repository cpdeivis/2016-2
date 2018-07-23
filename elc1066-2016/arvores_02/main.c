#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"

void imprime_asc(No * no){
	if(no != NULL){
		imprime_asc(arv_busca_filho(no,0)); //esquerda
		printf("%d \n", arv_busca_valor(no));
		imprime_asc(arv_busca_filho(no,1)); //direita
	}
}
void imprime_desc(No * no){
	if(no != NULL){
		imprime_desc(arv_busca_filho(no,1)); //direita
		printf("%d \n", arv_busca_valor(no));
		imprime_desc(arv_busca_filho(no,0)); //esquerda
	}
}
No* arv_buscaDeivis(No* no, int dir){
	if(arv_busca_filho(no, dir) == NULL)
		return no;
	else
		return arv_buscaDeivis(arv_busca_filho(no, dir), dir);
}
int calcula_diferenca(No * no){
	if(!arv_no_vazio(no)){
		No* esquerda = arv_buscaDeivis(no, 0);
		No* direita = arv_buscaDeivis(no, 1);
		return arv_busca_valor(direita) - arv_busca_valor(esquerda);
	}
	return -1;
}

void imprime_tab (No* no, char * lado){
	static int tab = 0;

	if (no==NULL) return;

	int x;
	for(x=0;x<tab;x++)
		printf("   ");
	printf("%d (%s)\n", arv_busca_valor(no), lado);

	tab+=1;
	imprime_tab(arv_busca_filho(no,0), "ESQ");
	imprime_tab(arv_busca_filho(no,1), "DIR");
	tab-=1;
}

int main(){
	Arvore * arv = arv_cria();

	arv_insere_no(arv, 10);
	arv_insere_no(arv, 50);
	arv_insere_no(arv, 40);
	arv_insere_no(arv, 20);
	arv_insere_no(arv, 60);

	printf("\n Impressao \n");
	imprime_tab(arv_busca_raiz(arv), "RAIZ");

	printf("\n");
	int valor = 50;
	No * resp = arv_busca_no(arv_busca_raiz(arv), valor);
	if (resp!=NULL)
		printf("No encontrado: %d", valor);
	else printf("No nao encontrado: %d ", valor);


	printf("\n");
	int diff = calcula_diferenca(arv_busca_raiz(arv));
	if (diff!=-1)
		printf("\nDiferenca do maior para o menor e de %d unidades", diff);

	printf("\n\n lista ascendente de valores:");
	imprime_asc(arv_busca_raiz(arv));

	printf("\n\n lista descendente de valores:");
	imprime_desc(arv_busca_raiz(arv));

	return 0;
}
