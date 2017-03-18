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

#include <memory>

#include "jsonabstractitem.h"
#include "jsonstreamreader.h"

namespace moba {

    class JsonException : public std::exception {

        public:
            virtual ~JsonException() throw() {

            }

            JsonException() {

            }

            JsonException(const std::string &what) {
                this->what__ = what;
            }

            virtual const char* what() const throw() {
                return this->what__.c_str();
            }

        private:
            std::string what__;
    };

    class JsonDecoder {

        public:
            JsonDecoder(JsonStreamReaderPtr reader, bool strict = false) : lastChar(0), reader(reader), strict(strict) {}
            JsonItemPtr decode();

        protected:
            void checkNext(const char x);
            char next(bool ignoreWhitespace = false);
            std::string next(int n);
            std::string nextKey();

            JsonItemPtr nextValue();
            JsonItemPtr parseValue(const std::string &s);
            JsonItemPtr nextJValue();

            JsonStringPtr nextString();
            JsonObjectPtr nextObject();
            JsonArrayPtr nextArray();

            char read();

            bool strict;
            static const int  MAX_STRING_LENGTH = 1024;
            char lastChar;
            JsonStreamReaderPtr reader;
    };
}
