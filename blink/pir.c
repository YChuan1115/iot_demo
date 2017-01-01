/*
  GPIO_INPUT example For raspberry pi 3
  WebSite : www.ittraining.com.tw  
  Programmer: robot@ittraining.com.tw
*/
#include <bcm2835.h>
#include <stdio.h>
 

#define LED1  5
#define LED2  13
#define GPIO_INPUT 26
#define COM 22
#define RELAY 27
#define BUTTON1 24
#define DIP2 20

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO

    int dip_value;
	int btn_value;
	int gpio_value;
    if (!bcm2835_init())
	return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RELAY, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_INPUT, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(BUTTON1, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(DIP2, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(COM, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(COM, HIGH);
	bcm2835_gpio_write(RELAY,HIGH);
    // Blink
	
    while (1)
    {
		
	 gpio_value= bcm2835_gpio_lev(GPIO_INPUT);
	 //dip_value= bcm2835_gpio_lev(DIP2);
	 btn_value= bcm2835_gpio_lev(BUTTON1);
	 printf("read from GPIO_INPUT (Press on): %d\n", gpio_value);	
	
	if (gpio_value==1 || btn_value==0) {	
	// Turn it on
	bcm2835_gpio_write(LED1, HIGH);
	bcm2835_gpio_write(LED2, HIGH);
    bcm2835_gpio_write(RELAY,HIGH);
	
    } else {
	
	// turn it off
	bcm2835_gpio_write(LED1, LOW);
	bcm2835_gpio_write(LED2, LOW);
     bcm2835_gpio_write(RELAY,LOW);

    }
	
	bcm2835_delay(500);  //500ms
	}
    bcm2835_close();
    return 0;
}

