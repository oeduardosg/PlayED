#ifndef _SONG_H_
#define _SONG_H_


typedef struct songType songType;

songType * createSong(char * songName, char * singerName);

void printSong(songType * song);

void freeSong(songType * song);

#endif