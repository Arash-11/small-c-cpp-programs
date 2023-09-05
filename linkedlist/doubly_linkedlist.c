#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *prev;
    struct node *next;
};
typedef struct node node_t;

void print_list(node_t *head) {
    node_t *tmp = head;

    while (tmp != NULL) {
        printf("%d - ", tmp->value);
        tmp = tmp->next;
    }

    printf("\n");
}

node_t *create_new_node(int value) {
    node_t *new_node = malloc(sizeof(node_t));

    if (!new_node) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }

    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

void insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    if (*head != NULL) (*head)->prev = node_to_insert;
    *head = node_to_insert;
}

void insert_after_node(node_t *node_to_insert_after, node_t *new_node) {
    new_node->next = node_to_insert_after->next;
    new_node->prev = node_to_insert_after;
    new_node->next->prev = new_node;
    node_to_insert_after->next = new_node;
}

node_t *find_node(node_t *head, int value) {
    node_t *tmp = head;

    while (tmp != NULL) {
        if (tmp->value == value) return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

node_t *get_prev_node(node_t *head, int value) {
    node_t *target = find_node(head, value);
    return target->prev;
}

void delete_node(node_t **head, node_t *node) {
    if (*head == node) {
        *head = node->next;
        node->next->prev = *head;
        free(node);
        return;
    }

    node_t *tmp = *head;

    while (tmp != NULL) {
        if (tmp == node) {
            if (node->prev != NULL) node->prev->next = node->next;
            if (node->next != NULL) node->next->prev = node->prev;
            free(node);
            return;
        }
        tmp = tmp->next;
    }
}

void free_list(node_t **head) {
    while (*head != NULL) {
        node_t *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }

    *head = NULL;
}

int main() {
    node_t *head = NULL;

    for (int i = 1; i <= 10; i++) {
        insert_at_head(&head, create_new_node(i));
    }

    node_t *new_tmp_node = create_new_node(11);
    insert_after_node(find_node(head, 2), new_tmp_node);

    int value = 11;
    node_t *tmp = get_prev_node(head, value);

    print_list(head);

    if (tmp != NULL) {
        printf("Previous node for %d is %d\n", value, tmp->value);
    } else {
        printf("Previous node for %d is NULL\n", value);
    }

    printf("\nAfter deleting node 10:\n");
    delete_node(&head, find_node(head, 10));
    print_list(head);

    printf("\nAfter deleting node 11:\n");
    delete_node(&head, find_node(head, 11));
    print_list(head);

    printf("\nAfter freeing all nodes:\n");
    free_list(&head);
    print_list(head);

    return 0;
}
