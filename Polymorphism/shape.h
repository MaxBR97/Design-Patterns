#ifndef SHAPE_H
#define SHAPE_H

typedef struct Shape Shape;

struct Shape {
    char* type;

    Shape* (*constructor)();
    void (*print)(Shape * self);
    float (*area)(Shape * self); //abstract
    void (*destroy)(Shape *self);
};

Shape* shape_constructor();
void shape_print(Shape *self);
float shape_area(Shape *self);
void shape_destroy(Shape* self);

#endif