# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# Copyright (C) 2006-2010 RobotCub Consortium
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

cmake_minimum_required(VERSION 3.5)

find_package(YARP COMPONENTS OS name math REQUIRED)

add_executable(yarpwide main.cpp)
target_link_libraries(yarpwide YARP::YARP_OS
                               YARP::YARP_init
                               YARP::YARP_name
                               YARP::YARP_math)
