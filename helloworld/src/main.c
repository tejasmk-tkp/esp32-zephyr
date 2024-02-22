#include <zephyr/kernel.h> //imports kernal functions, here k_msleep()
#include <zephyr/device.h> //imports device functions and macros, here device_is_ready and DEVICE_DT_GET, DT_NODELABEL
#include <zephyr/drivers/gpio.h> //imports gpio functions, here gpio_pin_configure and gpio_pin_set_raw

static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0)); //get the gpio0 device, gpio0 - Node label - find in devicetree

int main()
{
        if (!device_is_ready(gpio_ct_dev)) { //check is ddevice is available
                printk("GPIO device is not ready\n");
                return 0;
        }

        int ret;
        ret = gpio_pin_configure(gpio_ct_dev, 25, GPIO_OUTPUT_ACTIVE); //configure pin 25 as output

        if (ret != 0) { //check if pin is configured
                return ret;
        }

        while (true) {
                ret = gpio_pin_set_raw(gpio_ct_dev, 25, 1); //set pin 25 to high
                
                if (ret != 0) { //check if pin is set
                        return ret;
                }
                
                k_msleep(1000); //sleep for 1 second
                
                ret = gpio_pin_set_raw(gpio_ct_dev, 25, 0); //set pin 25 to low
                
                if (ret != 0){ //check if pin is set
                        return ret;
                }
                
                k_msleep(1000); //sleep for 1 second
        }

        return 0;
}
