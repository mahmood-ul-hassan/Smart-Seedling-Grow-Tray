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

#include "DHT.h"
#include <math.h>

#define abs(arg) (arg<0)? arg*(-1):arg

static uint8_t data[5];

static uint32_t expectPulse(DHT_config* DHT, uint8_t level);

#define TIMEOUT -1        /**< timeout on */

#define HIGH 1
#define LOW 0

/* GPIO configuration of DHT GPIO pin */
gpio_pin_config_t DHT_GPIO_config = {
  .direction = kGPIO_DigitalOutput,
  .outputLogic = 0U,
  .interruptMode = kGPIO_NoIntmode
};

/*******************************************************************************
* Function Name: DHT_begin
****************************************************************************//**
*
* Validate the DHT sensor configuration.
*
* \param DHT
* The pointer to the DHT_config instance.
*
* \return
* \ref DHT_status:	DHT_SUCCESS if configuration is OK
*
* \note
* DHT_begin function can be ingored.
*
*******************************************************************************/
DHT_status DHT_begin(DHT_config* DHT){
    DHT->_temperature = 999;
    DHT->_humidity = 999;
    DHT->_heatindex = 999;
    DHT->_updated = false;

	if( (DHT->_sensorType != DHT11) && (DHT->_sensorType != DHT12) && (DHT->_sensorType != DHT21) && (DHT->_sensorType != DHT22) && (DHT->_sensorType != AM2301)){
		return INVALID_SENSOR;
	}
	if((DHT->_GPIOport != GPIO1) && (DHT->_GPIOport != GPIO2) && (DHT->_GPIOport != GPIO3) && (DHT->_GPIOport != GPIO5)){
		return INVALID_PORT;
	}
	if(DHT->_GPIOpin > 32U){
		return INVALID_PIN;
	}
	return DHT_SUCCESS;
}

/*******************************************************************************
* Function Name: read_Temperature_Humidity
****************************************************************************//**
*
* Read the sensor values and store the values in temperature and humidity parameters of DHT instance.
* If the new values are read then DHT->update parameter will be set to TRUE otherwise FALSE.
* Consecutive temperature and humidity reading can only be read after certain minimum delay. (consult sensor datasheet)
*
*
* \param DHT
* The pointer to the DHT_config instance.
*
* \return
* \ref: NULL
*
* \note
* Only call this function after a certain minimum delay menioned in DHT sensor datasheet.
*
*******************************************************************************/
void read_Temperature_Humidity(DHT_config* DHT){
  float DHT_temperature = 999;
  float DHT_humidity = 999;
  if (DHT_read(DHT)) {
    switch (DHT->_sensorType) {
    case DHT11:
    	DHT_temperature = data[2];
    	if (data[3] & 0x80) {
			DHT_temperature = -1 - DHT_temperature;
    	}
    	DHT_temperature += (data[3] & 0x0f) * 0.1;
    	if (DHT->_CtoF) {
    		DHT_temperature = convertCtoF(DHT_temperature);
    	}
		DHT_humidity = data[0] + data[1] * 0.1;
    	break;
    case DHT12:
    	DHT_temperature = data[2];
    	DHT_temperature += (data[3] & 0x0f) * 0.1;
    	if (data[2] & 0x80) {
    		DHT_temperature *= -1;
    	}
    	if (DHT->_CtoF) {
    		DHT_temperature = convertCtoF(DHT_temperature);
    	}
		DHT_humidity = data[0] + data[1] * 0.1;
    	break;
    case DHT22:
    case DHT21:
    	DHT_temperature = ((uint16_t)(data[2] & 0x7F)) << 8 | data[3];
    	DHT_temperature *= 0.1;
    	if (data[2] & 0x80) {
    		DHT_temperature *= -1;
    	}
    	if (DHT->_CtoF) {
    		DHT_temperature = convertCtoF(DHT_temperature);
    	}
		DHT_humidity = ((uint16_t)data[0]) << 8 | data[1];
		DHT_humidity *= 0.1;
    	break;
    }
    DHT->_temperature = DHT_temperature;
    DHT->_humidity = DHT_humidity;
  }
}

/*******************************************************************************
* Function Name: convertCtoF
****************************************************************************//**
*
* Convert the temperature value from centigrade to fahrenheit
*
*
* \param c (float)
* Temperature Value in Centigrade
*
* \return
* \ref: Temperature Value in Fahrenheit (float)
*
* \note
*
*
*******************************************************************************/
float convertCtoF(float c){
	return c * 1.8 + 32;
}

