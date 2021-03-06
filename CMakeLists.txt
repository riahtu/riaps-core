cmake_minimum_required(VERSION 3.0.0)
project(riaps_core VERSION 1.1.18)
option(arch "amd64/armhf/arm64" "amd64")
option(BUILD_TESTS  "Build tests" ON)
set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wno-psabi")

set(PYBIND11_CPP_STANDARD -std=c++14)

#Set the platform
if (${arch} STREQUAL "armhf")
 set(TOOLCHAIN_NAME arm-linux-gnueabihf)
 set(TOOLCHAIN_PREFIX /usr/bin/${TOOLCHAIN_NAME})
 set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
 set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++-7)
 set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX})
 set (CMAKE_C_FLAGS "-std=c99")
elseif(${arch} STREQUAL "arm64")
 set(TOOLCHAIN_PREFIX /usr/bin/aarch64-linux-gnu)
 set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
 set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++-7)
 set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX})
 set (CMAKE_C_FLAGS "-std=c99")
else()
 set(CMAKE_C_COMPILER gcc-7)
 set(CMAKE_CXX_COMPILER g++-7)
 set (CMAKE_C_FLAGS "-std=c99")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the installation prefix
if (${arch} STREQUAL "armhf")
 set(prefix /usr/arm-linux-gnueabihf)
elseif(${arch} STREQUAL "arm64")
 set(prefix /usr/aarch64-linux-gnu)
else()
 set(prefix /usr/local)
endif()
set(CMAKE_INSTALL_PREFIX ${prefix})

set(DEPENDENCIES ${prefix})
set (LIBALLPATH_INCLUDE ${DEPENDENCIES}/include)
set (LIBALLPATH_LIB ${DEPENDENCIES}/lib)
include_directories(${LIBALLPATH_INCLUDE})
link_directories(${LIBALLPATH_LIB})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

include_directories(include)
include_directories(/usr/include/python3.6/)
include_directories(/usr/local/include/python3.6/)

# Process Cap'n Proto messages
add_custom_command(
        OUTPUT  "${CMAKE_SOURCE_DIR}/include/messaging/disco.capnp.c++"
        DEPENDS "${CMAKE_SOURCE_DIR}/include/messaging/capnp/disco.capnp"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/include/messaging/capnp"
        COMMAND capnp compile disco.capnp -oc++:../
        COMMENT "=== Processing cap'n p disco files ==="
)

add_custom_command(
        OUTPUT  "${CMAKE_SOURCE_DIR}/include/messaging/distcoord.capnp.c++"
        DEPENDS "${CMAKE_SOURCE_DIR}/include/messaging/capnp/distcoord.capnp"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/include/messaging/capnp"
        COMMAND capnp compile distcoord.capnp -oc++:../
        COMMENT "=== Processing cap'n p distcoord files ==="
        )

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    # Tests
    #add_subdirectory(examples/DistributedEstimator)
    #add_subdirectory(examples/DistributedEstimatorGroup)
    #add_subdirectory(examples/LeaderElection)
    #add_subdirectory(examples/Consensus)
    #add_subdirectory(examples/ActiveReplica)
    #add_subdirectory(examples/AdaptiveTimer)
    #add_subdirectory(examples/TSyncCA)
    #add_subdirectory(examples/TSyncGpio)
    #add_subdirectory(tests/StaticTimer)
    #add_subdirectory(tests/test_timer)
    #add_subdirectory(tests/GpioDeviceTesting)
    #add_subdirectory(tests/testPubSub/test_1_1/test_1_1)
    #add_subdirectory(tests/ScheduledTimer)
    #add_subdirectory(examples/Limits)
    #add_subdirectory(tests/DC/groupmsgtest)
    #add_subdirectory(tests/DC/groupleavetest)
    #add_subdirectory(tests/DC/leaderwithone)
    #add_subdirectory(tests/DC/leadermessage)
    #add_subdirectory(tests/DC/leaderwiththree)
    # add_subdirectory(tests/TimedTest)
    # add_subdirectory(examples/EchoIO)
    add_subdirectory(examples/pybind/WeatherMonitor)
    add_subdirectory(examples/pybind/DistributedEstimatorPybind)
    # add_subdirectory(tests/PeriodicTimerSync)
    # add_subdirectory(tests/DistributedVoltage)
    add_subdirectory(examples/pybind/Group)
endif()


# libriaps sources
list (APPEND riapslib_SOURCE
        include/messaging/disco.capnp.c++
        include/messaging/dc.capnp.c++
        src/componentmodel/ports/r_queryport.cc
        #src/componentmodel/ports/r_queryportgroup.cc
        src/componentmodel/ports/r_answerport.cc
        #src/componentmodel/ports/r_answerportgroup.cc
        src/componentmodel/ports/r_insideport.cc
        src/componentmodel/ports/r_periodictimer.cc
        src/componentmodel/ports/r_portbase.cc
        src/componentmodel/ports/r_porterror.cc
        src/componentmodel/ports/r_publisherport.cc
        src/componentmodel/ports/r_pubportbase.cc
        src/componentmodel/ports/r_pubportgroup.cc
        src/componentmodel/ports/r_recvport.cc
        src/componentmodel/ports/r_requestport.cc
        src/componentmodel/ports/r_responseport.cc
        src/componentmodel/ports/r_senderport.cc
        src/componentmodel/ports/r_subportbase.cc
        src/componentmodel/ports/r_subportgroup.cc
        src/componentmodel/ports/r_subscriberport.cc
        src/componentmodel/ports/r_timedport.cc
        src/componentmodel/r_pyactor.cc
        src/componentmodel/r_messageparams.cc
        src/componentmodel/r_componentbase.cc
        src/componentmodel/r_devicethread.cc
        src/componentmodel/r_discoverdapi.cc
        src/componentmodel/r_messagereader.cc
        src/componentmodel/r_parameter.cc
        src/framework/rfw_configuration.cc
        src/framework/rfw_network_interfaces.cc
        src/framework/rfw_security.cc
        src/groups/r_group.cc
        src/groups/r_grouplead.cc
        src/groups/r_groupid.cc
        src/groups/r_ownid.cc
        src/groups/r_groupdata.cc
        src/utils/r_utils.cc
        )

