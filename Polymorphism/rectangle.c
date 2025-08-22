#include <stdlib.h>
#include "rectangle.h"
#include "shape.h";

static char* rectangle_name = "Rectangle";

Rectangle* rectangle_constructor(float width, float height) {
    Rectangle* obj = malloc(sizeof(Rectangle));
    obj->super.type = malloc(strlen(rectangle_name) + 1);
    strcpy(obj->super.type, rectangle_name);
    obj->super.constructor = rectangle_constructor;
    obj->super.area = rectangle_area;
    obj->super.print = rectangle_print;
    obj->super.destroy = rectangle_destroy;

    obj->width = width;
    obj->height = height;

    return obj;
}

void rectangle_print(Shape *self) {
    Rectangle *obj = (Rectangle *)self;
    printf("This is a %s\n",obj->super.type);
}

float rectangle_area(Shape *self) {
    Rectangle *obj = (Rectangle *)self;
    return obj->width * obj->height;
}

void rectangle_destroy(Shape* self){
    Rectangle *obj = (Rectangle *)self;
    if(obj != NULL) {
        if (obj->super.type != NULL)
            free(obj->super.type); 
        free(obj);
    }
    printf("Rectangle destroyed\n");
}