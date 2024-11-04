#include "ssl_protocol.h"

SSL_Protocol::SSL_Protocol() : ops(), symmetric_key(ops.generateKey()) ,
    socket_buffer(std::make_unique<char[]>(BUFFER_SIZE)), buf_size(0) {
}

bool SSL_Protocol::sendMessage (std::string &message)  {
    ops.encrypt(ops.add_checksum(ops.compress(message)), symmetric_key);    
    if(buf_size + message.size() + 1 == BUFFER_SIZE)
            return false;
    for( char c : message ) {
        socket_buffer[buf_size] = c;
        buf_size++;
    }
    socket_buffer[buf_size] = '\0';
    buf_size++;
    return true;
}

std::string SSL_Protocol::receiveMessage() {
    int i = buf_size - 2;
    std::string ans;
    while( i >= 0 && socket_buffer[i] != '\0' ) {
        ans = socket_buffer[i] + ans;
        i--;
    }
    ops.decrypt(ans, symmetric_key);
    if(ops.validate_checksum(ans))
        std::cout << "checksum is valid" << std::endl;
    else 
        std::cout << "checksum is NOT valid" << std::endl;

    ops.decompress(ops.remove_checksum(ans));
    return ans;
}

std::string SSL_Protocol::pollRawMessage() const {
    int i = buf_size - 2;
    std::string ans;
    while( i >= 0 && socket_buffer[i] != '\0' ) {
        ans = socket_buffer[i] + ans;
        i--;
    }
    return ans;
}

SSL_Protocol::~SSL_Protocol(){}