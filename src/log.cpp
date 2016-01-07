/*
 *  Project:    CommonLib
 *
 *  Version:    1.0.0
 *  History:    V1.0    07/12/2013  SP - created
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
#include "log.h"

/*
#define DEFAULT                  "\e[39m"
#define BLACK                    "\e[30m"
#define RED                      "\e[31m"
#define GREEN                    "\e[32m"
#define YELLOW                   "\e[33m"
#define BLUE                     "\e[34m"
#define MAGENTA                  "\e[35m"
#define CYAN                     "\e[36m"
#define LIGHT_GRAY               "\e[37m"
#define DARK_GRAY                "\e[90m"
#define LIGHT_RED                "\e[91m"
#define LIGHT_GREEN              "\e[92m"
#define LIGHT_YELLOW             "\e[93m"
#define LIGHT_BLUE               "\e[94m"
#define LIGHT_MAGENTA            "\e[95m"
#define LIGHT_CYAN               "\e[96m"
#define WHITE                    "\e[97m"

#define BOLD_BRIGHT "\e[1m"
#define DIM         "\e[2m"
#define UNDERLINED  "\e[4m"
#define BLINK       "\e[5m"
#define REVERSE     "\e[7m"
#define HIDDEN      "\e[8m"

#define RESET_ALL        "\e[0m"
#define RESET_BOLD       "\e[21m"
#define RESET_DIM        "\e[22m"
#define RESET_UNDERLINDE "\e[24m"
#define RESET_BLINK      "\e[25m"
#define RESET_REVERSE    "\e[27m"
#define RESET_HIDDEN     "\e[28m"
*/

namespace tlog {
    CLogEntry::~CLogEntry() {
        log_.write(buffer.str(), this->szFile_, this->iLine_, this->logLevel_ );
    }

    CLog& CLog::theLogger() {
        static CLog instance;
        return instance;
    }

    void CLog::write(
        const std::string &strLogText, const char *szFile,
        const int &iLine, const enuLogLevel &logLevel
    ) {
        struct timeb sTimeB;
        char buffer[25] = "";

        ftime(&sTimeB);

        strftime(buffer, 21, "%d.%m.%Y %H:%M:%S.", localtime(&sTimeB.time));

        std::cerr <<
            buffer << std::setw(3) << std::setfill('0') << sTimeB.millitm <<
            " " << std::setw(12) << std::setfill(' ') << szFile <<
            ":" << std::setw(4) << std::setfill('0') << iLine;

        switch(logLevel) {
            case Emerg:
                std::cerr << " Emerg.:  ";
                break;

            case Alert:
                std::cerr << " Alert:   ";
                break;

            case Error:
                std::cerr << " Error:   ";
                break;

            case Warning:
                std::cerr << " Warning: ";
                break;

            case Info:
                std::cerr << " Info:    ";
                break;

            case Notice:
                std::cerr << " Debug:   ";
                break;
        }
        std::cerr << strLogText << std::endl;
    }
}
