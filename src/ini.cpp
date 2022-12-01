/*
 *  Project:    moba-common
 *
 *  Copyright (C) 2019 Stefan Paproth <pappi-@gmx.de>
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

#include <ini.h>
#include "exception.h"

// for further information have a look at https://docs.gtk.org/glib/struct.KeyFile.html

Ini::Ini(const std::string &fileName) {
    GError *error = nullptr;

    keyFile = g_key_file_new();

    if(!g_key_file_load_from_file(keyFile, fileName.c_str(), static_cast<GKeyFileFlags>(G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS), &error)) {
        throw moba::UnsupportedOperationException{error->message};
    }
}

Ini::~Ini() {
    //g_key_file_save_to_file(key_file, "test2.ini", &error);
    g_key_file_free(keyFile);
}

std::string Ini::getString(const std::string &group, const std::string &key, const std::string &def) {
    GError *error = nullptr;

    if(!g_key_file_has_key(keyFile, group.c_str(), key.c_str(), nullptr)) {
        return def;
    }

    gchar *tmp;
    tmp = g_key_file_get_string(keyFile, group.c_str(), key.c_str(), &error);
    if(tmp == nullptr && error != nullptr) {
        throw moba::UnsupportedOperationException{error->message};
    }
    std::string value{tmp};
    g_free(tmp);
    return value;
}

int Ini::getInt(const std::string &group, const std::string &key, int def) {
    GError *error = nullptr;

    if(!g_key_file_has_key(keyFile, group.c_str(), key.c_str(), nullptr)) {
        return def;
    }

    auto val = g_key_file_get_integer(keyFile, group.c_str(), key.c_str(), &error);
    if(error != nullptr) {
        throw moba::UnsupportedOperationException{error->message};
    }
    return val;
}
