#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "song.h"

typedef struct playlistType playlistType;

playlistType * createPlaylist(char * playlistName);

void insertCell(playlistType * playlist, songType * song);

void printPlaylist(playlistType * playlist);

void freePlaylist(playlistType * playlist);

playlistType * readPlaylistFile(char * playlistFileName);

#endif