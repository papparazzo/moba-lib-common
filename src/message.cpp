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

#include "message.h"

namespace {

    struct __MsgEnumClearTextStruct {
        moba::Message::MessageType type;
        std::string msg;
    } __msgEnumClearTextStruct[] = {
        {moba::Message::MT_VOID,                    "VOID"                   },
        {moba::Message::MT_ECHO_REQ,                "ECHO_REQ"               },
        {moba::Message::MT_ECHO_RES,                "ECHO_RES"               },
        {moba::Message::MT_ERROR,                   "ERROR"                  },

        {moba::Message::MT_CLIENT_START,            "CLIENT_START"           },
        {moba::Message::MT_CLIENT_CONNECTED,        "CLIENT_CONNECTED"       },
        {moba::Message::MT_CLIENT_CLOSE,            "CLIENT_CLOSE"           },
        {moba::Message::MT_CLIENT_SHUTDOWN,         "CLIENT_SHUTDOWN"        },
        {moba::Message::MT_CLIENT_RESET,            "CLIENT_RESET"           },
        {moba::Message::MT_CLIENT_SELF_TESTING,     "CLIENT_SELF_TESTING"    },

        {moba::Message::MT_MAX_CLIENT_COUNT,        "MAX_CLIENT_COUNT"       },
        {moba::Message::MT_NEW_CLIENT_STARTED,      "NEW_CLIENT_STARTED"     },
        {moba::Message::MT_CLIENT_CLOSED,           "CLIENT_CLOSED"          },
        {moba::Message::MT_RESET_CLIENT,            "RESET_CLIENT"           },
        {moba::Message::MT_SELF_TESTING_CLIENT,     "SELF_TESTING_CLIENT"    },

        {moba::Message::MT_SERVER_INFO_REQ,         "SERVER_INFO_REQ"        },
        {moba::Message::MT_SERVER_INFO_RES,         "SERVER_INFO_RES"        },
        {moba::Message::MT_CON_CLIENTS_REQ,         "CON_CLIENTS_REQ"        },
        {moba::Message::MT_CON_CLIENTS_RES,         "CON_CLIENTS_RES"        },

        {moba::Message::MT_GLOBAL_TIMER_EVENT,      "GLOBAL_TIMER_EVENT"     },
        {moba::Message::MT_GET_GLOBAL_TIMER,        "GET_GLOBAL_TIMER"       },
        {moba::Message::MT_SET_GLOBAL_TIMER,        "SET_GLOBAL_TIMER"       },
        {moba::Message::MT_GET_ENVIRONMENT,         "GET_ENVIRONMENT"        },
        {moba::Message::MT_SET_ENVIRONMENT,         "SET_ENVIRONMENT"        },
        {moba::Message::MT_GET_AMBIENCE,            "GET_AMBIENCE"           },
        {moba::Message::MT_SET_AMBIENCE,            "SET_AMBIENCE"           },
        {moba::Message::MT_GET_AUTO_MODE,           "GET_AUTO_MODE"          },
        {moba::Message::MT_SET_AUTO_MODE,           "SET_AUTO_MODE"          },
        {moba::Message::MT_GET_COLOR_THEME,         "GET_COLOR_THEME"        },
        {moba::Message::MT_SET_COLOR_THEME,         "SET_COLOR_THEME"        },
        {moba::Message::MT_COLOR_THEME_EVENT,       "COLOR_THEME_EVENT"      },
        {moba::Message::MT_GET_AMBIENT_LIGHT,       "GET_AMBIENT_LIGHT"      },
        {moba::Message::MT_SET_AMBIENT_LIGHT,       "SET_AMBIENT_LIGHT"      },

        {moba::Message::MT_EMERGENCY_STOP,          "EMERGENCY_STOP"         },
        {moba::Message::MT_EMERGENCY_STOP_CLEARING, "EMERGENCY_STOP_CLEARING"},
        {moba::Message::MT_GET_HARDWARE_STATE,      "GET_HARDWARE_STATE"     },
        {moba::Message::MT_SET_HARDWARE_STATE,      "SET_HARDWARE_STATE"     },
        {moba::Message::MT_HARDWARE_STATE_CHANGED,  "HARDWARE_STATE_CHANGED" },
        {moba::Message::MT_HARDWARE_SHUTDOWN,       "HARDWARE_SHUTDOWN"      },
        {moba::Message::MT_HARDWARE_RESET,          "HARDWARE_RESET"         },
        {moba::Message::MT_HARDWARE_SWITCH_STANDBY, "HARDWARE_SWITCH_STANDBY"},

        {moba::Message::MT_SYSTEM_NOTICE,           "SYSTEM_NOTICE"          },

        {moba::Message::MT_GET_LAYOUTS_REQ,         "GET_LAYOUTS_REQ"        },
        {moba::Message::MT_GET_LAYOUTS_RES,         "GET_LAYOUTS_RES"        },

        {moba::Message::MT_DEL_LAYOUT,              "DEL_LAYOUT"             },
        {moba::Message::MT_LAYOUT_DELETED,          "LAYOUT_DELETED"         },

        {moba::Message::MT_CREATE_LAYOUT_REQ,       "CREATE_LAYOUT_REQ"      },
        {moba::Message::MT_CREATE_LAYOUT_RES,       "CREATE_LAYOUT_RES"      },
        {moba::Message::MT_LAYOUT_CREATED,          "LAYOUT_CREATED"         },

        {moba::Message::MT_UPDATE_LAYOUT,           "UPDATE_LAYOUT"          },
        {moba::Message::MT_LAYOUT_UPDATED,          "LAYOUT_UPDATED"         },

        {moba::Message::MT_UNLOCK_LAYOUT,           "UNLOCK_LAYOUT"          },
        {moba::Message::MT_LAYOUT_UNLOCKED,         "LAYOUT_UNLOCKED"        },

        {moba::Message::MT_GET_LAYOUT_REQ,          "GET_LAYOUT_REQ"         },
        {moba::Message::MT_GET_LAYOUT_RES,          "GET_LAYOUT_RES"         },

    };
}

