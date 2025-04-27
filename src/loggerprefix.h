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

    inline std::ostream &operator<< (std::ostream &stream, const LogLevel &logLevel) {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        auto timer = std::chrono::system_clock::to_time_t(now);

        std::tm bt;

        localtime_r(&timer, &bt);

        stream <<
            std::put_time(&bt, "%Y-%m-%d %H:%M:%S.") << std::right <<
            std::setw(3) << std::setfill('0') << ms.count();

        switch(logLevel) {
            case LogLevel::CRITICAL:
                stream << " Critical: ";
                break;

            case LogLevel::ERROR:
                stream << " Error:    ";
                break;

            case LogLevel::WARNING:
                stream << " Warning:  ";
                break;

            case LogLevel::NOTICE:
                stream << " Notice:   ";
                break;
        }
        return stream;
    }
}
