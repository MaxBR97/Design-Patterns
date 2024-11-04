#include "ssl_protocol.h"

int main(int argc, char** argv) {
    std::unique_ptr<SSL_Protocol> network = std::make_unique<SSL_Protocol>();
    std::string myMessage("Some secret message");
    std::string copyOfOriginalMessage(myMessage);
    network->sendMessage(copyOfOriginalMessage);
    std::string messageAfterEncryption(network->pollRawMessage());
    std::string messageAfterDecryption(network->receiveMessage());
    std::cout << "Original message: " << myMessage.c_str() <<"\n"
              << "Encrypted message: " << messageAfterEncryption.c_str() << "\n"
              << "Decrypted message: " << messageAfterDecryption.c_str() << std::endl;
    return 0;
}