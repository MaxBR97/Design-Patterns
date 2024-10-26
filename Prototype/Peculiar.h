#ifndef PECULIAR_H
#define PECULIAR_H
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include "Cloneable.h"

class Peculiar : public Cloneable {
public:
    Peculiar(int x, int y,char* p_str, std::shared_ptr<char*> magic_p_str);
    // three ways to implement this design pattern in C++ :
    Peculiar (Peculiar& obj); //constructor
    //Peculiar operator()(Peculiar& obj) const; //constructor
    Peculiar& operator=(const Peculiar& obj); //assignment
    Peculiar* clone() const override; //custom interface (Java like)
    bool isEqual(Peculiar& c) const;
    void setStr(char* someString);
    void setMagicStr(char* magic_p_str);
    void printPeculiar();
    ~Peculiar();

private:
    int x;
    int y;
    char* p_str;
    std::shared_ptr<char*> magic_p_str;
};
#endif