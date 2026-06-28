/*
*  Project:    moba-common
 *
 *  Copyright (C) 2025 Stefan Paproth <pappi-@gmx.de>
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

#include <iomanip>
#include <chrono>
#include <ctime>
#include <sys/timeb.h>

#include <string>
#include <sstream>
#include <ostream>
#include <iostream>
#include <format>

namespace moba {

    enum class LogLevel: std::uint8_t {
        CRITICAL = 0,
        ERROR    = 1,
        WARNING  = 2,
        NOTICE   = 3,
        DEBUG    = 4,
        TRACE    = 5
    };

    inline std::string getTimeStamp(const std::chrono::time_point<std::chrono::system_clock>& timestamp) {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()) % 1000;
        return std::format("{:%Y-%m-%d %H:%M:%S}.{:03}", timestamp, ms.count());
    }

    inline std::string getTimeStamp() {
        return getTimeStamp(std::chrono::system_clock::now());
    }

    inline std::string getLogLevelString(const LogLevel &logLevel) {
        switch(logLevel) {
            case LogLevel::CRITICAL:
                return " Critical: ";

            case LogLevel::ERROR:
                return " Error:    ";

            case LogLevel::WARNING:
                return " Warning:  ";
                break;

            case LogLevel::NOTICE:
                return " Notice:   ";

            case LogLevel::DEBUG:
                return " Debug:    ";

            case LogLevel::TRACE:
                return " Trace:    ";
        }
        return " Unknown:  ";
    }

    inline std::ostream &operator<< (std::ostream &stream, const LogLevel &logLevel) {
        stream << getTimeStamp() << getLogLevelString(logLevel);
        return stream;
    }
}
