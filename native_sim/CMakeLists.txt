# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(digital_twin)


if(CONFIG_BOARD_NATIVE_SIM)
    # enable sim sources here
    FILE(GLOB specific_sources "native_sim/src/*.c" )
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/native_sim/inc)
   
else()
    #specify hardware drivers
   
    FILE(GLOB specific_sources 
        "hardwareControl/src/*.c" 
        "hardware/src/*.c")
    target_include_directories(app PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/hardwareControl/inc 
        ${CMAKE_CURRENT_SOURCE_DIR}/hardware/inc )
endif()
#set(SOURCES ${app_sources} ${app_headers})

FILE(GLOB app_sources "src/*.c" )       # common source files (both the sim and the real deal)
FILE(GLOB states "states/src/*.c" )
FILE(GLOB tests "tests/src/*.c" )       # Specifically for testing, might not be necessary later.

target_sources(app PRIVATE 
    ${app_sources}
    ${states}
    ${tests}        # Specifically for testing, might not be necessary later.
    
    ${specific_sources}
    ${hardware}
    )

target_include_directories(app PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/states/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/inc   # Specifically for testing, might not be necessary later.
)

message(STATUS "\n CMAKE DEBUG INFO \n Sources: ${app_sources}")
message(STATUS "States: ${states}")
message(STATUS "dir  ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS " \n\n\n\ FOR THE BOARD ${CONFIG_BOARD} \n\n\n\ " )
message(STATUS "$ENV{ZEPHYR_BASE}")
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/states/inc")

message(STATUS " END OF CMAKE \n\n\n\n\n\n\n\n\ " )