namespace moba {

    const std::string Message::MSG_HEADER  = "msgType";
    const std::string Message::DATA_HEADER = "msgData";

    Message::Message(MessageType msgType) {
        this->msgType = msgType;
    }

    Message::Message(MessageType msgType, JsonItemPtr data) {
        this->msgType = msgType;
        this->data = data;
    }

    Message::~Message() {
    }

    Message::MessageType Message::convertToMsgType(const std::string &msgName) {
        int size =
            sizeof(__msgEnumClearTextStruct) / sizeof(__msgEnumClearTextStruct[0]);

        for(int i = 0; i < size; ++i) {
            if(msgName == __msgEnumClearTextStruct[i].msg) {
                return __msgEnumClearTextStruct[i].type;
            }
        }
        return MT_UNKNOWN;
    }

    JsonStringPtr Message::convertToString(Message::MessageType mt) {
        int size =
            sizeof(__msgEnumClearTextStruct) / sizeof(__msgEnumClearTextStruct[0]);

        for(int i = 0; i < size; ++i) {
            if(__msgEnumClearTextStruct[i].type == mt) {
                return JsonStringPtr(
                    new JsonString(__msgEnumClearTextStruct[i].msg)
                );
            }
        }

        return JsonStringPtr(new JsonString("UNKNOWN"));
    }

    std::string Message::getRawMessage() const {
        JsonObject obj;
        obj["msgType"] = Message::convertToString(this->msgType);
        obj["msgData"] = this->data;
        return obj.getJsonString();
    }

    std::string Message::msgTypeAsString() const {
        int size =
            sizeof(__msgEnumClearTextStruct) / sizeof(__msgEnumClearTextStruct[0]);

        for(int i = 0; i < size; ++i) {
            if(__msgEnumClearTextStruct[i].type == this->msgType) {
                return __msgEnumClearTextStruct[i].msg;
            }
        }
        return "UNKNOWN";
    }
}

