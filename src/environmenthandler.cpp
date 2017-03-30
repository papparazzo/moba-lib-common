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

#include "environmenthandler.h"
#include "msghandler.h"

namespace moba {

    void EnvironmentHandler::sendSetGlobalTimer(const std::string &curModelTime, unsigned int intervall, unsigned int multiplicator) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["curModelTime" ] = toJsonStringPtr(curModelTime);
        (*obj)["intervall"    ] = toJsonNumberPtr(intervall);
        (*obj)["multiplicator"] = toJsonNumberPtr(multiplicator);
        this->mhp->sendMsg(Message(Message::MT_SET_GLOBAL_TIMER, obj));
    }

    void EnvironmentHandler::sendSetEnvironment(
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
        this->mhp->sendMsg(Message(Message::MT_SET_ENVIRONMENT, obj));
    }

    void EnvironmentHandler::sendSetAmbience(
        JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn
    ) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["curtainUp"   ] = toJsonToggleStatePtr(curtainUp);
        (*obj)["mainLightOn" ] = toJsonToggleStatePtr(mainLightOn);
        this->mhp->sendMsg(Message(Message::MT_SET_AMBIENCE, obj));
    }

    void EnvironmentHandler::sendSetColorTheme(
        const std::string &dimTime, const std::string &brightTime, JsonThreeState::ThreeState condition
    ) {
        JsonObjectPtr obj(new JsonObject());
        (*obj)["dimTime"   ] = toJsonStringPtr(dimTime);
        (*obj)["brightTime"] = toJsonStringPtr(brightTime);
        (*obj)["condition" ] = toJsonThreeStatePtr(condition);
        this->mhp->sendMsg(Message(Message::MT_SET_COLOR_THEME, obj));
    }

    void EnvironmentHandler::sendSetAmbientLight(const std::vector<EnvironmentHandler::AmbientLightData> &aldv) {
        JsonArrayPtr arr(new JsonArray());
        for(
            std::vector<EnvironmentHandler::AmbientLightData>::const_iterator iter = aldv.begin();
            iter != aldv.end();
            ++iter
        ) {
            JsonObjectPtr obj(new JsonObject());
            (*obj)["red"  ] = toJsonNumberPtr(iter->red);
            (*obj)["blue" ] = toJsonNumberPtr(iter->blue);
            (*obj)["white"] = toJsonNumberPtr(iter->white);
            arr->push_back(obj);
        }
        this->mhp->sendMsg(Message(Message::MT_SET_AMBIENT_LIGHT, arr));
    }
}