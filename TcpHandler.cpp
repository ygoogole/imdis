//
// Created by yi on 08/05/16.
//

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>          // inet_aton
#include <cstring>              // memset
#include "TcpHandler.h"

#include "Common.h"

imdis::fd_t imdis::TcpHandler::tcp_bind() {

    fd_t s;
    int opt = 1;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        return TCP_NET_ERROR;
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1){
        close(s);
        return TCP_NET_ERROR;
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port_);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    const char *addr = "192.168.50.140";
    if (inet_aton(addr, &sa.sin_addr) == 0) {
        close(s);
        return TCP_NET_ERROR;
    }

    if (bind(s, (struct sockaddr*)&sa, sizeof(sa)) == -1){
        close(s);
        return TCP_NET_ERROR;
    }

    if (listen(s, 64) == -1){
        close(s);
        return TCP_NET_ERROR;
    }

    return s;
}

imdis::fd_t imdis::TcpHandler::tcp_accept(fd_t server, std::string &ip, uint16_t &port) {

    imdis::fd_t s;
    struct sockaddr_in sa;
    uint32_t sa_len = sizeof(sa);

    if ((s = accept(server, (struct sockaddr*)&sa, &sa_len)) == -1){
        close(s);
        return TCP_NET_ERROR;
    }

    ip = inet_ntoa(sa.sin_addr);
    port = ntohs(sa.sin_port);

    return s;
}



