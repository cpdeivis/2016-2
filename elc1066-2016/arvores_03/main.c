#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "arvore.h"



void imprime_asc(No * no){
	if (no==NULL)
		return;

	imprime_asc(arv_busca_filho(no,0));
	printf("%d, ",arv_busca_valor(no) );
	imprime_asc(arv_busca_filho(no,1));

}

int calcula_altura(No * no){
	int dir = 0, esq = 0;
	if(no != NULL){
		esq = calcula_altura(arv_busca_filho(no, 0)); //esquerda
		dir = calcula_altura(arv_busca_filho(no, 1)); //direita

		return 1 + (esq < dir ? dir : esq);
	}
	return 0;
}


int main()
{

	printf("\n\n ************* TESTE 1 *************************************\n\n");
	Arvore * arv = arv_cria();

	arv_insere_no(arv, 10);
	arv_insere_no(arv, 50);
	arv_insere_no(arv, 40);
	arv_insere_no(arv, 20);
	arv_insere_no(arv, 60);
	arv_insere_no(arv, 40);


	printf("\n Impressao em ordem ascendente: ");
	imprime_asc(arv_busca_raiz(arv));

	int valor = 40;
	arv_remove_no(arv, valor);

	printf("\n Impressao em ordem ascendente apos remocao do no %d: ", valor);
	imprime_asc(arv_busca_raiz(arv));

	arv_remove_no(arv, valor);

	printf("\n Impressao em ordem ascendente apos remocao do no %d: ", valor);
	imprime_asc(arv_busca_raiz(arv));

	printf("\n\n ************* TESTE 2 *************************************\n\n");
	Arvore * arv1 = arv_cria();
	int x;
	srand( (unsigned) time(NULL));
	for (x=0;x<1000;x++)
	{
		int val = 1 + (rand() % 10);
		arv_insere_no(arv1, val);
	}


	printf("\n Impressao em ordem ascendente: ");
	imprime_asc(arv_busca_raiz(arv1));

	printf("\n");
	int altura = calcula_altura(arv_busca_raiz(arv1));
	printf("Altura da arvore: %d ", altura);

	return 0;
}
