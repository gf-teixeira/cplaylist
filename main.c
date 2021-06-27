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

void play(struct Node* head, int i){

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
        printf("\n6 - Play");
        printf("\n7 - Pausar");
        printf("\n8 - Proxima");
        printf("\n9 - Anterior\n");
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

            case 7:
                //toca primeiro elemento
                break;
            default:
                break;


        }
    }while(option != 0);
        // struct Node* head = (struct Node*) malloc(sizeof(struct Node));

    delete_list(&head);
    return 0;
}
