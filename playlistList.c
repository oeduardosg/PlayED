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

    playlistList * list = malloc(sizeof(playlistList));

    list -> first = list -> last = NULL;

    return list;
}

void insertPlaylist(playlistList * playlistList, playlistType * playlistToAdd){

    cellType * cell = malloc(sizeof(cellType));

    cell -> playlist = playlistToAdd;

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

int playlistListSimilarities(playlistList * list1, playlistList * list2){

    if(list1 == NULL || list2 == NULL) return 0;

    cellType * cell1 = NULL, * cell2 = NULL;
    int n = 0;

    for(cell1 = list1 -> first; cell1; cell1 = cell1 -> next){
        for(cell2 = list2 -> first; cell2; cell2 = cell2 -> next){
            if(!strcmp(getPlaylistName(cell1 -> playlist), getPlaylistName(cell2 -> playlist)))
                n += playlistSimilarities(cell1 -> playlist, cell2 -> playlist);
        }
    }

    return n;
}

void printInFilePlaylistList(playlistList * playlistList, FILE * file) {

    if(!playlistList) return;

    cellType * runner = playlistList -> first;
    int playlistsQuantity = 0;

    while(runner) {
        playlistsQuantity++;
        runner = runner -> next;
    }

    runner = playlistList -> first;
    
    fprintf(file, "%d", playlistsQuantity);

    while(runner) {
        fprintf(file, ";%s.txt", getPlaylistName(runner -> playlist));
        runner = runner -> next;
    }

}

void mashUpPlaylistLists(playlistList * list1, playlistList * list2) {

    int foundMashup = 0;
    cellType * runner1 = list1 -> first;

    while(runner1 && isMashup(runner1 -> playlist) != 1) {

        cellType * runner2 = list2 -> first;

        while(runner2 && isMashup(runner1 -> playlist) != 1) {

            if(!strcmp(getPlaylistName(runner1 -> playlist), getPlaylistName(runner2 -> playlist)) && !isMashup(runner1 -> playlist)) {

                cellType * runner3 = list1 -> first;

                while(runner3) {

                    if(!strcmp(getPlaylistName(runner2 -> playlist), getPlaylistName(runner3 -> playlist)) && isMashup(runner3 -> playlist)) {
                        addToFrom(runner3 -> playlist, runner2 -> playlist);
                        foundMashup = 1;
                    }

                    runner3 = runner3 -> next;
                }
                
                if(!foundMashup) {
                    playlistType * mashup = mashUpPlaylist(runner1 -> playlist, runner2 -> playlist);
                    insertPlaylist(list1, mashup);
                }

                foundMashup = 0;
            }

            runner2 = runner2 -> next;
        }

        runner1 = runner1 -> next;
    }

}