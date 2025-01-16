
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <hal/nrf_gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* Now we will make a new node by making a new oevrlay file and adding a new node there.
For making a new custom overlay file just goto config files on left then Devicetree and under there click create overlay file
It will automatically name it with your board.
then add a new node just copy from dts file the led1 node and rename it there with maybe led4

Here in overlay file if you have assigned a gpio which is already used on some other function then disable that first and use it then

*/

#define LED4_NODE			DT_NODELABEL(led4)		// accesing led1 node in the dts


int main(void)
{
	// const struct device *gpio0_dev = device_get_binding("gpio@50000000");		// here we are accessing it directly with gpio address
	// const struct device *gpio0_dev = device_get_binding(GPIO_NAME);
	// then use this port gpio0_dev to access the led pin
	// gpio_pin_configure(gpio0_dev, LED3_PIN0, GPIO_OUTPUT | LED3_FLAG);
	static const struct gpio_dt_spec led4_spec = GPIO_DT_SPEC_GET(LED4_NODE, gpios);
	gpio_pin_configure_dt(&led4_spec, GPIO_OUTPUT);


	while (1) {

		printk("Hello World!\n");
		gpio_pin_set_dt(&led4_spec, 1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set_dt(&led4_spec, 0);
		k_msleep(SLEEP_TIME_MS);

	}
	return 0;
}
