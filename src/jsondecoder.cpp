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

#include "jsondecoder.h"

#include <boost/algorithm/string.hpp>
#include <exception>
#include <sstream>

JsonItemPtr JsonDecoder::decode()  {
    this->checkNext('{');
    return this->nextObject();
}

void JsonDecoder::checkNext(const char x) {
    char c = this->next(!this->strict);
    if(c != x) {
        throw JsonException(
            std::string("expected '") +
            std::string(1, x) + "' found '" +
            std::string(1, c) + "'!"
        );
    }
}

char JsonDecoder::read() {
    return this->reader->read();
}

char JsonDecoder::next(bool ignoreWhitespace) {
    if(this->lastChar != 0) {
        char t = this->lastChar;
        this->lastChar = 0;
        return t;
    }
    char c;
    do {
        c = this->read();
    } while(::isspace(c) && ignoreWhitespace);

    if(c == -1 || c == 0) {
        throw JsonException("input stream corrupted!");
    }
    return c;
}

std::string JsonDecoder::next(int n) {
    std::stringstream ss;

    if(n == 0) {
        return "";
    }

    for(int i = 0; i < n; ++i) {
        ss << this->next();
    }
    return ss.str();
}

JsonObjectPtr JsonDecoder::nextObject() {
    JsonObjectPtr map(new JsonObject());
    std::string key;
    char c;

    for(int i = 0; i < JsonDecoder::MAX_STRING_LENGTH; ++i) {
        c = this->next(!this->strict);
        switch(c) {
            case '}':
                return map;

            case '"':
                key = this->nextKey();
                break;

            default:
                throw JsonException("invalid key");
        }
        this->checkNext(':');

        if(map->find(key) != map->end()) {
            throw JsonException(std::string("duplicate key <") + key + ">");
        }
        (*map)[key] = this->nextValue();

        switch(this->next(!this->strict)) {
            case ',':
                c = this->next(!this->strict);
                if(c == '}'){
                    throw JsonException("expected new key");
                }
                this->lastChar = c;
                break;

            case '}':
                return map;

            default:
                throw JsonException("expected a ',' or '}'");
        }
    }
    throw JsonException("maximum string-length reached!");
}

std::string JsonDecoder::nextKey() {
    std::stringstream sb;

    for(int i = 0; i < JsonDecoder::MAX_STRING_LENGTH; ++i) {
        char c = this->next();

        if(isspace(c) || !(isalnum(c) || c == '_' || c == '"')) {
            throw JsonException("key contains invalide char!");
        }

        if(c == '"') {
            std::string s = sb.str();
            boost::algorithm::trim(s);
            if(s.length() == 0) {
                throw JsonException("key is empty");
            }
            return s;
        }
        sb << c;
    }
    throw JsonException("maximum string-length reached!");
}

JsonItemPtr JsonDecoder::nextValue() {
    char c = this->next(!this->strict);
    switch(c) {
        case '"':
            return this->nextString();

        case '{':
            return this->nextObject();

        case '[':
            return this->nextArray();

        default:
            this->lastChar = c;
            return this->nextJValue();
    }
}

JsonStringPtr JsonDecoder::nextString() {
    char c;
    std::stringstream sb;
    for(int i = 0; i < JsonDecoder::MAX_STRING_LENGTH; ++i) {
        c = this->next();
        switch(c) {
            case '\n':
            case '\r':
                throw JsonException("invalid char");

            case '\\':
                c = this->next();
                switch (c) {
                    case 'b':
                        sb << '\b';
                        break;

                    case 't':
                        sb << '\t';
                        break;

                    case 'n':
                        sb << '\n';
                        break;

                    case 'f':
                        sb << '\f';
                        break;

                    case 'r':
                        sb << '\r';
                        break;

                    case 'u':
                        //FIXME sb.append((char)Integer.parseInt(this->next(4), 16));
                        break;

                    case '"':
                    case '\\':
                    case '/':
                        sb << c;
                        break;

                    default:
                        throw JsonException("invalid escape-sequence");
                }
                break;

            case '"':
                return toJsonStringPtr(sb.str());

            default:
                sb << c;
                break;
        }
    }
    throw JsonException("maximum string-length reached!");
}

JsonArrayPtr JsonDecoder::nextArray() {
    JsonArrayPtr v(new JsonArray());

    char c = this->next();

    if(c == ']') {
        return v;
    }
    this->lastChar = c;
    v->push_back(this->nextValue());

    while(true) {
        c = this->next();

        switch(c) {
            case ',':
                v->push_back(this->nextValue());
                break;

            case ']':
                return v;

            default:
                throw JsonException("expected ',' or ']'");
        }
    }
}

JsonItemPtr JsonDecoder::nextJValue()  {
    char c;
    std::stringstream sb;
    for(int i = 0; i < JsonDecoder::MAX_STRING_LENGTH; ++i) {
        c = this->next();

        if(c == ',' || c == ']' || c == '}') {
            this->lastChar = c;
            return this->parseValue(sb.str());
        }

        if(
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '-' || c == '+'
        ) {
            sb << c;
            continue;
        }
        throw JsonException("parsing error");
    }
    throw JsonException("maximum string-length reached!");
}

JsonItemPtr JsonDecoder::parseValue(const std::string &s) {
    if(!s.length()) {
        throw JsonException("empty value");
    }

    if(boost::iequals(s, "true")) {
        return toJsonBoolPtr(true);
    }
    if(boost::iequals(s, "false")) {
        return toJsonBoolPtr(false);
    }
    if(boost::iequals(s, "null")) {
        return toJsonNULLPtr();
    }
    char b = s[0];
    try {
        if((b >= '0' && b <= '9') || b == '-') {
            if(
                b == '0' &&
                s.length() > 2 &&
                (s[1] == 'x' || s[1] == 'X')
            ) {
                return JsonItemPtr(
                    new JsonNumber<long int>(strtol(&(s.c_str()[2]), NULL, 16))
                );
            }

            if(
                s.find('.') != std::string::npos ||
                s.find('e') != std::string::npos ||
                s.find('E') != std::string::npos
            ) {
                std::stringstream buffer;
                double output;
                buffer << s;
                buffer >> output;
                return toJsonNumberPtr(output);
            }
            return toJsonNumberPtr(atol(s.c_str()));
        }
    } catch(std::exception e) {
        throw JsonException(
            std::string("parsing, error could not determine value: <") +
            std::string(e.what()) + ">"
        );
    }
    std::cout << "---" << s << "---" << std::endl;

    throw JsonException("parsing error, could not determine value" );
}
