#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "geometry.h"

int main(int argc, char* argv[]) {
    char command[20] = "";
    int coords[6] = { 0 };
    bool isValidCLI = true;
     
    if (argc > 1) {
        strcpy(command, argv[1]);
        int expectedArgs = 0;
 
        if (strcmp(command, "-dis") == 0 || strcmp(command, "-area") == 0 || strcmp(command, "-mid") == 0) {
            expectedArgs = 4;
        }
        else if (strcmp(command, "-cir") == 0) {
            expectedArgs = 3;
        }
        else if (strcmp(command, "-bary") == 0) {
            expectedArgs = 6;
        }
        else {
            printf(" Unknown parameter '%s'.\n", command);
            isValidCLI = false;
        }
         
        if (isValidCLI) {
            if (argc - 2 != expectedArgs) {
                printf(" '%s' requires %d parameters.\n", command, expectedArgs);
                isValidCLI = false;
            }
            else {
                for (int i = 0; i < expectedArgs; i++) {
                    if (!isNumeric(argv[i + 2])) {
                        printf(" Arguments (x, y, r) must be integers.\n");
                        isValidCLI = false;
                        break;
                    }
                    coords[i] = atoi(argv[i + 2]);
                }
                 
                if (isValidCLI && strcmp(command, "-cir") == 0 && coords[2] <= 0) {
                    printf(" Radius 'r' must be a positive number.\n");
                    isValidCLI = false;
                }
            }
        }
    }
    else {
        isValidCLI = false;  
    }
     
    if (!isValidCLI) {
        printUsage(argv[0]); 
    }
    else {
    if (strcmp(command, "-dis") == 0) {
        double distance = calculateDistance(coords[0], coords[1], coords[2], coords[3]);
        printf("Distance: %f\n", distance);

    }
    else if (strcmp(command, "-area") == 0) {
        int area = calculateArea(coords[0], coords[1], coords[2], coords[3]);
        printf("Rectangle Area: %d\n", area);

    }
    else if (strcmp(command, "-mid") == 0) {
        double midX, midY;
        calculateMidpoint(coords[0], coords[1], coords[2], coords[3], &midX, &midY);
        printf("Midpoint: (%f, %f)\n", midX, midY);

    }
    else if (strcmp(command, "-cir") == 0) {
        double area = calculateCircleArea(coords[2]);
        printf("Circle Area: %f\n", area);

    }
    else if (strcmp(command, "-bary") == 0) {
        double cx, cy;
        calculateCentroid(coords[0], coords[1], coords[2], coords[3], coords[4], coords[5], &cx, &cy);
        printf("Centroid: (%f, %f)\n", cx, cy);
    }

    }
    return 0;
}