#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "song.h"

typedef struct playlistType playlistType;

/**
 * Cria uma playlist
 * 
 * input: playlistName (nome da playlist que será criada)
 * output: ponteiro para playlist nova
*/
playlistType * createPlaylist(char * playlistName);

/**
 * Insere uma nova célula de música na playlist
 * 
 * input: playlist (ponteiro para playlist)
 * input: song (música a ser adicionada)
*/
void insertCell(playlistType * playlist, songType * song);

/**
 * Imprime a playlist
 * 
 * input: ponteiro para playlist a ser impressa
 * input: string com o nome do usuário o qual a playlist pertence
 * input: inteiro que imprimirá uma playlist em um diretório de merge caso 1
*/
void printPlaylist(playlistType * playlist, char *name, int printMatch);

/**
 * Libera a playlist
 * 
 * input: ponteiro para playlist a ser liberada
*/
void freePlaylist(playlistType * playlist);

/**
 * Lê uma playlist em um arquivo
 * 
 * input: string com o nome do arquivo de texto a ser lido
 * output: ponteiro para a playlist lida
*/
playlistType * readPlaylistFile(char * playlistFileName);

/**
 * Confere se existe pelo menos uma música na playlist
 * 
 * input: ponteiro para playlist a ser conferida
 * output: inteiro com valor 1 caso exista música e 0 caso não
*/
int thereIsSong(playlistType * playlist);

/**
 * Verifica se existe uma determinada Música em uma Playlist
 * 
 * input: playlist (ponteiro para a playlist) e songName (nome da música a ser verificada)
 * 
 * output: inteiro com valor 1 se a Música existe na playlist e 0 caso contrário
*/
int thereIsThisSong(playlistType * playlist, char * songName);

/**
 * Dá o nome do primeiro cantor da playlist
 * 
 * input: playlist (ponteiro para playlist a ser conferida)
 * output: string de nome do primeiro cantor da playlist
*/
char * getFirstSingerName(playlistType * playlist);

/**
 * Devolve o nome da playlist
 * 
 * input: playlist (ponteiro para playlist a ser conferida)
 * output: string de nome da playlist
*/
char * getPlaylistName(playlistType *playlist);

/**
 * Recorta todas as músicas de um cantor/banda para outra playlist
 * 
 * input: singerPlaylist (ponteiro para playlist que receberá as músicas)
 * input: sourcePlaylist (ponteiro para a playlist que cederá as músicas)
 * input: singerName (string com nome do cantor/banda)
*/
void clipSingerToPlaylist(playlistType * singerPlaylist, playlistType * sourcePlaylist, char * singerName);

/**
 * Calcula a similaridade entre duas Playlists
 * 
 * inputs: playlist1, playlist2 (ponteiros para as Playlists a serem comparadas)
 * 
 * output: inteiro com o número de Músicas em comum entre as duas Playlists
*/
int playlistSimilarities(playlistType *playlist1, playlistType *playlist2);

/**
 * Retorna se uma playlist é match
 * 
 * input: playlist (ponteiro para playlist a ser conferida)
 * output: inteiro com valor 1 caso a playlist seja match
*/
int isMatch(playlistType * playlist);

/**
 * Faz um merge entre as playlists (sem repetir músicas de mesmo nome)
 * 
 * inputs: original e tomatch (ponteiros para as playlists a serem somadas)
 * output: ponteiro para a nova playlist de merge entre as duas anteriores
*/
playlistType * matchPlaylist(playlistType * original, playlistType * tomatch);

/**
 * Adiciona músicas de uma playlist a outra (sem que se repitam)
 * 
 * input: toAdd (ponteiro para a playlist que receberá as músicas)
 * input: source (ponteiro para a playlist que cederá mais músicas)
*/
void addToFrom(playlistType * toAdd, playlistType * source);

#endif
