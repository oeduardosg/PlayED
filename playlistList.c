#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlistList.h"

typedef struct cellPlLi cellTypePlLi;

struct playlistList{
    cellTypePlLi *first;
    cellTypePlLi *last;
};

struct cellPlLi{
    playlistType *playlist;
    cellTypePlLi *next;
    cellTypePlLi *prior;
};

playlistList* createPlaylistList(){
    playlistList *l = malloc(sizeof(playlistList));

    l->first = l->last = NULL;

    return l;
}

void insertPlaylist(playlistList *l, playlistType *p){
    cellTypePlLi *cel = malloc(sizeof(cellTypePlLi));

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

    for(cellTypePlLi *cel = l->first; cel; cel = cel->next){
        printPlaylist(cel->playlist);
    }

    printf("\n");
}

void freePlaylistList(playlistList *l){
    cellTypePlLi *cel = l->first;
    cellTypePlLi *aux = l->first;

    while(aux){
        cel = aux;
        aux = cel->next;
        freePlaylist(cel->playlist);
        free(cel);
    }

    free(l);
}





