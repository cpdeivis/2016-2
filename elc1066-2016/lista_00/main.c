#include <stdio.h>
#include "lista.h"

int main (void){
	No* inicio;/* declara uma lista n�o iniciada*/
	lst_cria(&inicio);/* inicia lista vazia*/
	lst_insere_ordenado (&inicio, 5);/* insere na lista o elemento 23*/
	lst_insere_ordenado (&inicio, 2);/* insere na lista o elemento 45*/
	lst_insere_ordenado (&inicio, 3);/* insere na lista o elemento 56*/
	lst_insere_ordenado (&inicio, 1);/* insere na lista o elemento 78*/
	lst_imprime (inicio);/* imprimir�: 78 56 45 23*/
	return 0;
}
