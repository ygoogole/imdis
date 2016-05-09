#include <iostream>
#include <memory>
#include "TcpHandler.h"
#include "Epoller.h"

using namespace std;

//global var in namespace imdis
namespace imdis{
    std::shared_ptr<imdis::Epoller> epoller_;
}

int main() {
    cout << "Hello, World!" << endl;

    imdis::fd_t server = imdis::TcpHandler::tcp_bind();
    if (server == imdis::TCP_NET_ERROR){
        return -1;
    }

    imdis::epoller_ = std::make_shared<imdis::Epoller>();
    std::shared_ptr<struct epoll_event> ev_server = std::shared_ptr<struct epoll_event>();
    imdis::epoller_->add_fd(imdis::epoller_->epfd_server_, server, ev_server);

//    std::make_thread();

//    std::shared_ptr<struct epoll_event> ev_io = std::shared_ptr<struct epoll_event>();
//    imdis::epoller_->add_fd(imdis::epoller_->epfd_io_, server, ev_io);

    std::string ip;
    uint16_t port;
    imdis::fd_t fd = imdis::TcpHandler::tcp_accept(server, ip, port);

    return 0;
}
