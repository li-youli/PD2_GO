#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>
#include <stddef.h>

#define PI 3.14159265358979323846
 
double calculateDistance(int x1, int y1, int x2, int y2);
int calculateArea(int x1, int y1, int x2, int y2);
void calculateMidpoint(int x1, int y1, int x2, int y2, double* midX, double* midY);
double calculateCircleArea(int r);
void calculateCentroid(int x1, int y1, int x2, int y2, int x3, int y3, double* cX, double* cY);
 
bool isNumeric(const char* str);
void flushInputBuffer();
int getValidCoordinate(const char* prompt);
int getValidRadius(const char* prompt);
void printUsage(const char* programName);

#endif