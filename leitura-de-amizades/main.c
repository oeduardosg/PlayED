#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"

int main() {
    ListaPessoas *lista = lerAmizades();

    imprimeListaPessoa(lista);

    liberaPessoas(lista);
    liberaListaPessoa(lista);

    return 0;

}