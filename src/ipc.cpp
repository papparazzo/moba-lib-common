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

#include <boost/algorithm/string.hpp>

#include "helper.h"
#include "ipc.h"
#include "log.h"
#include "exception.h"

namespace moba::common {

    IPC::IPC(key_t key, Type type) {
        int flags = S_IRWXU | S_IWGRP | S_IWOTH;;
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
        if(msgctl(this->mID, IPC_RMID, NULL) == -1) {
            LOG(LogLevel::ERROR) << getErrno("unable to delete msg-queue! ") << std::endl;
        }
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
        strncpy(msg.mtext, data.c_str(), IPC::MSG_LEN);
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
        if(boost::iequals(cmd, "EMERGENCY_STOP")) {
            return CMD_EMERGENCY_STOP;
        }
        if(boost::iequals(cmd, "EMERGENCY_RELEASE")) {
            return CMD_EMERGENCY_RELEASE;
        }
        if(boost::iequals(cmd, "TEST")) {
            return CMD_TEST;
        }
        if(boost::iequals(cmd, "RUN")) {
            return CMD_RUN;
        }
        if(boost::iequals(cmd, "HALT")) {
            return CMD_HALT;
        }
        if(boost::iequals(cmd, "CONTINUE")) {
            return CMD_CONTINUE;
        }
        if(boost::iequals(cmd, "RESET")) {
            return CMD_RESET;
        }
        if(boost::iequals(cmd, "TERMINATE")) {
            return CMD_TERMINATE;
        }
        if(boost::iequals(cmd, "INTERRUPT")) {
            return CMD_INTERRUPT;
        }
        if(boost::iequals(cmd, "RESUME")) {
            return CMD_RESUME;
        }
        if(boost::iequals(cmd, "SET_DURATION")) {
            return CMD_SET_DURATION;
        }
        throw IPCException{std::string("unknown command <" + cmd + ">")};
    }

    std::string IPC::getCMDAsString(IPC::Command cmd) {
        switch(cmd) {
            case CMD_EMERGENCY_STOP:
                return "EMERGENCY_STOP";

            case CMD_EMERGENCY_RELEASE:
                return "EMERGENCY_RELEASE";

            case CMD_TEST:
                return "TEST";

            case CMD_RUN:
                return "RUN";

            case CMD_HALT:
                return "HALT";

            case CMD_CONTINUE:
                return "CONTINUE";

            case CMD_RESET:
                return "RESET";

            case CMD_TERMINATE:
                return "TERMINATE";

            case CMD_INTERRUPT:
                return "INTERRUPT";

            case CMD_RESUME:
                return "RESUME";

            case CMD_SET_DURATION:
                return "SET_DURATION";

            default:
                throw UnsupportedOperationException{"IPC::Command is invalid"};
        }
    }
}
