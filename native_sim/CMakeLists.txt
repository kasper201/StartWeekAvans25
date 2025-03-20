# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

project(digital_twin)

#FILE(GLOB app_headers 
#    src/*.h 
 #   states/inc/*.h 
#)

FILE(GLOB app_sources "src/*.c" )       # common source files (both the sim and the real deal)
FILE(GLOB states "states/src/*.c" )

option(USE_SIMULATOR "Build for simulator (e.g., QEMU)" OFF)

if(USE_SIMULATOR)
    set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/config/sim_prj.conf)
    set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/native_sim.overlay)
else()
    set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/config/prj.conf)
    set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/app.overlay)
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

if(USE_SIMULATOR)
    # enable sim sources here
    FILE(GLOB sim "native_sim/src/*.c" )
    target_sources(sim)
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/native_sim/inc)
   
else()
 #specifie hardware drivers
   
endif()
#set(SOURCES ${app_sources} ${app_headers})


target_sources(app PRIVATE 
    ${app_sources}
    ${states}
    )

target_include_directories(app PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/states/inc
)

message(STATUS "Sources: ${app_sources}")
message(STATUS "States: ${states}")
message(STATUS "dir  ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS " \n\n\n\n\ " )
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/states/inc")

message(STATUS " \n\n\n\n\n\n\n\n\ " )
