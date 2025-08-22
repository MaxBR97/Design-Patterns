#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

typedef struct Square Square;

struct Square {
    Rectangle super;
};

Square* square_constructor(float edge);
void square_print(Shape *self);
float square_area(Shape *self);
void square_destroy(Shape *self);

#endif