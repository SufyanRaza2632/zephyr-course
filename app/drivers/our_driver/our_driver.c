#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT  our_driver
#define LED_NODE_DRIV DT_ALIAS(led3)
LOG_MODULE_REGISTER(our_driver,LOG_LEVEL_INF);

struct our_driver_data {
    int custom_value;
};

static struct our_driver_data data_iomico;
static const struct gpio_dt_spec led_driv = GPIO_DT_SPEC_GET(LED_NODE_DRIV, gpios);


int our_driver_custom_data_update(const struct device *dev, int value)
{
    struct our_driver_data *data =
        (struct our_driver_data *)dev->data;

    data->custom_value = value;

    LOG_INF("custom_value changed to %d",
            data->custom_value);

    return 0;


}
int our_driver_custom_data_read(const struct device *dev)
{
    struct our_driver_data *data =
        (struct our_driver_data *)dev->data;

    return data->custom_value;
}
static int sample_fetch_impl(const struct device *dev,
				     enum sensor_channel chan)
{
    LOG_INF("Hello from channel get, channel %d", chan);
    if(gpio_pin_set_dt(&led_driv,0 ) < 0 ) return 0;
    return 0;
}
static int channel_get_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val)
{

    LOG_INF("Hello from channel get, channel %d", chan);
     if(gpio_pin_set_dt(&led_driv,1 ) < 0 ) return 0;
    return 0;
}
        

static DEVICE_API(sensor, api_iomico) = {
    .channel_get  = channel_get_impl,
    .sample_fetch = sample_fetch_impl,
};

 

static int init(const struct device *dev)
{
 if (!gpio_is_ready_dt(&led_driv)) return 0;
 if (gpio_pin_configure_dt(&led_driv, GPIO_OUTPUT_ACTIVE) < 0) return 0;
 return 0;
}
 DEVICE_DT_INST_DEFINE(0  ,init,NULL,&data_iomico,NULL, POST_KERNEL,80, &api_iomico );