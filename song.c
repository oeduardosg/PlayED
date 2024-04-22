#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"

struct songType {
    char * songName;
    char * singerName;
};

songType * createSong(char * songName, char * singerName) {

    songType * song = (songType *) calloc(1, sizeof(songType));

    song -> songName = strdup(songName);
    song -> singerName = strdup(singerName);

return song;
}

void freeSong(songType * song) {
    
    free(song -> songName);
    free(song -> singerName);
    free(song);

}

void printSong(songType * song) {

    printf("%s - %s", song -> songName, song -> singerName);

}