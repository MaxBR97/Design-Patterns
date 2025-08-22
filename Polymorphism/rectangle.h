#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

typedef struct Rectangle Rectangle;

struct Rectangle {
    Shape super;
    float width;
    float height;
};

Rectangle* rectangle_constructor (float width, float height); 
void rectangle_print(Shape *self);
float rectangle_area(Shape *self);
void rectangle_destroy(Shape *self);

#endif