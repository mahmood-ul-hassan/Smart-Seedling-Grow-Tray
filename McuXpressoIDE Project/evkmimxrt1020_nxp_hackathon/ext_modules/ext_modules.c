/*
 * pwm_module.c
 *
 *  Created on: Jun 18, 2021
 *      Author: HASSAN
 */
#include <ext_modules.h>
#include <stdio.h>

#include "pca9685.h"
#include "ina219.h"
#include "ads1115.h"
#include "apds9930.h"
#include "DHT.h"
#include "board.h"
#include "pin_mux.h"

#include "fsl_lpi2c_cmsis.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Select OSC_CLK (24 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (1U)

#define I2C4           Driver_I2C4
#define I2C4_IRQ       LPI2C4_IRQn
#define I2C4_FREQ_FUNC LPI2C4_GetFreq
#define I2C4_FREQ      CLOCK_GetFreq(kCLOCK_OscClk) / LPI2C_CLOCK_SOURCE_DIVIDER

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool I2C4_CompletionFlag = false;

static PCA9685 pca9685_device;
static INA219 ina219_device;
static ADS1115 ads1115_device;
static DHT_config DHT_sensor;

float dht_readings[3];
float power_readings[3];
float adc_readings[4];
float als_reading;
uint16_t proximity_reading;
uint16_t pwm_readings[16];
bool COB_status;

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t I2C4_FREQ_FUNC(void)
{
    return I2C4_FREQ;
}

static void I2C4_InitTouchI2cClk(void)
{
    /* Set LPI2C_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    /* Set Lpi2c clock source. */
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
}

static void I2C4_SignalEvent(uint32_t event)
{
	/*
	switch (event)
    {
        // The master has sent a stop transition on the bus //
        case ARM_I2C_EVENT_TRANSFER_DONE:
        	I2C4_CompletionFlag = true;
            break;

        default:
            break;
    }
	*/
	I2C4_CompletionFlag = true;
}

void I2C4_Transmit(uint8_t slave_addr, uint8_t * txBuff, size_t bytestosend){
    /*  Reset master completion flag to false. */
	I2C4_CompletionFlag = false;

    /* Start transmitting I2C transfers on the LPI2C master peripheral */
	I2C4.MasterTransmit(slave_addr, txBuff, bytestosend, false);

    /*wait for master complete*/
    while (!I2C4_CompletionFlag)
    {
    }
}

void I2C4_Receive(uint8_t slave_addr, uint8_t * rxBuff, size_t bytestoread){
    /*  Reset master completion flag to false. */
	I2C4_CompletionFlag = false;

    /* Start transmitting I2C transfers on the LPI2C master peripheral */
	I2C4.MasterReceive(slave_addr, rxBuff, bytestoread, false);

    /*wait for master complete*/
    while (!I2C4_CompletionFlag)
    {
    }
}

