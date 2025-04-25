#include <zephyr/fs/fs.h>
#include <zephyr/kernel.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/storage/disk_access.h>
#include <ff.h>

#define MOUNT_POINT "/SD"
#define DISK_DRIVE_NAME "SD"  // Or "SDMMC" for native SDMMC

static FATFS fat_fs;



void test_log_file(const char *mnt_point)
{
	struct fs_dir_t dir;
	struct fs_dirent entry;
	struct fs_file_t log_fp;

	char filepath[128];
	bool found = false;

	fs_dir_t_init(&dir);

	if (fs_opendir(&dir, mnt_point) != 0) {
		printk("Failed to open directory: %s\n", mnt_point);
		return;
	}

	while (fs_readdir(&dir, &entry) == 0 && entry.name[0] != 0) {
		if (entry.type == FS_DIR_ENTRY_FILE) {
			printk("Found file: %s\n", entry.name);

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
	struct fs_mount_t mount = {
		.type = FS_FATFS,
		.mnt_point = MOUNT_POINT,
		.fs_data = &fat_fs,
		.storage_dev = (void *)DISK_DRIVE_NAME,
	};

	int ret = disk_access_init(DISK_DRIVE_NAME);
	if (ret) {
		printk("Disk access init failed: %d\n", ret);
		return -1;
	}

	ret = fs_mount(&mount);
	if (ret != 0) {
		printk("Failed to mount filesystem: %d\n", ret);
		return -1;
	}

	printk("Mounted SD card at %s\n", MOUNT_POINT);

	// 
	test_log_file(MOUNT_POINT);

	// Optionally unmount after test
	fs_unmount(&mount);
	return 0;
}