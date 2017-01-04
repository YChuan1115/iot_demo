#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<bme280_i2c/include/lib_i2c.h>
#include<bme280_i2c/include/bme280.h>
#include<pthread.h>
#include<bme280_i2c/include/my_debug.h>




struct bme280_t * bme280_new(uint8_t i2c_addr)
{
	struct bme280_t *bme;
	bme = (struct bme280_t *) malloc(sizeof(struct bme280_t));
	if(bme == 0) return 0;
	bme->i2c_addr = i2c_addr;
	return bme;
}



void bme280_free(struct bme280_t * bme)
{
	if(bme != 0)
		free(bme);
}

int bme280_get_id( struct bme280_t * bme) {
	uint8_t i2c_addr ;
	i2c_addr = bme->i2c_addr;
    return i2c_readReg(i2c_addr, BME280_REG_CHIP_ID);
}


int bme280_get_compensation_param(struct bme280_t * bme, int param)
{
    uint8_t buf[2];
    uint8_t reg;
	uint8_t i2c_addr = bme->i2c_addr;

    if( param <= BME280_DIG_P9 ){
        reg = param * 2 + BME280_REG_T1;
        i2c_read_data_block(i2c_addr, reg, buf, 2);
        return ( buf[0] | (buf[1] << 8 ) );
    }
    else if (param == BME280_DIG_H1){
        return i2c_readReg(i2c_addr, BME280_REG_H1);
    } else if (param == BME280_DIG_H2){
        i2c_read_data_block(i2c_addr, BME280_REG_H2, buf, 2);
        return ( buf[0] | (buf[1] << 8 ) );
    } else if (param == BME280_DIG_H3){
        return i2c_readReg(i2c_addr, BME280_REG_H3);
    } else if (param == BME280_DIG_H4){
        i2c_read_data_block(i2c_addr, BME280_REG_H4, buf, 2);
        return (buf[0] << 4) | (buf[1] & 0x0F);
    } else if (param == BME280_DIG_H5){
        i2c_read_data_block(i2c_addr, BME280_REG_H5, buf, 2);
        return (((buf[0] & 0xF0) >> 4 ) | (buf[1] << 4));
    } else if (param == BME280_DIG_H6){
        return i2c_readReg(i2c_addr, BME280_REG_H6);
    }
}




int bme280_read_compensation_param(struct bme280_t *bme)
{
	uint8_t i2c_addr ;
	uint8_t count;
	uint16_t regE5, regE6;
	uint8_t buff[24];

	i2c_addr = bme->i2c_addr;
	//Wire.write(regCalibStart);
	i2c_read_data_block(i2c_addr, BME280_REG_CALIB_START, buff, 24);
	bme->dig_T1 = (buff[0])  | (buff[1]  << 8 ) ;
	bme->dig_T2 = (buff[2])  | (buff[3]  << 8 ) ;
	bme->dig_T3 = (buff[4])  | (buff[5]  << 8 ) ;
	bme->dig_P1 = (buff[6])  | (buff[7]  << 8 ) ;
	bme->dig_P2 = (buff[8])  | (buff[9]  << 8 ) ;
	bme->dig_P3 = (buff[10]) | (buff[11] << 8 ) ;
	bme->dig_P4 = (buff[12]) | (buff[13] << 8 ) ;
	bme->dig_P5 = (buff[14]) | (buff[15] << 8 ) ;
	bme->dig_P6 = (buff[16]) | (buff[17] << 8 ) ;
	bme->dig_P7 = (buff[18]) | (buff[19] << 8 ) ;
	bme->dig_P8 = (buff[20]) | (buff[21] << 8 ) ;
	bme->dig_P9 = (buff[22]) | (buff[23] << 8 ) ;
	// then they go a bit strangely

	bme->dig_H1 = i2c_readReg(i2c_addr, BME280_REG_H1);
	
	i2c_read_data_block(i2c_addr, BME280_REG_CALIB_START2, buff, 7);
	
	bme->dig_H2 = buff[0];
	bme->dig_H2 |= (uint16_t)buff[1] << 8;
	bme->dig_H3 = buff[2];
	bme->dig_H4 = (uint16_t)buff[3] << 4; // bits 11:4
	regE5 = buff[4];
	bme->dig_H4 |= regE5 & 0b00001111; // bits 11:4
	bme->dig_H5 = regE5 >> 4;
	regE6 = buff[5];
	bme->dig_H5 |= regE6 << 4;
	bme->dig_H6 = buff[6];
}



