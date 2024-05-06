#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "playlistList.h"

typedef struct cellType cellType;

struct playlistList{
    cellType * first;
    cellType * last;
};

struct cellType{
    playlistType * playlist;
    cellType * next;
    cellType * prior;
};

playlistList * createPlaylistList(){

    playlistList * playlistList = malloc(sizeof(playlistList));

    playlistList -> first = playlistList -> last = NULL;

    return playlistList;
}

void insertPlaylist(playlistList * playlistList, playlistType * playlistToAdd){

    cellType * cell = malloc(sizeof(cellType));

    cell -> playlist = playlistList;

    if(playlistList -> last != NULL) playlistList -> last -> next = cell;
    cell -> next = NULL;
    cell -> prior = playlistList -> last;

    if(playlistList -> first == NULL) playlistList -> first = cell;
    playlistList -> last = cell;
}

void filePrintPlaylistList(playlistList * playlistList, char * playlistListName){

    if(playlistList -> first == NULL){
        printf("%s não possui playlists\n\n", playlistListName);
        return;
    }
    printf("Playlists de %s:\n", playlistListName);

    char folderName[100];

    for(cellType * cell = playlistList -> first; cell; cell = cell->next){
        sprintf(folderName, "Saida/%s", playlistListName);
        mkdir(folderName, S_IRWXU);
        printPlaylist(cell->playlist, playlistListName);
    }

    printf("\n");
}

void freePlaylistList(playlistList * playlistList){
    cellType * cell = playlistList -> first;
    cellType * aux = playlistList -> first;

    while(aux){
        cell = aux;
        aux = cell -> next;
        freePlaylist(cell -> playlist);
        free(cell);
    }

    free(playlistList);
}

playlistList * sortBySinger(playlistList * originalList) {

    playlistList * sortedList = createPlaylistList();

    cellType * aChecker = originalList -> first;

    while(aChecker) {

        while(thereIsSong(aChecker -> playlist)) {

            char * singer = getFirstSingerName(aChecker -> playlist);
            playlistType * singerPlaylist = createPlaylist(singer);
            cellType * bChecker = aChecker;

            while(bChecker) {
                
                clipSingerToPlaylist(singerPlaylist, bChecker -> playlist, singer);
                bChecker = bChecker -> next;

            }

            insertPlaylist(sortedList, singerPlaylist);

        }

    aChecker = aChecker -> next;

    }

    freePlaylistList(originalList);

return sortedList;
}

int playlistListSimilarities(playlistList *list1, playlistList *list2){

    if(list1 == NULL || list2 == NULL) return 0;

    cellType *celll1 = NULL, *celll2 = NULL;
    int n = 0;

    for(celll1 = list1->first; celll1; celll1 = celll1->next){
        for(celll2 = list2->first; celll2; celll2 = celll2->next){
            if(!strcmp(getPlaylistName(celll1->playlist), getPlaylistName(celll2->playlist)))
                n += playlistSimilarities(celll1->playlist, celll2->playlist);
        }
    }

    return n;
}