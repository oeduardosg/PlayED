#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

typedef struct cellType cellType;

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

    if(!playlist) return;

    printf("  %s:\n", playlist->playlistName);

    if(!playlist -> firstCell) {
        printf("   Não há músicas nessa playlist.\n");
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

    if(!playlist) return;
    
    if(!playlist -> firstCell) {
        free(playlist -> playlistName);
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

playlistType * readPlaylistFile(char * playlistFileName) {

    char playlistPath[65];
    sprintf(playlistPath, "entradas/%s", playlistFileName);

    FILE * playlistFile = fopen(playlistPath, "r");

    char playlistName[64];
    sscanf(playlistFileName, "%[^.].txt", playlistName);
    playlistType * playlist = createPlaylist(playlistName);

    if(!playlistFile) {
        printf("Erro ao abrir o arquivo %s\n", playlistFileName);
        return playlist;
    }

    char songName[64], singerName[64];

    while(fscanf(playlistFile, "%[^-]- %[^\n]\n", songName, singerName) == 2) {
        songName[strlen(songName) - 1] = '\0';
        songType * song = createSong(songName, singerName);
        insertCell(playlist, song);
    }

    fclose(playlistFile);

return playlist;
}

void removeCell(playlistType * playlist, char * songOrSingerName) {

    if(!playlist) {
        printf("Não há produtos na lista.");
        return;
    }

    cellType * checker = playlist -> firstCell;

    while(checker && strcmp(getSingerName(checker -> song), songOrSingerName) && strcmp(getSongName(checker -> song), songOrSingerName)) {
        checker = checker -> nextCell;
    }

    if(!checker) {
        printf("O produto não foi encontrado.\n");
        return;
    }

    if(checker == playlist -> firstCell) {
        playlist -> firstCell = playlist -> firstCell -> nextCell;
        playlist -> firstCell -> priorCell = NULL;
        freeCell(checker);
        return;
    }

    if(!checker -> nextCell) {
        checker -> priorCell -> nextCell = NULL;
        freeCell(checker);
        return;
    }

    checker -> priorCell -> nextCell = checker -> nextCell;
    checker -> nextCell -> priorCell = checker -> priorCell;

    freeCell(checker);

}


int thereIsSong(playlistType * playlist) {
return playlist -> firstCell -> song != NULL;
}

char * getFirstSingerName(playlistType * playlist) {
return getSingerName(playlist -> firstCell -> song);
}

void clipSingerToPlaylist(playlistType * singerPlaylist, playlistType * sourcePlaylist, char * singerName) {

    cellType * checker = sourcePlaylist -> firstCell;

    while(checker) {
        if(!strcmp(singerName, getSingerName(checker -> song))) {
            insertCell(singerPlaylist, checker -> song);
            removeCell(sourcePlaylist, getSingerName(checker -> song));
            //FALTA RESOLVER O PROBLEMA DOS FREES EM SONGS;
        }
    }

}