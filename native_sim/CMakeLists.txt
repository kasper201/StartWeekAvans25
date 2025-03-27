# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

project(digital_twin)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

option(USE_SIMULATOR "Build for simulator (e.g., QEMU)" OFF)

if(USE_SIMULATOR)                           # this ifstatement ensures that the right h files are included later in the process
    add_compile_definitions(USE_SIMULATOR)
else()
    add_compile_definitions(USE_HARDWARE)
endif()


if(USE_SIMULATOR)
    # enable sim sources here
    FILE(GLOB specific_sources "native_sim/src/*.c" )
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/native_sim/inc)
   
else()
    #specify hardware drivers
   
    FILE(GLOB specific_sources "hardwareControl/src/*.c" "hardware/src/*.c")
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hardwareControl/inc)
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hardware/inc)
endif()
#set(SOURCES ${app_sources} ${app_headers})

FILE(GLOB app_sources "src/*.c" )       # common source files (both the sim and the real deal)
FILE(GLOB states "states/src/*.c" )

#FILE(GLOB hardware "hardware/src/*.c")



target_sources(app PRIVATE 
    ${app_sources}
    ${states}
    
    ${specific_sources}
    ${hardware}
    )

target_include_directories(app PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/states/inc
)

message(STATUS "Sources: ${app_sources}")
message(STATUS "States: ${states}")
message(STATUS "dir  ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS " \n\n\n\n\ " )
message(STATUS "$ENV{ZEPHYR_BASE}")
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/states/inc")

message(STATUS " \n\n\n\n\n\n\n\n\ " )





# # SPDX-License-Identifier: Apache-2.0

# cmake_minimum_required(VERSION 3.20.0)
# find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
# project(blinky)


# # Gather source files using wildcards for src directory
# file(GLOB SRC_HARDWARE_SOURCES 			"hardware/src/*.c")
# file(GLOB SRC_HARDWARECONTROL_SOURCES 	"hardwareControl/src/*.c")
# file(GLOB SRC_MAIN_SOURCES 				"src/*.c")
# file(GLOB SRC_STATES_SOURCES 			"states/src/*.c")

# # Add your source files
# target_sources(app PRIVATE 
#     ${SRC_HARDWARE_SOURCES}
# 	${SRC_HARDWARECONTROL_SOURCES}
# 	${SRC_MAIN_SOURCES}
# 	${SRC_STATES_SOURCES}
# )

# # Add include directories
# target_include_directories(app PRIVATE
# 	${CMAKE_CURRENT_SOURCE_DIR}/hardware/inc
# 	${CMAKE_CURRENT_SOURCE_DIR}/hardwareControl/inc
# 	${CMAKE_CURRENT_SOURCE_DIR}/inc
# 	${CMAKE_CURRENT_SOURCE_DIR}/states/inc
# )