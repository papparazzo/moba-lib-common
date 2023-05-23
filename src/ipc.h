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

#pragma once

#include <cstdio>
#include <string>
#include <exception>

namespace moba {

class IPCException: public std::exception {

    std::string what_;
    
public:
    explicit IPCException(const std::string &err) noexcept: what_{err} {
    }

    IPCException() noexcept: what_{"Unknown error"} {
    }

    virtual ~IPCException() noexcept = default;

    virtual const char *what() const noexcept {
        return what_.c_str();
    }
};

class IPC {
public:
    static const size_t MSG_LEN     = 1024;
    static const int    DEFAULT_KEY = 123133;

    struct Message {
        long mtype;
        char mtext[IPC::MSG_LEN];
    };

    enum Type {
        TYPE_SERVER,
        TYPE_CLIENT
    };

    enum class Command {
        EMERGENCY_STOP    = 1,
        EMERGENCY_RELEASE = 2,
        TEST              = 3,
        RUN               = 4,
        HALT              = 5,
        CONTINUE          = 6,
        RESET             = 7,
        TERMINATE         = 8,
        INTERRUPT         = 9,
        RESUME            = 10,
        SET_DURATION      = 11,
    };

    IPC(key_t key = IPC::DEFAULT_KEY, Type type = TYPE_CLIENT);
    IPC(const IPC&) = delete;
    IPC& operator=(const IPC&) = delete;

    bool receive(long type, bool except = false);
    bool receive(Message &msg, long type = 0, bool except = false);
    bool send(const std::string &data, long type);
    bool send(const Message &msg);

    static Command getCMDFromString(const std::string &cmd);
    static std::string getCMDAsString(Command cmd);

    virtual ~IPC();

protected:
    int mID;
    Type type;
};
}
