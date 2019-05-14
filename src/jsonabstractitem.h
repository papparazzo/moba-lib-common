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
#include <map>
#include <vector>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <memory>

#include "exception.h"

namespace moba {
    class JsonAbstractItem {

        public:
            virtual ~JsonAbstractItem() {};
            virtual std::string getJsonString() const = 0;
    };

    using JsonItemPtr = std::shared_ptr<JsonAbstractItem>;

    class JsonArray : public JsonAbstractItem, public std::vector<JsonItemPtr> {

        public:
            std::string getJsonString() const {
                std::stringstream ss;
                ss << '[';
                for(JsonArray::const_iterator iter = this->begin(); iter != this->end(); ++iter) {
                    if(iter != this->begin()) {
                        ss << ',';
                    }
                    ss << (*iter)->getJsonString();
                }
                ss << ']';
                return ss.str();
            }
    };

    using JsonArrayPtr = std::shared_ptr<JsonArray>;

    class JsonObject : public JsonAbstractItem, public std::map<std::string, JsonItemPtr> {

        public:
            std::string getJsonString() const {
                std::stringstream ss;
                ss << '{';
                for(JsonObject::const_iterator iter = this->begin(); iter != this->end(); ++iter) {
                    if(iter != this->begin()) {
                        ss << ',';
                    }
                    ss << '"' << iter->first << "\":" << iter->second->getJsonString();
                }
                ss << '}';
                return ss.str();
            }
    };

    typedef std::shared_ptr<JsonObject> JsonObjectPtr;

    class JsonBool : public JsonAbstractItem {

        public:
            JsonBool(bool v) : v(v) {
            }

            JsonBool(const JsonBool &v) : v(v.v) {
            }

            operator bool() const {
                return this->v;
            }

