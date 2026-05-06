
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

void board_early_init_hook()
{
    printk("Board init message after console init\n");
    return 0;
}

SYS_INIT(board_early_init_hook, APPLICATION, 0);