#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
int getValidInt(const char* prompt, int min_val, int max_val) {
    char buffer[50];
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
            return 0;
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
 
double getValidDouble(const char* prompt, double min_val, double max_val) {
    char buffer[50];
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
            return 0;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        char* endptr;
        double value = strtod(buffer, &endptr);

        if (*endptr != '\0') {
            printf("[ERROR] Invalid format! Only numbers and decimals ('.') are allowed.\n");
            continue;
        }

        if (value < min_val || value > max_val) {
            printf("[ERROR] Grade must be between %.2f and %.2f!\n", min_val, max_val);
            continue;
        }

        return value;
    }
}


double** allocateArray(int num_courses, const int* students_per_course) {
    double** grade = (double**)calloc(num_courses, sizeof(double*));
    if (grade == NULL) {
        printf("[FATAL ERROR] Memory allocation failed for courses!\n");
        exit(1);
    }

    for (int i = 0; i < num_courses; i++) {
        grade[i] = (double*)calloc(students_per_course[i], sizeof(double));

        if (grade[i] == NULL) {
            printf("[FATAL ERROR] Memory allocation failed for students in Course %d!\n", i + 1);
            exit(1);
        }
    }

    return grade;
}

void freeAll(double** grade, int num_courses, int* students_per_course) {
    if (grade == NULL) return;

    for (int i = 0; i < num_courses; i++) {
        if (grade[i] != NULL) {
            free(grade[i]);
            grade[i] = NULL;
        }
    }
    free(grade);
    free(students_per_course);
}

void inputStudentGrades(double** grade, int num_courses, const int* students_per_course) {
    printf("\nGRADE ENTRY\n");
    for (int i = 0; i < num_courses; i++) {
        printf("\n--- Entering grades for Course %d (%d students) ---\n", i + 1, students_per_course[i]);

        for (int j = 0; j < students_per_course[i]; j++) {
            char prompt[100];
            sprintf(prompt, "Enter grade for Student %d (0.00 - 100.00): ", j + 1);
            grade[i][j] = getValidDouble(prompt, 0.0, 100.0);
        }
    }
}

void printGrades(double** grade, int num_courses, const int* students_per_course) {
    printf("\n FINAL COURSE GRADES \n");
    for (int i = 0; i < num_courses; i++) {
        printf("Course %d | %d Students | Grades: [ ", i + 1, students_per_course[i]);

        for (int j = 0; j < students_per_course[i]; j++) {
            printf("%.2f ", grade[i][j]);
        }
        printf("]\n");
    }
}


int main() {
    printf("=== DYNAMIC IRREGULAR 2D ARRAY: GRADE SYSTEM (DOUBLE VERSION) ===\n\n");

    int n = getValidInt("Enter the number of courses (n): ", 1, 1000);

    int* students_per_course = (int*)calloc(n, sizeof(int));
    if (students_per_course == NULL) {
        printf("[FATAL ERROR] Memory allocation failed!\n");
        return 1;
    }

    printf("\n--- Enter the number of students for each course ---\n");
    for (int i = 0; i < n; i++) {
        char prompt[50];
        sprintf(prompt, "Number of students in Course %d: ", i + 1);
        students_per_course[i] = getValidInt(prompt, 1, 1000);
    }

    double** grade = allocateArray(n, students_per_course);

    inputStudentGrades(grade, n, students_per_course);

    printGrades(grade, n, students_per_course);

    printf("\nFreeing memory securely...\n");
    freeAll(grade, n, students_per_course);
    printf("--> Memory cleared. Program exited safely.\n");

    return 0;
}