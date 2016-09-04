//
// Created by yi on 29/05/16.
//

#ifndef IMDIS_CLIENTHANDLER_H
#define IMDIS_CLIENTHANDLER_H

#include <Common.h>

namespace imdis{

    class ClientHandler {

    public:
        ClientHandler(fd_t fd)
                :fd_(fd)
        {}

        void read_query();
        void handle();

    private:
        fd_t fd_;
    };

}


#endif //IMDIS_CLIENTHANDLER_H
