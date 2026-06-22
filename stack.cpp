#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
typedef struct Node {
    char data;
    struct Node* next;
} Node;

int push(Node** top_ref, char c) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL) {
        return 0; 
    }
    newNode->data = c;
    newNode->next = *top_ref;
    *top_ref = newNode;
    return 1; 
}
 
void pop(Node** top_ref) {
    if (*top_ref == NULL) return;  

    Node* temp = *top_ref;
    *top_ref = (*top_ref)->next;
    free(temp);
}
 
int isEmpty(Node* top) {
    return top == NULL;
}
 
void freeStack(Node** top_ref) {
    Node* current = *top_ref;
    Node* next_node = NULL;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *top_ref = NULL;  
}
 
int isBalanced(const char* expression) {
    Node* stack = NULL;
    char last_char = '\0'; 

    for (int i = 0; expression[i] != '\0'; i++) {
        char c = expression[i];
         
        if (isspace((unsigned char)c)) {
            continue;
        }

        if (c == '(') {
            if (!push(&stack, c)) {
                printf("\n Memory allocation failed during Stack Push!\n"); 
                freeStack(&stack);
                exit(1);  
            }
        }
        else if (c == ')') { 
            if (last_char == '(') {
                printf("\n Empty parentheses detected. This is considered invalid!\n");
                freeStack(&stack);
                return 0;
            }

            if (isEmpty(stack)) {
                freeStack(&stack);
                return 0;
            }
             
            pop(&stack);
        }

        last_char = c;
    }

    int balanced = isEmpty(stack);

    freeStack(&stack);

    return balanced;
}
void readString(char* buffer, int size, const char* prompt) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) continue;

        if (buffer[0] == '\n') {
            printf("[ERROR] Expression cannot be empty! Please try again.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; 
        break;
    }
}

int main() {
    char expression[500];

    printf("LIST STACK PARENTHESES\n\n");

    readString(expression, sizeof(expression), "Enter a mathematical expression: ");

    if (isBalanced(expression)) {
        printf(">> The parentheses are CORRECTLY MATCHED!\n");
    }
    else {
        printf(">> The parentheses are NOT CORRECTLY MATCHED!\n");
    }

    return 0;
}