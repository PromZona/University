# Install script for directory: /cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/src/libnats.dll.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/src/cygnats-2.1.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cygnats-2.1.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cygnats-2.1.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cygnats-2.1.dll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/src/libnats_static.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE RENAME "nats.h" FILES "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src/deprnats.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nats" TYPE FILE FILES
    "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src/nats.h"
    "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src/status.h"
    "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src/version.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nats/adapters" TYPE FILE FILES
    "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src/adapters/libevent.h"
    "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/src/adapters/libuv.h"
    )
endif()

