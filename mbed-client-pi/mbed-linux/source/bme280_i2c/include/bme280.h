
#ifndef _BME280_H
#define _BME280_H

#ifdef __cplusplus
extern "C" {
#endif // def __cplusplus


#include<stdint.h>
#include<pthread.h>

#define BME280_REG_CALIB_START     0X88
#define BME280_REG_CHIP_ID         0XD0
#define BME280_REG_RESET           0XE0
#define BME280_REG_CALIB_START2    0XE1
#define BME280_REG_CTRL_HUM        0XF2
#define BME280_REG_STATUS          0XF3
#define BME280_REG_CTRL_MEAS       0XF4
#define BME280_REG_CONFIG          0XF5

#define BME280_REG_MEASURE_START 0XF7
#define BME280_REG_PRESS_MSB  0XF7
#define BME280_REG_PRESS_LSB  0XF8
#define BME280_REG_PRESS_XLSB 0XF9
#define BME280_REG_TEMP_MSB   0XFA
#define BME280_REG_TEMP_LSB   0XFB
#define BME280_REG_TEMP_XLSB  0XFC
#define BME280_REG_HUM_MSB    0XFD
#define BME280_REG_HUM_LSB    0XFE

struct bme280_t{
	uint8_t i2c_addr;
	uint32_t adc_h;
	uint32_t adc_t;
	uint32_t adc_p;

	uint16_t dig_T1;
	uint16_t dig_T2;
	uint16_t dig_T3;

	uint16_t dig_P1;
	uint16_t dig_P2;
	uint16_t dig_P3;
	uint16_t dig_P4;
	uint16_t dig_P5;
	uint16_t dig_P6;
	uint16_t dig_P7;
	uint16_t dig_P8;
	uint16_t dig_P9;

	uint16_t dig_H1;
	uint16_t dig_H2;
	uint16_t dig_H3;
	uint16_t dig_H4;
	uint16_t dig_H5;
	uint16_t dig_H6;

	uint32_t t_fine;
	int thread_stop;
	uint32_t loop_delay_us ;
	uint8_t mode;
	uint8_t pre_mode;
};


// -- BME280 compensation param Part
#define BME280_REG_T1 0x88
#define BME280_REG_T2 0x8A
#define BME280_REG_T3 0x8C
#define BME280_REG_P1 0x8E
#define BME280_REG_P2 0x90
#define BME280_REG_P3 0x92
#define BME280_REG_P4 0x94
#define BME280_REG_P5 0x96
#define BME280_REG_P6 0x98
#define BME280_REG_P7 0x9A
#define BME280_REG_P8 0x9C
#define BME280_REG_P9 0x9E
#define BME280_REG_H1 0xA1
#define BME280_REG_H2 0xE1
#define BME280_REG_H3 0xE3
#define BME280_REG_H4 0xE4
#define BME280_REG_H5 0xE5
#define BME280_REG_H6 0xE7

enum {
    BME280_DIG_T1 = 0,
    BME280_DIG_T2 = 1,
    BME280_DIG_T3 = 2,

    BME280_DIG_P1 = 3,
    BME280_DIG_P2 = 4,
    BME280_DIG_P3 = 5,
    BME280_DIG_P4 = 6,
    BME280_DIG_P5 = 7,
    BME280_DIG_P6 = 8,
    BME280_DIG_P7 = 9,
    BME280_DIG_P8 = 10,
    BME280_DIG_P9 = 11,

    BME280_DIG_H1 = 12,
    BME280_DIG_H2 = 13,
    BME280_DIG_H3 = 14,
    BME280_DIG_H4 = 15,
    BME280_DIG_H5 = 16,
    BME280_DIG_H6 = 17
    };           



enum {
	BME280_OS_SKIPPED,
	BME280_OS1x,
	BME280_OS2x,
	BME280_OS4x,
	BME280_OS8x,
	BME280_OS16x
};

enum{
	BME280_MODE_SLEEP,
	BME280_MODE_FORCED,
	BME280_MODE_NORMAL = 3
};

// bme280_write_standby_time(uint8_t t_sb) 
// t_sb
enum {
  BME280_TSB_0p5ms,
  BME280_TSB_62p5ms,
  BME280_TSB_125ms,
  BME280_TSB_250ms,
  BME280_TSB_500ms,
  BME280_TSB_1000ms,
  BME280_TSB_10ms,
  BME280_TSB_20ms
};



//bme280_write_filter_coefficient(uint8_t fc)
// fc
enum {
  BME280_FC_off,
  BME280_FC_2,
  BME280_FC_4,
  BME280_FC_8,
  BME280_FC_16
};




struct bme280_t * bme280_new(uint8_t i2c_addr);
void bme280_free(struct bme280_t * bme);
void bme280_initi(struct bme280_t *bme);
int  bme280_get_id(struct bme280_t * bme);
int  bme280_get_compensation_param(struct bme280_t * bme, int param);
int  bme280_read_compensation_param(struct bme280_t *bme);

void bme280_write_oversampling_pressure(struct bme280_t * bme, uint8_t bme280_os );
void bme280_write_oversampling_temperature(struct bme280_t * bme, uint8_t bme280_os );
void bme280_write_oversampling_humidity(struct bme280_t * bme, uint8_t bme280_os );
void bme280_write_mode(struct bme280_t * bme, uint8_t bme280_mode );
uint8_t bme280_is_measuring(struct bme280_t * bme);
void    bme280_read_measurements(struct bme280_t * bme);

void bme280_info(struct bme280_t *bme);
int32_t  bme280_compensate_T_int32(struct bme280_t * bme);
uint32_t bme280_compensate_P_int64(struct bme280_t * bme);
uint32_t bme280_compensate_P_int32(struct bme280_t * bme);
uint32_t bme280_compensate_H_int32(struct bme280_t * bme);

double   bme280_compensate_T_double(struct bme280_t * bme);
double   bme280_compensate_P_double(struct bme280_t * bme);
double   bme280_compensate_H_double(struct bme280_t * bme);

float  bme280_get_temperature(struct bme280_t * bme);
double bme280_get_temperature_most_accurate(struct bme280_t * bme);
float  bme280_get_humidity(struct bme280_t * bme);
double bme280_get_humidity_most_accurate(struct bme280_t * bme);
float  bme280_get_pressure(struct bme280_t * bme);
float  bme280_get_pressure_more_accurate(struct bme280_t * bme);
double bme280_get_pressure_most_accurate(struct bme280_t * bme);

void bme280_write_standby_time(struct bme280_t * bme,uint8_t t_sb);
void bme280_write_filter_coefficient(struct bme280_t * bme,uint8_t fc);
void * bme280_pthread_loop(void *arg);
int bme280_pthread_run(struct bme280_t * bme, pthread_t * pth);
void bme280_set_loop_delay_us(struct bme280_t * bme, uint32_t delay_us);
void bme280_show(struct bme280_t * bme);
void bme280_force_read_measurement(struct bme280_t * bme);

#ifdef __cplusplus
} // extern "C"
#endif // def __cplusplus

#endif 
