/*
 *  Project:    moba-common
 *
 *  Version:    1.0.0
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

#include <iomanip>
#include <ctime>
#include <sys/timeb.h>

#include "helper.h"
#include "log.h"

namespace moba {

    std::ostream &writeLoggerPrefix(std::ostream &stream, const std::string &file, const int &line, const LogLevel &logLevel) {
        timeb actual;
        char buffer[25] = "";

        ftime(&actual);
        strftime(buffer, 21, "%d.%m.%Y %H:%M:%S.", localtime(&actual.time));
        stream <<
            buffer << std::right << std::setw(3) << std::setfill('0') << actual.millitm <<
            std::setw(15) << std::setfill(' ') << moba::baseName(file) << ":" <<
            std::setw(4) << std::setfill('0') << line << " " << std::left <<
            std::setw(9) << std::setfill(' ');

        switch(logLevel) {
            case ERROR:
                stream << "Error: ";
                break;

            case WARNING:
                stream << "Warning: ";
                break;

            case INFO:
                stream << "Info: ";
                break;

            case NOTICE:
                stream << "Notice: ";
                break;

            case DEBUG:
                stream << "Debug: ";
                break;

            default:
                stream << "Unknown: ";
                break;
        }
        return stream;
    }
}
