/*
 *  Project:    moba-common
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
    
struct DrivingDirection {
    enum DrivingDirectionEnum {
        FORWARD,
        BACKWARD
    };

    DrivingDirection(std::uint8_t drivingDirection) {
         this->drivingDirection =
            static_cast<DrivingDirectionEnum>(drivingDirection);
    }

    DrivingDirection(
        DrivingDirectionEnum drivingDirection = DrivingDirection::FORWARD
    ): drivingDirection{drivingDirection} {
    }

    DrivingDirection(const std::string &drivingDirection) {
        setDrivingDirection(drivingDirection);
    }

    DrivingDirection(const DrivingDirection &) = default;

    void toggle() {
        drivingDirection = DrivingDirection::flip(drivingDirection);
    }

    void setDrivingDirection(const std::string &s) {
        if(s == "FORWARD") {
            drivingDirection = DrivingDirection::FORWARD;
        } else if(s == "BACKWARD") {
            drivingDirection = DrivingDirection::BACKWARD;
        } else {
            throw moba::UnsupportedOperationException{"invalid value given"};
        }
    }

    std::string getDrivingDirection() const {
        switch(drivingDirection) {
            case DrivingDirection::FORWARD:
                return "FORWARD";

            case DrivingDirection::BACKWARD:
                return "BACKWARD";
        }
        throw moba::UnsupportedOperationException{"Not supported."};
    }

    static DrivingDirectionEnum flip(DrivingDirection d) {
        return flip(d.drivingDirection);
    }

    static DrivingDirectionEnum flip(DrivingDirectionEnum d) {
        switch(d) {
            case BACKWARD:
                return FORWARD;

            case FORWARD:
                return BACKWARD;

            default:
                throw moba::UnsupportedOperationException{"Not supported."};
        }
    }

    DrivingDirectionEnum drivingDirection;
};
}
