#ifndef POINT_H
#define POINT_H

typedef struct Point {
    double x;
    double y;
} Point;

/**
 * Initialize and return a Point struct value.
 */
Point Point_ctor(double x, double y);

/**
 * Print a representation of a Point to stdout.
 */
void Point_print(Point *self);

#endif
