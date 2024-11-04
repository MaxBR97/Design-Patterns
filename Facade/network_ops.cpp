#include "network_ops.h"

Network_Ops::Network_Ops(){}
std::string& Network_Ops::compress(std::string& message) const {
    std::string compressed;
    char current_char = message[0];
    int count = 1;

    for (size_t i = 1; i < message.size(); ++i) {
        if (message[i] == current_char) {
            ++count;
        } else {
            compressed += std::to_string(count) + current_char;
            current_char = message[i];
            count = 1;
        }
    }
    compressed += std::to_string(count) + current_char;

    message = compressed;
    std::cout << "compressed to: " << message <<std::endl;
    return message;
}

std::string& Network_Ops::decompress(std::string& message) const {
    std::string decompressed;
    for (size_t i = 0; i < message.size(); ) {
        int count = 0;
        while (isdigit(message[i])) {
            count = count * 10 + (message[i] - '0');
            ++i;
        }

        char ch = message[i++];
        decompressed += std::string(count, ch);
    }

    message = decompressed;
    std::cout << "decompressed to: " << message <<std::endl;
    return message;
}

std::string& Network_Ops::add_checksum(std::string &message) const {
    short x = 0;
    for( char &c : message){
        x += static_cast<int>(c);
        x*=2;
    }
    //separate x to two bytes and append them to the string
    message += ((char)x);
    message += ((char)(x >> 8));
    std::cout << "added checksum: " << message <<std::endl;
        return message;
}
std::string& Network_Ops::remove_checksum(std::string &message) const {
    message.erase(message.size()-2);
    std::cout << "checksum removed: " << message <<std::endl;
    return message;
}
bool Network_Ops::validate_checksum(std::string &message) const{
    std::string copy(message);
    std::cout << "checksum comparison: " << copy <<std::endl;
    if( message == add_checksum(remove_checksum(copy)))
        return true;
    return false;
}

std::string& Network_Ops::encrypt(std::string& message, int key) const {
    //return message;
    for (char& c : message) {
        c += key;
    }
    std::cout << "encrypted to: " << message <<std::endl;
    return message;
}

std::string& Network_Ops::decrypt(std::string& message, int key) const {
    //return message;
    for (char& c : message) {
        c -= key;
    }
    std::cout << "decrypted to: " << message <<std::endl;
    return message;
}

int Network_Ops::generateKey() const {
    srand(time(nullptr));
    return rand() % 26;
}

Network_Ops::~Network_Ops(){}