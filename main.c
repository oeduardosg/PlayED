#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"
#include <sys/stat.h>

int main() {
    PeopleList * list = readFriends();
    readPeoplePlaylists(list);

    FILE *teste = fopen("Saida/teste", "w");

    if(!teste) mkdir("Saida", S_IRWXU);
    
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