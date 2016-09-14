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

#pragma once

#include <string>
#include <ostream>

#define LOG(loglevel)          moba::writeLoggerPrefix(std::cerr, __FILE__, __LINE__, (loglevel))
#define VC_LOG(VarName)        moba::writeLoggerPrefix(std::cerr, __FILE__, __LINE__, moba::NOTICE) << "content of [" #VarName "]\t = <" << (VarName) << ">"
#define EXC_LOG(excType, What) moba::writeLoggerPrefix(std::cerr, __FILE__, __LINE__, moba::WARNING) << (excType) << " exception occurred >> what(" << (What) << ") <<"

namespace moba {

    enum LogLevel {
        ERROR,
        WARNING,
        INFO,
        NOTICE,
        DEBUG
    };

    std::ostream &writeLoggerPrefix(std::ostream &stream, const std::string &file, const int &line, const LogLevel &logLevel);
}
