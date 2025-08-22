#include <stdlib.h>
#include "square.h"

static const char* square_name = "Square";

Square* square_constructor(float edge) {
    Square *obj = malloc(sizeof(Square));
    obj->super.height = edge;
    obj->super.width = edge;
    obj->super.super.type = malloc(strlen(square_name) + 1);
    strcpy(obj->super.super.type , square_name);
    obj->super.super.area = square_area;
    obj->super.super.print = square_print;
    obj->super.super.destroy = square_destroy;
    obj->super.super.constructor = square_constructor;

    return obj;
}

void square_print(Shape *self) {
    Square *obj = (Square *)self;
    printf("This is a %s\n",obj->super.super.type);
}
float square_area(Shape *self) {
    Square *obj = (Square *)self;
    return obj->super.width * obj->super.height;
}   
void square_destroy(Shape *self){
    Square *obj = (Square *)self;
    if(obj != NULL) {
        if (obj->super.super.type != NULL)
            free(obj->super.super.type); 
        free(obj);
    }
    printf("Square destroyed\n");
}
