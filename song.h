#ifndef _SONG_H_
#define _SONG_H_

typedef struct songType songType;

songType * createSong(char * songName, char * singerName);

void filePrintSong(songType * song, FILE *file);

void freeSong(songType * song);

char * getSongName(songType * song);

char * getSingerName(songType * song);

#endif