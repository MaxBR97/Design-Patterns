#include <string>

class Resource {
    public:
    int x;
    std::string name;

    Resource (int x, std::string name) : x(x) , name(name) {}
    void set (int x) {this->x = x;}
};