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

#include <pthread.h>

namespace moba {
    template <typename T> class Atomic {
        public:
            Atomic() {
                pthread_mutex_init(&this->m, NULL);
            }

            Atomic(const T& s) {
                pthread_mutex_init(&this->m, NULL);
                this->v = s;
            }

            Atomic& operator = (const T& s) {
                pthread_mutex_lock(&this->m);
                this->v = s;
                pthread_mutex_unlock(&this->m);
                return *this;
            }

            ~Atomic() {
                pthread_mutex_destroy(&this->m);
            }

            operator T() {
                T t;
                pthread_mutex_lock(&this->m);
                t = this->v;
                pthread_mutex_unlock(&this->m);
                return t;
            }

            Atomic<T>& operator++() {
                pthread_mutex_lock(&this->m);
                ++this->v;
                pthread_mutex_unlock(&this->m);
                return *this;
            }

            Atomic<T>& operator--() {
                pthread_mutex_lock(&this->m);
                --this->v;
                pthread_mutex_unlock(&this->m);
                return *this;
            }

            Atomic<T>& operator++(int) {
                Atomic<T> t = *this;
                ++*this;
                return t;
            }

            Atomic<T>& operator--(int) {
                Atomic<T> t = *this;
                --*this;
                return t;
            }
        protected:
            T v;
            pthread_mutex_t m;
    };
}