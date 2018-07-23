typedef struct no_het No_Het;

No_Het* no_het_proximo(No_Het * no);
void no_het_conecta(No_Het * no1, No_Het * no2);

No_Het* no_het_cria_ret (float b, float h);
No_Het* no_het_cria_circ (float r);
No_Het* no_het_cria_tri (float b, float h);

float no_het_calcula_area (No_Het* p);
char * no_het_recupera_tipo (No_Het* p);
