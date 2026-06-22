#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void freeAllLists(Node** heads, int num_lists) {
    for (int i = 0; i < num_lists; i++) {
        Node* current = heads[i];
        Node* next_node = NULL;

        while (current != NULL) {
            next_node = current->next;
            free(current);
            current = next_node;
        }
        heads[i] = NULL;  
    }
}
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
            printf("[ERROR] Input cannot be empty!\n");
            continue;
        }

        if (strchr(buffer, '\n') == NULL) {
            printf("[ERROR] Input exceeds maximum length!\n");
            clearBuffer();
            continue;
        } 
        if (strchr(buffer, ' ') != NULL) {
            printf("[ERROR] Spaces are strictly not allowed!\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        int value = atoi(buffer);
        if (value < min_val || value > max_val) {
            printf("[ERROR] Value must be between %d and %d!\n", min_val, max_val);
            continue;
        }

        return value;
    }
}

int insertSorted(Node** head_ref, int value) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL) {
        return 0; 
    }
    newNode->data = value;

    if (*head_ref == NULL || (*head_ref)->data >= value) {
        newNode->next = *head_ref;
        *head_ref = newNode;  
        return 1;
    }

    Node* current = *head_ref;

    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;

    return 1; 
}
int deleteOccurrences(Node** head_ref, int target) {
    if (*head_ref == NULL) return 0;

    int deleted_count = 0;

    while (*head_ref != NULL && (*head_ref)->data == target) {
        Node* temp = *head_ref;
        *head_ref = (*head_ref)->next;
        free(temp);
        deleted_count++;
    }

    Node* current = *head_ref;
    while (current != NULL && current->next != NULL) {
        if (current->next->data == target) {
            Node* temp = current->next;
            current->next = temp->next; 
            free(temp);
            deleted_count++;
        }
        else {
            current = current->next; 
        }
    }

    return deleted_count; 
}

void printAllLists(Node** heads, int num_lists) {
    printf("\n SORTED LINKED LISTS \n");
    for (int i = 0; i < num_lists; i++) {
        printf("Bucket [%d] (Range %02d-%02d): ", i, i * 100, (i * 100) + 99);

        Node* current = heads[i];
        if (current == NULL) {
            printf("(Empty)\n");
            continue;
        }

        while (current != NULL) {
            printf("%d ", current->data);
            if (current->next != NULL) {
                printf("-> ");
            }
            current = current->next;
        }
        printf("\n");
    }
}
 
int main() {
    srand((unsigned int)time(NULL));

    const int NUM_LISTS = 10;
    Node* heads[10] = { NULL };

    printf("  ARRAY OF LINKED LISTS GENERATOR \n");
    printf(">> Generating 30 random numbers (0-99)...\n");

    for (int i = 0; i < 30; i++) {
        int random_val = rand() % 1000; 

        if (random_val < 0 || random_val > 1000) {
            printf("[WARNING] Generated value %d is out of bounds. Skipping...\n", random_val);
            continue;
        }

        int target_index = random_val / 100;

        if (!insertSorted(&heads[target_index], random_val)) {
            printf("\n Memory allocation failed at number %d!\n", random_val); 
            freeAllLists(heads, NUM_LISTS);

            printf("--> Memory completely cleared. System halting.\n");
            return 1;  
        }
    }

    printf(" All numbers successfully generated and sorted!\n");
    printAllLists(heads, NUM_LISTS);

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Insert Number\n");
        printf("2. Delete Number\n");
        printf("3. Print All Sets\n");
        printf("4. Exit\n");

        int choice = getValidInt("Select Menu (1-4): ", 1, 4);

        if (choice == 1) {
            int new_val = getValidInt("Enter number to insert (0-999): ", 0, 999);
            int idx = new_val / 100;

            if (insertSorted(&heads[idx], new_val)) {
                printf(">> Successfully inserted %d into Set %d.\n", new_val, idx + 1);
            }
            else {
                printf("[ERROR] Memory full! Insertion failed.\n");
            }
        }
        else if (choice == 2) {
            int target = getValidInt("Enter number to delete (0-999): ", 0, 999);
            int idx = target / 100;

            int removed = deleteOccurrences(&heads[idx], target);
            if (removed > 0) {
                printf(">> Successfully deleted %d occurrence(s) of %d from Set %d.\n", removed, target, idx + 1);
            }
            else {
                printf(">> Number %d not found in the list.\n", target);
            }
        }
        else if (choice == 3) {
            printAllLists(heads, NUM_LISTS);
        }
        else if (choice == 4) {
            printf("\n Freeing allocated memory.\n");
            freeAllLists(heads, NUM_LISTS);
            break;
        }
    }

     
    
    return 0;
}