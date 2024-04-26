#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "song.h"

typedef struct playlistType playlistType;

playlistType * createPlaylist(char * playlistName);

void insertCell(playlistType * playlist, songType * song);

void printPlaylist(playlistType * playlist);

void freePlaylist(playlistType * playlist);

playlistType * readPlaylistFile(char * playlistFileName);

int thereIsSong(playlistType * playlist);

char * getFirstSingerName(playlistType * playlist);

void clipSingerToPlaylist(playlistType * singerPlaylist, playlistType * sourcePlaylist, char * singerName);

#endif