#ifndef amizades_h
#define amizades_h

#include <stdio.h>
#include "playlistList.h"

/*Funcoes com PersonType*/

typedef struct person personType;

/**
 * Cria uma Pessoa
 * 
 * inputs: name (nome da Pessoa)
 * 
 * output: ponteiro para a pessoa criada
*/
personType* createPerson(char *name);

/**
 * Libera uma Pessoa
 * 
 * inputs: person (ponteiro para a Pessoa a ser liberada)
*/
void freePerson(personType *person);

/**
 * inputs: person (ponteiro para Pessoa)
 * 
 * output: nome da Pessoa passada por parâmetro
*/
char* getPersonName(personType *person);

/**
 * inputs: person (ponteiro para Pessoa)
 * 
 * output: Lista de Playlists da Pessoa passada por parâmetro
*/
playlistListType* getPersonPlaylists(personType *person);

/**
 * Atribui uma Lista de Playlist à uma Pessoa
 * 
 * inputs: person (ponteiro para Pessoa) e playlistList (ponteiro para Lista de Playlists)
*/
void setPersonPlaylists(personType *person, playlistListType *playlistList);

/*Lista de Pessoas*/

typedef struct list PeopleList;

/**
 * Cria uma Lista de Pessoa
 * 
 * output: ponteiro para a Lista de Pessoas inicializada
*/
PeopleList* createPeopleList();

/**
 * Insere uma Pessoa na Lista
 * 
 * inputs: list (ponteiro para Lista de Pessoas) e person (ponteiro para a Pessoa ser adicionada)
*/
void insertPerson(PeopleList *list, personType *person);

/**
 * Remove uma Pessoa da Lista
 * 
 * inputs: list (ponteiro para Lista de Pessoas) e name (nome da Pessoa a ser removida da Lista)
*/
void removePerson(PeopleList *list, char *name);

/**
 * Imprime uma Lista de Pessoas,
 * printando o Nome, Amigos e Playlists (impressão em arquivo) de cada Pessoa
 * 
 * inputs: list (ponteiro para Lista de Pessoas)
*/
void printPeopleList(PeopleList *list);

/**
 * Libera apenas a Lista de Pessoas e suas Células
 * 
 * inputs: list (ponteiro para Lista de Pessoas)
*/
void freePeopleList(PeopleList *list);

/**
 * Libera apenas as Pessoas da Lista
 * 
 * inputs: list (ponteiro para Lista de Pessoas)
*/
void freePeople(PeopleList *list);

/*Funcoes com PeopleList*/

/**
 * Procura uma Pessoa com determinado nome em uma Lista de pessoas
 * 
 * inputs: list (ponteiro para Lista de Pessoas) e name (nome da Pessoa a ser procurada)
 * 
 * output: a primeira pessoa encontrada com esse nome
 * Caso nao exista ninguém com esse nome, retorna NULL
*/
personType* searchPerson(PeopleList *list, char *name);

/**
 * Adiciona amizade entre duas Pessoas (Pessoa1, Pessoa2),
 * simultaneamente adcionando a Pessoa1 na Lista de Amigos da Pessoa2 e vice-versa
 * 
 * inputs: list (ponteiro para Lista de Pessoa), name1 (nome da Pessoa1) e name2 (nome da Pessoa2)
*/
void addFriend(PeopleList *list, char *name1, char *name2);

/**
 * Imprime a Lista de Amigos da Pessoa com um determinado Nome
 * 
 * inputs: list (ponteiro para Lista de Pessoas) e name (nome da Pessoa cujo amigos serão printados)
*/
void printFriendsOf(PeopleList *list, char *name);

/**
 * Le o arquivo amizade.txt e organiza todas as Pessoas em uma Lista,
 * além de modelar a Rede de Amizades entre essas Pessoas
 * 
 * output: ponteiro para uma Lista de Pessoas completamente organizada
*/
PeopleList* readFriends();

/**
 * Le o arquivo playlists.txt e atribui todas as Playlists às suas determinadas Pessoas
 * 
 * inputs: list (ponteiro para Lista de Pessoas)
*/
void readPeoplePlaylists(PeopleList *list);

/**
 * Cria o arquivo similaridades.txt e 
 * calcula o número de músicas comuns entre amigos de uma Lista de Pessoas
 * 
 * inputs: list (ponteiro para Lista de Pessoas)
*/
void friendsSimilarities(PeopleList *list);

/**
 * Organiza (por nome de cantores) as Playlists de todas as Pessoas da Lista
 * 
 * inputs: list (ponteiro para Lista de Pessoas)
*/
void sortPlayListsPeople(PeopleList *list);

void filePrintRefactored(PeopleList * list);

void matchFriendsPlaylists(PeopleList * list);

#endif