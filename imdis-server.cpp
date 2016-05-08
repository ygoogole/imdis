#include <iostream>
#include "TcpHandler.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    imdis::fd_t server = imdis::TcpHandler::tcp_bind();
    if (server == imdis::TCP_NET_ERROR){
        return -1;
    }

    std::string ip;
    uint16_t port;
    imdis::fd_t fd = imdis::TcpHandler::tcp_accept(server, ip, port);

    return 0;
}
