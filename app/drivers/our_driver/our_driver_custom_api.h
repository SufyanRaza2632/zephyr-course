#pragma once 
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif
int our_driver_custom_data_update(const struct device *dev, int value);
int our_driver_custom_data_read(const struct device *dev);
#ifdef __cplusplus
}
#endif