#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum {
    BF_INCREMENT,
    BF_DECREMENT,
    BF_MOVE_RIGHT,
    BF_MOVE_LEFT,
} cmd_type;

typedef struct Node {
    cmd_type type;
    struct Node *next;
    struct Node *child;
} Node;


Node* create_node(cmd_type type) {
    Node *node = malloc(sizeof(Node));
    node->child = NULL;
    node->next = NULL;
    node->type = type;
    
    return node;
}


int main() {
    FILE* source = fopen("source.bf", "r");

    size_t size = 0;
    char *buffer = NULL;
 
    if (source == NULL) {
        exit(1);
    }
 
    do {
        char c = fgetc(source);

        if (feof(source))
            break ;
 
        if (c != ' ' && c != '\n') {
            buffer = realloc(buffer, size + 1);
            buffer[size] = c;
            size++;
        }

    }  while (1);
 
    fclose(source);

    Node* head = NULL;
    Node* current = NULL;

    for (int i = 0; i < size; i++) {
        Node *node = NULL;

        switch (buffer[i]) {
            case '+':
                node = create_node(BF_INCREMENT);
                break;
            case '-':
                node = create_node(BF_DECREMENT);
                break;
            case '>':
                node = create_node(BF_MOVE_RIGHT);
                break;
            case '<':
                node = create_node(BF_MOVE_LEFT);
                break;
            
            default:
                printf("Unknown command in the source code\n");
                break;
        }

        if (node != NULL) {
            if (head == NULL) {
                head = node;
            } else {
                current->next = node;
            }

            current = node;
        }
    }

    int memory[1024] = {0};
    int *ptr = memory;

    for (Node* i = head; i != NULL; i = i->next) {
        printf("Processing node of type: %d\n", i->type);
        switch (i->type) {
            case BF_INCREMENT:
                (*ptr)++;
                break;
            case BF_DECREMENT:
                (*ptr)--;
                break;
            case BF_MOVE_LEFT:
                ptr--;
                break;
            case BF_MOVE_RIGHT:
                ptr++;
                break;
            default:
                break;
        }
    }

    printf("Memory: ");
    for (int i = 0; i < 1024; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");

    free(buffer);

    return 0;
}