#ifndef MINIGAME4_H
#define MINIGAME4_H

#include <zephyr/kernel.h>
#include <stdio.h>
#include "threads.h"
#ifdef USE_SIMULATOR
#include <lvgl.h>
#include "hardware.h"
#else
#include "lcd.h"
#include "genericGpio.h"
#endif

#define mg4ThreadCount 3

void getMg4Threads(char ***, unsigned *);

int playMg4();
#define AMOUNT_QUESTIONS 4
#define AMOUNT_ANSWERS 3
#define MAX_SIZE 32

#endif // MINIGAME4_H