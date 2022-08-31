#include <stdio.h>
#include "Point.h"

Point Point_ctor(double x, double y) 
{
    Point p = { x, y };
    return p;
}

void Point_print(Point *self) {
    printf("Point(%f, %f)\n", self->x, self->y);
}
