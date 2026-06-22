#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Node {
    char name[100];
    int quantity;
    struct Node* next;
} Node;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readString(char* buffer, int size, const char* prompt) {

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) continue;

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
        break;
    }
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
Node* addTreasure(Node* head, const char* name, int quantity) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL) {
        printf("Sorry the memory isnt succesfully allocated\n");
        freeInventory(head);
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->quantity = quantity;

    newNode->next = head;
    printf("Succesfully Add!\n");

    return newNode;
}

void modifyTreasureQuantity(Node* head) {
    if (head == NULL) {
        printf("The inventory cant be found!\n");
    }
    char findName[100] = { '\0' };
    readString(findName, sizeof(findName), "Enter the name of treasure to modify!\n");

    Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->name, findName) == 0) {
            found = 1;
            printf("Current Quantity of '%s' is %d.\n", current->name, current->quantity);

            int new_quantity = getValidInt("Enter the new quantity", 1, 1000);
            current->quantity = new_quantity;

            printf("Update is Success, '%s' now have %d", current->name, current->quantity);
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("The inventory isnt existed!\n");
    }
}
void printAllTreasures(Node* head) {
    if (head == NULL) {
        printf("The inventory is empty right now!\n");
        return;
    }
    printf("All Treasures:\n");
    Node* current = head;
    int index = 1;

    while (current != NULL) {
        printf("%d. Name: %-15s | Quantity: %d\n", index, current->name, current->quantity);
        current = current->next;
        index++;
    }
}

void freeInventory(Node* head) {
    Node* current = head;
    Node* next_node = NULL;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}
int main() {
    Node* head = NULL;
    printf("Treasure Inventory Actived:\n");
    while (1) {
        printf("Menu:\n");
        printf("1. Add New Treasure\n");
        printf("2. Modify Treasure Quantity\n");
        printf("3. Print All Treasures\n");
        printf("4. Exit\n");

        int menu = getValidInt("Enter your choice (1-4): ", 1, 4);
        if (menu > 4) {
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            continue;
        }

        if (menu == 1) {
            char name[100];
            readString(name, sizeof(name), "Enter Treasure Name: ");
            int quantity = getValidInt("Enter Treasure Quantity: ", 1, 1000);
            head = addTreasure(head, name, quantity);
        }
        else if (menu == 2) {
            modifyTreasureQuantity(head);
        }
        else if (menu == 3) {
            printAllTreasures(head);
        }
        else if (menu == 4) {
            printf("\nBye.\n");

            freeInventory(head);
            head = NULL;

            printf(" Memory completely cleared. Program exited safely.\n");
            break;
        }
    }
    return 0;
}