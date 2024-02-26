#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(user_led), gpios);

int main(void) {
        if (!device_is_ready(led.port)){
                printk("Error: Device not ready\n");
                return 0;
        }

        int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT);

        if (ret != 0) {
                printk("Error: Unable to configure pin\n");
                return 0;
        }

        while (true) {
                ret = gpio_pin_toggle_dt(&led);

                if (ret != 0) {
                        printk("Error: Unable to toggle pin\n");
                        return 0;
                }

                k_msleep(1000);
        }
}
