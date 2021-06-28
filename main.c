#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x=0;

struct Node{
    int id; // id usado para ordenar por ordem de inserção.
    char title[15];
    struct Node *prev;
    struct Node *next;
};

//insert at end
void insertAtEnd(struct Node** head){

    char title_aux[256];
    printf("\nDigite o titulo da musica:");
    scanf("%s", title_aux);

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->next = NULL;
    strcpy(newNode->title, title_aux);

    //verificando se a lista está vazia.
    if(*head == NULL){
        newNode->prev = NULL;
        newNode->id = x;
        (*head) = newNode;
        return;
    }

    struct Node* last = (*head);

    while(last->next != NULL){
       last = last->next;
    }

    last->next = newNode;
    newNode->id = last->id + 1;
    newNode->prev = last;
    x++;
}

int list(struct Node* head){

    if(head == NULL){
        printf("Lista vazia");
        return 0;
    }

    struct Node* aux = head;
    while(aux != NULL){
        printf("\n%d", aux->id);
        printf(" %s", aux->title);
        aux = aux->next;
    }
    return 1;

}
//item = elemento a ser excluido
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
    return;


}
//retorna o endereço do item que está tocando.
struct Node* playSong(struct Node* item){
    system("pkill mpv");
    char aux_command[256];
    char command[256];
    strcpy(aux_command, " --no-audio-display --no-resume-playback --no-terminal --input-ipc-server=/tmp/mpvsocket &");
    strcpy(command, "mpv ");
    strcat(command, item->title);
    strcat(command, ".mp3");
    strcat(command, aux_command);
				//mpv 2pac.mp3 --no-audio-display --no-resume-playback --no-terminal --input-ipc-server=/tmp/mpvsocket &
				// para pausar: echo '{ "command": ["set_property", "pause", true] }' | socat - /tmp/mpvsocket
				//para voltar o play: echo '{ "command": ["set_property", "pause", false] }' | socat - /tmp/mpvsocket
				//matar processo: pkill mpv
    system(command);

    return item;

}

void stop (){

    system("echo \'{ \"command\" : [\"set_property\", \"pause\", true] }\' | socat - /tmp/mpvsocket");
}

void continueSong(){
    system("echo \'{ \"command\" : [\"set_property\", \"pause\", false] }\' | socat - /tmp/mpvsocket");
}
struct Node* returnItem (struct Node* head, int id){
    struct Node* aux = head;

    while(aux->id != id){
        aux = aux->next;
    }

    return aux;
}
void delete_list(struct Node** head){
    struct Node* current = (*head);
    struct Node* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
        in the caller. */
    (*head) = NULL;
}
int main(){


    printf("echo \'{ \"command\" : [\"set_porperty\", \"pause\", true] }\' | socat - /tmp/mpvsocket");
    struct Node* head = NULL;
    struct Node* aux_node;
    int option = -1;
    int aux;
    do{
        printf("\n\n");
        printf("\n0 - Sair");
        printf("\n1 - Inserir");
        printf("\n2 - Excluir");
        printf("\n3 - Listar");
        printf("\n4 - Ordenar por Título");
        printf("\n5 - Ordenar por ordem de inserção");
        printf("\n6 - Anterior\n");
        printf("\n7 - Play");
        printf("\n8 - Proxima");
        printf("\n9 - Pausar");
        printf("\n10 - Voltar a Tocar");
        scanf("%d", &option);

        switch(option){

            case 1:
                insertAtEnd(&head);
                break;

            case 2:
                if(list(head)==1){
                    printf("\nQual Musica deseja excluir? ");
                    scanf("%d", &aux);
                    //returnItem retorna o endereço do item com o id procurado.
                    //dessa forma, a função delete recebe o endereço de head e o endereço do elemento a ser removido
                    delete(&head, returnItem(head, aux));
                }
                break;

            case 3:
                list(head);
                break;

            case 6:

                if(aux_node->prev != NULL){
                    aux_node = playSong(aux_node->prev);
                }

                break;
            case 7:

                aux_node = playSong(head);

                break;

            case 8:
                if(aux_node->next != NULL){
                    aux_node = playSong(aux_node->next);
                }
                break;
            case 9:
                stop();
                break;
            case 10:
                continueSong();
                break;
            default:
                break;


        }
    }while(option != 0);
        // struct Node* head = (struct Node*) malloc(sizeof(struct Node));

    delete_list(&head);
    return 0;
}
