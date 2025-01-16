
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <hal/nrf_gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* Now we will access the button node and use to toggle the led
For this we will make button node, button call backs and interupts to make it work

Here in overlay file if you have assigned a gpio which is already used on some other function then disable that first and use it then

*/


#define LED1_NODE			DT_NODELABEL(led1)		// accesing led1 node in the dts
#define	BUTTON_NODE			DT_NODELABEL(button0)	// accesing button0


static const struct gpio_dt_spec led1_spec = GPIO_DT_SPEC_GET(LED1_NODE, gpios);		// making this spec structure global
static const struct gpio_dt_spec button_spec = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);	// making this spec structure global
																						//as we need to access in callbacks
static struct gpio_callback	button_cb;

// this call will have bitmask for pin number if we have more then on buttons to be used.  
void button_pressed_callback(const struct device *gpiob, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	gpio_pin_toggle_dt(&led1_spec);	// just toggle on every button press
}


int main(void)
{
	// const struct device *gpio0_dev = device_get_binding("gpio@50000000");		// here we are accessing it directly with gpio address
	// const struct device *gpio0_dev = device_get_binding(GPIO_NAME);
	// then use this port gpio0_dev to access the led pin
	// gpio_pin_configure(gpio0_dev, LED3_PIN0, GPIO_OUTPUT | LED3_FLAG);

	gpio_pin_configure_dt(&led1_spec, GPIO_OUTPUT);
	gpio_pin_configure_dt(&button_spec, GPIO_INPUT);

	gpio_init_callback(&button_cb, button_pressed_callback, BIT(button_spec.pin));	// initializing the button callback as there is
																					// bit making of pin number to be used here we need only 1

	// now register callback function
	gpio_add_callback(button_spec.port, &button_cb);	//you can add multiple callback functions here but we have only one here

	// now we have to activate the interupt, bcz we are using button struct so it should tell when the callback should be called
	gpio_pin_interrupt_configure_dt(&button_spec, GPIO_INT_EDGE_TO_ACTIVE);	// active on rising edge. When btn pressed then callback will be called

	while (1) {

		printk("Hello World!\n");

		k_msleep(SLEEP_TIME_MS);

	}
	return 0;
}
