#ifndef amizades_h
#define amizades_h

#include <stdio.h>

/*Funcoes com Pessoa*/

typedef struct pessoa Pessoa;

Pessoa* criaPessoa(char *nome);

void liberaPessoa(Pessoa *p);

/*Lista de Pessoas*/

typedef struct lista ListaPessoas;

ListaPessoas* criaListaPessoa();

void inserePessoa(ListaPessoas *l, Pessoa *p);

void retiraPessoa(ListaPessoas *l, char *nome);

void imprimeListaPessoa(ListaPessoas *l);

void liberaListaPessoa(ListaPessoas *l);

void liberaPessoas(ListaPessoas *l);

/*Funcoes com ListaPessoas*/

Pessoa* buscaPessoa(ListaPessoas *l, char *nome);

void adicionaAmigo(ListaPessoas *l, char *nome1, char *nome2);

void imprimeAmigosDe(ListaPessoas *l, char *nome);

ListaPessoas* lerAmizades();

#endif