void delay_us(uint32_t us){
	SDK_DelayAtLeastUs(us, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

void delay_ms(uint32_t ms){
	SDK_DelayAtLeastUs(ms * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

void init_ext_modules_i2c(void){
	/* The FreeRTOS kernel APIs are not used in I2C ISR, so the
	 * interrupt priority could be set to 0.
	 */
	NVIC_SetPriority(I2C4_IRQ, 0);

	I2C4_InitTouchI2cClk();

	/*Init I2C1 */
	I2C4.Initialize(I2C4_SignalEvent);
	I2C4.PowerControl(ARM_POWER_FULL);
	I2C4.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
}

/*Initialize PCA9685 PWM module*/
void pwm_module_begin(uint16_t pwm_feq)
{
	// Configure and Init PCA9685
    pca9685_getconfig(&pca9685_device);

    pca9685_device._i2cread = I2C4_Receive;
    pca9685_device._i2cwrite = I2C4_Transmit;
    pca9685_device._delay_ms = delay_ms;

    pca9685_init(&pca9685_device);

    pca9685_device._pwmfeq = pwm_feq;
    pca9685_setPWMFreq(&pca9685_device);
    for(uint8_t temp = 0; temp<16; temp++)
    	pwm_readings[temp]=pwm_module_getPWM(temp);
}

void pwm_module_setPWM(uint8_t ch, uint16_t duty_cycle){
	if(duty_cycle<4096){
		pwm_readings[ch]=duty_cycle;
		pca9685_setPWM(&pca9685_device, ch, 0, duty_cycle);
	}
	else{
		pwm_readings[ch]=4096;
		pca9685_setPWM(&pca9685_device, ch, 4096, 0);       // turns pin fully on
	}
}

uint16_t pwm_module_getPWM(uint8_t ch){
	static uint16_t pwm_val = 0;
	uint8_t* pwm_data;
	pwm_data = pca9685_getPWM(&pca9685_device, ch);
	if(pwm_data[3]&0x10){
		pwm_readings[ch]=0;
		return 0;
	}
	if(pwm_data[1]&0x10){
		pwm_readings[ch]=0x1000;
		return 0x1000;
	}
	pwm_val = ((uint16_t)pwm_data[3]<<8) & 0xff00;
	pwm_val += (uint16_t)pwm_data[2] & 0x00ff;
	pwm_readings[ch]=pwm_val;
	return pwm_val;
}

void pwm_module_setPWMFreq(uint16_t pwm_feq){
	pca9685_device._pwmfeq = pwm_feq;
    pca9685_setPWMFreq(&pca9685_device);
}

void pwm_module_DEMO(void){

  for (uint8_t pin=0; pin<16; pin++) {
	pca9685_setPWM(&pca9685_device, pin, 4096, 0);       // turns pin fully on
	delay_ms(500);
	pca9685_setPWM(&pca9685_device, pin, 0, 4096);       // turns pin fully off
	delay_ms(500);
  }
}

/*Initialize INA219 Power module*/
void power_module_begin(void){
	ina219_getconfig(&ina219_device);

	ina219_device._i2caddr = 0x41;
	ina219_device._i2cread = I2C4_Receive;
	ina219_device._i2cwrite = I2C4_Transmit;
	ina219_device._delay_ms = delay_ms;

	ina219_init(&ina219_device);		// 32V_2A
}
float power_module_voltage(void){
	return ina219_getBusVoltage_V(&ina219_device);
}
float power_module_current(void){
	return ina219_getCurrent_mA(&ina219_device);
}
float power_module_load(void){
	return ina219_getPower_mW(&ina219_device);
}

void power_module_Readings(void){
	power_readings[0] = ina219_getBusVoltage_V(&ina219_device);
	power_readings[1] = ina219_getCurrent_mA(&ina219_device);
	power_readings[2] = ina219_getPower_mW(&ina219_device);
}

/*Initialize INA219 Power module*/
void adc_module_begin(void){

	ads1115_device._i2cread = I2C4_Receive;
	ads1115_device._i2cwrite = I2C4_Transmit;
	ads1115_device._delay_ms = delay_ms;

	ADS1115_init(&ads1115_device);		// PGA: GAIN_TWOTHIRDS | SPS: 128 | Mode: Single-shot
}

float adc_module_readV(uint8_t ch){
	if(ch>3)
		return 0;

    switch (ch){
    	case 0:
    		return ADS1115_readADC(&ads1115_device, CH_0);
            break;
    	case 1:
    		return ADS1115_readADC(&ads1115_device, CH_1);
            break;
    	case 2:
    		return ADS1115_readADC(&ads1115_device, CH_2);
            break;
    	case 3:
    		return ADS1115_readADC(&ads1115_device, CH_3);
            break;

        default:
            break;
    }
}

uint16_t adc_module_read(uint8_t ch){
	if(ch>3)
		return 0;

    switch (ch){
    	case 0:
    		return ADS1115_readADC_raw(&ads1115_device, CH_0);
            break;
    	case 1:
    		return ADS1115_readADC_raw(&ads1115_device, CH_1);
            break;
    	case 2:
    		return ADS1115_readADC_raw(&ads1115_device, CH_2);
            break;
    	case 3:
    		return ADS1115_readADC_raw(&ads1115_device, CH_3);
            break;

        default:
            break;
    }
}

void adc_module_readings(void){
	adc_readings[0] = ADS1115_readADC(&ads1115_device, CH_0);
	adc_readings[1] = ADS1115_readADC(&ads1115_device, CH_1);
	adc_readings[2] = ADS1115_readADC(&ads1115_device, CH_2);
	adc_readings[3] = ADS1115_readADC(&ads1115_device, CH_3);
}


void als_module_begin(void){
	APDS9930_init(I2C4_Receive, I2C4_Transmit);
	enablePower();
	enableLightSensor(false);
	enableProximitySensor(false);
}

void als_module_ReadLight(float* als_value){
	readAmbientLightLuxF(als_value);
}

void als_module_ReadProximity(uint16_t* proximity_value){
	readProximity(proximity_value);
}

void als_module_Readings(void){
	readAmbientLightLuxF(&als_reading);
	readProximity(&proximity_reading);

	COB_status = (als_reading<5)?true:false;
}

void dht_module_begin(void){
    DHT_sensor._sensorType = DHT22;
    DHT_sensor._GPIOport=BOARD_INITPINS_DHT_GPIO_PORT;
    DHT_sensor._GPIOpin=BOARD_INITPINS_DHT_GPIO_PIN;
    DHT_sensor._MAXcycles=1000;
    DHT_sensor._delay_us=delay_us;
    DHT_sensor._CtoF = false;

    DHT_begin(&DHT_sensor);
}

void dht_module_read(float* dht_values){
	read_Temperature_Humidity(&DHT_sensor);
	computeHeatIndex(&DHT_sensor);
	dht_values[0] = DHT_sensor._temperature;
	dht_values[1] = DHT_sensor._humidity;
	dht_values[2] = DHT_sensor._heatindex;
}

void dht_module_readings(void){
	read_Temperature_Humidity(&DHT_sensor);
	computeHeatIndex(&DHT_sensor);
	dht_readings[0] = DHT_sensor._temperature;
	dht_readings[1] = DHT_sensor._humidity;
	dht_readings[2] = DHT_sensor._heatindex;
}

