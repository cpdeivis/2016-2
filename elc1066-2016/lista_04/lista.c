#include <stdlib.h>
#include "lista.h"

/* Defini��o dos tipos de objetos */
#define RET 0
#define TRI 1
#define CIR 2
#define PI 3.14


typedef struct retangulo {
	float b;
	float h;
} Retangulo;

typedef struct triangulo {
	float b;
	float h;
} Triangulo;

typedef struct circulo {
	float r;
} Circulo;


/* Defini��o do n� da estrutura */
struct no_het {
	int	tipo;
	void	*info;
	struct no_het *prox;
};

static float calc_area_ret (Retangulo* r);
static float calc_area_tri (Triangulo* t);
static float calc_area_cir (Circulo* c);


No_Het* no_het_proximo(No_Het * no)
{
	 return no->prox;
}

void no_het_conecta(No_Het * no1, No_Het * no2)
{
	 no1->prox = no2;
}

/* Cria um n� com um ret�ngulo */
No_Het* no_het_cria_ret (float b, float h)
{
	Retangulo* r = (Retangulo*) malloc(sizeof(Retangulo));	/* aloca ret�ngulo */
	r->b = b;
	r->h = h;

	No_Het* p = (No_Het*) malloc(sizeof(No_Het));			  /* aloca n� */
	p->tipo = RET;
	p->info = r;
	p->prox = NULL;

	return p;
}

/* Cria um n� com um ret�ngulo */
No_Het* no_het_cria_circ (float r)
{
	Circulo* c = (Circulo*) malloc(sizeof(Circulo));//aloca circulo
	c->r = r;

	No_Het* p = (No_Het*) malloc(sizeof(No_Het));
	p->tipo = CIR;
	p->info = c;
	p->prox = NULL;

	return p;
}

/* Cria um n� com um ret�ngulo */
No_Het* no_het_cria_tri (float b, float h)
{
	Triangulo* t = (Triangulo*) malloc(sizeof(Triangulo));	/* aloca trinagulo */
	t->b = b;
	t->h = h;

	No_Het* p = (No_Het*) malloc(sizeof(No_Het));			  /* aloca n� */
	p->tipo = TRI;
	p->info = t;
	p->prox = NULL;

	return p;
}

/* fun��o para c�lculo da �rea do n�  */
float no_het_calcula_area (No_Het* p)
{
	float a;
	switch (p->tipo) {
		case RET:
			a = calc_area_ret(p->info);
			break;
		case TRI:
			a = calc_area_tri(p->info);
			break;
		case CIR:
			a = calc_area_cir(p->info);
			break;
	}
	return a;
}


/* fun��o para c�lculo da �rea de um ret�ngulo */
static float calc_area_ret (Retangulo* r)
{
	return r->b * r->h;
}

/* fun��o para c�lculo da �rea de um tri�ngulo */
static float calc_area_tri (Triangulo* t)
{
	return (t->b * t->h) / 2;
}

/* fun��o para c�lculo da �rea de um c�rculo */
static float calc_area_cir (Circulo* c)
{
	return PI * c->r * c->r;
}


/* fun��o para c�lculo da �rea do n�  */
char * no_het_recupera_tipo (No_Het* p)
{
	char* c;
	switch (p->tipo) {
		case RET:
			c = "Retangulo";
			break;
		case CIR:
			c = "Circulo";
			break;
		case TRI:
			c = "Triangulo";
			break;
		default:
			c = "Na1 Definido";
			break;
	}
	return c;
}
