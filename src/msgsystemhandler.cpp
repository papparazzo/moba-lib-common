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

#include <string>

#include "msgsystemhandler.h"
#include "jsonabstractitem.h"

namespace moba {

    void MsgSystemHandler::sendSetHardwareState(MsgSystemHandler::HardwareState state) {
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
        msgep->sendMsg(Message(Message::MT_SET_HARDWARE_STATE, str));
    }

    void MsgSystemHandler::sendSystemNotice(MsgSystemHandler::NoticeType type, const std::string &caption, const std::string &text) {
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
        msgep->sendMsg(Message(Message::MT_SYSTEM_NOTICE, obj));
    }
}