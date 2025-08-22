#include <stdio.h>
#include <stdlib.h>
#include "shape.h"
#include "rectangle.h"
#include "square.h"

main() {
    Shape *shapes[3];

    shapes[0] = shape_constructor();
    shapes[1] = rectangle_constructor(3,5);
    shapes[2] = square_constructor(4);
    printf("Created a shape of type: %s\n", shapes[0]->type);   
    printf("Created a shape of type: %s\n", shapes[1]->type);   
    printf("Created a shape of type: %s\n", shapes[2]->type);
    shapes[0]->print(shapes[0]);
    shapes[1]->print(shapes[1]);
    shapes[2]->print(shapes[2]);
    printf("Area of shape 1: %.3f\n",shapes[1]->area(shapes[1]));
    printf("Area of shape 2: %.3f\n",shapes[2]->area(shapes[2]));


    shapes[0]->destroy(shapes[0]);
    shapes[1]->destroy(shapes[1]);
    shapes[2]->destroy(shapes[2]);
}