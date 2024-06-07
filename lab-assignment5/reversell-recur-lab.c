// name: Kaustubha Eluri 
// email: eluri.k@northeastern.edu

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef struct list {
    struct node* head;
} List;

/*-----creating the nodes----------*/
node_t* newNode(int num) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = num;
    node->next = NULL;
    return node;
}

/*---creating linked list----*/
List* init_LL() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

/*---Insert the nodes at the beginning of the list---*/
void insertFirst(List* l, int data) {
    node_t* node = newNode(data);
    node->next = l->head;
    l->head = node;
}

/*----display the output--------*/
void display(List* l) {
    node_t *temp;
    temp = l->head;
    while (temp != NULL) {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/*-------reversing the linked list using recursion------*/
void reverse(List* l, node_t* ptr) {
    if (ptr == NULL) {
        return;
    }
    if (ptr->next == NULL) {
        l->head = ptr;
        return;
    }
    reverse(l, ptr->next);
    ptr->next->next = ptr;
    ptr->next = NULL;
}

/*----Free the nodes-----*/
void freenode(List* l) {
    node_t *temp;
    while (l->head) {
        temp = l->head->next;
        free(l->head);
        l->head = temp;
    }
}

/*-----Main program--------------*/
int main() {
    List *list = init_LL();

    insertFirst(list, 44);
    insertFirst(list, 33);
    insertFirst(list, 22);
    insertFirst(list, 11);
    display(list);
    reverse(list, list->head);
    display(list);

    freenode(list);
    free(list);
    return 0;
}
