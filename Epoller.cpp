//
// Created by yi on 09/05/16.
//

#include "Epoller.h"
#include <sys/epoll.h>
#include <assert.h>

int imdis::Epoller::add_fd(imdis::fd_t epfd, imdis::fd_t fd, std::shared_ptr<struct epoll_event>& ev_ptr) {

    ev_ptr.get()->events = 0;
    ev_ptr.get()->data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, ev_ptr.get());
    assert(ret != -1);

    return 0;
}

imdis::Epoller::Epoller() {

    epfd_server_ = epoll_create(1);
    assert(epfd_server_ != -1);

    epfd_io_ = epoll_create(1);
    assert(epfd_io_ != -1);
}

imdis::Epoller::~Epoller() {

}

int imdis::Epoller::rm_fd(fd_t epfd, fd_t fd, std::shared_ptr<struct epoll_event> &ev_ptr) {

    ev_ptr->events = 0;
    ev_ptr->data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, ev_ptr.get());
    assert(ret != -1);

    return 0;
}

int imdis::Epoller::set_pollin(fd_t epfd, std::shared_ptr<struct epoll_event> &ev_ptr) {

    ev_ptr->events |= EPOLLIN;

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev_ptr->data.fd, ev_ptr.get());
}

int imdis::Epoller::set_pollout(fd_t epfd, std::shared_ptr<struct epoll_event> &ev_ptr) {

    ev_ptr->events |= EPOLLOUT;

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev_ptr->data.fd, ev_ptr.get());
}

int imdis::Epoller::reset_pollin(fd_t epfd, std::shared_ptr<struct epoll_event> &ev_ptr) {

    ev_ptr->events &= ~((short) EPOLLIN);

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev_ptr->data.fd, ev_ptr.get());
}

int imdis::Epoller::reset_pollout(fd_t epfd, std::shared_ptr<struct epoll_event> &ev_ptr) {

    ev_ptr->events &= ~((short) EPOLLOUT);

    return epoll_ctl(epfd, EPOLL_CTL_MOD, ev_ptr->data.fd, ev_ptr.get());
}















