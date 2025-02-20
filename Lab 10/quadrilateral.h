#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point {
    double x;
    double y;
};

struct Quadrilateral {
    struct Point points[4];  // Using array seems convenient instead of four Point nodes
    double area;
    double perimeter;
};

//These funtions have been defined in the quadrilateral.c file
double* calculate_angles(struct Quadrilateral quad); // returning array as reference
double calculate_perimeter(struct Quadrilateral quad);
double calculate_area(struct Quadrilateral quad);

#endif
