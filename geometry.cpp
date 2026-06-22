#define _CRT_SECURE_NO_WARNINGS
#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int calculateArea(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) * abs(y2 - y1);
}

void calculateMidpoint(int x1, int y1, int x2, int y2, double* midX, double* midY) {
    *midX = (x1 + x2) / 2.0;
    *midY = (y1 + y2) / 2.0;
}

double calculateCircleArea(int r) {
    return PI * pow(r, 2);
}

void calculateCentroid(int x1, int y1, int x2, int y2, int x3, int y3, double* cX, double* cY) {
    *cX = (x1 + x2 + x3) / 3.0;
    *cY = (y1 + y2 + y3) / 3.0;
}

bool isNumeric(const char* str) {
    if (str == NULL || *str == '\0' || *str == '\n') return false;
    if (*str == '-' || *str == '+') str++;  
    if (*str == '\0') return false; 

    while (*str) {
        if (!isdigit((unsigned char)*str)) return false; 
        str++;
    }
    return true;
}

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidCoordinate(const char* prompt) {
    char buffer[50];
    while (true) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            if (isNumeric(buffer)) { 
                    return atoi(buffer); 
            }
            printf("Coordinate must be a valid integer.\n");
        }
    }
}
 
int getValidRadius(const char* prompt) {
    int r;
    while (true) {
        r = getValidCoordinate(prompt);
        if (r > 0) {
            return r;
        }
        printf("Radius 'r' must be a strictly positive integer (r > 0).\n");
    }
}

void printUsage(const char* programName) {
    printf("\nUsage Instructions:\n");
    printf("  %s -dis x1 y1 x2 y2\n", programName);
    printf("  %s -area x1 y1 x2 y2\n", programName);
    printf("  %s -mid x1 y1 x2 y2\n", programName);
    printf("  %s -cir x y r\n", programName);
    printf("  %s -bary x1 y1 x2 y2 x3 y3\n\n", programName);
}