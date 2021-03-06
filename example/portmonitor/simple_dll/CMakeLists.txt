# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

cmake_minimum_required(VERSION 3.5)

find_package(YARP REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(YARP_FORCE_DYNAMIC_PLUGINS TRUE CACHE INTERNAL "yarp_pm_simple is always built with dynamic plugins")
# Warning: the <package> option of yarp_configure_plugins_installation should be different from the plugin name
yarp_configure_plugins_installation(simplemonitor_portmonitor)

yarp_prepare_plugin(simplemonitor TYPE SimpleMonitorObject
                                  INCLUDE Simple.h
                                  CATEGORY portmonitor)

yarp_add_plugin(yarp_pm_simple
                Simple.cpp
                Simple.h)
target_link_libraries(yarp_pm_simple ${YARP_LIBRARIES})
yarp_install(TARGETS yarp_pm_simple
             EXPORT yarp_pm_simple
             COMPONENT runtime
             LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
             ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
             YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})
