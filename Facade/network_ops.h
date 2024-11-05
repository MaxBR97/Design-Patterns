#pragma ONCE
#include <string>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>


class ChecksumAlgo {
public:
    ChecksumAlgo();
    std::string& add_checksum(std::string &message) const;
    std::string& remove_checksum(std::string &message) const;
    bool validate_checksum(std::string &message) const;
    ~ChecksumAlgo();
};

class EncryptAlgo {
public:
    EncryptAlgo();
    std::string& encrypt(std::string &message, int key) const;
    std::string& decrypt(std::string &message, int key) const;
    int generateKey() const;
    ~EncryptAlgo();
};

class CompressAlgo {
public:
    CompressAlgo();
    std::string& compress(std::string &message) const;
    std::string& decompress(std::string &message) const;
    ~CompressAlgo();
};