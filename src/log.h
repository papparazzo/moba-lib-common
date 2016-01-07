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

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <sys/timeb.h>

#define LOG(loglevel) static_cast<std::ostream&>(tlog::CLog::theLogger()(__FILE__, __LINE__, (loglevel)))

namespace tlog {
    enum enuLogLevel {
        Emerg   = 1,
        Alert   = 2,
        Error   = 3,
        Warning = 4,
        Info    = 5,
        Notice  = 6,                  
    };

    class CLog;
    class CLogEntry {
        friend class CLog;

        private:
            CLogEntry(
                CLog & log,
                const char* szFile,
                int iLine,
                tlog::enuLogLevel logLevel
            ) : log_(log), szFile_(szFile), iLine_(iLine), logLevel_(logLevel) {
            }

            CLogEntry(
                const CLogEntry& le
            ) : log_(le.log_), szFile_(le.szFile_), iLine_(le.iLine_), logLevel_(le.logLevel_) {
            }

        public:
            virtual ~CLogEntry();

            operator std::ostream&() {
                return buffer;
            }

        private:
            CLog& log_;
            const char* szFile_;
            int iLine_;
            tlog::enuLogLevel logLevel_;
            std::ostringstream buffer;
    };

    class CLog {
        private:
            CLog() {}                   // Konstruktor
            CLog(const CLog&);          // Copy-Konstruktor

        public:
            static CLog& theLogger();

            CLogEntry operator()(
                const char* szFile, int iLine, tlog::enuLogLevel logLevel
            ) {
                return CLogEntry(*this, szFile, iLine, logLevel);
            }

            void write(
                const std::string &strLogText,
                const char* szFile,
                const int &iLine,
                const enuLogLevel &logLevel
            );
    };
} // namespace tlog

#endif // _LOGGER_H_



