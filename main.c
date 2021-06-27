#include <stdio.h>
#include <stdlib.h>


struct Node{
    int id; // id usado para ordenar por ordem de inserção.
    char title[15];
    struct Node *prev;
    struct Node *next;
};

void insert(struct Node** head, char title[15]){

}

void delete(struct Node** head, char title[15]){

}

void play(struct Node* head, int i){

}
int main(){

    int option = -1;

    do{
        printf("\n0 - Sair");
        printf("\n1 - Inserir");
        printf("\n2 - Excluir");
        printf("\n3 - Listar");
        printf("\n4 - Ordenar por Título");
        printf("\n5 - Ordenar por ordem de inserção");
        printf("\n6 - Play");
        printf("\n7 - Pausar");
        printf("\n8 - Proxima");
        printf("\n9 - Anterior");
        scanf("%d", &option);

        switch(option){

            case 7:
                //play
                //toca primeiro elemento
                break;



        }
    }while(option != 0);
        // struct Node* head = (struct Node*) malloc(sizeof(struct Node));
        struct Node* head = NULL;

    return 0;
}
