set(CMAKE_SYSTEM_NAME Linux)
set(RIAPS_PREFIX /opt/riaps/armhf/)
set(ARCH armhf)
set(TOOLCHAIN_PREFIX arm-linux-gnueabihf)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
set (CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_C_FLAGS "-std=c99")
include_directories(${RIAPS_PREFIX}/include)
