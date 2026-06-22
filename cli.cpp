#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int validateAndParseArgs(int argc, char* argv[], int* numbers) {
    if (argc < 6 || argc > 11) {
        printf("[ERROR] Invalid number of arguments!\n");
        printf(">> You must provide between 5 and 10 integers.\n");
        printf(">> Usage Example: %s 5 1 3 6 8 3\n", argv[0]);
        return 0; 
    }

    // Loop through argv starting from index 1 (ignoring the program name at index 0)
    for (int i = 1; i < argc; i++) {
        char* current_arg = argv[i];
        int start_idx = 0;

        if (current_arg[0] == '-') {
            start_idx = 1;
            if (strlen(current_arg) == 1) {
                printf("[ERROR] Argument %d ('%s') is incomplete.\n", i, current_arg);
                return 0;
            }
        }

        // Strictly check every remaining character to ensure it's a pure digit
        for (int j = start_idx; current_arg[j] != '\0'; j++) {
            if (!isdigit((unsigned char)current_arg[j])) {
                printf("[ERROR] Argument %d ('%s') contains invalid characters or decimals.\n", i, current_arg);
                printf(">> Only pure integers are allowed!\n");
                return 0;
            }
        }

        // Conversion is safe. Store it in the array (offset by -1 because loop starts at 1)
        numbers[i - 1] = atoi(current_arg);
    }

    return 1; 
}

int calculateSum(const int* numbers, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return sum;
}

double calculateAverage(int sum, int count) {
    return (double)sum / count;
}

double calculateStandardDeviation(const int* numbers, int count, double average) {
    double variance_sum = 0.0;
    for (int i = 0; i < count; i++) {
        // (x_i - mean)^2
        variance_sum += pow(numbers[i] - average, 2);
    }
    double variance = variance_sum / count;
    return sqrt(variance);
}


int main(int argc, char* argv[]) {
    int numbers[10] = { 0 };

    int count = argc - 1;

    if (!validateAndParseArgs(argc, argv, numbers)) {
        return 1; 
    }

    int total_sum = calculateSum(numbers, count);
    double average = calculateAverage(total_sum, count);
    double std_deviation = calculateStandardDeviation(numbers, count, average);

    printf("總和: %d\n", total_sum);
    printf("平均: %.2f\n", average);
    printf("標準差: %.2f\n", std_deviation);

    return 0;
}