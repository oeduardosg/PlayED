#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"

int main() {
    PeopleList * list = readFriends();
    readPeoplePlaylists(list);

    printPeopleList(list);

    freePeople(list);
    freePeopleList(list);

    
    return 0;

}