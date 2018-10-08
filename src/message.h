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

#include <string>
#include <boost/any.hpp>

#include "jsonabstractitem.h"

namespace moba {

    class Message {

        public:
            enum MessageType { // FIXME: Enum ausplitten und den einzlenen Handlern zuteilen
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
                MT_CLIENT_SELF_TESTING,

            // ---- SERVER ----
                MT_MAX_CLIENT_COUNT,
                MT_NEW_CLIENT_STARTED,
                MT_CLIENT_CLOSED,
                MT_RESET_CLIENT,

                MT_SERVER_INFO_REQ,
                MT_SERVER_INFO_RES,
                MT_CON_CLIENTS_REQ,
                MT_CON_CLIENTS_RES,
                MT_SELF_TESTING_CLIENT,

            // ---- TIMER ----
                MT_GLOBAL_TIMER_EVENT,
                MT_GET_GLOBAL_TIMER,
                MT_SET_GLOBAL_TIMER,
                MT_GET_COLOR_THEME,
                MT_SET_COLOR_THEME,
                MT_COLOR_THEME_EVENT,

            // ---- ENV ----
                MT_GET_ENVIRONMENT,
                MT_SET_ENVIRONMENT,
                MT_GET_AMBIENCE,
                MT_SET_AMBIENCE,
                MT_GET_AMBIENT_LIGHT,
                MT_SET_AMBIENT_LIGHT,

            // ---- INTERFACE ----

                MT_SET_CONNECTIVITY,

            // ---- SYS ----
                MT_SET_AUTOMATIC_MODE,
                MT_SET_EMERGENCY_STOP,
                MT_SET_STANDBY_MODE,
                MT_GET_HARDWARE_STATE,
                MT_HARDWARE_STATE_CHANGED,
                MT_HARDWARE_SHUTDOWN,
                MT_HARDWARE_RESET,

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
                MT_UNLOCK_LAYOUT,
                MT_LAYOUT_UNLOCKED,

                MT_GET_LAYOUT_REQ,
                MT_GET_LAYOUT_RES,

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

            std::string getRawMessage() const;

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
}
