#include "Cloneable.h"
#include "Peculiar.h"
#include <memory>
#include <iostream>
#include <stdlib.h>
class Peculiar;
class Cloneable;


int main(int argc, char **argv) {
    char *obj1_str = new char[20];
    char *obj2_str = new char[20];
    char* obj3_str = new char[20];
    char* obj4_str = new char[20];
    strcpy(obj1_str, "1");
    strcpy(obj2_str, "2");
    strcpy(obj3_str, "3");
    strcpy(obj4_str, "4");

    char *obj1_str2 = new char[20];
    char *obj2_str2 = new char[20];
    char* obj3_str2 = new char[20];
    char* obj4_str2 = new char[20];
    strcpy(obj1_str2, "a");
    strcpy(obj2_str2, "b");
    strcpy(obj3_str2, "c");
    strcpy(obj4_str2, "d");
    std::unique_ptr<Peculiar> obj1 = std::make_unique<Peculiar>(11, 111, obj1_str , std::make_shared<char*>(obj1_str2));
    std::unique_ptr<Peculiar> obj2 = std::make_unique<Peculiar>(22, 222, obj2_str , std::make_shared<char*>(obj2_str2));
    std::unique_ptr<Peculiar> obj3 = std::make_unique<Peculiar>(33, 333, obj3_str , std::make_shared<char*>(obj3_str2));
    std::unique_ptr<Peculiar> obj4 = std::make_unique<Peculiar>(44, 444, obj4_str , std::make_shared<char*>(obj4_str2));

    *obj2 = *obj1;
    bool oneAndTwo = obj1->isEqual(*obj2);

    obj3 = std::make_unique<Peculiar>(*obj1);
    bool oneAndThree = obj1->isEqual(*obj3);

    *obj4 = *(obj1->clone());
    bool oneAndFour = obj1->isEqual(*obj4);

    obj1->printPeculiar();
    obj2->printPeculiar();
    std::cout <<" oneAndTwo: " << oneAndTwo  <<std::endl;
    std::cout <<" oneAndThree: " << oneAndThree << std::endl;
    std::cout << " oneAndFour: " << oneAndFour << std::endl;

    return 0;
}