# libriaps headers
list (APPEND riapslib_HEADERS
        include/componentmodel/ports/r_queryport.h
        include/componentmodel/ports/r_answerport.h
        include/componentmodel/ports/r_insideport.h
        include/componentmodel/ports/r_periodictimer.h
        include/componentmodel/ports/r_portbase.h
        include/componentmodel/ports/r_porterror.h
        include/componentmodel/ports/r_publisherport.h
        include/componentmodel/ports/r_pubportbase.h
        include/componentmodel/ports/r_pubportgroup.h
        include/componentmodel/ports/r_recvport.h
        include/componentmodel/ports/r_requestport.h
        include/componentmodel/ports/r_responseport.h
        include/componentmodel/ports/r_senderport.h
        include/componentmodel/ports/r_subportbase.h
        include/componentmodel/ports/r_subportgroup.h
        include/componentmodel/ports/r_subscriberport.h
        include/componentmodel/ports/r_timedport.h
        include/componentmodel/r_messagebuilder.h
        include/componentmodel/r_messagereader.h
        include/componentmodel/r_pyactor.h
        include/componentmodel/r_messageparams.h
        include/componentmodel/r_componentbase.h
        include/componentmodel/r_configuration.h
        include/componentmodel/r_devicethread.h
        include/componentmodel/r_discoverdapi.h
        include/componentmodel/r_parameter.h
        include/componentmodel/r_riapsmessage.h
        include/const/r_const.h
        include/groups/r_group.h
        include/groups/r_groupid.h
        include/groups/r_grouplead.h
        include/groups/r_groupservice.h
        include/groups/r_ownid.h
        include/groups/r_groupdata.h
        include/messaging/disco.capnp.h
        include/messaging/dc.capnp.h
        include/utils/r_expirable.h
        include/utils/r_expirablelist.h
        include/utils/r_timeout.h
        include/framework/rfw_security.h
        )

# libriaps
add_library(riaps SHARED
        ${riapslib_SOURCE}
        ${riapslib_HEADERS}
        )

target_link_libraries(riaps PRIVATE czmq zmq dl capnp kj opendht gnutls stdc++fs)
install(TARGETS riaps DESTINATION lib)

# rdiscoveryd source
list(APPEND RDISCOVERYD_SOURCE
        src/discoveryd/r_discoveryd.cc
        src/discoveryd/r_riaps_actor.cc
        src/discoveryd/r_msghandler.cc
        src/discoveryd/r_dhttracker.cc
        src/utils/r_lmdb.cc
        src/discoveryd/r_validator.cc
        src/discoveryd/r_dhtdata.cc
        include/messaging/disco.capnp.c++
        )

# rdiscoveryd headers
list(APPEND RDISCOVERYD_HEADERS
        include/discoveryd/r_riaps_actor.h
        include/discoveryd/r_discovery_types.h
        include/discoveryd/r_msghandler.h
        include/discoveryd/r_dhttracker.h
        include/framework/rfw_configuration.h
        include/framework/rfw_network_interfaces.h
        include/framework/rfw_security.h
        include/utils/r_lmdb.h
        include/utils/r_utils.h
        include/messaging/disco.capnp.h
        include/groups/r_group.h
        include/spdlog/spdlog.h
        include/utils/r_timeout.h
        include/discoveryd/r_validator.h
        include/discoveryd/r_dhtdata.h
        )

# rdiscoveryd
add_executable(rdiscoveryd
        ${RDISCOVERYD_SOURCE}
        ${RDISCOVERYD_HEADERS}
        )
target_link_libraries(rdiscoveryd czmq zmq opendht gnutls riaps capnp nettle hogweed gmp pthread kj lmdb stdc++fs)

install(TARGETS rdiscoveryd DESTINATION bin)

SET(MAJOR_VERSION "1")
SET(MINOR_VERSION "1")
SET(PATCH_VERSION "18")


IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
    INCLUDE(InstallRequiredSystemLibraries)
    SET(CPACK_SET_DESTDIR "on")
    SET(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
    SET(CPACK_GENERATOR "DEB")
    SET(CPACK_DEBIAN_PACKAGE_NAME "riapscore-${arch}")
    SET(CPACK_PACKAGE_DESCRIPTION "RiapsDiscoveryService")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This is the decentralized discovery service for RIAPS")
    SET(CPACK_PACKAGE_VENDOR "riaps")
    SET(CPACK_PACKAGE_CONTACT "riaps@vanderbilt.edu")
    SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
    SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
    SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
    SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${arch})
    SET(CPACK_COMPONENTS_ALL Libraries ApplicationData)
    INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

install(DIRECTORY include/ DESTINATION include)
        #PATTERN "boost" EXCLUDE)
