# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# Copyright (C) 2006-2010 RobotCub Consortium
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.


set(yarp_SRCS yarp.cpp)

add_executable(yarp ${yarp_SRCS})
target_link_libraries(yarp YARP::YARP_OS
                           YARP::YARP_init
                           YARP::YARP_serversql
                           YARP::YARP_run
                           YARP::YARP_companion)

install(TARGETS yarp
        COMPONENT utilities
        DESTINATION ${CMAKE_INSTALL_BINDIR})

set_property(TARGET yarp PROPERTY FOLDER "Command Line Tools")
