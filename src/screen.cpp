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

#include "screen.h"
#include <curses.h>
#include <iostream>

namespace moba {

Screen::Screen(const std::string &title, const bool debug): debug{debug} {
    if(debug) {
        return;
    }
    init(title);
}

Screen::~Screen() {
    if(debug) {
        return;
    }
    endwin();
}

void Screen::init(const std::string &title) {
    auto win = initscr();
    use_default_colors();
    curs_set(0);
    noecho();

    width = static_cast<unsigned int>(getmaxx(win));
    height = static_cast<unsigned int>(getmaxy(win));

    addch(ACS_ULCORNER);
    addch(ACS_HLINE);
    addch(' ');
    attron(A_BOLD);
    addstr(title.c_str());
    attroff(A_BOLD);
    addch(' ');
    for(unsigned int i = 1; i < width - title.length() - 5; ++i) {
        addch(ACS_HLINE);
    }

    move(0, width - 6);
    addch(ACS_HLINE);
    addch(' ');
    addch('x');
    addch(' ');
    addch(ACS_HLINE);
    addch(ACS_URCORNER);

    for(unsigned int i = 1; i < height - 1; ++i) {
        move(i, 0);
        addch(ACS_VLINE);
        move(i, width - 1);
        addch(ACS_VLINE);
    }

    move(height - 1, 0);
    addch(ACS_LLCORNER);
    addch(ACS_HLINE);

    std::string t = std::string("x: ") + std::to_string(width) + ", y: " + std::to_string(height) ;
    for(unsigned int i = 1; i < width - t.length() - 6; ++i) {
        addch(ACS_HLINE);
    }
    addch(ACS_HLINE);
    addch(' ');
    addstr(t.c_str());
    addch(' ');
    addch(ACS_HLINE);
    addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    refresh();
}

void Screen::mvprintw(int y, int x, const std::string &txt) const {
    if(debug) {
        std::cerr << txt << std::endl;
        return;
    }
    ::mvprintw(y, x, "%s", txt.c_str());
}

void Screen::mvprintw(int y, int x, const char *format, ...) const {
    va_list args;
    va_start(args, format);
    if(debug) {
        printf(format, args);
    } else {
        ::mvprintw(y, x, format, args);
    }
    va_end(args);
}

void Screen::refresh() const {
    if(!debug) {
        ::refresh();
    }
}

void Screen::printException(const std::string &where, const std::string &what) const {
    std::string txt = std::string("Exception in <") + what + "> in <" + where + "> occurred!";

    if(debug) {
        std::cerr << txt << std::endl;
        return;
    }

    attron(A_BLINK);
    ::mvprintw(2, 4, "%s", txt.c_str());
    attroff(A_BLINK);
    ::refresh();
}

void Screen::printStatus(const std::string &txt, bool blink) const {
    if(debug) {
        std::cerr << "Status: " << txt << std::endl;
        return;
    }

    move(height - 1, 2);

    attron(A_BOLD);
    addstr(" Status: ");
    attroff(A_BOLD);

    blink && attron(A_BLINK);
    addstr(txt.c_str());
    addch(' ');
    blink && attroff(A_BLINK);
    addch(ACS_HLINE);

    for(unsigned int i = 0; i < 25 - txt.length(); ++i) {
        addch(ACS_HLINE);
    }
    ::refresh();
}
}
