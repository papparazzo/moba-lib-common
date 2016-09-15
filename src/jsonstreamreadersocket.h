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

#include "jsonstreamreader.h"

namespace moba {

    class JsonStreamReaderSocket;

    typedef boost::shared_ptr<JsonStreamReaderSocket> JsonStreamReaderSocketPtr;

    class JsonStreamReaderSocket : public JsonStreamReader {

        public:
            JsonStreamReaderSocket(const std::string &host, int port);
            JsonStreamReaderSocket(int socket) : socket(socket) {
            }
            JsonStreamReaderSocket(const JsonStreamReaderSocket& orig) {}
            virtual ~JsonStreamReaderSocket() {};

            virtual char read();

        protected:
            int socket;

    };
}
