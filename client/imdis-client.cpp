#include <iostream>
#include <assert.h>
#include <cstring>
#include <unistd.h>
#include "TcpHandler.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, Client!" << std::endl;

    assert(argc == 2);
    imdis::bind_addr = argv[1];
    imdis::fd_t fd_client = imdis::TcpHandler::tcp_connect();

    std::string cmd = "set test_key 555";
    std::cout << "cmd is: " << cmd << std::endl;
    std::cout << "cmd length: " << cmd.size() << std::endl;

    int ret = imdis::TcpHandler::tcp_write(fd_client, const_cast<char *>(cmd.c_str()), cmd.size());

    close(fd_client);
    return 0;
}
