/*********
Nome do programador: Gabriel Teixeira
Data do Programa: 28/06/2021
Descrição do programa: Implementação de uma playlist utilizando lista duplamente encadeada.
O programa consegue tocar as musicas se os nomes forem válidos e o arquivo mp3  de mesmo nome
estiver na pasta do programa. Exemplo: Há um arquivo musica.mp3 na pasta do projeto, então
ao inserir uma musica na lista basta inserir o nome "musica".
Principais dificuldades encontradas nesta implementação: -
OBS: o programa possue alguns métodos nativos de sistemas Unix, além de utilizar o mpv media player
por linha de comando, então não é possível tocar música utilizando Windows.
Para rodar o sistema devidamente é necessário ter: *SO derivado de Unix *mpv player instalado.
*********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count=0;

struct Node{
    int id; // id é incrementado por ordem de inserção
    char title[256];
    struct Node *prev;
    struct Node *next;
};

int isEmpty(struct Node* head){
    if(head == NULL){
        return 1;
    }
    return 0;
}
void insertAtBegin(struct Node** head, char title[], int id){

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->prev = NULL;
    new_node->id = id;
    //se a lista estiver vazia o ponteiro head apontará para o novo elemento
    // e o atributo next do novo elemento recebe NULL
    strcpy(new_node->title, title);
    if(isEmpty(*head)){
        (*head) = new_node;
        new_node->next = NULL;

        system("clear");
        printf("\nMusica adicionada com sucesso.");
        return;
    }

    new_node->next = (*head);
    (*head)->prev = new_node;
    (*head) = new_node;

    system("clear");
    printf("\nMusica adicionada com sucesso.");
}

void insert(struct Node* item){
    char title_aux[256];
    printf("\nDigite o nome da musica: ");
    scanf("%s", title_aux);

    struct Node * new_node = (struct Node*) malloc(sizeof(struct Node));

    strcpy(new_node->title, title_aux);
    new_node->id = count;
    new_node->prev = item;
    new_node->next = item->next;

    if(item->next != NULL){
        item->next->prev = new_node;
    }
    item->next = new_node;
    count++;

    system("clear");
    printf("\nMusica adicionada com sucesso.");
}
void insertAtEnd(struct Node** head, char title[], int id){


    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->next = NULL;
    new_node->id = id;

    strcpy(new_node->title, title);

    if(*head == NULL){
        printf("ops");
        new_node->prev = NULL;
        (*head) = new_node;
        system("clear");
        printf("\nMusica adicionada com sucesso.");
        return;
    }

    struct Node* last = (*head);

    while(last->next != NULL){
       last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;

    system("clear");
    printf("\nMusica adicionada com sucesso.");
}

void list(struct Node* head){

    system("clear");
    if(isEmpty(head)){
        printf("Lista vazia");
        return;
    }
    printf("\n*** Playlist ***\n");
    struct Node* aux = head;
    while(aux != NULL){
        printf("[%d]", aux->id);
        printf(" %s ", aux->title);
        aux = aux->next;
    }


}

void sortById(struct Node** head){
    if(isEmpty(*head)){
        printf("\nLista vazia.");
        return;
    }
    int swapped;
    struct Node* current = *head;
    struct Node* next;
    while(current && current->next){
        next = current->next;
        while(next){
            swapped =0;
            if(current->id > next->id){
                swapped =1;
                const struct Node* aux_current_prev = current->prev;
                const struct Node* aux_current_next = current->next;
                if(current->prev != NULL){
                    current->prev->next = next;
                }
                if(current->next != NULL && current->next != next){
                    current->next->prev = next;
                }
                if(next->prev != NULL && next->prev != current){
                    next->prev->next = current;
                }
                if(next->next != NULL){
                    next->next->prev = current;
                }
                if(next->prev != current){
                    current->prev = next->prev;
                }else{
                    current->prev = next;
                }
                current->next = next->next;
                next->prev = (struct Node*) aux_current_prev;
                if(aux_current_next != next){
                    next->next = (struct Node*)aux_current_next;
                }else{
                    next->next = current;
                }
                if(current == (*head)){
                    (*head) = next;
                }
            }
            if(swapped==1){
                current = next;
            }
            next = next->next;
        }
        current = current->next;
    }

    system("clear");
    list(*head);
}

void sortByTitle(struct Node** head){
    if(isEmpty(*head)){
        printf("\nLista vazia.");
        return;
    }
    int swapped;
    struct Node* current = *head;
    struct Node* next;
    while(current && current->next){
        next = current->next;
        while(next){
            swapped =0;
            if(strcmp(current->title, next->title)>0){
                swapped =1;
                const struct Node* aux_current_prev = current->prev;
                const struct Node* aux_current_next = current->next;
                if(current->prev != NULL){
                    current->prev->next = next;
                }
                if(current->next != NULL && current->next != next){
                    current->next->prev = next;
                }
                if(next->prev != NULL && next->prev != current){
                    next->prev->next = current;
                }
                if(next->next != NULL){
                    next->next->prev = current;
                }
                if(next->prev != current){
                    current->prev = next->prev;
                }else{
                    current->prev = next;
                }
                current->next = next->next;
                next->prev = (struct Node*) aux_current_prev;
                if(aux_current_next != next){
                    next->next = (struct Node*)aux_current_next;
                }else{
                    next->next = current;
                }
                if(current == (*head)){
                    (*head) = next;
                }
            }
            if(swapped==1){
                current = next;
            }
            next = next->next;
        }
        current = current->next;
    }
    system("clear");
    list(*head);
}



void delete(struct Node** head, struct Node* item){

    if((*head) == item){
        (*head) = item->next;
    }
    //se  o elemento a ser deletado não é o último
    //o atributo prev (anterior) do elemento após o item a ser excluido recebe o elemento anterior ao item a ser excluido
    if(item->next != NULL){
        item->next->prev = item->prev;
    }
    //se o elemento a ser deletado não é o primeiro:
    //o antributo next (próximo) do elemento anterior recebe o atribudo next (próximo) do elemento a ser deletado.
    if(item->prev != NULL){
        item->prev->next = item->next;
    }
    free(item);
    system("clear");
    printf("\n Musica removida.");
    count--;
    return;


}
//retorna o endereço do item que está tocando.
struct Node* playSong(struct Node* item){
    system("pkill mpv");
    char aux_command[256];
    char command[256];

    strcpy(command, "mpv ");
    strcat(command, item->title);
    strcat(command, ".mp3");



    /*mpv can be controlled by external programs using the JSON-based IPC protocol. It can be enabled by specifying the path
     * to a unix socket or a named pipe using the option
     * --input-ipc-server. Clients can connect to this socket and send commands to the player or receive events from it.*/
    strcpy(aux_command, " --no-audio-display --no-resume-playback --no-terminal --input-ipc-server=/tmp/mpvsocket &");
    strcat(command, aux_command);
    system(command);

    system("clear");
    printf("\nTocando \U0001F3B5 %s \U0001F3B5", item->title);
    return item;

}

