#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#define DEBUG_MODE
#ifdef DEBUG_MODE
#define printf_testhandler printf
#else
#define printf_testhandler(...)
#endif //DEBUG_MODE

#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

#include <stdio.h>
#include "threads.h"
#include "locations.h"

#if defined(CONFIG_BOARD_NATIVE_SIM)
#include <lvgl.h>
#include "hardware.h"
#else
#include "lcd.h"
#include "genericGpio.h"
#endif

uint8_t handleTests();

#endif // TESTHANDLER_H