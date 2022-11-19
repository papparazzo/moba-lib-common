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
#include <boost/noncopyable.hpp>

namespace moba { namespace common {

    class IPCException : public std::exception {

        public:
            explicit IPCException(const std::string &err) throw() : what_(err) {
            }

            IPCException() throw() : what_("Unknown error") {
            }

            virtual ~IPCException() throw() {
            }

            virtual const char *what() const throw() {
                return what_.c_str();
            }

        private:
            std::string what_;
    };

    class IPC : private boost::noncopyable {

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

            enum Command {
                CMD_EMERGENCY_STOP    = 1,
                CMD_EMERGENCY_RELEASE = 2,
                CMD_TEST              = 3,
                CMD_RUN               = 4,
                CMD_HALT              = 5,
                CMD_CONTINUE          = 6,
                CMD_RESET             = 7,
                CMD_TERMINATE         = 8,
                CMD_INTERRUPT         = 9,
                CMD_RESUME            = 10,
                CMD_SET_DURATION      = 11,
            };

            IPC(key_t key = IPC::DEFAULT_KEY, Type type = TYPE_CLIENT);

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
}}
