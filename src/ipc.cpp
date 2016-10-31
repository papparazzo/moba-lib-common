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

#include "helper.h"
#include "ipc.h"
#include "log.h"

namespace moba {

    IPC::IPC(key_t key, IPC_TYPE type) {
        int flags = S_IRWXU | S_IWGRP | S_IWOTH;;
        if(type == SERVER) {
            flags |= IPC_CREAT | IPC_EXCL;
        }
        this->mID = msgget(key, flags);
        this->type = type;
        if(this->mID == -1) {
             throw IPCException(getErrno("msgget failed"));
        }
    }

    IPC::~IPC() {
        if(this->type == CLIENT) {
            return;
        }
        if(msgctl(this->mID, IPC_RMID, NULL) == -1) {
            LOG(ERROR) << getErrno("unable to delete msg-queue! ") << std::endl;
        }
    }

    bool IPC::receive(long msgtyp, bool except) {
        Message msg;
        return this->receive(msg, msgtyp, except);
    }

    bool IPC::receive(Message &msg, long msgtyp, bool except) {
        memset(msg.mtext, '\0', moba::IPC::MSG_LEN);
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
        throw IPCException(getErrno("msgrcv failed"));
    }

    bool IPC::send(const std::string &data, long type) {
        Message msg;
        msg.mtype = type;
        memset(msg.mtext, '\0', moba::IPC::MSG_LEN);
        strncpy(msg.mtext, data.c_str(), moba::IPC::MSG_LEN);
        this->send(msg);
    }

    bool IPC::send(const Message &msg) {
        if(msgsnd(this->mID, &msg, IPC::MSG_LEN, IPC_NOWAIT) == 0) {
            return true;
        }

        if(errno == EAGAIN) {
            return false;
        }

        throw IPCException(getErrno("msgsnd failed"));
    }
}
