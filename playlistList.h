#ifndef playlistList_h
#define platlistList_h

#include <stdio.h>
#include "playlist.h"

typedef struct playlistList playlistList;

playlistList* createPlaylistList();

void insertPlaylist(playlistList *l, playlistType *p);

void printPlaylistList(playlistList *l, char *name);

void freePlaylistList(playlistList *l);

playlistList * sortBySinger(playlistList * originalList);

#endif