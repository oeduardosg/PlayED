#ifndef playlistList_h
#define playlistList_h

#include <stdio.h>
#include "playlist.h"

typedef struct playlistList playlistListType;

playlistListType* createPlaylistList();

void insertPlaylist(playlistListType * playlistList, playlistType * playlistToAdd);

void filePrintPlaylistList(playlistListType * playlistList, char * playlistListName, int printMatch);

void freePlaylistList(playlistListType * playlistList);

playlistListType * sortBySinger(playlistListType * originalList);

int playlistListSimilarities(playlistListType * list1, playlistListType * list2);

void printRefactoredPlaylistList(playlistListType * playlistList, FILE * file);

void matchPlaylistLists(playlistListType * list1, playlistListType * list2);

#endif
