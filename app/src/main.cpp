#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include "../drivers/our_driver/our_driver_custom_api.h"


/* The devicetree node identifier for the "led0" alias. using DT_ALIAS */
#define LED_NODE DT_ALIAS(app_led)
#define LED_NODE_TEST DT_ALIAS(led1)
#define TEST_VALUE 1234
/* The devicetree node identifier for the "led0" alias. using DT_NODELABEL*/
//#define LED_NODE DT_NODELABEL(heartbeat_led)

/* The devicetree node identifier for the "led0" alias. using DT_PATH*/
//#define LED_NODE DT_PATH(leds, led_4)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
static const struct gpio_dt_spec led_test = GPIO_DT_SPEC_GET(LED_NODE_TEST, gpios);
const struct device* driver =DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

       
        
       


int main(void)
{
    struct sensor_value val;
    bool led_state = true;
    bool led_test_state = false;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (!gpio_is_ready_dt(&led_test)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    if (gpio_pin_configure_dt(&led_test, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    if(gpio_pin_set_dt(&led_test,0 ) < 0 ) return 0;
    int ret  = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);

    if (device_is_ready(driver)) {
    our_driver_custom_data_update(driver, TEST_VALUE);
}

    while (1) {
        //test();
        if(led_state)
                ret  = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        else
                ret = sensor_sample_fetch_chan(driver, SENSOR_CHAN_AMBIENT_TEMP);
        if (gpio_pin_toggle_dt(&led) < 0) return 0;
        if (gpio_pin_toggle_dt(&led_test) < 0) return 0;

        led_state = !led_state;
        led_test_state = !led_test_state;
        
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        printk("Hello WOrld/n");
    }
    return 0;
}
