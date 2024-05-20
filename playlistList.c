#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "playlistList.h"

typedef struct cellType cellType;

struct playlistList{
    cellType * first;
    cellType * last;
};

struct cellType{
    playlistType * playlist;
    cellType * next;
    cellType * prior;
};

playlistListType * createPlaylistList(){

    playlistListType * playlist = malloc(sizeof(playlistListType));

    playlist -> first = playlist -> last = NULL;

    return playlist;
}

void insertPlaylist(playlistListType * playlistList, playlistType * playlistToAdd){

    if(!playlistList) return;

    cellType * cell = malloc(sizeof(cellType));

    cell -> playlist = playlistToAdd;

    if(playlistList -> last != NULL) playlistList -> last -> next = cell;
    cell -> next = NULL;
    cell -> prior = playlistList -> last;

    if(playlistList -> first == NULL) playlistList -> first = cell;
    playlistList -> last = cell;
}

void filePrintPlaylistList(playlistListType * playlistList, char * name, int printMatch){

    if(!playlistList) return;

    if(playlistList -> first == NULL){
        printf("%s não possui playlists\n\n", name);
        return;
    }
    printf("Playlists de %s:\n", name);

    char folderName[100];

    for(cellType * cell = playlistList -> first; cell; cell = cell->next){
        if(printMatch) sprintf(folderName, "Merge/%s", name);
        else sprintf(folderName, "Saida/%s", name);
        mkdir(folderName, S_IRWXU);
        
        printPlaylist(cell->playlist, name, printMatch);
    }

    printf("\n");
}

void freePlaylistList(playlistListType * playlistList){

    if(!playlistList) return;

    cellType * cell = playlistList -> first;
    cellType * aux = playlistList -> first;

    while(aux){
        cell = aux;
        aux = cell -> next;
        freePlaylist(cell -> playlist);
        free(cell);
    }

    free(playlistList);
}

playlistListType * sortBySinger(playlistListType * originalList) {

    playlistListType * sortedList = createPlaylistList();

    //aChecker fará a primeira iteração passando por dentro de cada uma das playlists da lista
    cellType * aChecker = originalList -> first;

    while(aChecker) {

        /*Enquantro ouver musicas dentro da playlist em aChecker, elas serão transformadas em novas 
        * playlists a partir do nome do cantor encontrado
        */
        while(thereIsSong(aChecker -> playlist)) {

            char * singer = getFirstSingerName(aChecker -> playlist);
            playlistType * singerPlaylist = createPlaylist(singer);
            cellType * bChecker = aChecker;

            /*bChecker irá passar por dentro de TODAS as playlists (incluindo a ques está em aChecker) 
            * recortando as músicas do cantor passado e enviando as músicas para a playlist nova
            */
            while(bChecker) {
                
                clipSingerToPlaylist(singerPlaylist, bChecker -> playlist, singer);
                bChecker = bChecker -> next;

            }

            insertPlaylist(sortedList, singerPlaylist);
            //Dessa forma, as músicas de um mesmo cantor estarão sendo removidas de todas as playlists por clipSinger a cada iteração

        }

    aChecker = aChecker -> next;

    }

    freePlaylistList(originalList);

return sortedList;
}

int playlistListSimilarities(playlistListType * list1, playlistListType * list2){

    if(list1 == NULL || list2 == NULL) return 0;

    cellType * cell1 = NULL, * cell2 = NULL;
    int n = 0;

    for(cell1 = list1 -> first; cell1; cell1 = cell1 -> next){
        for(cell2 = list2 -> first; cell2; cell2 = cell2 -> next){
            if(!strcmp(getPlaylistName(cell1 -> playlist), getPlaylistName(cell2 -> playlist)))
                n += playlistSimilarities(cell1 -> playlist, cell2 -> playlist);
        }
    }

    return n;
}

void printRefactoredPlaylistList(playlistListType * playlistList, FILE * file) {

    if(!playlistList) return;

    cellType * runner = playlistList -> first;
    int playlistsQuantity = 0;

    while(runner) {
        playlistsQuantity++;
        runner = runner -> next;
    }

    runner = playlistList -> first;
    
    fprintf(file, "%d", playlistsQuantity);

    while(runner) {
        fprintf(file, ";%s.txt", getPlaylistName(runner -> playlist));
        runner = runner -> next;
    }

}

void matchPlaylistLists(playlistListType * list1, playlistListType * list2) {

    int foundMatch = 0;
    cellType * runner1 = list1 -> first;

    // runner1 vai receber uma playlist e continuar a verificação dela APENAS se não for uma playlist de match
    while(runner1 && isMatch(runner1 -> playlist) != 1) {

        cellType * runner2 = list2 -> first;

        // runner2 recebe a primeira playlist da lista 2 e também prosseguirá a verificação apenas se não for match
        while(runner2 && isMatch(runner1 -> playlist) != 1) {

            // Visto que todas as playlists tem o nome do artista, prosseguir verificando se runner1 e runner2 tem o mesmo nome
            // Caso tenham o mesmo nome, deve ser realizado o match entre elas
            if(!strcmp(getPlaylistName(runner1 -> playlist), getPlaylistName(runner2 -> playlist)) && !isMatch(runner1 -> playlist)) {

                cellType * runner3 = list1 -> first;

                /* runner3 vai ter o trabalho de:
                * Caso uma playlist de merge com o mesmo nome do artista seja encontrada, as músicas novas serão adicionadas
                * a essa playlist já existente
                * Caso não exista uma playlist no formato citado, runner3 permitirá que uma nova playlist seja criada e
                * fará o match entre runner1 e runner2
                */
                while(runner3) {

                    if(!strcmp(getPlaylistName(runner2 -> playlist), getPlaylistName(runner3 -> playlist)) && isMatch(runner3 -> playlist)) {
                        addToFrom(runner3 -> playlist, runner2 -> playlist);
                        foundMatch = 1;
                    }

                    runner3 = runner3 -> next;
                }
                
                if(!foundMatch) {
                    playlistType * match = matchPlaylist(runner1 -> playlist, runner2 -> playlist);
                    insertPlaylist(list1, match);
                }

                foundMatch = 0;
            }

            runner2 = runner2 -> next;
        }

        runner1 = runner1 -> next;
    }

}