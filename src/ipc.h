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

namespace moba {

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
            static const size_t MSG_LEN = 1024;

            struct Message {
                long mtype;
                char mtext[IPC::MSG_LEN];
            };

            enum IPC_TYPE {
                SERVER,
                CLIENT
            };

            enum IPC_CMD {
                EMERGENCY_STOP     = 1,
                EMERGENCY_RELEASE  = 3,
                TEST               = 4,
                RUN                = 6,

                //HALT               = 2,
                //CONTINUE           = 5,
                //STORE              = 7,
                //RESUME             = 8
            };

            IPC(key_t key, IPC_TYPE type = CLIENT);

            bool receive(long type, bool except = false);
            bool receive(Message &msg, long type = 0, bool except = false);
            bool send(const std::string &data, long type);
            bool send(const Message &msg);

            virtual ~IPC();

        protected:
            int mID;
            IPC_TYPE type;
    };
}

