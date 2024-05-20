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
 * Se printMatch for 0, printa as playlists normais na pasta Saida, caso contrario printa as playlists match na pasta Merge
*/
void filePrintPlaylistList(playlistListType * playlistList, char * name, int printMatch);

/**
 * Libera uma Lista de Playlists, incluindo as Playlists
 * 
 * input: playlistList (ponteiro para Lista de Pessoas a ser liberada)
*/
void freePlaylistList(playlistListType * playlistList);

/**
 * Reorganiza toda a lista de playlists para que as playlists estejam separadas por cantor/bandas apenas
 * 
 * input: origialList (ponteiro para a lista de playlists a ser reformulada)
 * output: ponteiro para a nova lista de playlists atualizada
*/
playlistListType * sortBySinger(playlistListType * originalList);

/**
 * Compara as similaridades entre duas Listas de Playlists
 * 
 * inputs: list1 e list2 (ponteiros para as Listas de Playlists a serem comparadas)
 * 
 * output: numero de músicas em comum entre as Listas de Playlists
*/
int playlistListSimilarities(playlistListType * list1, playlistListType * list2);

/**
 * Imprime a quantidade de playlists na lista e o nome de cada uma delas em arquivo
 * 
 * input: playlistList (ponteiro para lista de playlist a impressa)
 * input: file (nome do arquivo onde será impresso)
*/
void printRefactoredPlaylistList(playlistListType * playlistList, FILE * file);

/**
 * Realiza o match entre duas listas de playlist, criando e inserindo playlists novas à list1
 * 
 * inputs: list1 e list2 (ponteiros para as Listas de Playlists a serem somadas)
*/
void matchPlaylistLists(playlistListType * list1, playlistListType * list2);

#endif
