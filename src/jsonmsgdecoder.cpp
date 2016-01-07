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

#include "jsonmsgdecoder.h"

MessagePtr JsonMsgDecoder::decodeMsg() {

    this->checkNext('{');
    this->checkNext('"');
    std::string key = this->nextKey();

    if(key != Message::MSG_HEADER) {
        throw JsonException("invalid msg-header!");
    }

    this->checkNext(':');
    this->checkNext('"');

    std::string msgkey = this->nextKey();

    this->checkNext(',');
    this->checkNext('"');
    key = this->nextKey();

    if(key != Message::DATA_HEADER) {
        throw JsonException("invalid data-header!");
    }

    this->checkNext(':');
    JsonItemPtr o = this->nextValue();
    this->checkNext('}');
    return MessagePtr(new Message(Message::convertToMsgType(msgkey), o));
}
