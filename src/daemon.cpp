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

#include <daemon.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>

namespace moba {
    Daemon::Daemon(const std::string &appName):
    pidFileName{"/run/" + appName + ".pid"}, appName{appName} {
        openlog(appName.c_str(), LOG_PID | LOG_CONS | LOG_NDELAY, LOG_DAEMON);
        syslog(LOG_INFO, "<%s> started", appName.c_str());
    }

    Daemon::~Daemon() {
        if(pidFd != -1) {
            close(pidFd);
        }

        unlink(pidFileName.c_str());

        signal(SIGINT, SIG_DFL);

        syslog(LOG_INFO, "<%s> stopped", appName.c_str());
        closelog();
    }

    void Daemon::daemonize() {
        if(geteuid() != 0) {
            std::cerr <<
                "This daemon can only be run by root user, exiting" <<
                std::endl;
            
            exit(EXIT_FAILURE);
        }

        signal(SIGHUP, SIG_IGN); // no configs to read at this time

        if(chdir("/")) {
            std::cerr << "unable to change dir /" << std::endl;
            exit(EXIT_FAILURE);
        }
        umask(0);

        pidFd = open(pidFileName.c_str(), O_RDWR|O_CREAT, 0640);

        if(pidFd < 0) {
            std::cerr << 
                "unable to open file <" << pidFileName << "> for locking" << 
                std::endl;
            
            exit(EXIT_FAILURE);
        }

        if(lockf(pidFd, F_TLOCK, 0) < 0) {
            std::cerr << 
                "unable to lock file <" << pidFileName << ">" << std::endl;
            
            exit(EXIT_FAILURE);
        }

        auto spid = std::to_string(getpid());

        if(write(pidFd, spid.c_str(), spid.length()) <= 0) {
            std::cerr <<
                "unable to write in file <" << pidFileName << ">" << std::endl;
            
            exit(EXIT_FAILURE);
        }
    }
}