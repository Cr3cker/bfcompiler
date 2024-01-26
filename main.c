#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum {
    BF_INCREMENT,
    BF_DECREMENT,
    BF_MOVE_RIGHT,
    BF_MOVE_LEFT,
    BF_START_LOOP, 
    BF_END_LOOP,
    BF_PRINT,
    BF_INPUT,
} cmd_type;

typedef struct Node {
    cmd_type type;
    struct Node *next;
} Node;


Node* create_node(cmd_type type) {
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->type = type;
    
    return node;
}


int main() {
    FILE* source = fopen("source.b", "r");

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
            case '[':
                node = create_node(BF_START_LOOP);
                break;
            case ']':
                node = create_node(BF_END_LOOP);
                break;
            case '.':
                node = create_node(BF_PRINT);
                break;
            case ',':
                node = create_node(BF_INPUT);
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
    Node* start_loop_ptr = NULL;
    Node *loop_stack[1024];
    int stack_top = 0;

    Node* i = head;
    while (i != NULL) {
        switch (i->type) {
            case BF_INCREMENT:
                (*ptr)++;
                break;
            case BF_DECREMENT:
                if (*ptr != 0) (*ptr)--;
                break;
            case BF_MOVE_LEFT:
                ptr--;
                break;
            case BF_MOVE_RIGHT:
                ptr++;
                break;
            case BF_PRINT:
                printf("%c", *ptr);
                break;
            case BF_INPUT:
                scanf("%c", ptr);
                break;
            case BF_START_LOOP:
                loop_stack[stack_top++] = i;
                break;
            case BF_END_LOOP:
                if (*ptr > 0) {
                    i = loop_stack[stack_top - 1]; 
                } else {
                    stack_top--;  
                    i = i->next;
                }
                continue;
        }

        i = i->next; 
    }

    printf("Memory: ");
    for (int i = 0; i < 1024; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");

    free(buffer);

    return 0;
}