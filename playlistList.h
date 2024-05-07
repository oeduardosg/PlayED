#ifndef playlistList_h
#define platlistList_h

#include <stdio.h>
#include "playlist.h"

typedef struct playlistList playlistList;

playlistList* createPlaylistList();

void insertPlaylist(playlistList * playlistList, playlistType * playlistToAdd);

void filePrintPlaylistList(playlistList * playlistList, char * playlistListName);

void freePlaylistList(playlistList * playlistList);

playlistList * sortBySinger(playlistList * originalList);

int playlistListSimilarities(playlistList * list1, playlistList * list2);

#endif
