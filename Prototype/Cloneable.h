
#ifndef CLONEABLE_H
#define CLONEABLE_H
// Like Java's interface
class Cloneable;

class Cloneable {
public:
    virtual Cloneable* clone() const = 0;
};
#endif