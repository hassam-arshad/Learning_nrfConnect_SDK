
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <hal/nrf_gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* Now we will use device tree to access the GPIO. For that we will goto .dts file from device tree section on left 
and access the nrf52840dk_nrf52840.dts
There we can see the gpio0 defined already. like this 
/soc/gpio@50000000/
NRF5 GPIO node
gpio0: gpio@50000000 {.....}
we will access with this address.

Now after that as this is not recommended practice now we will use nodes to get this dene. We will use gpio0 node 
directly to access it and use in code. 
*/

#define GPIO_NODE			DT_NODELABEL(gpio0)	// this stands for device tree node slash soc gpio_50000000
#define GPIO_NAME			DEVICE_DT_NAME(GPIO_NODE)		// this will bind the name for gpio0 node as we defined above.
															// So now we have this name to be used in code as device 
#define GPIO_PIN			NRF_GPIO_PIN_MAP(0,15)

int main(void)
{
	// const struct device *gpio0_dev = device_get_binding("gpio@50000000");		// here we are accessing it directly with gpio address
	const struct device *gpio0_dev = device_get_binding(GPIO_NAME);
	// then use this port gpio0_dev to access the led pin
	gpio_pin_configure(gpio0_dev, GPIO_PIN, GPIO_OUTPUT);

	while (1) {

		printk("Hello World!\n");
		gpio_pin_set(gpio0_dev, GPIO_PIN, 1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set(gpio0_dev, GPIO_PIN, 0);
		k_msleep(SLEEP_TIME_MS);

	}
	return 0;
}
