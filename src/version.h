/*
 *  Project:    CommonLib
 *
 *  Version:    1.0.0
 *  History:    V1.0    02/11/2015  SP - created
 *
 *  Copyright (C) 2013 Stefan Paproth <pappi-@gmx.de>
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
        Version() : majorn(-1) {
        }

        Version(int major, int minor, int build, int patch) :
        majorn(majorn), minorn(minorn), buildn(buildn), patchn(patchn) {
        }

        Version(const Version &orig) :
        majorn(orig.majorn), minorn(orig.minorn),
        buildn(orig.buildn), patchn(orig.patchn) {
        }

        Version(const std::string &version);

        virtual ~Version() {
        };

        int compareMajor(const Version &v) const;

        int compareMinor(const Version &v) const;

        inline bool operator == (const Version &v) const {
            return
                this->majorn == v.majorn &&
                this->minorn == v.minorn &&
                this->buildn == v.buildn &&
                this->patchn == v.patchn;
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
        int majorn;
        int minorn;
        int buildn;
        int patchn;
};

