
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <hal/nrf_gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* Now we will again access the led node but with more simpler and stramlined way then the previos one. 
This will be better to use to access 
For example we will access the led1 which is defined like this in dts
		led1: led_1 {
			gpios = <&gpio0 14 GPIO_ACTIVE_LOW>;
			label = "Green LED 1";
		};

We will be accessiing using spec node as this will get us all port pin number and flags
we will change the set configure gpio function sto gpio_pin_set_dt where we will use dt at the end in name 
*/

#define LED1_NODE			DT_NODELABEL(led1)		// accesing led1 node in the dts


int main(void)
{
	// const struct device *gpio0_dev = device_get_binding("gpio@50000000");		// here we are accessing it directly with gpio address
	// const struct device *gpio0_dev = device_get_binding(GPIO_NAME);
	// then use this port gpio0_dev to access the led pin
	// gpio_pin_configure(gpio0_dev, LED3_PIN0, GPIO_OUTPUT | LED3_FLAG);
	static const struct gpio_dt_spec led1_spec = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
	gpio_pin_configure_dt(&led1_spec, GPIO_OUTPUT);


	while (1) {

		printk("Hello World!\n");
		gpio_pin_set_dt(&led1_spec, 1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set_dt(&led1_spec, 0);
		k_msleep(SLEEP_TIME_MS);

	}
	return 0;
}
