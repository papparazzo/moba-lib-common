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
#include <ostream>
#include <iostream>

#define LOG(loglevel)          moba::common::writeLoggerPrefix(std::cerr, __FILE__, __LINE__, (loglevel))
#define VC_LOG(VarName)        moba::common::writeLoggerPrefix(std::cerr, __FILE__, __LINE__, moba::common::LogLevel::NOTICE) << "content of [" #VarName "]\t = <" << (VarName) << ">" << std::endl;
#define EXC_LOG(excType, What) moba::common::writeLoggerPrefix(std::cerr, __FILE__, __LINE__, moba::common::LogLevel::WARNING) << (excType) << " exception occurred >> what(" << (What) << ") <<" << std::endl;

namespace moba { namespace common {

    enum class LogLevel {
        ERROR,
        WARNING,
        INFO,
        NOTICE,
        DEBUG
    };

    std::ostream &writeLoggerPrefix(std::ostream &stream, const std::string &file, const int &line, const LogLevel &logLevel);
}}