/*******************************************************************************
* Function Name: convertFtoC
****************************************************************************//**
*
* Convert the temperature value from fahrenheit to centigrade
*
*
* \param f (float)
* Temperature Value in Fahrenheit
*
* \return
* \ref: Temperature Value in Centigrade (float)
*
* \note
*
*
*******************************************************************************/
float convertFtoC(float f){
	return (f - 32) * 0.55555;
}

/*******************************************************************************
* Function Name: readHeatIndex
****************************************************************************//**
*
* Read the sensor values and store the values in temperature and humidity parameters of DHT instance.
* Then calculate the heat index based on temperature and humidity values. (Calculations are used from Adafruit DHT sensor library for Arduino).
* Consecutive heat index reading can only be read after certain minimum delay. (consult sensor datasheet)
* If this function is unable to read new values then it will calculate the heat index based on previous readings
* otherwise update the heat_index parameter of DHT instance to 999.
*
* \param DHT
* The pointer to the DHT_config instance.
*
* \return
* \ref: NULL
*
* \note
* Only call this function after a certain minimum delay menioned in DHT sensor datasheet.
*
*******************************************************************************/
void readHeatIndex(DHT_config* DHT) {
	read_Temperature_Humidity(DHT);
	if((DHT->_updated) || ((DHT->_temperature !=999) && (DHT->_humidity !=999)))
		computeHeatIndex(DHT);
	else
		DHT->_heatindex = 999;
}

/*******************************************************************************
* Function Name: computeHeatIndex
****************************************************************************//**
*
* Function to calculate the heat index based on temperature and humidity values. (Calculations are used from Adafruit DHT sensor library for Arduino).
* This function checks if temperature and humidity values are valid then it will calculate the heat index based
* otherwise update the heat_index parameter of DHT instance to 999.
*
* \param DHT
* The pointer to the DHT_config instance.
*
* \return
* \ref: NULL
*
* \note
*
*
*******************************************************************************/
void computeHeatIndex(DHT_config* DHT) {
	float heat_index;

	if((DHT->_temperature !=999) && (DHT->_humidity !=999)){

		if (!DHT->_CtoF)
			DHT->_temperature = convertCtoF(DHT->_temperature);

		heat_index = 0.5 * (DHT->_temperature + 61.0 + ((DHT->_temperature - 68.0) * 1.2) + (DHT->_humidity * 0.094));

		if (heat_index > 79) {
			heat_index = -42.379 + 2.04901523 * DHT->_temperature + 10.14333127 * DHT->_humidity +
						 -0.22475541 * DHT->_temperature * DHT->_humidity +
						 -0.00683783 * pow(DHT->_temperature, 2) +
						 -0.05481717 * pow(DHT->_humidity, 2) +
						  0.00122874 * pow(DHT->_temperature, 2) * DHT->_humidity +
						  0.00085282 * DHT->_temperature * pow(DHT->_humidity, 2) +
						 -0.00000199 * pow(DHT->_temperature, 2) * pow(DHT->_humidity, 2);

		if ((DHT->_humidity < 13) && (DHT->_temperature >= 80.0) && (DHT->_temperature <= 112.0))
			heat_index -= ((13.0 - DHT->_humidity) * 0.25) * sqrt((17.0 - abs(DHT->_temperature - 95.0)) * 0.05882);

		else if ((DHT->_humidity > 85.0) && (DHT->_temperature >= 80.0) && (DHT->_temperature <= 87.0))
			heat_index += ((DHT->_humidity - 85.0) * 0.1) * ((87.0 - DHT->_temperature) * 0.2);
	  }

		DHT->_heatindex = DHT->_CtoF ? heat_index : convertFtoC(heat_index);
		DHT->_temperature = convertFtoC(DHT->_temperature);
	}
	else
		DHT->_heatindex = 999;
}

