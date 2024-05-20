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
    int match;
    cellType * firstCell;
    cellType * lastCell;
};



playlistType * createPlaylist(char * playlistName) {

    playlistType * playlist = (playlistType *) calloc(1, sizeof(playlistType));

    playlist -> playlistName = strdup(playlistName);
    playlist -> match = 0;
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

void printPlaylist(playlistType * playlist, char *name, int printMatch) {

    if(!playlist) return;

    char fileName[100];  
    if(printMatch) {
        sprintf(fileName, "Merge/%s/%s.txt", name, playlist->playlistName);
    } else {
        sprintf(fileName, "Saida/%s/%s.txt", name, playlist->playlistName);
    }
    FILE *file = fopen(fileName, "w");

    

    printf("  %s:\n", playlist->playlistName);

    if(!playlist -> firstCell) {
        printf("   Não há músicas nessa playlist.\n");
        return;
    }

    cellType * checker = playlist -> firstCell;

    while(checker) {
        filePrintSong(checker -> song, file);
        checker = checker -> nextCell;
    }

    fclose(file);

}


//Libera uma célula e se removeSong for diferente de 0, remove música também
void freeCell(cellType * cell, int removeSong) {

    if(removeSong) freeSong(cell -> song);
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

    int songRemove = 1;
    if(isMatch(playlist)) songRemove = 0;

    while(checker) {
        toBeFreed = checker;
        checker = checker -> nextCell;
        freeCell(toBeFreed, songRemove); 
    }

    free(playlist -> playlistName);
    free(playlist);

}

playlistType * readPlaylistFile(char * playlistFileName) {

    char playlistPath[256];
    sprintf(playlistPath, "Entrada/%s", playlistFileName);

    FILE * playlistFile = fopen(playlistPath, "r");

    char playlistName[256];
    sscanf(playlistFileName, "%[^.].txt", playlistName);
    playlistType * playlist = createPlaylist(playlistName);

    if(!playlistFile) {
        printf("Erro ao abrir o arquivo %s\n", playlistFileName);
        return playlist;
    }

    char songString[512], songName[256], singerName[256];

    while(fscanf(playlistFile, "%[^\n]\n", songString) == 1) {
        clipSongData(songName, singerName, songString);
        songType * song = createSong(songName, singerName);
        insertCell(playlist, song);
    }

    fclose(playlistFile);

return playlist;
}

/**
 * Remove uma célula
 * 
 * inputs: ponteiro para a playlist, nome da música e um inteiro que se for diferente de 0 vai remover a música
*/
void removeCell(playlistType * playlist, char * songOrSingerName, int removeSong) {

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
        freeCell(checker, removeSong);
        return;
    }

    if(!checker -> nextCell) {
        if(checker -> priorCell) checker -> priorCell -> nextCell = NULL;
        freeCell(checker, removeSong);
        return;
    }

    checker -> priorCell -> nextCell = checker -> nextCell;
    checker -> nextCell -> priorCell = checker -> priorCell;

    freeCell(checker, removeSong);

}


int thereIsSong(playlistType * playlist) {
return playlist -> firstCell != NULL;
}

char * getFirstSingerName(playlistType * playlist) {
return getSingerName(playlist -> firstCell -> song);
}

char * getPlaylistName(playlistType *playlist){
return playlist -> playlistName;
}

int thereIsThisSong(playlistType * playlist, char * songName){

    for(cellType * checker = playlist -> firstCell; checker; checker = checker -> nextCell){
        if(!strcmp(songName, getSongName(checker -> song))) return 1;
    }

return 0;
}

void clipSingerToPlaylist(playlistType * singerPlaylist, playlistType * sourcePlaylist, char * singerName) {

    cellType * checker = sourcePlaylist -> firstCell;
    cellType * aux = NULL;

    while(checker) {

        aux = checker;
        checker = checker -> nextCell;

        if(!strcmp(singerName, getSingerName(aux -> song))) {
            if(thereIsThisSong(singerPlaylist, getSongName(aux -> song))) 
                removeCell(sourcePlaylist, getSingerName(aux -> song), 1);
            else {
                insertCell(singerPlaylist, aux -> song);
                removeCell(sourcePlaylist, getSingerName(aux -> song), 0);
            }
        }

    }


}

int playlistSimilarities(playlistType *playlist1, playlistType *playlist2){
    if(playlist1 == NULL || playlist2 == NULL) return 0;
     
    cellType *cell1 = NULL, *cell2 = NULL;
    int n = 0;

    for(cell1 = playlist1->firstCell; cell1; cell1 = cell1->nextCell){
        for(cell2 = playlist2->firstCell; cell2; cell2 = cell2->nextCell){
            if(!strcmp(getSongName(cell1->song), getSongName(cell2->song))) n++;
        }
    }

    return n;
}

int isMatch(playlistType * playlist) {
return playlist -> match == 1;
}

playlistType * matchPlaylist(playlistType * original, playlistType * toMatch) {

    original -> match = 0;

    playlistType * match = createPlaylist(original -> playlistName);
    match -> match = 1;

    cellType * runner1 = original -> firstCell;

    while(runner1) {

        insertCell(match, runner1 -> song);
        runner1 = runner1 -> nextCell;

    }

    cellType * runner2 = toMatch -> firstCell;
    int alreadyExists = 0;

    while(runner2) {

        runner1 = original -> firstCell;

        if(!thereIsThisSong(original, getSongName(runner2 -> song))) {
            insertCell(match, runner2 -> song);
        }

        runner2 = runner2 -> nextCell;
    }

return match;
}

void addToFrom(playlistType * dest, playlistType * src) {

    cellType * songToAdd = src -> firstCell;
    int alreadyExists = 0;

    while(songToAdd) {

        cellType * checkInDest = dest -> firstCell;

        if(!thereIsThisSong(dest, getSongName(songToAdd -> song))) {
            insertCell(dest, songToAdd -> song);
        }

        songToAdd = songToAdd -> nextCell;
    }

}