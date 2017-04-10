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
#include <vector>

#include <boost/shared_ptr.hpp>

#include "message.h"
#include "jsonabstractitem.h"
#include "version.h"

namespace moba {

    class MsgHandlerException : public std::exception {

        public:
            virtual ~MsgHandlerException() throw() {

            }

            MsgHandlerException(const std::string &what) {
                this->what__ = what;
            }

            virtual const char* what() const throw() {
                return this->what__.c_str();
            }

        private:
            std::string what__;
    };

    class MsgHandler {

        public:
            MsgHandler();
            virtual ~MsgHandler();

            void connect(const std::string &host, int port);

            void connect();

            MessagePtr recieveMsg(time_t timeoutSec = 0);

            // ---- Client ----
            long registerApp(const std::string &appName, Version version, const JsonArrayPtr &groups);

            void sendVoid() {this->sendMsg(Message::MT_VOID);}

            void sendEchoReq(const std::string &data) {this->sendMsg(Message::MT_ECHO_REQ, data);}

            void sendClientClose() {this->sendMsg(Message::MT_CLIENT_CLOSE);}

            // ---- Server ----
            void sendResetClient(long id) {this->sendMsg(Message::MT_RESET_CLIENT, toJsonNumberPtr(id));}

            void sendSelfTestingClient(long id) {this->sendMsg(Message::MT_SELF_TESTING_CLIENT, toJsonNumberPtr(id));}

            void sendServerInfoReq() {this->sendMsg(Message::MT_SERVER_INFO_REQ);}

            void sendConClientsReq() {this->sendMsg(Message::MT_CON_CLIENTS_REQ);}

            long getAppId() {return this->appId;}

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

            static const int MSG_HANDLER_BUFF_SIZ = 2048;
            static const int MSG_HANDLER_TIME_OUT_SEC = 2;
            static const int MSG_HANDLER_TIME_OUT_USEC = 0;
    };

    typedef boost::shared_ptr<MsgHandler> MsgHandlerPtr;
}