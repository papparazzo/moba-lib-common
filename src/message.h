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

#ifndef MESSAGE_H
#define	MESSAGE_H

#include <string>
#include <boost/any.hpp>

#include "jsonabstractitem.h"

class Message {
    public:
        enum MessageType {
        // ---- CLIENT ----
            MT_VOID,
            MT_ECHO_RES,
            MT_ECHO_REQ,
            MT_ERROR,

            MT_CLIENT_START,
            MT_CLIENT_CONNECTED,
            MT_CLIENT_CLOSE,
            MT_CLIENT_SHUTDOWN,
            MT_CLIENT_RESET,

        // ---- SERV ----
            MT_MAX_CLIENT_COUNT,
            MT_NEW_CLIENT_STARTED,
            MT_CLIENT_CLOSED,
            MT_RESET_CLIENT,

            MT_SERVER_INFO_REQ,
            MT_SERVER_INFO_RES,
            MT_CON_CLIENTS_REQ,
            MT_CON_CLIENTS_RES,

        // ---- ENV ----
            MT_GLOBAL_TIMER_EVENT,
            MT_GET_GLOBAL_TIMER,
            MT_SET_GLOBAL_TIMER,
            MT_GET_ENVIRONMENT,
            MT_SET_ENVIRONMENT,
            MT_SET_AUTO_MODE,
            MT_GET_COLOR_THEME,
            MT_SET_COLOR_THEME,
            MT_COLOR_THEME_EVENT,

        // ---- SYS ----
            MT_EMERGENCY_STOP,
            MT_EMERGENCY_STOP_CLEARING,
            MT_GET_HARDWARE_STATE,
            MT_SET_HARDWARE_STATE,
            MT_HARDWARE_STATE_CHANGED,
            MT_HARDWARE_SHUTDOWN,
            MT_HARDWARE_RESET,
            MT_HARDWARE_SWITCH_STANDBY,

        // ---- TLT ----
            MT_GET_LAYOUTS_REQ,
            MT_GET_LAYOUTS_RES,
            MT_DEL_LAYOUT,
            MT_LAYOUT_DELETED,
            MT_CREATE_LAYOUT_REQ,
            MT_CREATE_LAYOUT_RES,
            MT_LAYOUT_CREATED,
            MT_UPDATE_LAYOUT,
            MT_LAYOUT_UPDATED,

            MT_SYSTEM_NOTICE,

            MT_UNKNOWN
        };

        Message(MessageType msgType = MT_VOID);
        Message(MessageType msgType, JsonItemPtr data);

        virtual ~Message();

        static const std::string MSG_HEADER;
        static const std::string DATA_HEADER;

        static JsonStringPtr convertToString(MessageType mt);
        static MessageType convertToMsgType(const std::string &msgName);

        MessageType getMsgType() const {
            return this->msgType;
        }

        JsonItemPtr getData() const {
            return this->data;
        }

        std::string msgTypeAsString() const;

        template<typename charT, typename traits>
        friend std::basic_ostream<charT, traits> &
        operator<< (std::basic_ostream<charT, traits> &lhs, Message const &rhs) {
            return lhs << rhs.msgTypeAsString();
        }

    protected:
        MessageType msgType;
        JsonItemPtr data;
};

typedef boost::shared_ptr<Message> MessagePtr;

#endif	// MESSAGE_H
