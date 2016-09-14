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
#include <map>
#include <vector>
#include <sstream>

#include <boost/shared_ptr.hpp>

namespace moba {
    class JsonAbstractItem {

        public:
            virtual ~JsonAbstractItem() {};
            virtual std::string getJsonString() const = 0;
    };

    typedef boost::shared_ptr<JsonAbstractItem> JsonItemPtr;

    class JsonArray : public JsonAbstractItem, public std::vector<JsonItemPtr> {

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

    typedef boost::shared_ptr<JsonArray> JsonArrayPtr;

    class JsonObject : public JsonAbstractItem, public std::map<std::string, JsonItemPtr> {

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

    typedef boost::shared_ptr<JsonObject> JsonObjectPtr;

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

    typedef boost::shared_ptr<JsonBool> JsonBoolPtr;

    class JsonNULL : public JsonAbstractItem {

        public:
            operator bool() const {
                return false;
            }

            std::string getJsonString() const {
                return "null";
            };
    };

    typedef boost::shared_ptr<JsonNULL> JsonNULLPtr;

    class JsonSwitch : public JsonAbstractItem {

        public:
            enum Switch {
                ON,
                AUTO,
                UNSET,
                TRIGGER,
                OFF
            };

            JsonSwitch(JsonSwitch::Switch v) : v(v) {
            }

            std::string getJsonString() const {
                switch(this->v) {
                    case ON:
                        return "\"ON\"";

                    case OFF:
                        return "\"OFF\"";

                    case AUTO:
                        return "\"AUTO\"";

                    case UNSET:
                        return "\"UNSET\"";

                    case TRIGGER:
                        return "\"TRIGGER\"";
                }
            }

            Switch getVal() {
                return this->v;
            }

        protected:
            Switch v;
    };

    typedef boost::shared_ptr<JsonSwitch> JsonSwitchPtr;

    class JsonToggleState : public JsonAbstractItem {

        public:
            enum ToggleState {
                ON,
                OFF,
                UNSET
            };

            JsonToggleState(JsonToggleState::ToggleState v) : v(v) {
            }

            std::string getJsonString() const {
                switch(this->v) {
                    case ON:
                        return "\"ON\"";

                    case OFF:
                        return "\"OFF\"";

                    case UNSET:
                        return "\"UNSET\"";
                }
            }

            ToggleState getVal() {
                return this->v;
            }

        protected:
            ToggleState v;
    };

    typedef boost::shared_ptr<JsonToggleState> JsonToggleStatePtr;

    class JsonThreeState : public JsonAbstractItem {

        public:
            enum ThreeState {
                ON,
                OFF,
                AUTO,
                UNSET
            };

            JsonThreeState(JsonThreeState::ThreeState v) : v(v) {
            }

            std::string getJsonString() const {
                switch(this->v) {
                    case ON:
                        return "\"ON\"";

                    case OFF:
                        return "\"OFF\"";

                    case AUTO:
                        return "\"AUTO\"";

                    case UNSET:
                        return "\"UNSET\"";
                }
            }

            ThreeState getVal() {
                return this->v;
            }

        protected:
            ThreeState v;

    };

    typedef boost::shared_ptr<JsonThreeState> JsonThreeStatePtr;

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

    typedef boost::shared_ptr<JsonString>         JsonStringPtr;

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

    typedef boost::shared_ptr<JsonNumber<int> >   JsonIntPtr;
    typedef boost::shared_ptr<JsonNumber<float> > JsonFloatPtr;

    inline JsonBoolPtr toJsonBoolPtr(bool v) {
        return JsonBoolPtr(new JsonBool(v));
    }

    inline JsonStringPtr toJsonStringPtr(const std::string &v) {
        return JsonStringPtr(new JsonString(v));
    }

    inline JsonSwitchPtr toJsonSwitchPtr(JsonSwitch::Switch v) {
        return JsonSwitchPtr(new JsonSwitch(v));
    }

    inline JsonToggleStatePtr toJsonToggleStatePtr(JsonToggleState::ToggleState v) {
        return JsonToggleStatePtr(new JsonToggleState(v));
    }

    inline JsonThreeStatePtr toJsonThreeStatePtr(JsonThreeState::ThreeState v) {
        return JsonThreeStatePtr(new JsonThreeState(v));
    }

    inline JsonNULLPtr toJsonNULLPtr() {
        return JsonNULLPtr(new JsonNULL());
    }

    template <typename T>
    inline boost::shared_ptr<JsonNumber<T> > toJsonNumberPtr(T v) {
        return boost::shared_ptr<JsonNumber<T> >(new JsonNumber<T>(v));
    }

    inline int castToInt(JsonItemPtr ptr) {
        return boost::dynamic_pointer_cast<JsonNumber<int> >(ptr)->getVal();
    }

    inline float castToFloat(JsonItemPtr ptr) {
        return boost::dynamic_pointer_cast<JsonNumber<float> >(ptr)->getVal();
    }

    inline std::string castToString(JsonItemPtr ptr) {
        return *boost::dynamic_pointer_cast<std::string>(ptr);
    }

    inline bool castToBool(JsonItemPtr ptr) {
        return boost::dynamic_pointer_cast<JsonBool>(ptr)->getVal();
    }

    inline JsonSwitch::Switch castToSwitch(JsonItemPtr ptr) {
        return boost::dynamic_pointer_cast<JsonSwitch>(ptr)->getVal();
    }

    inline JsonToggleState::ToggleState castToToggleState(JsonItemPtr ptr) {
        return boost::dynamic_pointer_cast<JsonToggleState>(ptr)->getVal();
    }

    inline JsonThreeState::ThreeState castToThreeState(JsonItemPtr ptr) {
        return boost::dynamic_pointer_cast<JsonThreeState>(ptr)->getVal();
    }
}
