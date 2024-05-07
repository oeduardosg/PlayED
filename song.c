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

void filePrintSong(songType * song, FILE* file) {

    fprintf(file, "%s - %s\n", song -> singerName, song -> songName);

}

char * getSongName(songType * song) {
    return song -> songName;
}

char * getSingerName(songType * song) {
    return song -> singerName;
}

void clipSongData(char * songName, char * singerName, char * songString) {
    
    for(int i = 0; songString[i] != '\0'; i++) {
        if(songString[i] == ' ' && songString[i + 1] == '-') {
            for(int j = 0; j < i; j++) {
                singerName[j] = songString[j];
            }
            singerName[i] = '\0';
            char * start = songString + i + 3;
            strcpy(songName, start);
            return;
        }
    }

}
