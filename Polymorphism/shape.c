#include "shape.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Shape *shape_constructor() {
    Shape *obj = malloc(sizeof(Shape));
    obj->type = malloc(strlen("Shape") + 1);
    strcpy(( obj->type ), "Shape");
    obj->constructor = shape_constructor;
    obj->print = shape_print;
    obj->area = NULL; // abstract method, no implementation
    obj->destroy = shape_destroy;
    return obj;
}

void shape_print(Shape *self) {
    printf("This is a %s\n", self->type);
}

// abstract method
// float shape_area(Shape *self) { 
//     return 0.0;
// }

void shape_destroy(Shape* self) {
    if (self) {
        free(self->type); // Free the duplicated string
        free(self);
    }
    printf("Shape destroyed\n");
}