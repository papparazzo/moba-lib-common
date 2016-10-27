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

    class IPC {

        public:
            enum IPC_TYPE {
                READING,
                WRITING
            };

            IPC(IPC_TYPE type, const std::string &ffile);
            virtual ~IPC();

            void readLine(std::string &data);
            void writeLine(const std::string &data);

        protected:
            static const int BUFFER_SIZE = 1024;

            std::string ffile;
            FILE *stream;
            IPC_TYPE type;

            void init();
            void terminate();
            void reset();
            IPC(const IPC&) {

            }
    };
}

