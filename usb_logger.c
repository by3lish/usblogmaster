#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/timekeeping.h>

// SET YOUR OWN USERNAME INSTEAD OF ELISH OR SET THE LOCATION FOR THE LOG FILE
#define LOG_FILE_PATH "/home/elish/usblog.txt"

static void format_date(char *buffer, size_t size) {
    struct timespec64 ts;
    struct tm tm;
    ktime_get_real_ts64(&ts);
    time64_to_tm(ts.tv_sec, 0, &tm);
    snprintf(buffer, size, "%02d.%02d.%04ld", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

static void write_to_file(const char *message) {
    struct file *file;
    loff_t pos = 0;
    int ret;

    file = filp_open(LOG_FILE_PATH, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (IS_ERR(file)) {
        pr_err("Failed to open log file: %ld\n", PTR_ERR(file));
        return;
    }

    ret = kernel_write(file, message, strlen(message), &pos);
    if (ret < 0)
        pr_err("Failed to write to log file\n");

    filp_close(file, NULL);
}

static int usb_notify(struct notifier_block *nb, unsigned long action, void *data) {
    struct usb_device *dev = data;
    char date_buffer[32];
    char log_message[256];

    format_date(date_buffer, sizeof(date_buffer));

    switch (action) {
        case USB_DEVICE_ADD:
            snprintf(log_message, sizeof(log_message),
                     "Device Plugged In: Name='%s', Type='USB', Date='%s'\n",
                     dev->product ? dev->product : "Unknown", date_buffer);
            write_to_file(log_message);
            pr_info("%s", log_message);
            break;

        case USB_DEVICE_REMOVE:
            snprintf(log_message, sizeof(log_message),
                     "Device Removed: Name='%s'\n",
                     dev->product ? dev->product : "Unknown");
            write_to_file(log_message);
            pr_info("%s", log_message);
            break;

        default:
            break;
    }
    return NOTIFY_OK;
}

static struct notifier_block usb_nb = {
    .notifier_call = usb_notify
};

static int __init usb_logger_init(void) {
    usb_register_notify(&usb_nb);
    pr_info("USB Device Logger Module Loaded\n");
    return 0;
}

static void __exit usb_logger_exit(void) {
    usb_unregister_notify(&usb_nb);
    pr_info("USB Device Logger Module Unloaded\n");
}

module_init(usb_logger_init);
module_exit(usb_logger_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("by3lish");
MODULE_DESCRIPTION("USB Device Logger Module");

