/*
 *  Project:    moba-common
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <string>

#include "helper.h"
#include "ipc.h"
#include "exception.h"

namespace moba {

    IPC::IPC(key_t key, Type type) {
        int flags = S_IRWXU | S_IWGRP | S_IWOTH;
        if(type == TYPE_SERVER) {
            flags |= IPC_CREAT | IPC_EXCL;
        }
        this->mID = msgget(key, flags);
        this->type = type;
        if(this->mID == -1) {
             throw IPCException{getErrno("msgget failed")};
        }
    }

    IPC::~IPC() {
        if(this->type == TYPE_CLIENT) {
            return;
        }
        msgctl(this->mID, IPC_RMID, NULL);
    }

    bool IPC::receive(long msgtyp, bool except) {
        Message msg;
        return this->receive(msg, msgtyp, except);
    }

    bool IPC::receive(Message &msg, long msgtyp, bool except) {
        ::memset(msg.mtext, '\0', IPC::MSG_LEN);
        int msgflg = IPC_NOWAIT;
        if(except) {
            msgflg |= MSG_EXCEPT;
        }
        if(msgrcv(this->mID, &msg, IPC::MSG_LEN, msgtyp, msgflg) > 0) {
            return true;
        }
        if(errno == ENOMSG) {
            return false;
        }
        throw IPCException{getErrno("msgrcv failed")};
    }

    bool IPC::send(const std::string &data, long type) {
        Message msg;
        msg.mtype = type;
        memset(msg.mtext, '\0', IPC::MSG_LEN);

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wstringop-truncation"
        strncpy(msg.mtext, data.c_str(), IPC::MSG_LEN);
        #pragma GCC diagnostic pop
        return this->send(msg);
    }

    bool IPC::send(const Message &msg) {
        if(msgsnd(this->mID, &msg, IPC::MSG_LEN, IPC_NOWAIT) == 0) {
            return true;
        }

        if(errno == EAGAIN) {
            return false;
        }

        throw IPCException{getErrno("msgsnd failed")};
    }

    IPC::Command IPC::getCMDFromString(const std::string &cmd) {
        if(cmd == "EMERGENCY_STOP") {
            return Command::EMERGENCY_STOP;
        }
        if(cmd == "EMERGENCY_RELEASE") {
            return Command::EMERGENCY_RELEASE;
        }
        if(cmd == "TEST") {
            return Command::TEST;
        }
        if(cmd == "RUN") {
            return Command::RUN;
        }
        if(cmd == "HALT") {
            return Command::HALT;
        }
        if(cmd == "CONTINUE") {
            return Command::CONTINUE;
        }
        if(cmd == "RESET") {
            return Command::RESET;
        }
        if(cmd == "TERMINATE") {
            return Command::TERMINATE;
        }
        if(cmd == "INTERRUPT") {
            return Command::INTERRUPT;
        }
        if(cmd == "RESUME") {
            return Command::RESUME;
        }
        if(cmd == "SET_DURATION") {
            return Command::SET_DURATION;
        }
        throw IPCException{std::string("unknown command <" + cmd + ">")};
    }

    std::string IPC::getCMDAsString(IPC::Command cmd) {
        switch(cmd) {
            case Command::EMERGENCY_STOP:
                return "EMERGENCY_STOP";

            case Command::EMERGENCY_RELEASE:
                return "EMERGENCY_RELEASE";

            case Command::TEST:
                return "TEST";

            case Command::RUN:
                return "RUN";

            case Command::HALT:
                return "HALT";

            case Command::CONTINUE:
                return "CONTINUE";

            case Command::RESET:
                return "RESET";

            case Command::TERMINATE:
                return "TERMINATE";

            case Command::INTERRUPT:
                return "INTERRUPT";

            case Command::RESUME:
                return "RESUME";

            case Command::SET_DURATION:
                return "SET_DURATION";

            default:
                throw UnsupportedOperationException{"IPC::Command is invalid"};
        }
    }
}
