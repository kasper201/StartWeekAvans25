#ifndef MINIGAME6_H
#define MINIGAME6_H

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


#define mg6ThreadCount 3

void getMg6Threads(char ***, unsigned *);

int playMg6();

#endif // MINIGAME6_H