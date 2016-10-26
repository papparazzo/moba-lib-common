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

#include "signalhandler.h"
#include "helper.h"

namespace {
    const int MAX_SIG = 31;
    int sigmap[MAX_SIG] = {
        -1, -1, -1, -1,
        -1, -1, -1, -1,
        -1, -1, -1, -1,
        -1, -1, -1, -1,

        -1, -1, -1, -1,
        -1, -1, -1, -1,
        -1, -1, -1, -1,
        -1, -1, -1
    };

    void signalCallBack(int sig) {
        sigmap[sig] = 1;
    }
}

namespace moba {
    SignalHandler::SignalHandler(int signr) {
        if(signr < 1 || signr > MAX_SIG) {
            throw SignalHandlerException("signr out of range");
        }

        if(sigmap[signr] != -1) {
            throw SignalHandlerException("signr allready in use");
        }

        struct sigaction handler;

        handler.sa_handler = &signalCallBack;
        sigemptyset(&handler.sa_mask);
        handler.sa_flags = SA_RESTART;

        if(sigaction(signr, &handler, NULL) < 0) {
            throw SignalHandlerException(getErrno("sigaction failed"));
        }
        this->signr = signr;
        sigmap[this->signr] = 0;
    }

    SignalHandler::~SignalHandler() {
        struct sigaction handler;

        handler.sa_handler = SIG_DFL;
        sigemptyset(&handler.sa_mask);
        handler.sa_flags = SA_RESTART;

        sigaction(this->signr, &handler, NULL);
        sigmap[this->signr] = -1;
    }

    void SignalHandler::resetSignalState() {
        this->lockSignal();
        sigmap[this->signr] = 0;
        this->unlockSignal();

    }

    bool SignalHandler::hasSignalTriggered() {
        this->lockSignal();
        bool retVal = (bool)sigmap[this->signr];
        this->unlockSignal();
        return retVal;
    }

    void SignalHandler::lockSignal() {
        sigset_t lockMask;
        sigemptyset(&lockMask);
        sigaddset(&lockMask, this->signr);
        sigprocmask(SIG_BLOCK, &lockMask, NULL);
    }

    void SignalHandler::unlockSignal() {
        sigset_t lockMask;
        sigemptyset(&lockMask);
        sigaddset(&lockMask, signr);
        sigprocmask(SIG_UNBLOCK, &lockMask, NULL);
    }
}
