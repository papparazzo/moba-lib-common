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

#include "msgenvhandler.h"

namespace moba {

    void MsgEnvHandler::sendSetEnvironment(
        JsonSwitch::Switch thunder, JsonSwitch::Switch wind,
        JsonSwitch::Switch rain, JsonSwitch::Switch environmentSound,
        JsonSwitch::Switch aux1, JsonSwitch::Switch aux2, JsonSwitch::Switch aux3
    ) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["thunderStorm"      ] = toJsonSwitchPtr(thunder);
        (*obj)["wind"              ] = toJsonSwitchPtr(wind);
        (*obj)["rain"              ] = toJsonSwitchPtr(rain);
        (*obj)["environmentSound"  ] = toJsonSwitchPtr(environmentSound);
        (*obj)["aux01"             ] = toJsonSwitchPtr(aux1);
        (*obj)["aux02"             ] = toJsonSwitchPtr(aux2);
        (*obj)["aux03"             ] = toJsonSwitchPtr(aux3);
        msgep->sendMsg(Message(Message::MT_SET_ENVIRONMENT, obj));
    }

    void MsgEnvHandler::sendSetAmbience(
        JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn
    ) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["curtainUp"   ] = toJsonToggleStatePtr(curtainUp);
        (*obj)["mainLightOn" ] = toJsonToggleStatePtr(mainLightOn);
        msgep->sendMsg(Message(Message::MT_SET_AMBIENCE, obj));
    }

    void MsgEnvHandler::sendSetAmbientLight(const std::vector<MsgEnvHandler::AmbientLightData> &aldv) {
        JsonArrayPtr arr(new JsonArray());
        for(
            std::vector<MsgEnvHandler::AmbientLightData>::const_iterator iter = aldv.begin();
            iter != aldv.end();
            ++iter
        ) {
            JsonObjectPtr obj(new JsonObject());
            (*obj)["red"  ] = toJsonNumberPtr(iter->red);
            (*obj)["blue" ] = toJsonNumberPtr(iter->blue);
            (*obj)["white"] = toJsonNumberPtr(iter->white);
            arr->push_back(obj);
        }
        msgep->sendMsg(Message(Message::MT_SET_AMBIENT_LIGHT, arr));
    }
}