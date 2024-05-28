#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node{
    double value;
    struct node *next;
} Node;

typedef struct linkedList{
    Node *head;
} LinkedList;

/*typedef struct {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    int sex, age;
    double height;
} User;

typedef struct {
    User users[MAX_USER_COUNT];
    int count;
} UserDatabase;*/

LinkedList* createList();

void addNode(LinkedList *list, double val);

void printList(LinkedList *list);

void deleteNode(LinkedList *list, double val);
#endif
