#include <stdlib.h>
#include <stdio.h>
#include "../include/LinkedList.h"

LinkedList* createList(){
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void addNode(LinkedList *list, double val){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = NULL;
    if (list->head == NULL){
        list->head = newNode;
    }
    else{
        Node *temp = list->head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(LinkedList *list){
    Node *temp = list->head;
    while (temp != NULL){
        printf("%.2f ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void deleteNode(LinkedList *list, double val){
    Node *temp = list->head, *prev;
    // If head node itself holds the value to be deleted
    if (temp != NULL && temp->value == val){
        list->head = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
    // Find previous node of the node to be deleted
    while (temp != NULL && temp->value != val){
        prev = temp;
        temp = temp->next;
    }
    // If value was not present in linked list
    if (temp == NULL){
        printf("Value not found in list.\n");
        return;
    }
    // Unlink the node from linked list
    prev->next = temp->next;
    free(temp); // Free memory
}