            std::string getJsonString() const override {
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

    using JsonBoolPtr = std::shared_ptr<JsonBool>;

    class JsonNULL : public JsonAbstractItem {

        public:
            operator bool() const {
                return false;
            }

            std::string getJsonString() const override {
                return "null";
            };
    };

    using JsonNULLPtr = std::shared_ptr<JsonNULL>;

    class JsonString : public JsonAbstractItem, public std::string {

        public:
            JsonString(const std::string &v) : std::string(v) {
            }

            std::string getJsonString() const override {
                std::stringstream ss;
                ss << '"';
                for(std::size_t i = 0; i < this->length(); ++i) {
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

    using JsonStringPtr = std::shared_ptr<JsonString>;

    class JsonSwitch : public JsonAbstractItem {

        public:
            enum Switch {
                ON,
                AUTO,
                UNSET,
                TRIGGER,
                OFF
            };

            JsonSwitch(JsonStringPtr s) {
                if(*s == "ON") {
                    v = ON;
                } else if(*s == "AUTO") {
                    v = AUTO;
                } else if(*s == "UNSET") {
                    v = UNSET;
                } else if(*s == "TRIGGER") {
                    v = TRIGGER;
                } else if(*s == "OFF") {
                    v = OFF;
                }
            }

            JsonSwitch(JsonSwitch::Switch v) : v(v) {
            }

            std::string getJsonString() const override {
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

                    default:
                        throw UnsupportedOperationException("IPC::Command is invalid");
                }
            }

            Switch getVal() {
                return this->v;
            }

        protected:
            Switch v;
    };

    using JsonSwitchPtr = std::shared_ptr<JsonSwitch>;

    class JsonToggleState : public JsonAbstractItem {

        public:
            enum ToggleState {
                ON,
                OFF,
                UNSET
            };

            JsonToggleState(JsonStringPtr s) {
                if(*s == "ON") {
                    v = ON;
                } else if(*s == "UNSET") {
                    v = UNSET;
                } else if(*s == "OFF") {
                    v = OFF;
                }
            }

            JsonToggleState(JsonToggleState::ToggleState v) : v(v) {
            }

            std::string getJsonString() const override {
                switch(this->v) {
                    case ON:
                        return "\"ON\"";

                    case OFF:
                        return "\"OFF\"";

                    case UNSET:
                        return "\"UNSET\"";

                    default:
                        throw UnsupportedOperationException("IPC::Command is invalid");
                }
            }

            ToggleState getVal() {
                return this->v;
            }

        protected:
            ToggleState v;
    };

    using JsonToggleStatePtr = std::shared_ptr<JsonToggleState>;

    class JsonThreeState : public JsonAbstractItem {

        public:
            enum ThreeState {
                ON,
                OFF,
                AUTO,
                UNSET
            };

            JsonThreeState(JsonStringPtr s) {
                if(*s == "ON") {
                    v = ON;
                } else if(*s == "OFF") {
                    v = OFF;
                } else if(*s == "AUTO") {
                    v = AUTO;
                } else if(*s == "UNSET") {
                    v = UNSET;
                }
            }

            JsonThreeState(JsonThreeState::ThreeState v) : v(v) {
            }

            std::string getJsonString() const override {
                switch(this->v) {
                    case ON:
                        return "\"ON\"";

                    case OFF:
                        return "\"OFF\"";

                    case AUTO:
                        return "\"AUTO\"";

                    case UNSET:
                        return "\"UNSET\"";

                    default:
                        throw UnsupportedOperationException("IPC::Command is invalid");
                }
            }

            ThreeState getVal() {
                return this->v;
            }

        protected:
            ThreeState v;

    };

    using JsonThreeStatePtr = std::shared_ptr<JsonThreeState>;

    template <typename T> class JsonNumber : public JsonAbstractItem {

        public:
            JsonNumber(T v) : v(v) {
            }

            JsonNumber(const JsonNumber &v) : v(v.v) {
            }
            virtual ~JsonNumber() {};

            std::string getJsonString() const override {
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

    using JsonIntPtr = std::shared_ptr<JsonNumber<long int>>;
    using JsonFloatPtr = std::shared_ptr<JsonNumber<float>>;

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
    inline std::shared_ptr<JsonNumber<T> > toJsonNumberPtr(T v) {
        return std::shared_ptr<JsonNumber<T>>(new JsonNumber<T>(v));
    }

    inline int castToInt(JsonItemPtr ptr) {
        return std::dynamic_pointer_cast<JsonNumber<long int>>(ptr)->getVal();
    }

    inline float castToFloat(JsonItemPtr ptr) {
        return std::dynamic_pointer_cast<JsonNumber<float>>(ptr)->getVal();
    }

    inline std::string castToString(JsonItemPtr ptr) {
        return *std::dynamic_pointer_cast<std::string>(ptr);
    }

    inline bool castToBool(JsonItemPtr ptr) {
        return std::dynamic_pointer_cast<JsonBool>(ptr)->getVal();
    }

    inline JsonSwitch::Switch castToSwitch(JsonItemPtr ptr) {
        return JsonSwitch(std::dynamic_pointer_cast<JsonString>(ptr)).getVal();
    }

    inline JsonToggleState::ToggleState castToToggleState(JsonItemPtr ptr) {
        return JsonToggleState(std::dynamic_pointer_cast<JsonString>(ptr)).getVal();
    }

    inline JsonThreeState::ThreeState castToThreeState(JsonItemPtr ptr) {
        return JsonThreeState(std::dynamic_pointer_cast<JsonString>(ptr)).getVal();
    }

    inline void prettyPrint(JsonItemPtr ptr, std::ostream &out) {

        if(!ptr) {
            out << "{}";
            return;
        }

        std::string str = ptr->getJsonString();
        unsigned int indent = 0;

        for(size_t i = 0; i < str.length(); ++i) {
            switch(str[i]) {
                case '{':
                case '[':
                    out << str[i] << std::endl << std::setw(++indent * 4);
                    break;

                case ',':
                    out << str[i] << std::endl << std::setw(indent * 4);
                    break;

                case '}':
                case ']':
                    out << std::endl << std::setw(--indent * 4) << str[i];
                    break;

                default:
                    out << str[i];
            }
        }
        out << std::endl;
        return;
    }
}
