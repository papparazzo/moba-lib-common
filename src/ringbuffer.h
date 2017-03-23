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

#pragma once

#include <exception>
#include <string>
#include <cstddef>

namespace moba {

    class RingbufferException : public std::exception {

        public:
            virtual ~RingbufferException() throw() {

            }

            RingbufferException(const std::string &what) {
                this->what__ = what;
            }

            virtual const char* what() const throw() {
                return this->what__.c_str();
            }

        private:
            std::string what__;
    };

    template <typename T> class Ringbuffer {
        public:
            static const std::size_t BUFFER_SIZE = 1024;

            std::size_t size;
            std::size_t ptrW;
            std::size_t ptrR;

            bool isFull;

            T *items;

            explicit Ringbuffer(std::size_t size = Ringbuffer::BUFFER_SIZE) :
            size(size), ptrW(0), ptrR(0), isFull(false) {
                this->items = new T[this->size];
            }

            virtual ~Ringbuffer() {
                delete[] this->items;
            }

            void reset(std::size_t newSize = 0) {
                delete[] this->items;
                if(newSize > 0) {
                    this->size = newSize;
                }
                this->items = new T[this->size];
                this->ptrW = 0;
                this->ptrR = 0;
            }

            void push(const T item) {
                if(this->isFull) {
                    throw RingbufferException("Ring-buffer is full");
                }

                this->items[this->ptrW] = item;
                this->ptrW = ++this->ptrW % this->size;
                if(this->ptrR == this->ptrW) {
                    this->isFull = true;
                }
            }

            T peek() {
                if(this->ptrR == this->ptrW && !this->isFull) {
                    throw RingbufferException("Ring-buffer is empty");
                }
                return this->items[this->ptrR];
            }

            T pop() {
                T tmp = this->peek();
                this->ptrR = ++this->ptrR % this->size;
                this->isFull = false;
                return tmp;
            }

            bool full() {
                this->isFull;
            }

            std::size_t getBufferSize() {
                return this->size;
            }

            std::size_t getItemsCount() {
                if(this->isFull) {
                    return this->size;
                }
                if(this->ptrR == this->ptrW) {
                    return 0;
                }
                if(this->ptrR < this->ptrW) {
                    return this->ptrW - this->ptrR;
                }
                return this->size - this->ptrR + this->ptrW;
            }
    };
}