void bme280_write_oversampling_pressure(struct bme280_t * bme, uint8_t bme280_os )
{
	uint8_t ctrl_mesa;
	uint8_t i2c_addr = bme->i2c_addr;
	ctrl_mesa = i2c_readReg(i2c_addr , BME280_REG_CTRL_MEAS);
	ctrl_mesa = ctrl_mesa & 0b11100011;
	ctrl_mesa = ctrl_mesa | (bme280_os << 2);

	i2c_writeReg(i2c_addr, BME280_REG_CTRL_MEAS, ctrl_mesa);
}



void bme280_write_oversampling_temperature(struct bme280_t * bme, uint8_t bme280_os )
{
	uint8_t ctrl_mesa;
	uint8_t i2c_addr = bme->i2c_addr;
	ctrl_mesa = i2c_readReg(i2c_addr , BME280_REG_CTRL_MEAS);
	ctrl_mesa = ctrl_mesa & 0b00011111;
	ctrl_mesa = ctrl_mesa | (bme280_os << 5);
	i2c_writeReg(i2c_addr, BME280_REG_CTRL_MEAS, ctrl_mesa);
}



void bme280_write_oversampling_humidity(struct bme280_t * bme, uint8_t bme280_os )
{
	uint8_t i2c_addr = bme->i2c_addr;
	i2c_writeReg(i2c_addr, BME280_REG_CTRL_HUM, bme280_os);
}


void bme280_write_mode(struct bme280_t * bme, uint8_t bme280_mode )
{
	uint8_t i2c_addr = bme->i2c_addr;
	uint8_t ctrl_mesa;
	ctrl_mesa = i2c_readReg(i2c_addr, BME280_REG_CTRL_MEAS);
	ctrl_mesa = ctrl_mesa & 0b11111100;
	ctrl_mesa = ctrl_mesa | bme280_mode;

	i2c_writeReg(i2c_addr, BME280_REG_CTRL_MEAS,ctrl_mesa);
}



uint8_t bme280_is_measuring(struct bme280_t * bme)
{
	uint8_t i2c_addr = bme->i2c_addr;
	if(i2c_readReg(i2c_addr, BME280_REG_STATUS) & 0b00001000)
		return 1;
	else
		return 0;
}



void bme280_read_measurements(struct bme280_t * bme)
{
	uint8_t i2c_addr = bme->i2c_addr;
	uint8_t data[8];
	i2c_read_data_block(i2c_addr, BME280_REG_MEASURE_START ,data, 8);
	bme->adc_h = (uint32_t)data[7] | ( (uint32_t)data[6] << 8);

	bme->adc_t  = (uint32_t)data[5] >> 4;
	bme->adc_t |= (uint32_t)data[4] << 4;
	bme->adc_t |= (uint32_t)data[3] << 12;

	bme->adc_p  = (uint32_t)data[2] >> 4;
	bme->adc_p |= (uint32_t)data[1] << 4;
	bme->adc_p |= (uint32_t)data[0] << 12;
}




void bme280_info(struct bme280_t *bme)
{
	printf("------ Info of BME280 ------\n ");
	printf("    ID: %04X\n", bme280_get_id(bme));
	printf("dig_T1: %04X  ",bme->dig_T1);
	printf("dig_T2: %04X  ",bme->dig_T2);
	printf("dig_T3: %04X\n\n",bme->dig_T3);
	printf("dig_P1: %04X  ",bme->dig_P1);
	printf("dig_P2: %04X  ",bme->dig_P2);
	printf("dig_P3: %04X\n",bme->dig_P3);
	printf("dig_P4: %04X  ",bme->dig_P4);
	printf("dig_P5: %04X  ",bme->dig_P5);
	printf("dig_P6: %04X\n",bme->dig_P6);
	printf("dig_P7: %04X  ",bme->dig_P7);
	printf("dig_P8: %04X  ",bme->dig_P8);
	printf("dig_P9: %04X\n\n",bme->dig_P9);
	printf("dig_H1: %04X  ",bme->dig_H1);
	printf("dig_H2: %04X  ",bme->dig_H2);
	printf("dig_H3: %04X\n",bme->dig_H3);
	printf("dig_H4: %04X  ",bme->dig_H4);
	printf("dig_H5: %04X  ",bme->dig_H5);
	printf("dig_H6: %04X\n",bme->dig_H6);
}



