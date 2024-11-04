#pragma ONCE
#include "network_ops.h"
#define BUFFER_SIZE 50

// This class provides the abstraction of the SSL protocol suit (compression, MAC checksum, and encryption)
// This might not be the accurate SSL protocl and it ignores some of it's aspects but it isnt relevant for the
// current Facade pattern demonstration.
class SSL_Protocol {
public:
    SSL_Protocol();
    bool sendMessage(std::string &message);
    std::string receiveMessage();
    std::string pollRawMessage() const;
    ~SSL_Protocol();
private:
    Network_Ops ops;
    int symmetric_key;
    std::unique_ptr<char[]> socket_buffer;
    int buf_size;


};