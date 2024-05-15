#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "song.h"

typedef struct playlistType playlistType;

playlistType * createPlaylist(char * playlistName);

void insertCell(playlistType * playlist, songType * song);

void printPlaylist(playlistType * playlist, char *name, int printMatch);

void freePlaylist(playlistType * playlist);

playlistType * readPlaylistFile(char * playlistFileName);

int thereIsSong(playlistType * playlist);

int thereIsThisSong(playlistType * playlist, char * songName);

char * getFirstSingerName(playlistType * playlist);

char * getPlaylistName(playlistType *playlist);

void clipSingerToPlaylist(playlistType * singerPlaylist, playlistType * sourcePlaylist, char * singerName);

int playlistSimilarities(playlistType *playlist1, playlistType *playlist2);

int isMatch(playlistType * playlist);

playlistType * matchPlaylist(playlistType * original, playlistType * tomatch);

void addToFrom(playlistType * toAdd, playlistType * source);

#endif
