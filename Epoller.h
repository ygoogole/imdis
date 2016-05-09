//
// Created by yi on 09/05/16.
//

#ifndef IMDIS_EPOLLER_H
#define IMDIS_EPOLLER_H

#include "Common.h"
#include <sys/epoll.h>
#include <memory>

namespace imdis{

    class Epoller {

    public:
        fd_t epfd_server_;
        fd_t epfd_io_;

        Epoller();
        ~Epoller();

        Epoller(const Epoller& ) = delete;
        Epoller& operator=(const Epoller &) = delete;

        int add_fd(fd_t epfd, fd_t fd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int rm_fd(fd_t epfd, fd_t fd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int set_pollin(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int set_pollout(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int reset_pollin(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int reset_pollout(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
    };

}


#endif //IMDIS_EPOLLER_H
