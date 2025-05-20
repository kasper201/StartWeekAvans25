#include "SD.h"
#define DISK_DRIVE_NAME "SD"


struct fs_mount_t* get_mountpoint(){
    

   // static FATFS fat_fs_data;  // Needed if you're using FATFS

    static struct fs_mount_t mount = {
        .type = FS_FATFS,
        .mnt_point = "/SD",
        //.fs_data = &fat_fs_data,
        .storage_dev = (void *)DISK_DRIVE_NAME,
    };

    return &mount;
}

void init(){
    fs_mount(get_mountpoint());
}

void deinit(){
    fs_unmount(get_mountpoint());
}

/*
void addscore(int score){
    
}


Trivia get_trivia(nr) ;
Int get_score(){

}

Location get_location(int nr);
Settings get_settings();
Int event_log(char* logString){
fs_open("dedicated pointer" ,log, FS_O_WRITE | FS_O_CREATE | FS_O_APPEND )
}
*/


void log_file()
{
    const char *mnt_point = get_mountpoint()->mnt_point;
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

				if (fs_open(&log_fp, filepath, FS_O_READ) == 0) {
					printk("Opened log file: %s\n", filepath);

					// Example read:
					char buf[64];
					ssize_t len = fs_read(&log_fp, buf, sizeof(buf) - 1);
					if (len > 0) {
						buf[len] = '\0';
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