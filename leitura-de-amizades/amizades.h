#ifndef amizades_h
#define amizades_h

#include <stdio.h>

typedef struct pessoa Person;

typedef struct lista ListaPessoas;

Person* criaPessoa(char *nome);

void liberaPessoa(Person *p);

/**/

ListaPessoas* criaListaPessoa();

void inserePessoa(ListaPessoas *l, Person *p);

void retiraPessoa(ListaPessoas *l, char *nome);

void imprimeListaPessoa(ListaPessoas *l);

void liberaListaPessoa(ListaPessoas *l);

void liberaPessoas(ListaPessoas *l);

/**/

Person* buscaPessoa(ListaPessoas *l, char *nome);

void adicionaAmigo(ListaPessoas *l, char *nome1, char *nome2);

void imprimeAmigosDe(ListaPessoas *l, char *nome);


#endif