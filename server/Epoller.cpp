//
// Created by yi on 09/05/16.
//

#include "Epoller.h"
#include "../TcpHandler.h"
#include <sys/epoll.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>

int imdis::Epoller::add_fd(imdis::fd_t epfd, imdis::fd_t fd, epoll_event *ev) {

    ev->events = 0;
    ev->data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, ev);
    assert(ret != -1);

    return 0;
}

imdis::Epoller::Epoller()
    :stop_server_(false)
    ,stop_io_(false){

    epfd_server_ = epoll_create(1);
    assert(epfd_server_ != -1);

    epfd_io_ = epoll_create(1);
    assert(epfd_io_ != -1);
}

imdis::Epoller::~Epoller() {

}

int imdis::Epoller::rm_fd(fd_t epfd, fd_t fd, epoll_event *ev) {

    ev->events = 0;
    ev->data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, ev);
    assert(ret != -1);

    return 0;
}

int imdis::Epoller::set_pollin(fd_t epfd, epoll_event *ev) {

    ev->events |= EPOLLIN;

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev->data.fd, ev);
}

int imdis::Epoller::set_pollout(fd_t epfd, epoll_event *ev) {

    ev->events |= EPOLLOUT;

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev->data.fd, ev);
}

int imdis::Epoller::reset_pollin(fd_t epfd, epoll_event *ev) {

    ev->events &= ~((short) EPOLLIN);

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev->data.fd, ev);
}

int imdis::Epoller::reset_pollout(fd_t epfd, epoll_event *ev) {

    ev->events &= ~((short) EPOLLOUT);

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev->data.fd, ev);
}

void imdis::Epoller::server_loop() {

    std::cout << "looping in server_loop" << std::endl;

    struct epoll_event ev_buf[max_io_event];

    while(!stop_server_){

        //fd_t fd = handle_conection_request();
        //std::cout << "accpeted fd = " << fd << std::endl;
        // -1, block forever,
        // 0, return right away
        int n = epoll_wait(epfd_server_, &ev_buf[0], max_io_event, -1);

        for (int i = 0; i < n; ++i){

            std::cout << "n = " << n << " fd " << ev_buf[i].data.fd << " polled in server_loop" << std::endl;

            if (ev_buf[i].data.fd == -1)
                continue;

            if (ev_buf[i].events & EPOLLIN){
                fd_t fd = handle_conection_request();
                std::cout << "accpeted fd = " << fd << std::endl;
                //std::shared_ptr<struct epoll_event> evt_ptr = std::make_shared<struct epoll_event>();
                struct epoll_event ev;
                add_fd(epfd_io_, fd, &ev);
                set_pollin(epfd_io_, &ev);
                //set_pollout(epfd_io_, &ev);
            }
        }
    }
}

void imdis::Epoller::io_loop() {

    std::cout << "looping in io_loop" << std::endl;
    struct epoll_event ev_buf[max_io_event];

    while(!stop_io_){

        // -1, block forever,
        // 0, return right away
        int n = epoll_wait(epfd_io_, &ev_buf[0], max_io_event, -1);

        for (int i = 0; i < n; ++i){

            std::cout << "fd " << ev_buf[i].data.fd << " polled in io_loop" << std::endl;

            if (ev_buf[i].data.fd == -1)
                continue;

            if (ev_buf[i].events & EPOLLIN){

                read_in(ev_buf[i].data.fd);
                std::cout << "receive from client" << std::endl;
                //return ;
            }

            if (ev_buf[i].events & EPOLLOUT){

                std::cout << "reply to client" << std::endl;
                // reply to client
            }
        }
    }
}

std::thread imdis::Epoller::spawn_server_loop() {

    return std::thread([&]{server_loop();});
}

std::thread imdis::Epoller::spawn_io_loop() {

    return std::thread([&]{io_loop();});
}

imdis::fd_t imdis::Epoller::handle_conection_request() {

    std::string ip;
    uint16_t port;
    return TcpHandler::tcp_accept(imdis::fd_server, ip, port);

}

void imdis::Epoller::read_in(fd_t fd) {

    char buf[10];
    ssize_t n = read(fd, buf, 10);

    std::cout << n << " bytes read from socket " << fd << std::endl;
}





























