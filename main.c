#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "player.h"
#include "list.h"

int main(){
    struct Node* head = NULL;
    int count = readPlaylist(&head);
    if(count <= 0){
	    count = 1;
    }
    struct Node* current_song = NULL;
    int option = -1;
    int insert_option;
    int item_id;
    int success;
    char aux_title[256];
    do{
    	success=0;
        printf("\n\n");
        printf("**** MENU ****");
        printf("\n0 - Sair");
        printf("\n1 - Inserir");
        printf("\n2 - Excluir");
        printf("\n3 - Listar");
        printf("\n4 - Ordenar por Ordem de Insercao");
        printf("\n5 - Ordenar por Título");
        printf("\n6 - Anterior");
        printf("\n7 - Play");
        printf("\n8 - Proxima");
        printf("\n9 - Pausar");
        printf("\n10 - Voltar a Tocar\n");
        scanf("%d", &option);
        switch(option){

            case 1:
                system("clear");
                printf("\n1 - Inserir no Inicio");
                printf("\n2 - Inserir entre duas musicas");
                printf("\n3 - Inserir no Final\n");
                scanf("%d", &insert_option);

                switch(insert_option){
                    case 1:

                        printf("\nDigite o nome da musica: ");
                        scanf("%s", aux_title);
                        success = insertAtBegin(&head, aux_title, count);
                        break;
                    case 2:
                        if(!isEmpty(head)){
                            list(head);
                            printf("\nDeseja inserir apos qual musica?\n");
                            scanf("%d", &item_id);
                            success = insert(returnItem(head, item_id), count);
                        }
                        break;
                    case 3:
                        printf("\nDigite o nome da musica: ");
                        scanf("%s", aux_title);
                        success = insertAtEnd(&head, aux_title, count);
                        break;
                    default:
                        printf("\nValor Invalido");
                        break;
                }
                if(success==1){
		            count++;
                    printf("\nMusica adicionada com successo.");
                }
                break;

            case 2:
                if(!isEmpty(head)){
                    list(head);
                    printf("\nQual Musica deseja excluir?\n");
                    scanf("%d", &item_id);
                    success = removeItem(&head, returnItem(head, item_id));
                    if(success==1){
                        count--;
                    }
                }
                break;

            case 3:
                list(head);
                break;
            case 4:
                sortById(&head);
                break;
            case 5:
                sortByTitle(&head);
                break;
            case 6:
                if((current_song != NULL) && (current_song->prev != NULL)){
                    current_song = playSong(current_song->prev);
                }
                break;
            case 7:
                if(!(isEmpty(head))){
                    current_song = playSong(head);
                }
                break;
            case 8:

                if((current_song != NULL) && (current_song->next != NULL)){
                    current_song = playSong(current_song->next);
                }

                break;
            case 9:

                if(current_song != NULL){
                    stop();
                }

                break;
            case 10:
                if(current_song != NULL){
                    continueSong();
                }
                break;

            default:
                break;
        }
    }while(option != 0);

    savePlaylist(head);
    deleteList(&head);
    
    return 0;
}
