

#include "quadrilateral.h"

/* 
   This file contains all the functions to calculate area, perimeter, 
   and angles between the sides of a quadrilateral. The functions defined are:

   - dot_product()        : Computes the dot product
   - calculate_angles()   : Computes the four internal angles and return an array
   - cross_prod()         : Computes the cross product of two vectors (used for area calculation).
   - compute_triangle_area() : Calculates the area of a triangle using the cross product.
   - calculate_area()     : Computes the total area of the quadrilateral by dividing it into two triangles.
   - distance()           : Computes the Euclidean distance between two points.
   - calculate_perimeter(): Computes the perimeter of the quadrilateral by summing the side lengths.
*/

// Dot Product Calculation
double dot_product(struct Point a, struct Point b, struct Point c) {
    double ABx = b.x - a.x;
    double ABy = b.y - a.y;
    double BCx = c.x - b.x;
    double BCy = c.y - b.y;
    
    double dot = ABx * BCx + ABy * BCy;
    double magA = sqrt(ABx * ABx + ABy * ABy);
    double magB = sqrt(BCx * BCx + BCy * BCy);
    
    return acos(dot / (magA * magB)) * (180.0 / M_PI);
}

// Angles between the sides of the quadralateral using doc product
double* calculate_angles(struct Quadrilateral quad) {
    double* results = (double*)malloc(4 * sizeof(double));
    if (results == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Calculation
    results[0] = dot_product(quad.points[0], quad.points[1], quad.points[2]);
    results[1] = dot_product(quad.points[1], quad.points[2], quad.points[3]);
    results[2] = dot_product(quad.points[2], quad.points[3], quad.points[0]);
    results[3] = dot_product(quad.points[3], quad.points[0], quad.points[1]);

    return results;
}


// Cross product function (As metntioned in lecture slide)
void cross_prod(double u[], double v[], double w[]) {
    w[0] = u[1] * v[2] - u[2] * v[1];
    w[1] = u[2] * v[0] - u[0] * v[2];
    w[2] = u[0] * v[1] - u[1] * v[0];
}

// Function to compute the area of a triangle (following lecture slide)
double compute_triangle_area(struct Point p1, struct Point p2, struct Point p3) {
    double u[3] = {p3.x - p1.x, p3.y - p1.y, 0.0};
    double v[3] = {p2.x - p1.x, p2.y - p1.y, 0.0};
    double w[3];

    cross_prod(u, v, w);
    return 0.5 * fabs(w[2]);  // Triangle area
}

// Function to calculate quadrilateral area
double calculate_area(struct Quadrilateral quad) {
    double area1 = compute_triangle_area(quad.points[0], quad.points[1], quad.points[2]);
    double area2 = compute_triangle_area(quad.points[0], quad.points[2], quad.points[3]);
    return area1 + area2;
}



double distance(struct Point a, struct Point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}


// Perimeter calculation
double calculate_perimeter(struct Quadrilateral quad) {
    double perimeter = 0;
    for (int i = 0; i < 4; i++) {
        perimeter += distance(quad.points[i], quad.points[(i + 1) % 4]);
    }
    return perimeter;
}