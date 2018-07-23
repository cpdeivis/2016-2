#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"

int quant_maiores(No *no, int v);
int gera_vetor_maiores(No *no, int v, int **vetor);
int calcula_altura(No *no);
int balanceada(No *no);

void imprime_asc(No *no){
	if (no == NULL)
		return;

	imprime_asc(arv_busca_filho(no, 0));
	printf("%d, ", arv_busca_valor(no));
	imprime_asc(arv_busca_filho(no, 1));
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

int balanceada(No *no){
	int dir = 0, esq = 0;
	unsigned int diff = 0;
	if(no != NULL){
		dir = calcula_altura(arv_busca_filho(no, 1));
		esq = calcula_altura(arv_busca_filho(no, 0));
		diff = dir - esq;
		if(diff < 2){
			balanceada(arv_busca_filho(no, 1));
			balanceada(arv_busca_filho(no, 0));
			return 1;
		}
		return 0;
	}
	return 0;
}

int quant_maiores(No *no, int v){
	int aux = 0;
	if(no != NULL){
		if(arv_busca_valor(no) > v)
			aux++;
		aux += (quant_maiores(arv_busca_filho(no,0), v) + quant_maiores(arv_busca_filho(no,1),v));
	}
	return aux;
}

void insere_Deivis(No *no, int v, int **vetor, int *pos){
	if(no != NULL){
		if(arv_busca_valor(no) > v){
			(*vetor)[*pos] = arv_busca_valor(no);
			(*pos)++;
		}
		if(arv_busca_filho(no,0) != NULL && arv_busca_valor(arv_busca_filho(no,0)) > v)
			insere_Deivis(arv_busca_filho(no,0), v, vetor, pos);
		if(arv_busca_filho(no,1) != NULL && arv_busca_valor(arv_busca_filho(no,1)) > v)
			insere_Deivis(arv_busca_filho(no,1), v, vetor, pos);
	}
}
int gera_vetor_maiores(No *no, int v, int **vetor){
	int tam = quant_maiores(no, v);
	if(tam > 0)
	{
		*vetor = (int *)malloc(sizeof(int) * tam);
		int pos = 0;
		insere_Deivis(no, v, vetor, &pos);
		return tam;
	}
	return 0;
}

int main(){
	printf("\n\n******************* TESTE 1 ******************************");
	Arvore *arv = arv_cria();

	arv_insere_no(arv, 1);
	arv_insere_no(arv, 2);
	arv_insere_no(arv, 3);
	arv_insere_no(arv, 4);
	arv_insere_no(arv, 5);
	arv_insere_no(arv, 6);
	arv_insere_no(arv, 7);

	printf("\n");
	int bal = balanceada(arv_busca_raiz(arv));
	if (bal)
		printf("\nBalanceada");
	else
		printf("\nNao Balanceada");

	printf("\n\n******************* TESTE 2 ******************************");
	Arvore *arv1 = arv_cria();

	arv_insere_no(arv1, 4);
	arv_insere_no(arv1, 6);
	arv_insere_no(arv1, 2);
	arv_insere_no(arv1, 5);
	arv_insere_no(arv1, 1);
	arv_insere_no(arv1, 7);
	arv_insere_no(arv1, 3);

	printf("\n");
	bal = balanceada(arv_busca_raiz(arv1));
	if (bal)
	printf("\nBalanceada");
	else
		printf("\nNao Balanceada");

	int *vetor;
	int tam = gera_vetor_maiores(arv_busca_raiz(arv1), 3, &vetor);

	printf("\n\nvetor gerado: ");
	int x;
	for (x = 0; x < tam; x++)
	{
		printf("%d ", vetor[x]);
	}
	printf("\n");

	return 0;
}
