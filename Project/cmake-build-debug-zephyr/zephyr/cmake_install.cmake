# Install script for directory: /home/flits/zephyrproject/zephyr

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/flits/Workspace/zephyr-sdk-0.16.8/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/adi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/altera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/flits/Documents/school/semesterproject/startweekavans25/Project/cmake-build-debug-zephyr/zephyr/cmake/reports/cmake_install.cmake")
endif()

