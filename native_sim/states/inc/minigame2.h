#ifndef MINIGAME2_H
#define MINIGAME2_H

#define DEBUG_MODE
#ifdef DEBUG_MODE
#define printf_minigame2 printf
#else
#define printf_minigame2(...)
#endif //DEBUG_MODE

#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

#include <stdio.h>
#include "threads.h"

#if defined(CONFIG_BOARD_NATIVE_SIM)
#include <lvgl.h>
#include "hardware.h"
#else
#include "lcd.h"
#include "genericGpio.h"
#endif


#define mg2ThreadCount 4

void getMg2Threads(char ***, unsigned *);

int playMg2();

#endif // MINIGAME2_H