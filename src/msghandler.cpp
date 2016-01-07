/*
 *  Project:    CommonLib
 *
 *  Version:    1.0.0
 *  History:    V1.0    07/12/2013  SP - created
 *
 *  Copyright (C) 2013 Stefan Paproth <pappi-@gmx.de>
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

#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <sstream>
#include <iostream>

#include "jsondecoder.h"
#include "jsonmsgdecoder.h"

#include "msghandler.h"
#include "jsonstreamreadersocket.h"

MsgHandler::MsgHandler() : appId(-1) {
    this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(this->socket == -1) {
        throw MsgHandlerException("socket creation failed");
    }
}

MsgHandler::~MsgHandler() {
    close(this->socket);
}

void MsgHandler::connect(const std::string &host, int port) {
    struct sockaddr_in host_addr;

    memset(&host_addr, 0, sizeof (host_addr));
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = inet_addr(host.c_str());

    if(host_addr.sin_addr.s_addr == INADDR_NONE) {
        struct hostent *hostn;

        hostn = gethostbyname(host.c_str());

        if(hostn == NULL) {
            throw MsgHandlerException("resolving url failed");
        }
        memcpy(
            (char*) &host_addr.sin_addr.s_addr,
            hostn->h_addr_list[0],
            hostn->h_length
        );
    }

    if(::connect(
        this->socket,
        (struct sockaddr*) &host_addr,
        sizeof (host_addr)
    ) == -1) {
        throw MsgHandlerException("connection to host failed");
    }
}

long MsgHandler::registerApp(const std::string &appName, Version version, const JsonArrayPtr &groups) {
    JsonObjectPtr obj(new JsonObject());

    (*obj)["appName"] = toJsonStringPtr(appName);
    (*obj)["version"] = version.toJsonPtr();
    (*obj)["msgGroups" ] = groups;

    Message msg(Message::MT_CLIENT_START, obj);
    this->sendMsg(msg);
    MessagePtr mptr = this->recieveMsg(MSG_HANDLER_TIME_OUT_SEC);
    if(mptr->getMsgType() != Message::MT_CLIENT_CONNECTED) {
        MsgHandlerException("did not recieve CLIENT_CONNECTED");
    }

    JsonItemPtr item = mptr->getData();

    boost::shared_ptr<JsonNumber<long int> > o =
    boost::dynamic_pointer_cast<JsonNumber<long int> >(item);
    return this->appId = o->getVal();
}

MessagePtr MsgHandler::recieveMsg(time_t timeoutSec) {
    struct timeval timeout;
    fd_set         read_sock;

    FD_ZERO(&read_sock);
    FD_SET(this->socket, &read_sock);

    timeout.tv_sec = timeoutSec;
    timeout.tv_usec = MSG_HANDLER_TIME_OUT_USEC;

    if(::select(this->socket + 1, &read_sock, NULL, NULL, &timeout) == -1) {
        throw MsgHandlerException("select-error occured!");
    }

    if(!FD_ISSET(this->socket, &read_sock)) {
        return MessagePtr();
    }

    JsonStreamReaderSocketPtr reader(new JsonStreamReaderSocket(this->socket));
    JsonMsgDecoder decoder(reader);
    return decoder.decodeMsg();
}

void MsgHandler::sendSetGlobalTimer(bool fireEvents, const std::string &curModelTime, unsigned int multiplicator, unsigned int intervall) {
    JsonObjectPtr obj(new JsonObject());
    (*obj)["fireEvents"   ] = toJsonBoolPtr(fireEvents);
    (*obj)["curModelTime" ] = toJsonStringPtr(curModelTime);
    (*obj)["multiplicator"] = toJsonNumberPtr(multiplicator);
    (*obj)["intervall"    ] = toJsonNumberPtr(intervall);
    this->sendMsg(Message(Message::MT_SET_GLOBAL_TIMER, obj));
}

void MsgHandler::sendSetEnvironment() {
    JsonObjectPtr obj(new JsonObject());
    // FIXME: parameter fehlen noch...
    (*obj)["thunderStorm"      ] = toJsonThreeStatePtr(JsonThreeState::ON);
    (*obj)["wind"              ] = toJsonThreeStatePtr(JsonThreeState::AUTO);
    (*obj)["rain"              ] = toJsonThreeStatePtr(JsonThreeState::OFF);
    (*obj)["curtainUp"         ] = toJsonBoolPtr(true);
    (*obj)["mainLightOn"       ] = toJsonBoolPtr(false);
    (*obj)["aux01"             ] = toJsonThreeStatePtr(JsonThreeState::OFF);
    this->sendMsg(Message(Message::MT_SET_ENVIRONMENT, obj));
}

void MsgHandler::sendSetHardwareState(HardwareState state) {
    JsonStringPtr str;
    switch(state) {
        case HS_ERROR:
            str = toJsonStringPtr("ERROR");
            break;

        case HS_STANDBY:
            str = toJsonStringPtr("STANDBY");
            break;

        case HS_POWER_OFF:
            str = toJsonStringPtr("POWER_OFF");
            break;

        case HS_READY:
            str = toJsonStringPtr("READY");
            break;
    }
    this->sendMsg(Message(Message::MT_SET_HARDWARE_STATE, str));
}

void MsgHandler::sendSystemNotice(MsgHandler::NoticeType type, const std::string &caption, const std::string &text) {
    JsonObjectPtr obj(new JsonObject());
    JsonStringPtr str;
    switch(type) {
        case NT_INFO:
            str = toJsonStringPtr("INFO");
            break;

        case NT_WARNING:
            str = toJsonStringPtr("WARNING");
            break;

        case NT_ERROR:
            str = toJsonStringPtr("ERROR");
            break;
    }

    (*obj)["type"   ] = str;
    (*obj)["caption"] = toJsonStringPtr(caption);
    (*obj)["text"   ] = toJsonStringPtr(text);
    this->sendMsg(Message(Message::MT_SYSTEM_NOTICE, obj));
}

void MsgHandler::sendCreateLayout(const std::string &name, const std::string &description, int width, int height) {
    JsonObjectPtr obj(new JsonObject());
    (*obj)["name"       ] = toJsonStringPtr(name);
    (*obj)["description"] = toJsonStringPtr(description);
    (*obj)["width"      ] = toJsonNumberPtr(width);
    (*obj)["height"     ] = toJsonNumberPtr(height);
    this->sendMsg(Message(Message::MT_CREATE_LAYOUT_REQ, obj));
}

void MsgHandler::sendUpdateLayout(long id, const std::string &name, const std::string &description, int width, int height) {
    JsonObjectPtr obj(new JsonObject());
    (*obj)["id"         ] = toJsonNumberPtr(id);
    (*obj)["name"       ] = toJsonStringPtr(name);
    (*obj)["description"] = toJsonStringPtr(description);
    (*obj)["width"      ] = toJsonNumberPtr(width);
    (*obj)["height"     ] = toJsonNumberPtr(height);
    this->sendMsg(Message(Message::MT_UPDATE_LAYOUT, obj));
}

void MsgHandler::sendMsg(const Message::MessageType type, const JsonItemPtr &msgData) {
    JsonObject obj;
    obj["msgType"] = Message::convertToString(type);
    obj["msgData"] = msgData;
    this->sendMsg(obj);
}

void MsgHandler::sendMsg(const Message::MessageType type, const std::string &msgData) {
    JsonObject obj;
    obj["msgType"] = Message::convertToString(type);
    obj["msgData"] = JsonStringPtr(new JsonString(msgData));
    this->sendMsg(obj);
}

void MsgHandler::sendMsg(const Message &msg) {
    JsonObject obj;
    obj["msgType"] = Message::convertToString(msg.getMsgType());
    obj["msgData"] = msg.getData();
    this->sendMsg(obj);
}

void MsgHandler::sendMsg(const std::string &msgType, const std::string &msgData) {
    JsonObject obj;
    obj["msgType"] = JsonStringPtr(new JsonString(msgType));
    obj["msgData"] = JsonStringPtr(new JsonString(msgData));
    this->sendMsg(obj);
}

void MsgHandler::sendMsg(const JsonObject &obj) {
    std::string s = obj.getJsonString();
    ssize_t c = ::send(this->socket, s.c_str(), s.length(), 0);
    if(c == -1 || c != s.length()) {
        MsgHandlerException("sending <" + s + "> failed");
    }
}

