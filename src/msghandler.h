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

            long registerApp(const std::string &appName, Version version, const JsonArrayPtr &groups);

            void sendVoid() {this->sendMsg(Message::MT_VOID);}

            void sendEchoReq(const std::string &data) {this->sendMsg(Message::MT_ECHO_REQ, data);}

            MessagePtr recieveMsg(time_t timeoutSec = 0);

            // ---- Client ----
            void sendClientClose() {this->sendMsg(Message::MT_CLIENT_CLOSE);}

            // ---- Server ----
            void sendResetClient(long id) {this->sendMsg(Message::MT_RESET_CLIENT, toJsonNumberPtr(id));}

            void sendSelfTestingClient(long id) {this->sendMsg(Message::MT_SELF_TESTING_CLIENT, toJsonNumberPtr(id));}

            void sendServerInfoReq() {this->sendMsg(Message::MT_SERVER_INFO_REQ);}

            void sendConClientsReq() {this->sendMsg(Message::MT_CON_CLIENTS_REQ);}

            // ---- Environment ----
            void sendGetGlobalTimer() {this->sendMsg(Message::MT_GET_GLOBAL_TIMER);}

            void sendSetGlobalTimer(const std::string &curModelTime, unsigned int intervall, unsigned int multiplicator);

            void sendGetEnvironment() {this->sendMsg(Message::MT_GET_ENVIRONMENT);}

            void sendSetEnvironment(JsonSwitch::Switch thunder, JsonSwitch::Switch wind, JsonSwitch::Switch rain, JsonSwitch::Switch environmentSound, JsonSwitch::Switch aux1, JsonSwitch::Switch aux2, JsonSwitch::Switch aux3);

            void sendGetAmbience() {this->sendMsg(Message::MT_GET_AMBIENCE);}

            void sendSetAmbience(JsonToggleState::ToggleState curtainUp, JsonToggleState::ToggleState mainLightOn);

            void sendSetAutoMode(bool on) {this->sendMsg(Message::MT_SET_AUTO_MODE, toJsonBoolPtr(on));}

            void sendGetAutoMode() {this->sendMsg(Message::MT_GET_AUTO_MODE);}

            void sendGetColorTheme() {this->sendMsg(Message::MT_GET_COLOR_THEME);}

            void sendSetColorTheme(const std::string &dimTime, const std::string &brightTime, JsonThreeState::ThreeState condition);

            void sendGetAmbientLight() {this->sendMsg(Message::MT_GET_AMBIENT_LIGHT);}

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

            // ---- System ----
            void sendEmergencyStop() {this->sendMsg(Message::MT_EMERGENCY_STOP);}

            void sendEmergencyStopClearing() {this->sendMsg(Message::MT_EMERGENCY_STOP_CLEARING);}

            void sendGetHardwareState()  {this->sendMsg(Message::MT_GET_HARDWARE_STATE);}

            enum HardwareState {
                HS_ERROR,
                HS_STANDBY,
                HS_POWER_OFF,
                HS_READY
            };

            void sendSetHardwareState(HardwareState state);

            void sendHardwareShutdown() {this->sendMsg(Message::MT_HARDWARE_SHUTDOWN);}

            void sendHardwareReset() {this->sendMsg(Message::MT_HARDWARE_RESET);}

            void sendHardwareSwitchStandby() {this->sendMsg(Message::MT_HARDWARE_SWITCH_STANDBY);}

            // ---- Tracklayout ----
            void sendTrackLayoutRequest() {this->sendMsg(Message::MT_GET_LAYOUTS_REQ);}

            void sendDeleteLayout(long id) {this->sendMsg(Message::MT_DEL_LAYOUT, toJsonNumberPtr(id));}

            void sendCreateLayout(const std::string &name, const std::string &description, int width, int height);

            void sendUpdateLayout(long id, const std::string &name, const std::string &description, int width, int height);

            enum NoticeType {
                NT_INFO,
                NT_WARNING,
                NT_ERROR
            };

            void sendSystemNotice(NoticeType type, const std::string &caption, const std::string &text);

            long getAppId() {return this->appId;}

        protected:
            int socket;
            long appId;

            static const int MSG_HANDLER_BUFF_SIZ = 2048;
            static const int MSG_HANDLER_TIME_OUT_SEC = 2;
            static const int MSG_HANDLER_TIME_OUT_USEC = 500000;

            void sendMsg(const Message::MessageType type, const JsonItemPtr &msgData);
            void sendMsg(const std::string &msgType, const std::string &msgData);
            void sendMsg(const Message::MessageType type);
            void sendMsg(const Message::MessageType type, const std::string &msgData);
            void sendMsg(const Message &msg);
            void sendMsg(const JsonObject &obj);
    };
}
