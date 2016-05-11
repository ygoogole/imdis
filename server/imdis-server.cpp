#include <iostream>
#include <memory>
#include <fcntl.h>
#include <assert.h>
#include "TcpHandler.h"
#include "Epoller.h"

using namespace std;

//global var in namespace imdis
namespace imdis{
    std::shared_ptr<imdis::Epoller> epoller;
    imdis::fd_t fd_server;
}

int main() {
    cout << "Hello, World!" << endl;

    imdis::fd_server = imdis::TcpHandler::tcp_bind();
    if (imdis::fd_server == imdis::TCP_NET_ERROR){
        return -1;
    }

    int flag = fcntl(imdis::fd_server, F_GETFL, 0);
    assert (flag != -1);
    flag |= O_NONBLOCK;
    int s = fcntl(imdis::fd_server, F_SETFL, flag);
    assert (s != -1);

    imdis::epoller = std::make_shared<imdis::Epoller>();
    //std::shared_ptr<struct epoll_event> ev_server = std::make_shared<struct epoll_event>();
    epoll_event ev;
    imdis::epoller->add_fd(imdis::epoller->epfd_server_, imdis::fd_server, &ev);
    imdis::epoller->set_pollin(imdis::epoller->epfd_server_, &ev);

//    std::make_thread();

//    std::shared_ptr<struct epoll_event> ev_io = std::shared_ptr<struct epoll_event>();
//    imdis::epoller->add_fd(imdis::epoller->epfd_io_, server, ev_io);

//    std::string ip;
//    uint16_t port;
//    imdis::fd_t fd = imdis::TcpHandler::tcp_accept(imdis::fd_server, ip, port);

    std::thread server_thread = imdis::epoller->spawn_server_loop();
    std::thread io_thread = imdis::epoller->spawn_io_loop();

    server_thread.join();
    io_thread.join();

    return 0;
}
