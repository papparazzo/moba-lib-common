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

#pragma once

#include <glib.h>
#include <string>
#include <memory>

namespace moba {

    class Ini {
    public:
        Ini(const std::string &fileName);
        virtual ~Ini() noexcept;

        void reopen();

        std::string getString(const std::string &group, const std::string &key, const std::string &def = "");
        int getInt(const std::string &group, const std::string &key, int def);

        void setString(const std::string &group, const std::string &key, const std::string &value);
        void setInt(const std::string &group, const std::string &key, int value);

    protected:
        GKeyFile *keyFile;
        std::string fileName;
    };

    using IniPtr = std::shared_ptr<Ini>;
}
