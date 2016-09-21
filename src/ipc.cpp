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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <cerrno>
#include <cstdio>
#include <cstring>

#include "helper.h"
#include "ipc.h"

namespace moba {

    IPC::IPC(IPC_TYPE type, const std::string &ffile) : type(type), ffile(ffile) {
        sigignore(SIGPIPE);
        this->init();
    }

    IPC::~IPC() {
        this->terminate();
    }

    void IPC::reset() {
        this->terminate();
        this->init();
    }

    void IPC::init() {
        struct stat attribut;

        if(
            stat(this->ffile.c_str(), &attribut) == 0 &&
            S_ISFIFO(attribut.st_mode) == 0 &&
            unlink(this->ffile.c_str()) == -1
        ) {
            throw IPCException(getErrno("unlink failed"));
        }

        if(mkfifo(this->ffile.c_str(), S_IRUSR | S_IWUSR) == -1 && errno != EEXIST) {
            throw IPCException(getErrno("Unable to create FIFO"));
        }

        this->stream = fopen(this->ffile.c_str(), "w+");
        if(this->stream == NULL) {
            throw IPCException(getErrno("Unable to open FIFO"));
        }
        int fd = fileno(this->stream);
        fcntl(fd, F_SETFD, fcntl(fd, F_GETFD, 0) | FD_CLOEXEC);
    }

    void IPC::terminate() {
        if(this->stream == NULL) {
            return;
        }
        fclose(this->stream);
        this->stream = NULL;
    }

    void IPC::writeLine(const std::string &data) {
        if(this->type == READING) {
            throw IPCException("type is set to reading");
        }
        std::string line = data + "\n";
        size_t l = line.length();
        if(fwrite(line.c_str(), 1, l, this->stream) != l) {
            throw IPCException(getErrno("writing failed"));
        }
    }

    void IPC::readLine(std::string &data) {
        if(this->type == WRITING) {
            throw IPCException("type is set to writing");
        }

        char buffer[IPC::BUFFER_SIZE];

        if(fgets(buffer, IPC::BUFFER_SIZE, this->stream) != NULL) {
            data = std::string(buffer);
            return;
        }
        if(feof(this->stream)) {
            throw IPCException("end-of-file reached.");
        }
        throw IPCException(getErrno("could not read"));
    }
}

