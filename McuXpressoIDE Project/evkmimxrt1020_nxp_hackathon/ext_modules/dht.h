/*!
 *  @file DHT.h
 *
 *  This is a library for DHT series of low cost temperature/humidity sensors.
 *
 *  This library is inspired from Adafruit DHT Sensor Library library for arduinos.
 *
 *  Written by ArduinoEasy.
 *
 *  Twitter: @ArduinoEasy
 *
 */

#ifndef DHT_H_
#define DHT_H_

#include "fsl_gpio.h"

/* Define types of sensors. */
#define DHT11 11 /**< DHT TYPE 11 */
#define DHT12 12 /**< DHY TYPE 12 */
#define DHT22 22 /**< DHT TYPE 22 */
#define DHT21 21 /**< DHT TYPE 21 */
#define AM2301 21 /**< AM2301 */

typedef enum {
	DHT_ERROR = 0,
	DHT_SUCCESS,
	INVALID_SENSOR,
	INVALID_PORT,
	INVALID_PIN,
	INVALID_PIN_CONFIGURATION
}DHT_status;

typedef void (*Delay_us_t)(uint32_t delay_us);

typedef struct {
    float _temperature;
    float _humidity;
    float _heatindex;
    GPIO_Type* _GPIOport;
    uint32_t _GPIOpin;
    uint32_t _MAXcycles;	// 1 millisecond timeout for reading pulses from DHT sensor.
    uint8_t _CtoF;
    uint8_t _sensorType;
    uint8_t _updated;
    Delay_us_t _delay_us;
}DHT_config;

DHT_status DHT_begin(DHT_config* DHT);

void read_Temperature_Humidity(DHT_config* DHT);

float convertCtoF(float);
float convertFtoC(float);

void readHeatIndex(DHT_config* DHT);
void computeHeatIndex(DHT_config* DHT);

uint8_t DHT_read (DHT_config* DHT);

#endif /* DHT_H_ */
