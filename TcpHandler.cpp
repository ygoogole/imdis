//
// Created by yi on 08/05/16.
//

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>          // inet_aton
#include <cstring>              // memset
#include <assert.h>
#include <iostream>
#include <netdb.h>
#include "TcpHandler.h"

namespace imdis{
    std::string bind_addr = "";
    uint16_t port = 6666;
}

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
    sa.sin_port = htons(imdis::port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (inet_aton(imdis::bind_addr.c_str(), &sa.sin_addr) == 0) {
        close(s);
        return TCP_NET_ERROR;
    }

    int ret = 0;
    if ( (ret = bind(s, (struct sockaddr*)&sa, sizeof(sa))) == -1){
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

int imdis::TcpHandler::tcp_setnonblock(fd_t fd) {

    int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes)) == -1) {
        return -1;
    }

    return 0;
}

imdis::fd_t imdis::TcpHandler::tcp_connect() {

    assert(imdis::bind_addr != "");

    int s, on = 1;
    struct sockaddr_in sa;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout << "create socket failed";
        return -1;
    }

    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sa.sin_family = AF_INET;
    sa.sin_port = htons(imdis::port);
    if (inet_aton(imdis::bind_addr.c_str(), &sa.sin_addr) == 0) {
        struct hostent *he;

        he = gethostbyname(imdis::bind_addr.c_str());
        if (he == NULL) {
            std::cout << "can't resolve: " << imdis::bind_addr.c_str() << std::endl;
            close(s);
            return -1;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }

    /*if (flags & ANET_CONNECT_NONBLOCK) {
        if (anetNonBlock(err,s) != ANET_OK)
            return ANET_ERR;
    }*/
    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        std::cout << "Connect error " << std::endl;
        close(s);
        return -1;
    }

    return s;
}

int imdis::TcpHandler::tcp_write(int fd, char *buf, int count)
{
    int nwritten, totlen = 0;
    while(totlen != count) {
        nwritten = write(fd,buf,count-totlen);
        if (nwritten == 0) return totlen;
        if (nwritten == -1) return -1;
        totlen += nwritten;
        buf += nwritten;
    }
    return totlen;
}

int imdis::TcpHandler::tcp_read(int fd, char *buf, int count) {

    int nread, totlen = 0;
    while(totlen != count) {
        nread = read(fd,buf,count-totlen);
        if (nread == 0) return totlen;
        if (nread == -1) return -1;
        totlen += nread;
        buf += nread;
    }
    return totlen;
}



