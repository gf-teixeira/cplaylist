#ifndef NODE_H_
#define NODE_H_


struct Node{
    int id; // id é incrementado por ordem de inserção
    char title[256];
    struct Node *prev;
    struct Node *next;
};

#endif // NODE_H_
