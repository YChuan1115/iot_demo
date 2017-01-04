#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pthread.h>
#include "bme280_i2c/include/my_debug.h"

#include "bme280_i2c/include/bcm2835.h"
#include "bme280_i2c/include/bme280.h"

#define BME280_ADDR 0x76

void bme280run()
{
	struct bme280_t *bme;
	
	//-- init the bcm2835 library
    bcm2835_init();
    i2c_start();


	//-- new a bme280 device module with i2c_addr
	bme = bme280_new(BME280_ADDR);     if(bme == 0) perror("i2c failed");
	bme280_initi(bme);
	while(1){
		usleep(5000000);
		bme280_force_read_measurement(bme);
		bme280_show(bme);
	};


	// -- END
	bme280_write_mode(bme,BME280_MODE_SLEEP);
	bme280_free(bme);
	bcm2835_close();

}
