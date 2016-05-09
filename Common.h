//
// Created by yi on 08/05/16.
//

#ifndef IMDIS_COMMON_H
#define IMDIS_COMMON_H

#include <memory>

namespace imdis{

    typedef int fd_t;

    enum error_code_t{
        TCP_NET_ERROR = -1,
    };

    class Epoller;
    extern std::shared_ptr<imdis::Epoller> epoller_;
}
#endif //IMDIS_COMMON_H
