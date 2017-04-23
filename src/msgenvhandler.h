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

    class MsgEnvHandler {
        public:
            MsgEnvHandler(MsgEndpointPtr msgep) : msgep(msgep) {
            }

            virtual ~MsgEnvHandler() {
            }

            void sendGetEnvironment() {msgep->sendMsg(Message::MT_GET_ENVIRONMENT);}

            void sendSetEnvironment(JsonSwitch::Switch thunder, JsonSwitch::Switch wind, JsonSwitch::Switch rain, JsonSwitch::Switch environmentSound, JsonSwitch::Switch aux1, JsonSwitch::Switch aux2, JsonSwitch::Switch aux3);

            void sendGetAmbience() {msgep->sendMsg(Message::MT_GET_AMBIENCE);}

            void sendSetAmbience(JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn);

            void sendGetAmbientLight() {msgep->sendMsg(Message::MT_GET_AMBIENT_LIGHT);}

            struct AmbientLightData {
                AmbientLightData() {};
                AmbientLightData(int red, int blue, int green, int white) {
                    this->red = red;
                    this->blue = blue;
                    this->green = green;
                    this->white = white;
                }
                int red;
                int blue;
                int green;
                int white;
            };

            void sendSetAmbientLight(const AmbientLightData &ald);

        protected:
            MsgEndpointPtr msgep;

    };
}

