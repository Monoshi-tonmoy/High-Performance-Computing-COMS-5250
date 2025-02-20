#include "quadrilateral.h"

int main() {
    struct Quadrilateral quad;

    // Read 4 points from the user
    printf("Enter the 4 points of the quadrilateral (x y format):\n");
    for (int i = 0; i < 4; i++) {
        printf("Point %d: ", i + 1);
        scanf("%lf %lf", &quad.points[i].x, &quad.points[i].y);
    }

    // Calculate perimeter
    quad.perimeter = calculate_perimeter(quad);
    printf("\nPerimeter: %.2f\n", quad.perimeter);

    // Calculate area
    quad.area = calculate_area(quad);
    printf("Area: %.2f\n", quad.area);

    // Calculate the angles
    double* angles = calculate_angles(quad);
    printf("Angles:\n");
    for (int i = 0; i < 4; i++) {
        printf("Angle %d: %.2f degrees\n", i + 1, angles[i]);
    }

    // free pointer
    free(angles);

    return 0;
}
