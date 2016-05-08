//
// Created by yi on 08/05/16.
//

#ifndef IMDIS_TCPHANDLER_H
#define IMDIS_TCPHANDLER_H


#include <string>
#include "Common.h"

namespace imdis{

    class TcpHandler {

        static const uint16_t port_ = 6666;
    public:
        static fd_t tcp_bind();
        //fd_t connect();
        static fd_t tcp_accept(fd_t server, std::string &ip, uint16_t &port);
    };
}



#endif //IMDIS_TCPHANDLER_H
