#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    char team_name[100];
    int num_members;
    char captain_name[100];
    char email[100];
    char** member_names; 
} Team;


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readString(char* buffer, int size, const char* prompt) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) continue;

        if (buffer[0] == '\n') {
            printf("[ERROR] Input cannot be empty! Please try again.\n");
            continue;
        }

        if (strchr(buffer, '\n') == NULL) {
            printf("[ERROR] Input exceeds maximum length! Please try again.\n");
            clearBuffer();
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; 
        return 1;
    }
}

int getValidInt(const char* prompt, int min_val, int max_val) {
    char buffer[50];
    while (1) {
        if (!readString(buffer, sizeof(buffer), prompt)) continue;

        int is_valid = 1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isdigit((unsigned char)buffer[i])) {
                is_valid = 0;
                break;
            }
        }

        if (!is_valid) {
            printf("[ERROR] Only pure numbers are allowed!\n");
            continue;
        }

        int value = atoi(buffer);
        if (value < min_val || value > max_val) {
            printf("[ERROR] Value must be between %d and %d!\n", min_val, max_val);
            continue;
        }

        return value;
    }
}

int isValidEmail(const char* email) {
    if (strchr(email, '@') == NULL) {
        printf("[ERROR] Invalid email format! Must contain an '@' symbol.\n");
        return 0;
    }
    return 1;
}


void inputTeamData(Team* teams, int num_teams) {
    for (int i = 0; i < num_teams; i++) {
        printf("\n--- Entering Details for Team %d ---\n", i + 1);

        readString(teams[i].team_name, sizeof(teams[i].team_name), "Enter Team Name: ");

        teams[i].num_members = getValidInt("Enter total number of members (Max 5, including captain): ", 1, 5);

        readString(teams[i].captain_name, sizeof(teams[i].captain_name), "Enter Captain's Name: ");

        while (1) {
            readString(teams[i].email, sizeof(teams[i].email), "Enter Contact Email: ");
            if (isValidEmail(teams[i].email)) break;
        }

        int regular_members = teams[i].num_members - 1;

        if (regular_members > 0) {
            teams[i].member_names = (char**)calloc(regular_members, sizeof(char*));
            if (teams[i].member_names == NULL) {
                printf("[FATAL ERROR] Memory allocation failed for member array!\n");
                exit(1);
            }

            for (int j = 0; j < regular_members; j++) {
                char temp_name[150];
                printf("Enter Member %d Name: ", j + 1);
                readString(temp_name, sizeof(temp_name), "");

                teams[i].member_names[j] = (char*)calloc(strlen(temp_name) + 1, sizeof(char));
                if (teams[i].member_names[j] == NULL) {
                    printf("[FATAL ERROR] Memory allocation failed for member name!\n");
                    exit(1);
                }

                strcpy(teams[i].member_names[j], temp_name);
            }
        }
        else {
            teams[i].member_names = NULL;
        }
    }
}

void displayTeamData(Team* teams, int num_teams) {
    printf("\n TALENT SHOW REGISTRATION LIST \n");

    for (int i = 0; i < num_teams; i++) {
        printf("\n[ Team %d ]\n", i + 1);
        printf("Team Name : %s\n", teams[i].team_name);
        printf("Total Members: %d\n", teams[i].num_members);
        printf("Captain : %s\n", teams[i].captain_name);
        printf("Email : %s\n", teams[i].email);

        int regular_members = teams[i].num_members - 1;
        for (int j = 0; j < regular_members; j++) {
            printf("Member %d : %s\n", j + 1, teams[i].member_names[j]);
        }
    }
}

void freeAllMemory(Team* teams, int num_teams) {
    for (int i = 0; i < num_teams; i++) {
        int regular_members = teams[i].num_members - 1;
       
        if (regular_members > 0 && teams[i].member_names != NULL) {
            for (int j = 0; j < regular_members; j++) {
                free(teams[i].member_names[j]);
            }
            free(teams[i].member_names);
        }
    }
    free(teams);
}

int main() {
    printf("=== TALENT SHOW REGISTRATION SYSTEM ===\n\n");

    int m = getValidInt("How many participating teams? : ", 1, 100);

    Team* teams = (Team*)calloc(m, sizeof(Team));
    if (teams == NULL) {
        printf("[FATAL ERROR] Memory allocation failed for teams!\n");
        return 1;
    }

    inputTeamData(teams, m);

    displayTeamData(teams, m);

    freeAllMemory(teams, m);

    return 0;
}