void bme280_initi(struct bme280_t *bme)
{
	// 
	bme280_read_compensation_param(bme);
	bme280_write_oversampling_pressure(bme, BME280_OS1x);
	bme280_write_oversampling_temperature(bme, BME280_OS1x);
	bme280_write_oversampling_humidity(bme, BME280_OS1x);
	bme280_write_mode(bme, BME280_MODE_FORCED);
	while(bme280_is_measuring(bme)){
		usleep(200);
	}
	bme280_read_measurements(bme);

#ifdef MYDEBUG
	printf("T:%6.2f C, H:%6.2f%%, P:%6.2f\n", 
			bme280_get_temperature(bme),
			bme280_get_humidity(bme),
			bme280_get_pressure(bme));
	printf("More Accurate measurement: \n");
	printf("P:%f\n", bme280_get_pressure_more_accurate(bme));
	printf("Most Accurate measurement: \n");
	printf("T:%f, H:%f, P:%f\n", 
			bme280_get_temperature_most_accurate(bme),
			bme280_get_humidity_most_accurate(bme),
			bme280_get_pressure_most_accurate(bme));
#else 

#endif 
	

	bme280_write_standby_time(bme, BME280_TSB_0p5ms);  // tsb = 0.5ms
	bme280_write_filter_coefficient(bme, BME280_FC_16);   // IIR Filter coefficient 16
	bme280_write_oversampling_pressure(bme, BME280_OS16x);  // pressure x16
	bme280_write_oversampling_temperature(bme, BME280_OS2x);  // temperature x2
	bme280_write_oversampling_humidity(bme, BME280_OS1x);   // humidity x1

	bme280_write_mode(bme, BME280_MODE_NORMAL);
	bme280_set_loop_delay_us(bme,(uint32_t)500000);
}



int32_t bme280_compensate_T_int32(struct bme280_t *bme)
{
	int32_t var1, var2, T;

	var1 = ((((bme->adc_t >> 3) -((int32_t )bme->dig_T1 << 1))) * ((int32_t)bme->dig_T2)) >> 11;
	var2 = (((((bme->adc_t >> 4) - ((int32_t)bme->dig_T1)) * ((bme->adc_t >> 4) - ((int32_t)bme->dig_T1))) >> 12) * ((int32_t)bme->dig_T3)) >> 14;
	bme->t_fine = var1 + var2;
	T = (bme->t_fine * 5 + 128) >> 8;
	return T;
}




uint32_t bme280_compensate_P_int64(struct bme280_t *bme)
{
	int64_t var1, var2, p;

	var1 = ((int64_t )bme->t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)bme->dig_P6;
	var2 = var2 + (( var1 * (int64_t)bme->dig_P5) << 17);
	var2 = var2 + (((int64_t)bme->dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t)bme->dig_P3) >> 8) + ((var1 * (int64_t)bme->dig_P2) << 12);
	var1 = (((((int64_t)1)<<47)+var1)) * ((int64_t)bme->dig_P1) >> 33;
	if (var1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576 - bme->adc_p;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)bme->dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)bme->dig_P8) * p) >> 19;

	p = ((p + var1 + var2) >> 8) + (((int64_t)bme->dig_P7)<<4);
	return (uint32_t)p;
}




