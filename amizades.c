#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"

/*Funcoes com Pessoa*/

struct pessoa{
    char *nome;
    ListaPessoas *amigos;
};

Pessoa* criaPessoa(char *nome){
    Pessoa *p = malloc(sizeof(Pessoa));

    p->nome = strdup(nome);
    p->amigos = criaListaPessoa();

    return p;
}

void liberaPessoa(Pessoa *p){
    free(p->nome);
    liberaListaPessoa(p->amigos);
    free(p);
}

/*Lista de Pessoas*/

typedef struct celula Celula;

struct lista{
    Celula *first;
    Celula *last;
};

struct celula{
    Pessoa *pessoa;
    Celula *prox;
    Celula *ant;
};

ListaPessoas* criaListaPessoa(){
    ListaPessoas *l = malloc(sizeof(ListaPessoas));

    l->first = l->last = NULL;

    return l;
}

void inserePessoa(ListaPessoas *l, Pessoa *p){
    Celula *cel = malloc(sizeof(Celula));

    cel->pessoa = p;

    if(l->last != NULL) l->last->prox = cel;
    cel->prox = NULL;
    cel->ant = l->last;

    if(l->first == NULL) l->first = cel;
    l->last = cel;
}

void retiraPessoa(ListaPessoas *l, char *nome){
    Celula *cel;
    for(cel = l->first; cel!= NULL; cel = cel->prox){
        if(!strcmp(cel->pessoa->nome, nome)) break;
    }

    if(!cel){
        printf("Nao achou a pessoa\n");
        return;
    }
    

    if(cel->prox != NULL) cel->prox->ant = cel->ant;
    if(cel->ant != NULL) cel->ant->prox = cel->prox;

    if(cel->ant == NULL) l->first = cel->prox;
    if(cel->prox == NULL)  l->last = cel->ant;
        
    free(cel);
}

void imprimeListaPessoa(ListaPessoas *l){
    printf("Lista de Pessoa:\n");

    for(Celula *cel = l->first; cel; cel = cel->prox){
        printf("%s\n", cel->pessoa->nome);
        imprimeAmigosDe(l, cel->pessoa->nome);
    }
}

void liberaPessoas(ListaPessoas *l){
    Celula *cel = l->first;

    while(cel){
        liberaPessoa(cel->pessoa);
        cel = cel->prox;
    }
}

void liberaListaPessoa(ListaPessoas *l){
    Celula *cel = l->first;
    Celula *aux = l->first;

    while(aux){
        cel = aux;
        aux = cel->prox;
        free(cel);
    }

    free(l);
}

/*Funcoes com ListaPessoas*/

Pessoa* buscaPessoa(ListaPessoas *l, char *nome){
    Celula *cel;
    for(cel = l->first; cel!= NULL; cel = cel->prox){
        if(!strcmp(cel->pessoa->nome, nome)) break;
    }

    if(cel == NULL) return NULL;

    return cel->pessoa;
}

void adicionaAmigo(ListaPessoas *l, char *nome1, char *nome2){
    Pessoa *pessoa1 = buscaPessoa(l, nome1);
    Pessoa *pessoa2 = buscaPessoa(l, nome2);

    inserePessoa(pessoa1->amigos, pessoa2);
    inserePessoa(pessoa2->amigos, pessoa1);
}

void imprimeAmigosDe(ListaPessoas *l, char *nome){
    Pessoa *p = buscaPessoa(l, nome);
    
    printf("Amigos de %s:\n", nome);
    for(Celula *cel = p->amigos->first; cel; cel = cel->prox){
        printf("%s\n", cel->pessoa->nome);
    }
    printf("\n");
}

ListaPessoas* lerAmizades(){
    ListaPessoas *lista = criaListaPessoa();
    FILE *amizade = fopen("amizade.txt", "r");

    char nome1[50], nome2[50];
    
    while(fscanf(amizade, "%[^;]%*c", nome1) == 1){
        fscanf(amizade, "%[^\n]%*c", nome2);
        if(buscaPessoa(lista, nome1) == NULL){
            Pessoa *p1 = criaPessoa(nome1);
            inserePessoa(lista, p1);
        }
        if(buscaPessoa(lista, nome2) == NULL){
            Pessoa *p2 = criaPessoa(nome2);
            inserePessoa(lista, p2);
        }
        adicionaAmigo(lista, nome1, nome2);
    }

    fclose(amizade);

    return lista;
}
