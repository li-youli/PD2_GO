#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Node {
    float data;
    struct Node* next;
} Node;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInt(const char* prompt, int min_val, int max_val) {
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if (buffer[0] == '\n') {
            printf(" Input cannot be empty!\n");
            continue;
        }

        if (strchr(buffer, '\n') == NULL) {
            printf(" Input exceeds maximum length!\n");
            clearBuffer();
            continue;
        }


        if (strchr(buffer, ' ') != NULL) {
            printf(" Spaces are strictly not allowed!\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        int value = atoi(buffer);
        if (value < min_val || value > max_val) {
            printf(" Value must be between %d and %d!\n", min_val, max_val);
            continue;
        }

        return value;
    }
}

void freeList(Node* head) {
    Node* current = head;
    Node* next_node = NULL;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}
float generateRandomFloat() {
    int front = rand() % 51;
    int back = rand() % 100;
    return front + ((float)back / 100.0f);
}

Node* insertAtTail(Node* head, float value) {
    Node* currentPtr;
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL) {
        printf(" Memory allocation failed!\n");
        freeList(head);
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;
    currentPtr = head;
    if (head != NULL) {
        while (currentPtr->next != NULL) {
            currentPtr = currentPtr->next;
        }
        currentPtr->next = newNode;
    }
    else {
        head = newNode;
    }

    return head;
}

void printList(Node* head) {
    if (head == NULL) {
        printf(" The list is currently empty.\n");
        return;
    }

    printf("\n[ ");
    Node* current = head;
    while (current != NULL) {
        printf("%.2f ", current->data);
        if (current->next != NULL) {
            printf("\n");
        }
        current = current->next;
    }
    printf(" ]\n");
}

void findExtremes(Node* head) {
    if (head == NULL) {
        printf(" Cannot find extremes in an empty list.\n");
        return;
    }

    float max_val = head->data;
    float min_val = head->data;

    Node* current = head->next;
    while (current != NULL) {
        if (current->data > max_val) max_val = current->data;
        if (current->data < min_val) min_val = current->data;
        current = current->next;
    }

    printf("\n--> Maximum Value: %.2f\n", max_val);
    printf("--> Minimum Value: %.2f\n", min_val);
}

int countNodes(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void searchNode(Node* head, int total_nodes) {
    if (head == NULL) {
        printf(" The list is empty. Nothing to search.\n");
        return;
    }

    int index = getValidInt("Enter the position to search (e.g., 1 for first node): ", 1, total_nodes);

    Node* current = head;
    for (int i = 1; i < index; i++) {
        current = current->next;
    }

    printf(" The value at position %d is: %.2f\n", index, current->data);
}
       


int main() {
    srand((unsigned int)time(NULL));

    Node* head = NULL;

    printf("=== DYNAMIC FLOAT LINKED LIST ===\n\n");

    int m = getValidInt("How many random numbers do you want to generate? : ", 1, 10000);

    printf(">> Generating and inserting %d numbers into the Linked List...\n", m);
    for (int i = 0; i < m; i++) {
        float new_val = generateRandomFloat();
        head = insertAtTail (head, new_val);
    }
    printf(">> Insertion complete!\n");

    while (1) {
        printf("1) Display All Data\n");
        printf("2) Find Maximum and Minimum\n");
        printf("3) Search for a Specific Position\n");
        printf("-1) Exit System\n");

        int menu = getValidInt("Select Menu: ", -1, 3);

        if (menu == 1) {
            printList(head);
        }
        else if (menu == 2) {
            findExtremes(head);
        }
        else if (menu == 3) {
            int total = countNodes(head);
            searchNode(head, total);
        }
        else if (menu == -1) {
            printf("\n Freeing Memory.\n");
            freeList(head);
            head = NULL; break;
        }
    }

    return 0;
}