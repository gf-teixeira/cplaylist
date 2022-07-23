#ifndef LIST_H
#define LIST_H

int isEmpty(struct Node* head);
void sortById(struct Node** head);
void sortByTitle(struct Node** head);
struct Node* returnItem (struct Node* head, int id);
int insertAtBegin(struct Node** head, char title[], int id);
int insert(struct Node* item, int id);
int insertAtEnd(struct Node** head, char title[], int id);
void list(struct Node* head);
int removeItem(struct Node** head, struct Node* item);
void savePlaylist(struct Node* head);
int readPlaylist(struct Node** head);
void deleteList(struct Node** head);
#endif // LIST_H
