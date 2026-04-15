#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void) {
    printk(KERN_INFO "MiniDocker Monitor Loaded\n");
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "MiniDocker Monitor Removed\n");
}

MODULE_LICENSE("GPL");