uint32_t bme280_compensate_P_int32(struct bme280_t *bme)
{
	int32_t var1, var2;
	uint32_t p;
	var1 = (((int32_t)bme->t_fine)>>1) - (int32_t)64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)bme->dig_P6);
	var2 = var2 + ((var1*((int32_t)bme->dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t)bme->dig_P4)<<16);
	var1 = (((bme->dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)bme->dig_P2) * var1)>>1))>>18;
	var1 =((((32768+var1))*((int32_t)bme->dig_P1))>>15);
	if (var1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	p = (((uint32_t)(((int32_t)1048576)- bme->adc_p)-(var2>>12)))*3125;
	if (p < 0x80000000) {
		p = (p << 1) / ((uint32_t)var1);
	} else {
		p = (p / (uint32_t)var1) * 2;
	}
	var1 = (((int32_t)bme->dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t)(p>>2)) * ((int32_t)bme->dig_P8))>>13;
	p = (uint32_t)((int32_t)p + ((var1 + var2 + bme->dig_P7) >> 4));
	return p;
}





uint32_t bme280_compensate_H_int32(struct bme280_t *bme)
{
	int32_t v_x1_u32r;
	v_x1_u32r = (bme->t_fine - ((int32_t)76800));
	v_x1_u32r = (((((bme->adc_h << 14) - (((int32_t)bme->dig_H4) << 20) - (((int32_t)bme->dig_H5) * v_x1_u32r)) +
	((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)bme->dig_H6)) >> 10) * (((v_x1_u32r *
	((int32_t)bme->dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
	((int32_t)bme->dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)bme->dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32_t)(v_x1_u32r>>12);
}





double   bme280_compensate_T_double(struct bme280_t *bme)
{
	double var1, var2, T;

	var1 = (((double)bme->adc_t)/16384.0 - ((double)bme->dig_T1)/1024.0) * ((double)bme->dig_T2);
	var2 = ((((double)bme->adc_t)/131072.0 - ((double)bme->dig_T1)/8192.0) *
	(((double)bme->adc_t)/131072.0 - ((double) bme->dig_T1)/8192.0)) * ((double)bme->dig_T3);
	bme->t_fine = (int32_t)(var1 + var2);
	T = (var1 + var2) / 5120.0;
	return T;
}





double   bme280_compensate_P_double(struct bme280_t * bme)
{
	double var1, var2, p;
	
	var1 = ((double) bme->t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)bme->dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)bme->dig_P5) * 2.0;
	var2 = (var2/4.0)+(((double)bme->dig_P4) * 65536.0);
	var1 = (((double)bme->dig_P3) * var1 * var1 / 524288.0 + ((double)bme->dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)bme->dig_P1);
	if (var1 == 0.0) {
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 - (double)bme->adc_p;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)bme->dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)bme->dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)bme->dig_P7)) / 16.0;
	return p;
}





double   bme280_compensate_H_double(struct bme280_t * bme)
{
	double var_H;
	 
	var_H = (((double) bme->t_fine) - 76800.0);
	var_H = (bme->adc_h - (((double)bme->dig_H4) * 64.0 + ((double)bme->dig_H5) / 16384.0 * var_H)) *
	          (((double)bme->dig_H2) / 65536.0 * (1.0 + ((double)bme->dig_H6) / 67108864.0 * var_H *
	          (1.0 + ((double)bme->dig_H3) / 67108864.0 * var_H)));
	var_H = var_H * (1.0 - ((double)bme->dig_H1) * var_H / 524288.0);
	if (var_H > 100.0) {
		var_H = 100.0;
	} else if (var_H < 0.0) {
		var_H = 0.0;
	}  
		return var_H;
}




float  bme280_get_temperature(struct bme280_t * bme) 
{
	return (float)bme280_compensate_T_int32(bme) / 100;
}



double bme280_get_temperature_most_accurate(struct bme280_t * bme) 
{
	return bme280_compensate_T_double(bme);
}



float bme280_get_humidity(struct bme280_t * bme) 
{
	return (float)bme280_compensate_H_int32(bme) / 1024;
}



double bme280_get_humidity_most_accurate(struct bme280_t * bme) 
{
	return bme280_compensate_H_double(bme);
}




float bme280_get_pressure(struct bme280_t * bme) 
{
	return (float)bme280_compensate_P_int32(bme) / 100;
}




float bme280_get_pressure_more_accurate(struct bme280_t * bme) 
{
	return (float)bme280_compensate_P_int64(bme) / 256 / 100;
} 




