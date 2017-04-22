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

#include "message.h"
#include "msgendpoint.h"
#include "jsonabstractitem.h"

namespace moba {

    class MsgTimerHandler {
        public:
            MsgTimerHandler(MsgEndpointPtr msgep) : msgep(msgep) {
            }

            virtual ~MsgTimerHandler() {
            }

            void sendGetGlobalTimer() {msgep->sendMsg(Message::MT_GET_GLOBAL_TIMER);}

            void sendSetGlobalTimer(const std::string &curModelTime, unsigned int multiplicator);

            void sendGetAutoMode() {msgep->sendMsg(Message::MT_GET_AUTO_MODE);}

            void sendSetAutoMode(bool on) {msgep->sendMsg(Message::MT_SET_AUTO_MODE, toJsonBoolPtr(on));}

            void sendGetColorTheme() {msgep->sendMsg(Message::MT_GET_COLOR_THEME);}

            void sendSetColorTheme(const std::string &dimTime, const std::string &brightTime, JsonThreeState::ThreeState condition);

        protected:
            MsgEndpointPtr msgep;

    };
}

