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

#include "version.h"
#include <sstream>
#include <vector>
#include <iomanip>

namespace moba {

    Version::Version(const std::string &version) {
        parseFromString(version);
    }

    std::string Version::getString() const {
        if(ver[Version::MAJOR] == -1) {
            return "0.0.0-0000";
        }

        std::stringstream o;

        o <<
            ver[Version::MAJOR] << "." << ver[Version::MINOR] << "." <<
            ver[Version::BUILD] << "-" << std::setw(4) <<
            std::setfill('0') << ver[Version::PATCH];

        return o.str();
    }

    int Version::compareMajor(const Version &v) const {
        if(this->ver[MAJOR] < v.ver[MAJOR]) {
            return -1;
        }
        if(this->ver[MAJOR] > v.ver[MAJOR]) {
            return 1;
        }
        return 0;
    }

    int Version::compareMinor(const Version &v) const {
        if(this->ver[MINOR] < v.ver[MINOR]) {
            return -1;
        }
        if(this->ver[MINOR] > v.ver[MINOR]) {
            return 1;
        }
        return 0;
    }

    bool Version::operator <(const Version &v) const {
        if(this->ver[MAJOR] < v.ver[MAJOR]) {
            return true;
        }
        if(this->ver[MAJOR] > v.ver[MAJOR]) {
            return false;
        }
        if(this->ver[MINOR] < v.ver[MINOR]) {
            return true;
        }
        if(this->ver[MINOR] > v.ver[MINOR]) {
            return false;
        }
        if(this->ver[BUILD] < v.ver[BUILD]) {
            return true;
        }
        if(this->ver[BUILD] > v.ver[BUILD]) {
            return false;
        }
        if(this->ver[PATCH] < v.ver[PATCH]) {
            return true;
        }
        if(this->ver[PATCH] > v.ver[PATCH]) {
            return false;
        }
        return false;
    }

    bool Version::operator >(const Version &v) const {
        return !this->operator <(v);
    }

    bool Version::operator <=(const Version &v) const {
        return this->operator <(v) || this->operator ==(v);
    }

    bool Version::operator >=(const Version &v) const {
        return this->operator >(v) || this->operator ==(v);
    }

    void Version::parseFromString(std::string version) {
        if(version.length() == 0) {
            throw VersionException{"version-string is empty or not set"};
        }

        try {
            size_t p = version.rfind('-');

            if(p == std::string::npos) {
                p = version.rfind('.');
            }
            if(p == std::string::npos) {
                throw VersionException{"invalid version-string given"};
            }

            ver[3] = std::stoi(version.substr(p + 1));

            size_t f;
            --p;
            for(int i = 2; i >= 0; --i) {
                f = version.rfind('.', p);
                if(f == std::string::npos) {
                    f = -1;
                }
                ver[i] = std::stoi(version.substr(f + 1, p - f));
                p = f - 1;
            }
        } catch(...) {
            throw VersionException{"converting failed"};
        }
    }

    std::ostream& operator<<(std::ostream &out, const Version &v) {
        out << v.getString();
        return out;
    }
}
