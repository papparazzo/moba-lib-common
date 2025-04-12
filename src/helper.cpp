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

#include <cerrno>
#include <cstring>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "helper.h"

namespace moba {

std::string getErrno(const std::string &txt) {
    std::stringstream ss;

    char buffer[BUFSIZ];
    ss << txt << " <" << errno << ": " << strerror_r(errno, buffer, BUFSIZ) << ">";
    return ss.str();
}

std::string baseName(const std::string &path) {
    size_t i;
    for(i = path.length(); i > 0; i--) {
        if(path[i - 1] != '/') {
            break;
        }
    }
    size_t p = path.rfind('/');
    if(p == std::string::npos || i == 0) {
        return path;
    }
    return std::string(path, p + 1, i - p);
}

std::string getLicense(bool briefly) {
    if(briefly) {
        return "Licensed under GNU AFFERO GENERAL PUBLIC LICENSE, Version 3";
    }

    return
        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU Affero General Public License as\n"
        "published by the Free Software Foundation, either version 3 of the\n"
        "License, or (at your option) any later version.\n\n"

        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
        "GNU Affero General Public License for more details.\n\n"

        "You should have received a copy of the GNU Affero "
        "General Public License\n"
        "along with this program. If not, see "
        "<http://www.gnu.org/licenses/agpl.txt>.";
}

void printAppData(const AppData &appData) {
    std::cerr << "------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cerr << "  name:     " << appData.appName << std::endl;
    std::cerr << "  version:  " << appData.version << " ";
#ifdef DEBUG_MODE
    std::cerr << "[debug]" << std::endl;
#else
    std::cerr << "[release]" << std::endl;
#endif
    std::cerr << "  build on: " << appData.date << " " << appData.time << std::endl;
    std::cerr << std::endl;
    std::cerr << "  copyright (C) 2015 by Stefan Paproth <pappi-@gmx.de>" << std::endl;
    std::cerr << std::endl;
    std::cerr << "  " << getLicense(true) << std::endl;
    std::cerr << std::endl;
    std::cerr << "  You should have received a copy of the license along with this program." << std::endl;
    std::cerr << "  If not, see <https://www.gnu.org/licenses/agpl.txt> for further information!" << std::endl;
    std::cerr << "------------------------------------------------------------------------------------------------------------" << std::endl;
}
}
