/*
 * pwm_module.h
 *
 *  Created on: Jun 18, 2021
 *      Author: HASSAN
 */

#ifndef EXT_MODULES_H_
#define EXT_MODULES_H_

#include <stdint.h>
#include <stdbool.h>

void init_ext_modules_i2c(void);

void pwm_module_begin(uint16_t pwm_feq);
uint16_t pwm_module_getPWM(uint8_t ch);
void pwm_module_setPWM(uint8_t ch, uint16_t duty_cycle);
void pwm_module_setPWMFreq(uint16_t pwm_feq);
void pwm_module_DEMO(void);

void power_module_begin(void);
float power_module_voltage(void);		//V
float power_module_current(void);		//mA
float power_module_load(void);			//mW
void power_module_Readings(void);

/*
// ADC channels //
typedef enum {
	CH0 = (0x4000),
	CH1 = (0x5000),
	CH2 = (0x6000),
	CH3 = (0x7000),
} ads1115_Ch_t;

float adc_module_readV(ads1115_Ch_t ch);
uint16_t adc_module_read(ads1115_Ch_t ch);
*/

void adc_module_begin(void);
float adc_module_readV(uint8_t ch);
uint16_t adc_module_read(uint8_t ch);
void adc_module_readings(void);

void als_module_begin(void);
void als_module_ReadLight(float* als_value);
void als_module_ReadProximity(uint16_t* proximity_value);
void als_module_Readings(void);

void dht_module_begin(void);
void dht_module_read(float* dht_values);
void dht_module_readings(void);

#endif /* EXT_MODULES_H_ */
