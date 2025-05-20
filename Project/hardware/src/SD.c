
#include <zephyr/kernel.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/storage/disk_access.h>
#include <zephyr/fs/fs.h>

#include <ff.h>

// testing purosses
#include "lcd.h"
#include "genericGpio.h"

#ifdef CONFIG_ARCH_POSIX
#define native_loop() k_sleep(K_MSEC(1))
#else
#define native_loop()
#endif
//


#define MOUNT_POINT "/SD"
#define DISK_DRIVE_NAME "SD"  // Or "SDMMC" for native SDMMC

static FATFS fat_fs;
K_TIMER_DEFINE(secTimerSD, NULL, NULL);


void test_log_file(const char *mnt_point)
{
	struct fs_dir_t dir;
	struct fs_dirent entry;
	struct fs_file_t log_fp;

	char filepath[256];
	bool found = false;

	fs_dir_t_init(&dir);

	if (fs_opendir(&dir, mnt_point) != 0) {
		printk("Failed to open directory: %s\n", mnt_point);
		return;
	}

	while (fs_readdir(&dir, &entry) == 0 && entry.name[0] != 0) {
		if (entry.type == FS_DIR_ENTRY_FILE) {
			printk("Found file: %s\n", entry.name);
			lcdStringWrite("found file");
			k_timer_start(&secTimerSD, K_MSEC(3000), K_NO_WAIT);
			while (!(k_timer_status_get(&secTimerSD) > 0)){native_loop();}	

			if (strcmp(entry.name, "log.txt") == 0) {
				found = true;

				snprintk(filepath, sizeof(filepath), "%s/%s", mnt_point, entry.name);
				fs_file_t_init(&log_fp);

				if (fs_open(&log_fp ,filepath , FS_O_WRITE | FS_O_CREATE | FS_O_APPEND ) == 0) {
					printk("found/made log file: %s\n", filepath);

					// Example write:
					const char *buf = "HELLO world";
					ssize_t lenw = fs_write(&log_fp, buf, strlen(buf));
					if (lenw > 0) {
						
						printk("Contents written:\n%s\n", buf);
					} else {
						printk("write failed\n");
					}
					fs_sync(&log_fp);
					fs_close(&log_fp);
				}

				if (fs_open(&log_fp, filepath, FS_O_READ) == 0) {
					printk("Opened log file: %s\n", filepath);

					// Example read:
					char buf[64];
					ssize_t lenr = fs_read(&log_fp, buf, sizeof(buf) - 1);
					if (lenr > 0) {
						buf[lenr] = '\0';
						printk("Contents:\n%s\n", buf);
					} else {
						printk("Empty or read failed\n");
					}

					fs_close(&log_fp);
				} else {
					printk("Failed to open log.txt\n");
				}
				break;  // Exit loop once found
			}
		}
	}

	fs_closedir(&dir);

	if (!found) {
		printk("log.txt not found on SD card.\n");
	}
}


int testSD(){

	lcdEnable();
	lcdStringWrite("startSD test");
	k_timer_start(&secTimerSD, K_MSEC(5000), K_NO_WAIT);
	while (!(k_timer_status_get(&secTimerSD) > 0)){native_loop();}	

	struct fs_mount_t mount = {
		.type = FS_FATFS,
		.mnt_point = MOUNT_POINT,
		.fs_data = &fat_fs,
		.storage_dev = (void *)DISK_DRIVE_NAME,

	};

	int ret = disk_access_init(DISK_DRIVE_NAME);
	if (ret) {
		lcdStringWrite("disk failure");
		k_timer_start(&secTimerSD, K_MSEC(10000), K_NO_WAIT);
		while (!(k_timer_status_get(&secTimerSD) > 0)){native_loop();}
		printk("Disk access init failed: %d\n", ret);
		return -1;
	}

	ret = fs_mount(&mount);
	if (ret != 0) {
		lcdStringWrite("mount failure");
		k_timer_start(&secTimerSD, K_MSEC(10000), K_NO_WAIT);
		while (!(k_timer_status_get(&secTimerSD) > 0)){native_loop();}
		printk("Failed to mount filesystem: %d\n", ret);
		return -1;
	}

	printk("Mounted SD card at %s\n", MOUNT_POINT);

	// 
	test_log_file(MOUNT_POINT);

	// Optionally unmount after test
	fs_unmount(&mount);

	lcdStringWrite("succesfull unmount");
	
	k_timer_start(&secTimerSD, K_MSEC(10000), K_NO_WAIT);
	while (!(k_timer_status_get(&secTimerSD) > 0)){native_loop();}	

	lcdClear();
	lcdDisable();
	return 0;
}