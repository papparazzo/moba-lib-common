/*
 *  Project:    moba-blocksystem
 *
 *  Copyright (C) 2020 Stefan Paproth <pappi-@gmx.de>
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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include "exception.h"

namespace moba {
    
enum class SwitchStand {
    STRAIGHT_1 = 0,
    BEND_1     = 1,
    STRAIGHT_2 = 2,
    BEND_2     = 3,
};

inline SwitchStand stringToSwitchStandEnum(const std::string &s) {
    if(s == "STRAIGHT_1") {
        return SwitchStand::STRAIGHT_1;
    } else if(s == "BEND_1") {
        return SwitchStand::BEND_1;
    } else if(s == "STRAIGHT_2") {
        return SwitchStand::STRAIGHT_2;
    } else if(s == "BEND_2") {
        return SwitchStand::BEND_2;
    } else {
        throw moba::UnsupportedOperationException{"SwitchStand: invalid value given"};
    }
}

inline std::string switchStandEnumToString(const SwitchStand s) {
    switch(s) {
        case SwitchStand::STRAIGHT_1:
            return "STRAIGHT_1";

        case SwitchStand::BEND_1:
            return "BEND_1";

        case SwitchStand::STRAIGHT_2:
            return "STRAIGHT_2";

        case SwitchStand::BEND_2:
            return "BEND_2";

        default:
            throw moba::UnsupportedOperationException{"SwitchStand: invalid value given"};
    }
}
}
