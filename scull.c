#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
MODULE_LICENSE("Dual BSD/GPL");

//キャラクタ型デバイスの構造体の登録

#define MY_MAJOR        42

struct scull_dev {
    struct cdev cdev;
};

struct scull_dev dev;

struct file_operations scull_fops = {
        .owner  =   THIS_MODULE,
//        .read   =   scull_read,
//        .write  =   scull_write,
//        .unlocked_ioctl  =   scull_ioctl,
//        .open   =   scull_open,
//        .release    =   scull_release,
};

int init_func(void)
{
    int i, err;

    err = register_chrdev_region(MKDEV(MY_MAJOR, 0), 0, "scull");

    if (err != 0) {
        return err;
    }

    cdev_init(&dev.cdev, &scull_fops);
    cdev_add(&dev.cdev, MKDEV(MY_MAJOR, 0), 1);

    return 0;
}

void cleanup_func(void)
{
    cdev_del(&dev.cdev);
    unregister_chrdev_region(MKDEV(MY_MAJOR, 0), 0);
}

module_init(init_func);
module_exit(cleanup_func);