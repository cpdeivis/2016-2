#include "stdlib.h"
#include "stdio.h"
#include "lista.h"

int main (void)
{
	No* inicio = NULL;

	printf("\nInserindo elementos 10, 20, 30, 40, 50 e 60");
	lst_insere(&inicio,30);
	lst_insere(&inicio,20);
	lst_insere(&inicio,10);
	lst_insere_final(&inicio,40);
	lst_insere_final(&inicio,50);
	lst_insere_final(&inicio,60);

	lst_imprime(inicio);

	printf("\nRetirando elemento 10");
	lst_retira(&inicio,10);
	lst_imprime(inicio);

	printf("\nRetirando elemento 60");
	lst_retira(&inicio,60);
	lst_imprime(inicio);

	printf("\nRetirando elemento 40");
	lst_retira(&inicio,40);
	lst_imprime(inicio);

	printf("\nBuscando elemento 50");
	No * n = lst_busca(inicio, 50);
	if (n!=NULL){
		printf("\nAchei. Imprimindo de tr�s para frente\n");
		lst_imprime_para_tras(n);
	}
	else printf("\nElemento nao existe!");

	return 0;
}
