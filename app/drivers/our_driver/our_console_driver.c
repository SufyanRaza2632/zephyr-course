#include <zephyr/shell/shell.h>
#include "our_driver_custom_api.h"
#include <zephyr/drivers/sensor.h>


const struct device* driver =DEVICE_DT_GET(DT_NODELABEL(our_driver0));

static int fetch_handler(const struct shell* sh,int argc, char ** argv)
{
    shell_info(sh, "Hello from fetch handler\n");
    int ret = sensor_sample_fetch_chan(driver, SENSOR_CHAN_AMBIENT_TEMP);
}

static int read_handler(const struct shell* sh,int argc, char ** argv)
{
    shell_info(sh, "Hello from read handler\n");
    struct sensor_value val;
    int ret  = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_fprintf(sh, SHELL_ERROR, "Sensor channel get value %d.%d \n",val.val1,val.val2);
    return 0;
}

static int info_handler(const struct shell* sh,int argc, char ** argv)
{
    shell_info(sh, "Hello from info handler\n");
    shell_fprintf(sh,SHELL_INFO, "driver name: %s \ndriver status: %d\n", driver->name ,driver->state->init_res);
    return 0;
}
static int set_value_handler(const struct shell* sh,int argc, char ** argv)
{
   
    shell_info(sh, "Hello from set value handler\n");
    int set_val = atoi(argv[1]);
    if (set_val <0  || set_val> 100)
        shell_error(sh,"The input value is not in the valid range\n");
    else
    {
        if (device_is_ready(driver))
            our_driver_custom_data_update(driver, set_val);
   
    int ret_val = our_driver_custom_data_read(driver);
    shell_fprintf(sh,SHELL_INFO, "Value  %d is written to the device\n Reading from device. The value is %d\n",set_val, ret_val);
     }
     return 0;
}
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd,
[0]= SHELL_CMD_ARG(fetch,NULL,"This command will call sample sensor fetch", fetch_handler, 1 , 0),
[1]= SHELL_CMD_ARG(read,NULL,"This command will call channel get and print the results", read_handler, 1 , 0),
[2]= SHELL_CMD_ARG(info,NULL,"This command will print the device name and ready state", info_handler, 1 , 0),
[3]= SHELL_CMD_ARG(set,NULL,"This command will set the value to device data", set_value_handler, 2 , 0),
[4]= SHELL_SUBCMD_SET_END,

);

SHELL_CMD_REGISTER(sensor,&sensor_subcmd, "Set of Sensor subcommands", NULL);