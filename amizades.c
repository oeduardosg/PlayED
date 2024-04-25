#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"

/*Funcoes com personType*/

struct person{
    char *name;
    PeopleList *friends;
    playlistList *playlists;
};

personType* createPerson(char *name){
    personType *p = malloc(sizeof(personType));

    p->name = strdup(name);
    p->friends = createPeopleList();
    p->playlists = createPlaylistList();

    return p;
}

void freePerson(personType *p){
    free(p->name);
    freePeopleList(p->friends);
    freePlaylistList(p->playlists);
    free(p);
}

/*Lista de Pessoas*/

typedef struct cellType cellType;

struct list{
    cellType *first;
    cellType *last;
};

struct cellType{
    personType *person;
    cellType *next;
    cellType *prior;
};

PeopleList* createPeopleList(){
    PeopleList *l = malloc(sizeof(PeopleList));

    l->first = l->last = NULL;

    return l;
}

void insertPerson(PeopleList *l, personType *p){
    cellType *cel = malloc(sizeof(cellType));

    cel->person = p;

    if(l->last != NULL) l->last->next = cel;
    cel->next = NULL;
    cel->prior = l->last;

    if(l->first == NULL) l->first = cel;
    l->last = cel;
}

void removePerson(PeopleList *l, char *name){
    cellType *cel;
    for(cel = l->first; cel!= NULL; cel = cel->next){
        if(!strcmp(cel->person->name, name)) break;
    }

    if(!cel){
        printf("Nao achou a pessoa\n");
        return;
    }
    

    if(cel->next != NULL) cel->next->prior = cel->prior;
    if(cel->prior != NULL) cel->prior->next = cel->next;

    if(cel->prior == NULL) l->first = cel->next;
    if(cel->next == NULL)  l->last = cel->prior;
        
    free(cel);
}

void printPeopleList(PeopleList *l){
    if(!l) return;
    
    printf("Lista de Pessoas:\n");

    for(cellType *cel = l->first; cel; cel = cel->next){
        printf("-%s\n", cel->person->name);
        printFriendsOf(l, cel->person->name);
        printPlaylistList(cel->person->playlists, cel->person->name);
    }
}

void freePeople(PeopleList *l){
    if(!l) return;

    cellType *cel = l->first;

    while(cel){
        freePerson(cel->person);
        cel = cel->next;
    }
}

void freePeopleList(PeopleList *l){
    if(!l) return;

    cellType *cel = l->first;
    cellType *aux = l->first;

    while(aux){
        cel = aux;
        aux = cel->next;
        free(cel);
    }

    free(l);
}

/*Funcoes com PeopleList*/

personType* searchPerson(PeopleList *l, char *name){
    if(!l) return NULL;

    cellType *cel;
    for(cel = l->first; cel!= NULL; cel = cel->next){
        if(!strcmp(cel->person->name, name)) break;
    }

    if(cel == NULL) return NULL;

    return cel->person;
}

void addFriend(PeopleList *l, char *name1, char *name2){
    personType *person1 = searchPerson(l, name1);
    personType *person2 = searchPerson(l, name2);

    insertPerson(person1->friends, person2);
    insertPerson(person2->friends, person1);
}

void printFriendsOf(PeopleList *l, char *name){
    personType *p = searchPerson(l, name);
    
    printf("Amigos de %s:\n", name);
    for(cellType *cel = p->friends->first; cel; cel = cel->next){
        printf("  %s\n", cel->person->name);
    }
}

PeopleList* readFriends(){
    FILE *amizade = fopen("entradas/amizade.txt", "r");

    if(!amizade) {
        printf("Erro ao abrir o arquivo amizade.txt\n");
        return NULL;
    }

    PeopleList *lista = createPeopleList();

    char name1[50], name2[50];
    
    while(fscanf(amizade, "%[^;]%*c", name1) == 1){
        fscanf(amizade, "%[^\n]%*c", name2);
        if(searchPerson(lista, name1) == NULL){
            personType *p1 = createPerson(name1);
            insertPerson(lista, p1);
        }
        if(searchPerson(lista, name2) == NULL){
            personType *p2 = createPerson(name2);
            insertPerson(lista, p2);
        }
        addFriend(lista, name1, name2);
    }

    fclose(amizade);

    return lista;
}

void readPeoplePlaylists(PeopleList *l){
    if(!l) return;

    FILE *playlist = fopen("entradas/playlist.txt", "r");

    if(!playlist){
        printf("Erro ao abrir o arquivo playlist.txt\n");
        return;
    }

    char name[50];
    int qtd = 0;
    char playlistName[50];

    while(fscanf(playlist, "%[^;]%*c", name) == 1){
        personType *person = searchPerson(l, name);
        if(person == NULL) {
            printf("Essa pessoa nao foi cadastrada\n");
            fscanf(playlist, "%d%*c", &qtd);
            for(int i = 0; i < qtd; i++){
                if(i == qtd - 1) fscanf(playlist, "%[^\n]%*c", playlistName);
                else fscanf(playlist, "%[^;]%*c", playlistName);
            }
            continue;
        }

        fscanf(playlist, "%d%*c", &qtd);
        for(int i = 0; i < qtd; i++){
            if(i == qtd - 1) fscanf(playlist, "%[^\n]%*c", playlistName);
            else fscanf(playlist, "%[^;]%*c", playlistName);

            insertPlaylist(person->playlists, readPlaylistFile(playlistName));
        }
    }

    fclose(playlist);
}
