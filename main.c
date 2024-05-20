#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"
#include <sys/stat.h>

int main() {
    PeopleList * list = readFriends();
    readPeoplePlaylists(list);

    //Teste para ver se o diretório Saida já existe
    FILE *teste = fopen("Saida/teste", "w");

    //Se não existir, cria ele
    if(!teste) mkdir("Saida", S_IRWXU);
    
    //Se existir, apaga o arquivo de teste criado
    if(teste) {
        remove("Saida/teste");
        fclose(teste);
    }

    sortPlayListsPeople(list);
    friendsSimilarities(list);
    filePrintRefactored(list);

    printPeopleList(list);
    matchFriendsPlaylists(list);

    
    freePeople(list);
    freePeopleList(list);

    return 0;

}