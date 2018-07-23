#include "stdlib.h"
#include "stdio.h"
#include "lista.h"


void imprime(No_Het * no)
{
	No_Het* aux = no;
	if(aux != NULL)
		do {
			printf("A area do %s eh: %.2f;\n", no_het_recupera_tipo(aux), no_het_calcula_area(aux));
			aux = no_het_proximo(aux);
		} while(aux != NULL);

}

void calculaMaiorArea(No_Het * no)
{
	No_Het* aux = no;
	No_Het* max = no;
	if(aux != NULL){
		do {
			if(no_het_calcula_area(aux) > no_het_calcula_area(max))
				max = aux;
			aux = no_het_proximo(aux);
		} while(aux != NULL);
		printf("A maior area eh do %s e eh: %.2f;\n", no_het_recupera_tipo(max), no_het_calcula_area(max));
	}
}


int main (void)
{

	No_Het * n1 = no_het_cria_circ(4);

	No_Het * n2 = no_het_cria_ret(10,4);

	No_Het * n3 = no_het_cria_tri(10,4);

	if (!n2 || !n3)
	{
		exit(1);
	}

	no_het_conecta(n1, n2);
	no_het_conecta(n2, n3);

	printf("\n Impressao dos objetos criados");
	printf("\n");
	float area = no_het_calcula_area(n1);
	printf("\n Objeto: %s", no_het_recupera_tipo(n1));
	printf("\n Area: %.2f", area);

	printf("\n");
	area = no_het_calcula_area(n2);
	printf("\n Objeto: %s", no_het_recupera_tipo(n2));
	printf("\n Area: %.2f", area);

	printf("\n");
	area = no_het_calcula_area(n3);
	printf("\n Objeto: %s", no_het_recupera_tipo(n3));
	printf("\n Area: %.2f", area);

	printf("\n");
	printf("\n Impressao de todos objetos encadeados");
	imprime(n1);

	printf("\n");
	calculaMaiorArea(n1);

	return 0;
}
