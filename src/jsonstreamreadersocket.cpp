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
#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <cstring>

#include "jsonstreamreadersocket.h"

namespace moba {

    JsonStreamReaderSocket::JsonStreamReaderSocket(const std::string &host, int port) {
        struct sockaddr_in host_addr;

        ::memset(&host_addr, 0, sizeof (host_addr));
        host_addr.sin_family = AF_INET;
        host_addr.sin_port = htons(port);
        host_addr.sin_addr.s_addr = inet_addr(host.c_str());

        if(host_addr.sin_addr.s_addr == INADDR_NONE) {
            struct hostent *hostn;

            hostn = gethostbyname(host.c_str());

            if(hostn == NULL) {
                throw JsonStreamReaderException("resolving url failed");
            }
            memcpy(
                (char*) &host_addr.sin_addr.s_addr,
                hostn->h_addr_list[0],
                hostn->h_length
            );
        }

        if(
            ::connect(socket, (struct sockaddr*) &host_addr, sizeof(host_addr)
        ) == -1) {
            throw JsonStreamReaderException("connection to host failed");
        }
    }

    char JsonStreamReaderSocket::read() {
        char data;
        ::recv(socket, &data, sizeof(data), 0);
        return data;
    }
}
