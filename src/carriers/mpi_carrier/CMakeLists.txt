# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# Copyright (C) 2006-2010 RobotCub Consortium
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

include(CMakeDependentOption)
cmake_dependent_option(MPI_DEBUG_MSG "Turn on status messages for MPI Carrier" OFF
                       "NOT SKIP_mpi OR NOT SKIP_mpibcast" OFF)
if(MPI_DEBUG_MSG)
  add_definitions(-DMPI_DEBUG)
endif(MPI_DEBUG_MSG)


yarp_prepare_plugin(mpi
                    CATEGORY carrier
                    TYPE MpiP2PCarrier
                    INCLUDE MpiP2PCarrier.h
                    EXTRA_CONFIG CODE="MPI_____"
                    DEPENDS "YARP_HAS_MPI")

if(NOT SKIP_mpi)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  yarp_add_plugin(yarp_mpi MpiCarrier.cpp
                           MpiComm.cpp
                           MpiStream.cpp
                           MpiP2PStream.cpp
                           MpiCarrier.h
                           MpiP2PCarrier.h
                           MpiStream.h
                           MpiP2PStream.h
                           MpiComm.h)

  target_link_libraries(yarp_mpi PRIVATE YARP::YARP_OS)
  list(APPEND YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS YARP_OS)

  target_include_directories(yarp_mpi SYSTEM PRIVATE ${MPI_INCLUDE_PATH})
  target_link_libraries(yarp_mpi PRIVATE ${MPI_LIBRARIES})
#   list(APPEND YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS MPI) (not using targets)

  yarp_install(TARGETS yarp_mpi
               EXPORT YARP_${YARP_PLUGIN_MASTER}
               COMPONENT ${YARP_PLUGIN_MASTER}
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
               YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

  set(YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS ${YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS} PARENT_SCOPE)

  set_property(TARGET yarp_mpi PROPERTY FOLDER "Plugins/Carrier")
endif()


yarp_prepare_plugin(mpibcast
                    CATEGORY carrier
                    TYPE MpiBcastCarrier
                    INCLUDE MpiBcastCarrier.h
                    EXTRA_CONFIG CODE="MPIBCAST"
                    DEPENDS "YARP_HAS_MPI")

if(NOT SKIP_mpibcast)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  yarp_add_plugin(yarp_mpibcast MpiCarrier.cpp
                                MpiBcastCarrier.cpp
                                MpiComm.cpp
                                MpiStream.cpp
                                MpiBcastStream.cpp
                                MpiCarrier.h
                                MpiBcastCarrier.h
                                MpiStream.h
                                MpiBcastStream.h
                                MpiComm.h)

  target_link_libraries(yarp_mpibcast PRIVATE YARP::YARP_OS)
  list(APPEND YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS YARP_OS)

  target_include_directories(yarp_mpibcast SYSTEM PRIVATE ${MPI_INCLUDE_PATH})
  target_link_libraries(yarp_mpibcast PRIVATE ${MPI_LIBRARIES})
#   list(APPEND YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS MPI) (not using targets)

  yarp_install(TARGETS yarp_mpibcast
               COMPONENT ${YARP_PLUGIN_MASTER}
               EXPORT YARP_${YARP_PLUGIN_MASTER}
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
               YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

  set(YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS ${YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS} PARENT_SCOPE)

  set_property(TARGET yarp_mpibcast PROPERTY FOLDER "Plugins/Carrier")

endif()
