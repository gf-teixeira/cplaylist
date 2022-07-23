#ifndef NODE_H_
#define NODE_H_

struct Node{
    int id; 
    char title[256];
    struct Node *prev;
    struct Node *next;
};

#endif // NODE_H_
