/**
 *  Project:    moba-common
 *
 *  Copyright (C) 2025 Stefan Paproth <pappi-@gmx.de>
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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include <string>

namespace moba {

class Screen final {
public:
    explicit Screen(const std::string &title, bool debug = false);
    ~Screen();

    void mvprintw(int y, int x, const char *format, ...) const;
    void mvprintw(int y, int x, const std::string &txt) const;

    void refresh() const;

    void printException(const std::string &where, const std::string &what) const;
    void printStatus(const std::string &txt, bool blink) const;

    template<class T>
    void printBuffer(int y, int x, const T &buffer) {
        for (auto str: buffer) {
            mvprintw(y++, x, str);
        }
        refresh();
    }

private:
    bool debug;
    unsigned int width;
    unsigned int height;

    void init(const std::string &title);
};

} // moba

