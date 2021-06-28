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
void insertAtBegin(struct Node** head){

    char title_aux[256];
    printf("\nDigite o nome da musica:");
    scanf("%s", title_aux);

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));


    strcpy(new_node->title, title_aux);
    new_node->prev = NULL;
    new_node->id = count;
    count++;
    //se a lista estiver vazia o ponteiro head apontará para o novo elemento
    // e o atributo next do novo elemento recebe NULL

    if(isEmpty(*head)){
        (*head) = new_node;
        new_node->next = NULL;
        return;
    }

    new_node->next = (*head);
    (*head)->prev = new_node;
    (*head) = new_node;

    printf("\nElemento adicionado com sucesso.");
}

void insert(struct Node* item){
    char title_aux[256];
    printf("\nDigite o nome da musica");
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
    printf("\nElemento adicionado com sucesso.");
}
void insertAtEnd(struct Node** head){

    char title_aux[256];
    printf("\nDigite o Nome da musica:");
    scanf("%s", title_aux);

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->next = NULL;
    strcpy(new_node->title, title_aux);

    //verificando se a lista está vazia.
    new_node->id = count;
    count++;
    if(*head == NULL){
        new_node->prev = NULL;
        (*head) = new_node;
        return;
    }

    struct Node* last = (*head);

    while(last->next != NULL){
       last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
    count++;

    printf("\nElemento adicionado com sucesso.");
}

void list(struct Node* head){

    if(isEmpty(head)){
        printf("Lista vazia");
        return;
    }

    struct Node* aux = head;
    while(aux != NULL){
        printf("\n%d", aux->id);
        printf(" %s", aux->title);
        aux = aux->next;
    }


}

void sortById(struct Node** head){
    if(isEmpty(*head)){
        printf("\nLista vazia.");
        return;
    }

    struct Node* current = *head;
    struct Node* next;
    struct Node* aux;

    while(current && current->next){
        next = current->next;

        while(next){
            if(current->id > next->id){
                printf("\ncurrent->prev: %p", current->prev);

                aux=current;
                aux->next = current->next;

                if(current->prev != NULL){
                    current->prev->next = next;
                }
                next->prev = current->prev;

                current->prev = next;
                current->next = next->next;

                next->next = current;

                printf("\nnext->prev: %p", next->prev);

                if(current == (*head)){
                    (*head) = next;
                }
            }
            list(*head);
            next = next->next;
        }
        current = current->next;
    }

}

void sortByTitle(struct Node** head){

    if(isEmpty(*head)){
        printf("\nLista vazia.");
        return;
    }

    struct Node* current = *head;
    struct Node* next;
    struct Node* aux;

    while(current && current->next){
        next = current->next;

        while(next){
            if(strcmp(current->title, next->title)>0){
                printf("\ncurrent->prev: %p", current->prev);

                aux=current;
                aux->next = current->next;

                if(current->prev != NULL){
                    current->prev->next = next;
                }
                next->prev = current->prev;

                current->prev = next;
                current->next = next->next;

                next->next = current;

                printf("\nnext->prev: %p", next->prev);

                if(current == (*head)){
                    (*head) = next;
                }
            }
            list(*head);
            next = next->next;
        }
        current = current->next;
    }

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
    strcpy(aux_command, " --no-audio-display --no-resume-playback --no-terminal --input-ipc-server=/tmp/mpvsocket &");
    strcat(command, aux_command);
    //comando para tocar proxima musica se essa terminar...
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

    struct Node* head = NULL;
    struct Node* aux_node;
    int option = -1;
    int insert_option;
    int aux;
    do{
        printf("\n\n");
        printf("****MENU****");
        printf("\n0 - Sair");
        printf("\n1 - Inserir");
        printf("\n2 - Excluir");
        printf("\n3 - Listar");
        printf("\n4 - Ordenar por Título");
        printf("\n5 - Ordenar por ordem de inserção");
        printf("\n6 - Anterior");
        printf("\n7 - Play");
        printf("\n8 - Proxima");
        printf("\n9 - Pausar");
        printf("\n10 - Voltar a Tocar\n");
        scanf("%d", &option);

        switch(option){

            case 1:
                printf("\n1 - Inserir no Inicio");
                printf("\n2 - Inserir entre duas musicas");
                printf("\n3 - Inserir no Final\n");
                scanf("%d", &insert_option);

                switch(insert_option){
                    case 1:
                        insertAtBegin(&head);
                        break;
                    case 2:
                        if(!isEmpty(head)){
                            list(head);
                            printf("\nDeseja inserir apos qual musica?");
                            scanf("%d", &aux);
                            insert(returnItem(head, aux));
                        }
                        break;
                    case 3:
                        insertAtEnd(&head);
                        break;
                    default:
                        printf("valor invalido");
                        break;

                }
                break;

            case 2:
                if(!isEmpty(head)){
                    list(head);
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
            case 4:
                sortByTitle(&head);
                break;
            case 5:
                sortById(&head);
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

    delete_list(&head);
    return 0;
}
