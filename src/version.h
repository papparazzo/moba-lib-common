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
#include <exception>

#include "jsonabstractitem.h"

namespace moba {

    class VersionException : public std::exception {

        public:
            virtual ~VersionException() throw() {
            }

            VersionException(const std::string &what) {
                this->what__ = what;
            }

            virtual const char *what() const throw() {
                return this->what__.c_str();
            }

        private:
            std::string what__;
    };

    class Version : public JsonAbstractItem {

        public:

            Version() {
                this->ver[MAJOR] = -1;
            }

            Version(int major, int minor = 0, int build = 0, int patch = 0) {
                this->ver[MAJOR] = major;
                this->ver[MINOR] = minor;
                this->ver[BUILD] = build;
                this->ver[PATCH] = patch;
            }

            Version(const Version &orig) {
                this->ver[MAJOR] = orig.ver[MAJOR];
                this->ver[MINOR] = orig.ver[MINOR];
                this->ver[BUILD] = orig.ver[BUILD];
                this->ver[PATCH] = orig.ver[PATCH];
            }

            Version(const std::string &version);

            virtual ~Version() {
            };

            int compareMajor(const Version &v) const;

            int compareMinor(const Version &v) const;

            inline bool operator == (const Version &v) const {
                return
                    this->ver[MAJOR] == v.ver[MAJOR] &&
                    this->ver[MINOR] == v.ver[MINOR] &&
                    this->ver[BUILD] == v.ver[BUILD] &&
                    this->ver[PATCH] == v.ver[PATCH];
            }

            inline bool operator != (const Version &v) const {
                return !this->operator ==(v);
            }

            bool operator <(const Version &v) const;
            bool operator >(const Version &v) const;

            bool operator <=(const Version &v) const;
            bool operator >=(const Version &v) const;

            friend std::ostream& operator<<(std::ostream &out, const Version &v);


            std::string getJsonString() const;

            JsonItemPtr toJsonPtr() {
                return JsonItemPtr(new Version(*this));
            }

        protected:
            enum VersionPart {
                MAJOR = 0,
                MINOR = 1,
                BUILD = 2,
                PATCH = 3
            };
            int ver[4];
    };
}
