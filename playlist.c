#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

struct cellType {
    songType * song;
    cellType * priorCell;
    cellType * nextCell;
};


struct playlistType {
    char * playlistName;
    cellType * firstCell;
    cellType * lastCell;
};



playlistType * createPlaylist(char * playlistName) {

    playlistType * playlist = (playlistType *) calloc(1, sizeof(playlistType));

    playlist -> playlistName = strdup(playlistName);
    playlist -> firstCell = NULL;
    playlist -> lastCell = NULL;

return playlist;
}

void insertCell(playlistType * playlist, songType * song) {

    cellType * newCell = (cellType *) calloc(1, sizeof(cellType));

    newCell -> song = song;
    newCell -> nextCell = NULL;

    if(!playlist -> firstCell) {
        newCell -> priorCell = NULL;
        playlist -> firstCell = newCell;
        playlist -> lastCell = newCell;
    }
    else {
        playlist -> lastCell -> nextCell = newCell;
        newCell -> priorCell = playlist -> lastCell;
        playlist -> lastCell = newCell;
    }

}

void printPlaylist(playlistType * playlist) {

    if(!playlist -> firstCell) {
        printf("Não há músicas nessa playlist.\n");
        return;
    }

    cellType * checker = playlist -> firstCell;

    while(checker) {
        printSong(checker -> song);
        printf("\n");
        checker = checker -> nextCell;
    }

}

void freeCell(cellType * cell) {

    freeSong(cell -> song);
    free(cell);

}

void freePlaylist(playlistType * playlist) {
    
    if(!playlist -> firstCell) {
        free(playlist);
        return;
    }

    cellType * checker = playlist -> firstCell;
    cellType * toBeFreed;

    while(checker) {
        toBeFreed = checker;
        checker = checker -> nextCell;
        freeCell(toBeFreed); 
    }

    free(playlist -> playlistName);
    free(playlist);

}

playlistType * readPlaylistFile(const char * playlistFileName) {

    FILE * playlistFile = fopen(playlistFileName, "r");

    if(!playlistFile) {
        printf("Erro ao abrir o arquivo %s", playlistFileName);
        return NULL;
    }

    char playlistName[64];
    sscanf(playlistFileName, "%[^.].txt", playlistName);
    playlistType * playlist = createPlaylist(playlistName);

    char songName[64], singerName[64];

    while(fscanf(playlistFile, "%[^-]- %[^\n]\n", songName, singerName) == 2) {
        songName[strlen(songName) - 1] = '\0';
        songType * song = createSong(songName, singerName);
        insertCell(playlist, song);
    }

    fclose(playlistFile);

return playlist;
}