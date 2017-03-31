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

#include "msghandler.h"
#include "jsonabstractitem.h"
#include "message.h"

namespace moba {

    class LayoutHandler {
        public:
            LayoutHandler(MsgHandlerPtr mhp) : mhp(mhp) {
            }

            // ---- Tracklayout ----
            void sendGetLayoutsRequest() {this->mhp->sendMsg(Message::MT_GET_LAYOUTS_REQ);}

            void sendDeleteLayout(long id) {this->mhp->sendMsg(Message::MT_DEL_LAYOUT, toJsonNumberPtr(id));}

            void sendCreateLayout(const std::string &name, const std::string &description);

            void sendUpdateLayout(long id, const std::string &name, const std::string &description);

            void sendUnlockLayout(long id) {this->mhp->sendMsg(Message::MT_UNLOCK_LAYOUT, toJsonNumberPtr(id));}

            void sendGetLayoutRequest(long id) {this->mhp->sendMsg(Message::MT_GET_LAYOUT_REQ, toJsonNumberPtr(id));}

        protected:
            MsgHandlerPtr mhp;
    };
}


