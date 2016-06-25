/*
 *  json
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

#ifndef JSONSTREAMREADER_H
#define	JSONSTREAMREADER_H

#include <boost/shared_ptr.hpp>
#include <exception>

class JsonStreamReaderException : public std::exception {

    public:
        virtual ~JsonStreamReaderException() throw() {

        }

        JsonStreamReaderException(const std::string& what) {
            this->what__ = what;
        }

        virtual const char* what() const throw() {
            return this->what__.c_str();
        }

    private:
        std::string what__;
};

class JsonStreamReader;

typedef boost::shared_ptr<JsonStreamReader> JsonStreamReaderPtr;

class JsonStreamReader {
    public:
        virtual ~JsonStreamReader() {};
        virtual char read() = 0;

    private:

};

#endif	/* JSONSTREAMREADER_H */