/*******************************************************************************
* Function Name: DHT_read
****************************************************************************//**
*
* Function to read the temperature and humidity values of DHT sensors based on its type selected in DHT instance
* (Calculations are used from Adafruit DHT sensor library for Arduino).
* This function checks if temperature and humidity values are valid if true then change the DHT->_updated parameter to TRUE
* otherwise FALSE
*
* \param DHT
* The pointer to the DHT_config instance.
*
* \return
* \ref: DHT->_updated
* 		true - pass ; false - failed
*
* \note
* Only call this function after a certain minimum delay menioned in DHT sensor datasheet.
*
*******************************************************************************/
uint8_t DHT_read(DHT_config* DHT) {
	// Reset 40 bits of received data to zero.
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	// Send start signal.  See DHT datasheet for full signal diagram:
	//   http://www.adafruit.com/datasheets/Digital%20humidity%20and%20temperature%20sensor%20AM2302.pdf

	// Go into high impedence state to let pull-up raise data line level and
	// start the reading process.

	/* Initialize DHT GPIO pin as output */
	DHT_GPIO_config.direction = kGPIO_DigitalOutput;
	GPIO_PinInit(DHT->_GPIOport, DHT->_GPIOpin, &DHT_GPIO_config);


	GPIO_PinWrite(DHT->_GPIOport, DHT->_GPIOpin, 1U);
	DHT->_delay_us(1000U);

	// First set data line low for a period according to sensor type
	GPIO_PinWrite(DHT->_GPIOport, DHT->_GPIOpin, 0U);

	switch (DHT->_sensorType) {
	case DHT22:
	case DHT21:
		DHT->_delay_us(1100U); // data sheet says "at least 1ms"
		break;
	case DHT11:
	default:
		DHT->_delay_us(20000U); // data sheet says at least 18ms, 20ms just to be safe
		break;
	}

	uint32_t cycles[80];

	// End the start signal by setting data line high for 40 microseconds.
	DHT_GPIO_config.direction = kGPIO_DigitalInput;
	GPIO_PinInit(DHT->_GPIOport, DHT->_GPIOpin, &DHT_GPIO_config);

    // Delay a moment to let sensor pull data line low.
	DHT->_delay_us(55U);

	// Now start reading the data line to get the value from the DHT sensor.

    // Turn off interrupts temporarily because the next sections
    // are timing critical and we don't want any interruptions.
	__disable_irq();

    // First expect a low signal for ~80 microseconds followed by a high signal
    // for ~80 microseconds again.
    if (expectPulse(DHT, LOW) == TIMEOUT) {
        DHT->_updated = false;
		return DHT->_updated;
    }
    if (expectPulse(DHT, HIGH) == TIMEOUT) {
        DHT->_updated = false;
		return DHT->_updated;
    }

    // Now read the 40 bits sent by the sensor.  Each bit is sent as a 50
    // microsecond low pulse followed by a variable length high pulse.  If the
    // high pulse is ~28 microseconds then it's a 0 and if it's ~70 microseconds
    // then it's a 1.  We measure the cycle count of the initial 50us low pulse
    // and use that to compare to the cycle count of the high pulse to determine
    // if the bit is a 0 (high state cycle count < low state cycle count), or a
    // 1 (high state cycle count > low state cycle count). Note that for speed
    // all the pulses are read into a array and then examined in a later step.
	for (int i = 0; i < 80; i += 2) {
		cycles[i] = expectPulse(DHT, LOW);
		cycles[i + 1] = expectPulse(DHT, HIGH);
	}
    // Timing critical code is now complete.

    /* enable interrupts */
    __enable_irq();

	// Inspect pulses and determine which ones are 0 (high state cycle count < low
	// state cycle count), or 1 (high state cycle count > low state cycle count).
	for (int i = 0; i < 40; ++i) {
		uint32_t lowCycles = cycles[2 * i];
		uint32_t highCycles = cycles[2 * i + 1];
		if ((lowCycles == TIMEOUT) || (highCycles == TIMEOUT)) {
			return DHT->_updated;
		}
		data[i / 8] <<= 1;
		// Now compare the low and high cycle times to see if the bit is a 0 or 1.
		if (highCycles > lowCycles) {
			// High cycles are greater than 50us low cycle count, must be a 1.
			data[i / 8] |= 1;
		}
		// Else high cycles are less than (or equal to, a weird case) the 50us low
		// cycle count so this must be a zero.  Nothing needs to be changed in the
		// stored data.
	}
	// Check we read 40 bits and that the checksum matches.
	if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
	    DHT->_updated = true;
		return DHT->_updated;
	} else {
        DHT->_updated = false;
		return DHT->_updated;
	}
}

/*******************************************************************************
* Function Name: DHT_read
****************************************************************************//**
*
* Function to check for the incoming voltage level and return number of loop cycle which are used to determine the
* incoming data bit either 0 or 1.
*
* \param DHT
* The pointer to the DHT_config instance.
*
* \param level
* Expected signal level on MCU input
*
* \return
* \ref: count (uint32_t)
*		number of cycles taked to get level
*		-1 in case of TIMEOUT
*
* \note
*
*
*******************************************************************************/
// Expect the signal line to be at the specified level for a period of time and
// return a count of loop cycles spent at that level (this cycle count can be
// used to compare the relative time of two pulses).  If more than a millisecond
// Elapses without the level changing then the call fails with a 0 response.
static uint32_t expectPulse(DHT_config* DHT, uint8_t level) {
  uint32_t count = 0;
  while (GPIO_PinRead(DHT->_GPIOport, DHT->_GPIOpin) == level) {
    if (count++ >= DHT->_MAXcycles) {
      return TIMEOUT; // Exceeded timeout, fail.
    }
  }
  return count;
}
