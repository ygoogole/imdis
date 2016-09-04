//
// Created by yi on 29/05/16.
//

#ifndef IMDIS_COMMAND_H
#define IMDIS_COMMAND_H

#include <string>

namespace imdis{

    class Command {
    public:
        Command(std::string cmd_str);
        int process_command();

    private:
        std::string argv_;
        uint8_t argc;
    };
}

#endif //IMDIS_COMMAND_H