void stop (){

    system("echo \'{ \"command\" : [\"set_property\", \"pause\", true] }\' | socat - /tmp/mpvsocket");

    system("clear");
}

void continueSong(){
    system("echo \'{ \"command\" : [\"set_property\", \"pause\", false] }\' | socat - /tmp/mpvsocket");

    system("clear");
}
struct Node* returnItem (struct Node* head, int id){
    struct Node* aux = head;

    while(aux->id != id){
        aux = aux->next;
    }

    return aux;
}
void savePlaylist(struct Node* head){
    struct Node* item = head;
    FILE *f_playlist;
    f_playlist = fopen("playlist.dat", "wb+");

    while(item != NULL){
        fwrite(item, sizeof(struct Node), 1, f_playlist);
        item = item->next;
    }
    fclose(f_playlist);
}
void readingPlaylist(struct Node** head){
    FILE * f_playlist;
    int new_count=0;
    if ((f_playlist = fopen("playlist.dat", "ab+")) == NULL)
	{
		printf("File open error\n ");
		return;
	}
    struct Node* item = (struct Node*)malloc(sizeof(struct Node));

    while(fread(item, sizeof(struct Node), 1, f_playlist)){
        if(item){
            new_count = item->id;
            insertAtEnd(head, item->title, item->id);
        }
    }
    count = new_count;
    system("clear");
}

void deleteList(struct Node** head){
    struct Node* current = (*head);
    struct Node* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    (*head) = NULL;
}
int main(){


    struct Node* head = NULL;

    readingPlaylist(&head);
    struct Node* current_song = NULL;
    int option = -1;
    int insert_option;
    int aux;
    char aux_title[256];
    do{
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
                        count++;
                        insertAtBegin(&head, aux_title, count);
                        break;
                    case 2:
                        if(!isEmpty(head)){
                            list(head);
                            printf("\nDeseja inserir apos qual musica?\n");
                            scanf("%d", &aux);
                            insert(returnItem(head, aux));
                        }
                        break;
                    case 3:
                        printf("\nDigite o nome da musica: ");
                        scanf("%s", aux_title);
                        count++;
                        insertAtEnd(&head, aux_title, count);
                        break;
                    default:
                        printf("\nValor Invalido");
                        break;

                }
                break;

            case 2:
                if(!isEmpty(head)){
                    list(head);
                    printf("\nQual Musica deseja excluir?\n");
                    scanf("%d", &aux);
                    //returnItem retorna o endereço do item com o id procurado.
                    //dessa forma, a função delete recebe o endereço de head e o endereço do elemento a ser removido
                    delete(&head, returnItem(head, aux));
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
