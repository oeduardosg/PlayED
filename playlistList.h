#ifndef playlistList_h
#define playlistList_h

#include <stdio.h>
#include "playlist.h"

typedef struct playlistList playlistListType;

/**
 * Cria uma Lista de Playlist
 * 
 * output: ponteiro para a Lista de Playlists inicializada
*/
playlistListType* createPlaylistList();

/**
 * Insere uma Playlist na Lista
 * 
 * input: playlistList (ponteiro para a Lista de Playlists) e
 * input: playlistToAdd (ponteiro para a Playlist a ser adicionada)
*/
void insertPlaylist(playlistListType * playlistList, playlistType * playlistToAdd);

/**
 * Printa uma Lista de Playlists em arquivo
 * 
 * input: playlistList (ponteiro para Lista de Playlists),
 * input: name (nome da Pessoa que tem essa Lista de Playlist)
 * input: printMatch (indica se as playlists normais serão printadas ou as playlists originadas por match/merge)
 * 
 * Se printMatch for 0, printa as playlists match na pasta Merge, caso contrario printa as playlists normais na pasta Saida
*/
void filePrintPlaylistList(playlistListType * playlistList, char * name, int printMatch);

/**
 * Libera uma Lista de Playlists, incluindo as Playlists
 * 
 * input: playlistList (ponteiro para Lista de Pessoas a ser liberada)
*/
void freePlaylistList(playlistListType * playlistList);

playlistListType * sortBySinger(playlistListType * originalList);

/**
 * Compara as similaridades entre duas Listas de Playlists
 * 
 * inputs: list1 e list2 (ponteiros para as Listas de Playlists a serem comparadas)
 * 
 * output: numero de músicas em comum entre as Listas de Playlists
*/
int playlistListSimilarities(playlistListType * list1, playlistListType * list2);

void printRefactoredPlaylistList(playlistListType * playlistList, FILE * file);

void matchPlaylistLists(playlistListType * list1, playlistListType * list2);

#endif
