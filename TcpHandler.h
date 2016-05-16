//
// Created by yi on 08/05/16.
//

#ifndef IMDIS_TCPHANDLER_H
#define IMDIS_TCPHANDLER_H

#include "Common.h"

namespace imdis{

    class TcpHandler {

    public:
        static fd_t tcp_bind();
        //fd_t connect();
        static fd_t tcp_accept(fd_t server, std::string &ip, uint16_t &port);

        //disable nagle's algorithm
        static int tcp_setnonblock(fd_t fd);
        static imdis::fd_t tcp_connect();
        static int tcp_write(int fd, char *buf, int count);
        static int tcp_read(int fd, char *buf, int count);
    };
}



#endif //IMDIS_TCPHANDLER_H
