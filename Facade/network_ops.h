#pragma ONCE
#include <string>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>


class Network_Ops {
public:
    Network_Ops();
    std::string& compress(std::string &message) const;
    std::string& decompress(std::string &message) const;
    std::string& add_checksum(std::string &message) const;
    std::string& remove_checksum(std::string &message) const;
    bool validate_checksum(std::string &message) const;
    std::string& encrypt(std::string &message, int key) const;
    std::string& decrypt(std::string &message, int key) const;
    int generateKey() const;
    ~Network_Ops();
};