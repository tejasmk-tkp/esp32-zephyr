#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(user_led), gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_NODELABEL(user_button), gpios);

static struct gpio_callback button_callback;

void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
        gpio_pin_toggle(led.port, led.pin);
}

int main(void) {

        if (!device_is_ready(led.port)) {
                printk("Error: LED device is not ready\n");
                return 0;
        }

        if (!device_is_ready(button.port)) {
                printk("Error: Button device is not ready\n");
                return 0;
        }

        gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
        gpio_pin_configure_dt(&button, GPIO_INPUT);
        
        gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
        
        gpio_init_callback(&button_callback, button_pressed, BIT(button.pin));
        gpio_add_callback_dt(&button, &button_callback);

}
