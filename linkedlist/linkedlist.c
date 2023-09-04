#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};
typedef struct node node_t;

void printlist(node_t *head) {
    node_t *temporary = head;

    while (temporary != NULL) {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

node_t *create_new_node(int value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}

void insert_after_node(node_t *node_to_insert_after, node_t *newnode) {
    newnode->next = node_to_insert_after->next;
    node_to_insert_after->next = newnode;
}

void delete_node(node_t *head, node_t *node_to_delete) {
    node_t *tmp = head;
    node_t *prev_node = NULL;

    while (tmp != NULL) {
        if (tmp->value == node_to_delete->value) {
            if (prev_node != NULL) prev_node->next = node_to_delete->next;
            free(node_to_delete);
        }
        prev_node = tmp;
        tmp = tmp->next;
    }
}

node_t *find_node(node_t *head, int value) {
    node_t *tmp = head;

    while (tmp != NULL) {
        if (tmp->value == value) return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

int main() {
    node_t *head = NULL;
    node_t *tmp;

    for (int i = 0; i < 10; i++) {
        tmp = create_new_node(i);
        insert_at_head(&head, tmp);
    }

    printf("Insert new node 8 after node 7777:\n");
    insert_after_node(find_node(head, 8), create_new_node(7777));
    printlist(head);

    printf("\n");

    printf("Delete node 7777:\n");
    delete_node(head, find_node(head, 7777));
    printlist(head);

    return 0;
}
