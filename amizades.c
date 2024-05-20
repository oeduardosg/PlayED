#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amizades.h"
#include <sys/stat.h>

/*Funcoes com personType*/

struct person{
    // nome da Pessoa
    char *name;

    //Lista de Amigos da Pessoa
    PeopleList *friends;

    //Lista de Playlists da Pessoa
    playlistListType *playlists;

    //Se a pessoa já foi printada no arquivo similaridades.txt
    int printed;
};

personType* createPerson(char *name){
    personType *p = malloc(sizeof(personType));

    p->name = strdup(name);
    p->friends = createPeopleList();
    p->playlists = createPlaylistList();
    p->printed = 0;

    return p;
}

void freePerson(personType *person){
    free(person->name);
    freePeopleList(person->friends);
    freePlaylistList(person->playlists);
    free(person);
}

char* getPersonName(personType *person){
    return person->name;
}

playlistListType* getPersonPlaylists(personType *person){
    return person->playlists;
}

void setPersonPlaylists(personType *person, playlistListType *playlistList){
    person->playlists = playlistList;
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

void insertPerson(PeopleList *list, personType *person){
    if(!list) return;
    
    cellType *cel = malloc(sizeof(cellType));

    cel->person = person;

    if(list->last != NULL) list->last->next = cel;
    cel->next = NULL;
    cel->prior = list->last;

    if(list->first == NULL) list->first = cel;
    list->last = cel;
}

void removePerson(PeopleList *list, char *name){
    if(!list) return;

    cellType *cel;
    for(cel = list->first; cel!= NULL; cel = cel->next){
        if(!strcmp(getPersonName(cel->person), name)) break;
    }

    if(!cel){
        printf("Nao achou a pessoa\n");
        return;
    }
    

    if(cel->next != NULL) cel->next->prior = cel->prior;
    if(cel->prior != NULL) cel->prior->next = cel->next;

    if(cel->prior == NULL) list->first = cel->next;
    if(cel->next == NULL)  list->last = cel->prior;
        
    free(cel);
}

void printPeopleList(PeopleList *list){
    if(!list) return;

    printf("Lista de Pessoas:\n");

    for(cellType *cel = list->first; cel; cel = cel->next){
        printf("-%s\n", getPersonName(cel->person));
        printFriendsOf(list, getPersonName(cel->person));
        filePrintPlaylistList(getPersonPlaylists(cel->person), getPersonName(cel->person), 0);
    }
}

void freePeople(PeopleList *list){
    if(!list) return;

    cellType *cel = list->first;

    while(cel){
        freePerson(cel->person);
        cel = cel->next;
    }
}

void freePeopleList(PeopleList *list){
    if(!list) return;

    cellType *cel = list->first;
    cellType *aux = list->first;

    while(aux){
        cel = aux;
        aux = cel->next;
        free(cel);
    }

    free(list);
}

/*Funcoes com PeopleList*/

personType* searchPerson(PeopleList *list, char *name){
    if(!list) return NULL;

    cellType *cel;
    for(cel = list->first; cel!= NULL; cel = cel->next){
        if(!strcmp(getPersonName(cel->person), name)) break;
    }

    if(cel == NULL) return NULL;

    return cel->person;
}

void addFriend(PeopleList *list, char *name1, char *name2){
    personType *person1 = searchPerson(list, name1);
    personType *person2 = searchPerson(list, name2);

    insertPerson(person1->friends, person2);
    insertPerson(person2->friends, person1);
}

void printFriendsOf(PeopleList *list, char *name){
    if(!list) return;

    personType *person = searchPerson(list, name);
    
    printf("Amigos de %s:\n", name);
    for(cellType *cel = person->friends->first; cel; cel = cel->next){
        printf("  %s\n", getPersonName(cel->person));
    }
}

PeopleList* readFriends(){
    FILE *amizadeFile = fopen("Entrada/amizade.txt", "r");

    if(!amizadeFile) {
        printf("Erro ao abrir o arquivo amizade.txt\n");
        return NULL;
    }

    PeopleList *list = createPeopleList();

    char name1[50], name2[50];

    char key = ';';
    while(key == ';'){
        fscanf(amizadeFile, "%[^; ^\n]%c", name1, &key);
        personType *p1 = createPerson(name1);
        insertPerson(list, p1);
    }
    
    while(fscanf(amizadeFile, "%[^;]%*c", name1) == 1){
        fscanf(amizadeFile, "%[^\n]%*c", name2);
        addFriend(list, name1, name2);
    }

    fclose(amizadeFile);

    return list;
}

void readPeoplePlaylists(PeopleList *list){
    if(!list) return;

    FILE *playlistFile = fopen("Entrada/playlists.txt", "r");

    if(!playlistFile){
        printf("Erro ao abrir o arquivo playlist.txt\n");
        return;
    }

    char name[50];
    int qtd = 0;
    char playlistName[50];

    while(fscanf(playlistFile, "%[^;]%*c", name) == 1){
        personType *person = searchPerson(list, name);
        if(person == NULL) {
            printf("Essa pessoa nao foi cadastrada\n");

            fscanf(playlistFile, "%d%*c", &qtd);
            fscanf(playlistFile, "%[^\n]%*c", playlistName);
            continue;
        }

        fscanf(playlistFile, "%d%*c", &qtd);
        for(int i = 0; i < qtd; i++){
            fscanf(playlistFile, "%[^\n ^;]%*c", playlistName);

            insertPlaylist(getPersonPlaylists(person), readPlaylistFile(playlistName));
        }
    }

    fclose(playlistFile);
}


void friendsSimilarities(PeopleList *list){
    if(list == NULL) return;
    cellType *cell1 = NULL, *cell2 = NULL;
    int n = 0;

    FILE *file = fopen("Saida/similaridades.txt", "w");

    for(cell1 = list->first; cell1; cell1 = cell1->next){
        for(cell2 = cell1->person->friends->first, n = 0; cell2; cell2 = cell2->next){
            n = playlistListSimilarities(getPersonPlaylists(cell1->person), getPersonPlaylists(cell2->person));
            
            if(!cell2->person->printed)
                fprintf(file, "%s;%s;%d\n", getPersonName(cell1->person), getPersonName(cell2->person), n);
        }
        cell1->person->printed = 1;
    }

    fclose(file);
}

void sortPlayListsPeople(PeopleList *list){
    if(list == NULL) return;

    for(cellType *cel = list->first; cel; cel = cel->next){
        setPersonPlaylists(cel->person, sortBySinger(getPersonPlaylists(cel->person)));
    }
}

void filePrintRefactored(PeopleList * list) {

    if(!list) return;

    FILE * file = fopen("Saida/played-refatorada.txt", "w");

    cellType * runner = list -> first;

    while(runner) {
        fprintf(file, "%s;", runner -> person -> name);
        printRefactoredPlaylistList(runner -> person -> playlists, file);
        fprintf(file, "\n");
        runner = runner -> next;
    }

    fclose(file);

}

void matchFriendsPlaylists(PeopleList * list) {

    FILE *teste = fopen("Merge/teste", "w");

    if(!teste) mkdir("Merge", S_IRWXU);
    
    if(teste) {
        remove("Merge/teste");
        fclose(teste);
    }

    if(!list) {
        printf("A lista a ser feito match não existe.\n");
        return;
    }

    cellType * runner = list -> first;

    while(runner) {

        cellType * runnerFriends = runner -> person -> friends -> first;

        while(runnerFriends) {

            matchPlaylistLists(runner -> person -> playlists, runnerFriends -> person -> playlists);
            runnerFriends = runnerFriends -> next;

        }
        
        runner = runner -> next;
    }

    
    for(cellType *cel = list->first; cel; cel = cel->next){
        filePrintPlaylistList(getPersonPlaylists(cel->person), getPersonName(cel->person), 1);
    }
}