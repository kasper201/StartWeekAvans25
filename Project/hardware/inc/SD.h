
#ifndef SD_H
#define SD_H

#include <zephyr/fs/fs.h>
#include <string.h>
#include <ff.h>


// testing purosses
#include "lcd.h"
#include "genericGpio.h"
//

int testSD();
void find_and_open_log_file(const char *mnt_point);


#endif