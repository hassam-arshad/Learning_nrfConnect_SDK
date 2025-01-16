
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <hal/nrf_gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* Now we will use device tree to access the led nodes which are defined already. 
For example we will access the led3 which is defined like this in dts
		led3: led_3 {
			gpios = <&gpio0 16 GPIO_ACTIVE_LOW>;
			label = "Green LED 3";
		};

*/

#define LED3_NODE			DT_NODELABEL(led3)	
#define LED3_GPIO_NODE		DT_PHANDLE_BY_IDX(LED3_NODE,gpios,0)	// this is handling the led node as we did last time like /soc/gpio@50000000/
#define GPIO_NAME			DEVICE_DT_NAME(LED3_GPIO_NODE)		// this will bind the name for gpio0 node as we defined above.
															// So now we have this name to be used in code as device 
#define LED3_PIN0			DT_GPIO_PIN(LED3_NODE, gpios)	// we access pin number here 16
#define	LED3_FLAG			DT_GPIO_FLAGS(LED3_NODE, gpios)	// here we are accessing the flag to make it high or low based on if its 
															// being set active high or active low in dts. 
															//So with this its automatically getting and making high and low

int main(void)
{
	// const struct device *gpio0_dev = device_get_binding("gpio@50000000");		// here we are accessing it directly with gpio address
	const struct device *gpio0_dev = device_get_binding(GPIO_NAME);
	// then use this port gpio0_dev to access the led pin
	gpio_pin_configure(gpio0_dev, LED3_PIN0, GPIO_OUTPUT | LED3_FLAG);

	while (1) {

		printk("Hello World!\n");
		gpio_pin_set(gpio0_dev, LED3_PIN0, 1);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_set(gpio0_dev, LED3_PIN0, 0);
		k_msleep(SLEEP_TIME_MS);

	}
	return 0;
}
