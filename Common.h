//
// Created by yi on 08/05/16.
//

#ifndef IMDIS_COMMON_H
#define IMDIS_COMMON_H

#include <memory>
#include <vector>

namespace imdis{

    typedef int fd_t;

    enum error_code_t{
        TCP_NET_ERROR = -1,
    };

    enum{
        max_io_event = 256,
    };

    class Epoller;
    extern std::shared_ptr<imdis::Epoller> epoller;
    extern imdis::fd_t fd_server;
    //extern std::vector<std::shared_ptr<struct epoll_event> >
}
#endif //IMDIS_COMMON_H
