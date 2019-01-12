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

#include <exception>
#include <string>
#include <boost/shared_ptr.hpp>
#include <ctime>

#include "message.h"
#include "jsonabstractitem.h"
#include "version.h"

namespace moba {

    class MsgEndpointException : public std::exception {

        public:
            virtual ~MsgEndpointException() throw() {

            }

            MsgEndpointException(const std::string &what) {
                this->what__ = what;
            }

            virtual const char* what() const throw() {
                return this->what__.c_str();
            }

        private:
            std::string what__;
    };

    class MsgEndpoint {

        public:
            MsgEndpoint(const std::string &host, int port);
            virtual ~MsgEndpoint();

            long connect();

            long connect(const std::string &appName, Version version, const JsonArrayPtr &groups);

            MessagePtr recieveMsg(time_t timeoutSec = 0);

            long getAppId() {return appId;}

            // ---- message transmission ----
            void sendMsg(const Message::MessageType type, const JsonItemPtr &msgData);

            void sendMsg(const std::string &msgType, const std::string &msgData);

            void sendMsg(const Message::MessageType type);

            void sendMsg(const Message::MessageType type, const std::string &msgData);

            void sendMsg(const Message &msg);

            void sendMsg(const JsonObject &obj);

        protected:
            int socket;
            long appId;

            std::string host;
            int port;

            std::string appName;
            Version version;
            JsonArrayPtr groups;

            static const int MSG_HANDLER_BUFF_SIZ = 2048;
            static const int MSG_HANDLER_TIME_OUT_SEC = 2;
            static const int MSG_HANDLER_TIME_OUT_USEC = 0;

            long registerApp();
            void init();
    };

    using MsgEndpointPtr = boost::shared_ptr<MsgEndpoint>;
}