#include "stdlib.h"
#include "stdio.h"
#include "fila.h"

void imprime (Fila * f){
	if (!fila_vazia(f)) {
		int j = fila_tamanho(f);
		for (int i = 0; i < j; i++) {
			printf("%d\n", fila_retira(f));
		}
	}
	else
		printf("Sem Elementos!\n");
}

void imprime2 (Fila * f){
	if (!fila_vazia(f)) {
		Fila * th = fila_cria();
		int j = fila_tamanho(f), i, aux;
		for (i = 0; i < j; i++) {
			aux = fila_retira(f);
			printf("%d\n", aux);
			fila_insere(th, aux);
		}
		fila_libera(f);
		f  = th;
	}
	else
		printf("Sem Elementos!\n");
}

int main (void)
{

	Fila * f = fila_cria();
	fila_insere(f, 10);
	fila_insere(f, 15);
	fila_insere(f, 20);


	int tam = fila_tamanho(f);
	printf("\nTamanho da lista: %d", tam);

	printf("\nElementos");
	imprime2(f);

	printf("\n\nElementos pares");
	Fila * f2 = separaPares(f);
	imprime2(f2);
	return 0;
}
