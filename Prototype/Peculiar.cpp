#include "Peculiar.h"
#include <iostream>
Peculiar::Peculiar(int x, int y, char* p_str, std::shared_ptr<char*> magic_p_str) :
x(x), y(y), p_str(p_str), magic_p_str(magic_p_str) {
    // this->x = x;
    // this->y = y;
    // this->p_str = p_str;
    // this->magic_p_str = magic_p_str; 
}

Peculiar::Peculiar (Peculiar& obj) {
    this->x = obj.x; //deep copy
    this->y = obj.y; //deep copy
    this->p_str = new char[strlen(obj.p_str) + 1];
    strcpy(this->p_str, obj.p_str); //deep copy
    this->magic_p_str = obj.magic_p_str; //shallow copy
}

Peculiar& Peculiar::operator= (const Peculiar& obj)  {
    this->x = obj.x; //deep copy
    this->y = obj.y; //deep copy
    strcpy(this->p_str, obj.p_str); //deep copy
    this->magic_p_str = obj.magic_p_str; //shallow copy
    return *this;
}

Peculiar* Peculiar::clone () const  {
    char* new_p_str = new char[strlen(this->p_str) + 1];
    strcpy(new_p_str, this->p_str);
    Peculiar* ans = new Peculiar(x , y, new_p_str, this->magic_p_str);
    return ans;
}

bool Peculiar::isEqual(Peculiar& c) const {
    if(this->x == c.x &&
        this->y == c.y &&
        !strcmp(this->p_str, c.p_str) &&
        this->magic_p_str == c.magic_p_str){
            
            return true;
    }
    
    return false;
}

void Peculiar::setStr(char* someString) {
    strcpy(this->p_str, someString);
}

void Peculiar::setMagicStr( char *magic_p_str) {
    this->magic_p_str.reset(&magic_p_str);
}


void Peculiar::printPeculiar() {
    std::cout << "x: " << this->x << "\ny: " << this->y << "\np_str address: " << (long)(this->p_str)
              << "\np_str: " << this->p_str
              << "\n*magic_p_str: " << *this->magic_p_str << "\nmagic_p_str: " << this->magic_p_str
              << std::endl;
}
Peculiar::~Peculiar() {

}