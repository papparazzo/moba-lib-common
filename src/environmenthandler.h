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
#include <vector>

#include "message.h"
#include "jsonabstractitem.h"
#include "msghandler.h"

namespace moba {

    class EnvironmentHandler {
        public:
            EnvironmentHandler(MsgHandlerPtr mhp) : mhp(mhp) {
            }

            // ---- GlobalTimer ----
            void sendGetGlobalTimer() {this->mhp->sendMsg(Message::MT_GET_GLOBAL_TIMER);}

            void sendSetGlobalTimer(const std::string &curModelTime, unsigned int intervall, unsigned int multiplicator);

            void sendSetAutoMode(bool on) {this->mhp->sendMsg(Message::MT_SET_AUTO_MODE, toJsonBoolPtr(on));}

            void sendGetAutoMode() {this->mhp->sendMsg(Message::MT_GET_AUTO_MODE);}

            void sendGetColorTheme() {this->mhp->sendMsg(Message::MT_GET_COLOR_THEME);}

            void sendSetColorTheme(const std::string &dimTime, const std::string &brightTime, JsonThreeState::ThreeState condition);

            // ---- Environment ----
            void sendGetEnvironment() {this->mhp->sendMsg(Message::MT_GET_ENVIRONMENT);}

            void sendSetEnvironment(JsonSwitch::Switch thunder, JsonSwitch::Switch wind, JsonSwitch::Switch rain, JsonSwitch::Switch environmentSound, JsonSwitch::Switch aux1, JsonSwitch::Switch aux2, JsonSwitch::Switch aux3);

            void sendGetAmbience() {this->mhp->sendMsg(Message::MT_GET_AMBIENCE);}

            void sendSetAmbience(JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn);

            void sendGetAmbientLight() {this->mhp->sendMsg(Message::MT_GET_AMBIENT_LIGHT);}

            struct AmbientLightData {
                AmbientLightData() {};
                AmbientLightData(int red, int blue, int white) {
                    this->red = red;
                    this->blue = blue;
                    this->white = white;
                }
                int red;
                int blue;
                int white;
            };

            void sendSetAmbientLight(const std::vector<AmbientLightData> &aldv);

        protected:
            MsgHandlerPtr mhp;
    };
}