double bme280_get_pressure_most_accurate(struct bme280_t * bme) 
{
	return bme280_compensate_P_double(bme) / 100;
}





void bme280_write_standby_time(struct bme280_t * bme,uint8_t t_sb) 
{
	uint8_t conf;
	uint8_t i2c_addr;

	i2c_addr = bme->i2c_addr;
	conf = i2c_readReg(i2c_addr, BME280_REG_CONFIG);
	conf = conf & 0b00011111; 
	conf = conf | (t_sb << 5); 

	i2c_writeReg(i2c_addr, BME280_REG_CONFIG, conf);
}   



void bme280_write_filter_coefficient(struct bme280_t * bme,uint8_t fc) 
{

	uint8_t conf;
	uint8_t i2c_addr;
	i2c_addr = bme->i2c_addr;
	conf = i2c_readReg(i2c_addr, BME280_REG_CONFIG);
	// We want to change osrs_p which is bits 4,3,2
	conf = conf & 0b11100011; // mask out the bits we care about
	conf = conf | (fc << 2); // Set the magic bits
	i2c_writeReg(i2c_addr, BME280_REG_CONFIG, conf);
} 


void * bme280_pthread_loop(void *arg)
{
	struct bme280_t * bme;
	bme = (struct bme280_t *) arg;
	while( bme->thread_stop == 0){
		if(bme->mode == 0){
			if(bme->pre_mode != 0){
				bme280_write_mode(bme,BME280_MODE_SLEEP);
				bme->pre_mode = 0;
			}
		}
		else if(bme->mode == 3){
			bme280_write_mode(bme,BME280_MODE_NORMAL);
			if(bme->pre_mode != 3){
				bme280_write_mode(bme,BME280_MODE_NORMAL);
				bme->pre_mode = 3;
			}
			while(bme280_is_measuring(bme)) {;}
			bme280_read_measurements(bme);
		}
		else if(bme->mode == 1){
			bme->pre_mode = 1;
			bme280_write_mode(bme, BME280_MODE_FORCED );
			while(bme280_is_measuring(bme)) {;}
			bme280_read_measurements(bme);
		}

		usleep(bme->loop_delay_us);
	}
	//printf("bme280 pthread loop stop, and bme280 enter sleep mode.\n");
	DEBUGPRINTF("bme280 pthread loop stop, and bme280 enter sleep mode.\n");
	bme280_write_mode(bme, BME280_MODE_SLEEP);
	return 0;
}



// 
int bme280_pthread_run(struct bme280_t * bme, pthread_t * pth)
{
	int res;

	bme->thread_stop = 0;

	if(pth)
		res = pthread_create(pth, 0, bme280_pthread_loop, (void *) bme);
	else{
		fprintf(stderr,"error: empty pthread_t of bme280.\n");
		return -1;
	}

	if(res){
		fprintf(stderr, "error : pthread_create.\n");
		return -1;
	}
	return 0;
}

void bme280_set_loop_delay_us(struct bme280_t * bme, uint32_t delay_us)
{
	if(bme)
		bme->loop_delay_us = delay_us;
}

void bme280_show(struct bme280_t * bme)
{
	printf("-----------START--------------\n");
	printf("T:%6.2f *C, H:%6.2f%%, P:%6.2f hpa\n", 
			bme280_get_temperature(bme),
			bme280_get_humidity(bme),
			bme280_get_pressure(bme));
	printf("More Accurate measurement: \n");
	printf("P:%f\n", bme280_get_pressure_more_accurate(bme));
	printf("Most Accurate measurement: \n");
	printf("T:%f, H:%f, P:%f\n", 
			bme280_get_temperature_most_accurate(bme),
			bme280_get_humidity_most_accurate(bme),
			bme280_get_pressure_most_accurate(bme));
	printf("-----------END--------------\n");
}


void bme280_force_read_measurement(struct bme280_t * bme)
{
	bme280_write_mode(bme, BME280_MODE_FORCED);
	while(bme280_is_measuring(bme)){;}
	bme280_read_measurements(bme);
}
////////////////////////////////////////



