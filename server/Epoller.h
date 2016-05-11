//
// Created by yi on 09/05/16.
//

#ifndef IMDIS_EPOLLER_H
#define IMDIS_EPOLLER_H

#include "../Common.h"
#include <sys/epoll.h>
#include <memory>
#include <thread>

namespace imdis{

    class Epoller {

    public:
        fd_t epfd_server_;
        fd_t epfd_io_;

        bool stop_server_;
        bool stop_io_;

        Epoller();
        ~Epoller();

        Epoller(const Epoller& ) = delete;
        Epoller& operator=(const Epoller &) = delete;
/*
        int add_fd(fd_t epfd, fd_t fd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int rm_fd(fd_t epfd, fd_t fd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int set_pollin(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int set_pollout(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int reset_pollin(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
        int reset_pollout(fd_t epfd, std::shared_ptr<struct epoll_event>& ev_ptr);
*/
        int add_fd(fd_t epfd, fd_t fd, epoll_event *ev);
        int rm_fd(fd_t epfd, fd_t fd, epoll_event *ev);
        int set_pollin(fd_t epfd, epoll_event *ev);
        int set_pollout(fd_t epfd, epoll_event *ev);
        int reset_pollin(fd_t epfd, epoll_event *ev);
        int reset_pollout(fd_t epfd, epoll_event *ev);


        void server_loop();
        void io_loop();

        std::thread spawn_server_loop();
        std::thread spawn_io_loop();

        imdis::fd_t handle_conection_request();


        void read_in(fd_t fd);
    };

}


#endif //IMDIS_EPOLLER_H
