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

#include "stopwatch.h"

StopWatch::StopWatch() : counter(0){
}

StopWatch::~StopWatch() {

}

StopWatch::start() {
    ++counter;
}

StopWatch::reset() {
    counter = 0;
}

StopWatch::lap() {
/*
   gettimeofday(&t1, NULL);
  gettimeofday(&t2, NULL);

  elapsedTime += ((t2.tv_sec * 1000000) + t2.tv_usec)
              - ((t1.tv_sec * 1000000) + t1.tv_usec);

            LOG(moba::WARNING) << "finish " << (elapsedTime / 40950) << " -- " <<  (elapsedTime2 / 40950) << std::endl;

 */
}

