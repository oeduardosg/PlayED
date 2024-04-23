#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlistList.h"

typedef struct cellType cellType;

struct playlistList{
    cellType *first;
    cellType *last;
};

struct cellType{
    playlistType *playlist;
    cellType *next;
    cellType *prior;
};

playlistList* createPlaylistList(){
    playlistList *l = malloc(sizeof(playlistList));

    l->first = l->last = NULL;

    return l;
}

void insertPlaylist(playlistList *l, playlistType *p){
    cellType *cel = malloc(sizeof(cellType));

    cel->playlist = p;

    if(l->last != NULL) l->last->next = cel;
    cel->next = NULL;
    cel->prior = l->last;

    if(l->first == NULL) l->first = cel;
    l->last = cel;
}

void printPlaylistList(playlistList *l, char *name){
    if(l->first == NULL){
        printf("%s nao tem playlists\n\n", name);
        return;
    }
    printf("Playlists de %s:\n", name);

    for(cellType *cel = l->first; cel; cel = cel->next){
        printPlaylist(cel->playlist);
    }

    printf("\n");
}

void freePlaylistList(playlistList *l){
    cellType *cel = l->first;
    cellType *aux = l->first;

    while(aux){
        cel = aux;
        aux = cel->next;
        freePlaylist(cel->playlist);
        free(cel);
    }

    free(l);
}





