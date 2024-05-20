#ifndef _SONG_H_
#define _SONG_H_

typedef struct songType songType;

/**
 * Cria uma música
 * 
 * input: songName(string com nome da música)
 * input: singerName(string com nome do cantor/banda)
 * output: ponteiro para songType
*/
songType * createSong(char * songName, char * singerName);

/**
 * Imprime música em arquivo
 * 
 * input: song (ponteiro para música a ser impressa em arquivo)
 * input: file (ponteiro para o arquivo em que será impressa a música)
*/
void filePrintSong(songType * song, FILE *file);

/**
 * Libera música
 * 
 * input: song (ponteiro para música a ser liberada)
*/
void freeSong(songType * song);

/**
 * Retorna string de nome da música
 * 
 * input: song (ponteiro para música a ser analisada)
 * output: string de nome da música
*/
char * getSongName(songType * song);

/**
 * Retorna string de nome do cantor/banda
 * 
 * input: song (ponteiro para música a ser analisada)
 * output: string de nome do cantor/banda
*/
char * getSingerName(songType * song);

/**
 * Separa os dados de uma string em nome da música e nome do cantor/banda
 * 
 * input: songName (string que receberá o nome da música)
 * input: singerName (string que receberá o nome do cantor/banda)
 * input: songString (string geral com os dados a serem recortados)
*/
void clipSongData(char * songName, char * singerName, char * songString);

#endif