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

#include "helper.h"

namespace moba {

    enum class LogLevel {
        CRITICAL,
        ERROR,
        WARNING,
        NOTICE
    };

    inline std::string getTimeStamp(const std::chrono::time_point<std::chrono::system_clock>& timestamp) {
        std::stringstream ss;

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()) % 1000;
        auto timer = std::chrono::system_clock::to_time_t(timestamp);

        std::tm bt;

        localtime_r(&timer, &bt);

        ss <<
            std::put_time(&bt, "%Y-%m-%d %H:%M:%S.") << std::right <<
            std::setw(3) << std::setfill('0') << ms.count();
        return ss.str();
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
        }
    }

    inline std::ostream &operator<< (std::ostream &stream, const LogLevel &logLevel) {
        stream << getTimeStamp() << getLogLevelString(logLevel);
        return stream;
    }
}
