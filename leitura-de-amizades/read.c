#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"

int main() {
    ListaPessoas *lista = criaListaPessoa();

    char nome1[50], nome2[50];
    
    while(scanf("%[^;]%*c", nome1) == 1){
        scanf("%[^\n]%*c", nome2);
        if(buscaPessoa(lista, nome1) == NULL){
            Person *p1 = criaPessoa(nome1);
            inserePessoa(lista, p1);
        }
        if(buscaPessoa(lista, nome2) == NULL){
            Person *p2 = criaPessoa(nome2);
            inserePessoa(lista, p2);
        }
        adicionaAmigo(lista, nome1, nome2);
    }

    imprimeListaPessoa(lista);

    liberaPessoas(lista);
    liberaListaPessoa(lista);

    return 0;

}