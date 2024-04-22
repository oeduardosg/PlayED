#ifndef amizades_h
#define amizades_h

#include <stdio.h>

/*Funcoes com PersonType*/

typedef struct person personType;

personType* createPerson(char *name);

void freePerson(personType *p);

/*Lista de Pessoas*/

typedef struct list PeopleList;

PeopleList* createPeopleList();

void insertPerson(PeopleList *l, personType *p);

void removePerson(PeopleList *l, char *name);

void printPeopleList(PeopleList *l);

void freePeopleList(PeopleList *l);

void freePeople(PeopleList *l);

/*Funcoes com PeopleList*/

personType* searchPerson(PeopleList *l, char *name);

void addFriend(PeopleList *l, char *name1, char *name2);

void printFriendsOf(PeopleList *l, char *name);

PeopleList* readFriends();

#endif