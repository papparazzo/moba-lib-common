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

#ifndef JSONITEM_H
#define	JSONITEM_H

#include <string>
#include <map>
#include <vector>
#include <sstream>

#include <boost/shared_ptr.hpp>

class JsonAbstractItem {
    public:
        virtual ~JsonAbstractItem() {};
        virtual std::string getJsonString() const = 0;
};

class JsonArray : public JsonAbstractItem, public std::vector<boost::shared_ptr<JsonAbstractItem> > {
    public:
        std::string getJsonString() const {
            std::stringstream ss;
            ss << '[';
            for(
                JsonArray::const_iterator iter = this->begin();
                iter != this->end();
                ++iter
            ) {
                if(iter != this->begin()) {
                    ss << ',';
                }
                ss << (*iter)->getJsonString();
            }
            ss << ']';
            return ss.str();
        }
};

class JsonObject : public JsonAbstractItem, public std::map<std::string, boost::shared_ptr<JsonAbstractItem> > {
    public:
        std::string getJsonString() const {
            std::stringstream ss;
            ss << '{';
            for(
                JsonObject::const_iterator iter = this->begin();
                iter != this->end();
                ++iter
            ) {
                if(iter != this->begin()) {
                    ss << ',';
                }
                ss << '"' << iter->first << "\":" << iter->second->getJsonString();
            }
            ss << '}';
            return ss.str();
        }
};

class JsonBool : public JsonAbstractItem {
    public:
        JsonBool(bool v) : v(v) {
        }
        JsonBool(const JsonBool &v) : v(v.v) {
        }
        operator bool() const {
            return this->v;
        }
        std::string getJsonString() const {
            if(this->v) {
                return "true";
            }
            return "false";
        };

        bool getVal() {
            return this->v;
        }

    protected:
        bool v;
};

class JsonNULL : public JsonAbstractItem {
    public:
        operator bool() const {
            return false;
        }
        std::string getJsonString() const {
            return "null";
        };
};

class JsonThreeState : public JsonAbstractItem {
    public:
        enum ThreeState {
            ON,
            OFF,
            AUTO
        };

        JsonThreeState(JsonThreeState::ThreeState v) : v(v) {
        }

        std::string getJsonString() const {
            switch(this->v) {
                case ON:
                    return "ON";
                case OFF:
                    return "OFF";
                case AUTO:
                    return "AUTO";
            }
        }

    protected:
        ThreeState v;
};

class JsonString : public JsonAbstractItem, public std::string {

    public:
        JsonString(const std::string &v) : std::string(v) {

        }

        std::string getJsonString() const {
            std::stringstream ss;
            ss << '"';
            for(size_t i = 0; i < this->length(); ++i) {
                switch(this->data()[i]) {
                    case '"':
                        ss << "\\\"";
                        break;
                    case '\n':
                        ss << "\\n";
                        break;
                    default:
                        ss << this->data()[i];
                }
            }
            ss << '"';
            return ss.str();
        };
};

template <typename T> class JsonNumber : public JsonAbstractItem {
    public:
        JsonNumber(T v) : v(v){
        }
        JsonNumber(const JsonNumber &v) : v(v.v) {
        }
        virtual ~JsonNumber() {};

        std::string getJsonString() const {
            std::stringstream ss;
            ss << this->v;
            return ss.str();
        };

        T getVal() {
            return this->v;
        }

        JsonNumber<T> operator = (const JsonNumber<T> &v) const {
            this->v = v;
        }

    protected:
        T v;
};

typedef boost::shared_ptr<JsonAbstractItem> JsonItemPtr;
typedef boost::shared_ptr<JsonArray>        JsonArrayPtr;
typedef boost::shared_ptr<JsonObject>       JsonObjectPtr;
typedef boost::shared_ptr<JsonString>       JsonStringPtr;
typedef boost::shared_ptr<JsonBool>         JsonBoolPtr;
typedef boost::shared_ptr<JsonThreeState>   JsonThreeStatePtr;

inline JsonBoolPtr toJsonBoolPtr(bool v) {
    return JsonBoolPtr(new JsonBool(v));
}

inline JsonStringPtr toJsonStringPtr(const std::string &v) {
    return JsonStringPtr(new JsonString(v));
}

inline JsonThreeStatePtr toJsonThreeStatePtr(JsonThreeState::ThreeState v) {
    return JsonThreeStatePtr(new JsonThreeState(v));
}

template <typename T>
boost::shared_ptr<JsonNumber<T> > toJsonNumberPtr(T v) {
    return boost::shared_ptr<JsonNumber<T> >(new JsonNumber<T>(v));
}

#endif	// JSONITEM_H
