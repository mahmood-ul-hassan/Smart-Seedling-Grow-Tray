/*!
 * @file ads1115.c
 *
 * twitter: @ArduinoEasy
 */

#include <ads1115.h>
#include <stdio.h>
#include <stdlib.h>

#include "fsl_common.h"

AT_NONCACHEABLE_SECTION_INIT(uint8_t ads1115_txBuff[3]);
AT_NONCACHEABLE_SECTION_INIT(uint8_t ads1115_rxBuff[2]);

static void ADS1115_WriteRegister(ADS1115 *ads1115_module, uint8_t reg, uint16_t value);
static int16_t ADS1115_ReadRegister(ADS1115 *ads1115_module, uint8_t reg);
static float get_lsb_multiplier(adsGain_t gain);
//static uint32_t get_delay_usec(adsSPS_t sps);
static uint32_t get_delay_msec(adsSPS_t sps);
static uint16_t get_adc_config(ADS1115 *ads1115_module);

void ADS1115_WriteRegister (ADS1115 *ads1115_module, uint8_t reg, uint16_t value){
//	uint8_t data[3];
	ads1115_txBuff[0] = reg;
	ads1115_txBuff[1] = (value >> 8);
	ads1115_txBuff[2] = (value & 0xFF);

	ads1115_module->_i2cwrite(ads1115_module->m_i2cAddress, ads1115_txBuff, 3);
//	HAL_I2C_Write(ads1115_module->m_i2cAddress, ads1115_txBuff, sizeof(ads1115_txBuff), false);
}

int16_t ADS1115_ReadRegister(ADS1115 *ads1115_module, uint8_t reg){
//	uint8_t data[2];
	ads1115_txBuff[0] = reg;

	ads1115_module->_i2cwrite(ads1115_module->m_i2cAddress, ads1115_txBuff, 1);
	ads1115_module->_i2cread(ads1115_module->m_i2cAddress, ads1115_rxBuff, 2);
//	HAL_I2C_Write(ads1115_module->m_i2cAddress, &reg, 1, false);
//	HAL_I2C_Read(ads1115_module->m_i2cAddress, data, sizeof(data), false);

	return (ads1115_rxBuff[0] << 8) | ads1115_rxBuff[1];
}

float get_lsb_multiplier(adsGain_t gain){
	float lsb_multiplier=0;
  switch (gain) {
  case (GAIN_TWOTHIRDS):
    lsb_multiplier = 0.1875;
    break;
  case (GAIN_ONE):
    lsb_multiplier = 0.125;
    break;
  case (GAIN_TWO):
    lsb_multiplier = 0.0625;
    break;
  case (GAIN_FOUR):
    lsb_multiplier = 0.03125;
    break;
  case (GAIN_EIGHT):
    lsb_multiplier = 0.015625;
    break;
  case (GAIN_SIXTEEN):
    lsb_multiplier = 0.0078125;
    break;
	default:
    lsb_multiplier = 0.0625;
    break;
  }
	return lsb_multiplier;
}

/*
uint32_t get_delay_usec(adsSPS_t sps){
	uint32_t delay = 0;
  switch (sps) {
  case (SPS_8):
    delay = 125000;
    break;
  case (SPS_16):
    delay = 62500;
    break;
  case (SPS_32):
    delay = 31250;
    break;
  case (SPS_64):
    delay = 15625;
    break;
  case (SPS_128):
    delay = 7825;
    break;
  case (SPS_250):
    delay = 4000;
    break;
  case (SPS_475):
    delay = 2150;
    break;
  case (SPS_860):
    delay = 1200;
    break;
	default:
    delay = 7825;
    break;
  }
	return delay;
}
*/
uint32_t get_delay_msec(adsSPS_t sps){
	uint32_t delay = 0;
  switch (sps) {
  case (SPS_8):
    delay = 125;
    break;
  case (SPS_16):
    delay = 63;
    break;
  case (SPS_32):
    delay = 32;
    break;
  case (SPS_64):
    delay = 16;
    break;
  case (SPS_128):
    delay = 8;
    break;
  case (SPS_250):
    delay = 4;
    break;
  case (SPS_475):
    delay = 3;
    break;
  case (SPS_860):
    delay = 2;
    break;
	default:
    delay = 8;
    break;
  }
	return delay;
}

uint16_t get_adc_config(ADS1115 *ads1115_module){
	ads1115_module->m_conversionDelay = get_delay_msec(ads1115_module->m_samplingRate);
	ads1115_module->m_lsbMultiplier = get_lsb_multiplier(ads1115_module->m_gain)/1000;

  return
      ADS1115_REG_CONFIG_CQUE_NONE |    // Disable the comparator (default val)
      ADS1115_REG_CONFIG_CLAT_NONLAT |  // Non-latching (default val)
      ADS1115_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
      ads1115_module->m_compMode |							// Comparator Mode
      ads1115_module->m_samplingRate |					// Sampling Rate
      ads1115_module->m_gain |									// PGA Gain
      ads1115_module->m_mode;									// ADC mode
}

/**************************************************************************/
/*!
    @brief  Instantiates a new ADS1115 struct w/appropriate properties
    @param  Device struct
*/
/**************************************************************************/
void ADS1115_init(ADS1115 *ads1115_module){
	// Start with default values
	ads1115_module->m_i2cAddress = ADS1115_ADDRESS;

	ads1115_module->m_samplingRate = SPS_128;							// 128 samples per second (default)
	ads1115_module->m_mode 		= ADS1115_REG_CONFIG_MODE_SINGLE;	// Single-shot mode (default)
	ads1115_module->m_gain 		= GAIN_TWOTHIRDS;					// +/- 6.144V range (limited to VDD +0.3V max!)
	ads1115_module->m_compMode 	= CMODE_TRAD;						// Traditional comparator (default val)

  ads1115_module->config =
      ADS1115_REG_CONFIG_CQUE_NONE |    // Disable the comparator (default val)
      ADS1115_REG_CONFIG_CLAT_NONLAT |  // Non-latching (default val)
      ADS1115_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
      ads1115_module->m_compMode |				// Comparator Mode
      ads1115_module->m_samplingRate |			// Sampling Rate
      ads1115_module->m_gain |					// PGA Gain
      ads1115_module->m_mode;					// ADC mode

	ads1115_module->m_conversionDelay = (uint8_t)ADS1115_CONVERSIONDELAY;
}

/**************************************************************************/
/*!
    @brief  Reset a ADS1115
    @param  Device struct
*/
/**************************************************************************/
void ADS1115_reset(ADS1115 *ads1115_module){
//	uint8_t cmd = 0x06;
	ads1115_txBuff[0] = 0x06;

	ads1115_module->_i2cwrite(ads1115_module->m_i2cAddress, ads1115_txBuff, 1);
//	HAL_I2C_Write(ads1115_module->m_i2cAddress, &cmd, 1, false);
}

/**************************************************************************/
/*!
    @brief  Sets the gain and input voltage range
    @param gain gain setting to use
*/
/**************************************************************************/
void ADS1115_setGain(ADS1115 *ads1115_module, adsGain_t gain){
	ads1115_module->m_gain = gain;
}

/**************************************************************************/
/*!
    @brief  Gets a gain and input voltage range
    @return the gain setting
*/
/**************************************************************************/
adsGain_t ADS1115_getGain(ADS1115 *ads1115_module){
	return ads1115_module->m_gain;
}

/**************************************************************************/
/*!
    @brief  Sets the Sampling rate
		@param  sps: sampling rate to use
*/
/**************************************************************************/
void ADS1115_setSPS(ADS1115 *ads1115_module, adsSPS_t sps){
	ads1115_module->m_samplingRate = sps;
}

/**************************************************************************/
/*!
    @brief  Gets the Sampling rate
    @return the sampling rate
*/
/**************************************************************************/
adsSPS_t ADS1115_getSPS(ADS1115 *ads1115_module){
	return ads1115_module->m_samplingRate;
}

/**************************************************************************/
/*!
    @brief  Sets a ADC conversion mode setting
    @param  mode
*/
/**************************************************************************/
void ADS1115_setCONV(ADS1115 *ads1115_module, adsCONV_t mode){
	ads1115_module->m_mode = mode;
}

/**************************************************************************/
/*!
    @brief  Gets a ADC conversion mode setting
    @return the conversion setting
*/
/**************************************************************************/
adsCONV_t ADS1115_getCONV(ADS1115 *ads1115_module){
	return ads1115_module->m_mode;
}

/**************************************************************************/
/*!
    @brief  Gets a single-ended ADC reading from the specified channel
    @param channel ADC channel to read
    @return the ADC reading
*/
/**************************************************************************/
float ADS1115_readADC(ADS1115 *ads1115_module, adc_Ch_t channel){
  if ((channel & ~ADS1115_REG_CONFIG_MUX_MASK) != 0) {
    return 0;
  }

  uint16_t config = get_adc_config(ads1115_module);;
	config |= channel;
  config |= ADS1115_REG_CONFIG_OS_SINGLE;

	ads1115_module->config = config;

	uint16_t ret_val;
	do{
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}
	while( (ret_val & ADS1115_REG_CONFIG_OS_MASK) == ADS1115_REG_CONFIG_OS_BUSY);

	do{
		ADS1115_WriteRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG, config);
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}while( (ret_val & ADS1115_REG_CONFIG_MUX_MASK) != (config & ADS1115_REG_CONFIG_MUX_MASK) );

	ads1115_module->_delay_ms(ads1115_module->m_conversionDelay);

	do{
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}
	while( (ret_val & ADS1115_REG_CONFIG_OS_MASK) == ADS1115_REG_CONFIG_OS_BUSY);

	if(channel>ADS1115_REG_CONFIG_MUX_DIFF_2_3)
		return (float)abs(ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONVERT)) * ads1115_module->m_lsbMultiplier;
	else
		return (float)ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONVERT) * ads1115_module->m_lsbMultiplier;
}

/**************************************************************************/
/*!
    @brief  Gets a single-ended ADC reading from the specified channel
    @param channel ADC channel to read
    @return the ADC reading
*/
/**************************************************************************/
int16_t ADS1115_readADC_raw(ADS1115 *ads1115_module, adc_Ch_t channel){

  if ((channel & ~ADS1115_REG_CONFIG_MUX_MASK) != 0) {
    return 0;
  }

  uint16_t config = get_adc_config(ads1115_module);;
	config |= channel;
  config |= ADS1115_REG_CONFIG_OS_SINGLE;

	ads1115_module->config = config;

	uint16_t ret_val = ADS1115_REG_CONFIG_OS_BUSY;
	do{
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}
	while( (ret_val & ADS1115_REG_CONFIG_OS_MASK) == ADS1115_REG_CONFIG_OS_BUSY);

	do{
		ADS1115_WriteRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG, config);
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}while( (ret_val & ADS1115_REG_CONFIG_MUX_MASK) != (config & ADS1115_REG_CONFIG_MUX_MASK) );

	ads1115_module->_delay_ms(ads1115_module->m_conversionDelay);

	do{
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}
	while( (ret_val & ADS1115_REG_CONFIG_OS_MASK) == ADS1115_REG_CONFIG_OS_BUSY);

	return ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONVERT);
}

/**************************************************************************/
/*!
    @brief  Sets up the comparator to operate in basic mode, causing the
            ALERT/RDY pin to assert (go from high to low) when the ADC
            value exceeds the specified threshold.
            This will also set the ADC in continuous conversion mode.
    @param channel ADC channel to use
    @param threshold comparator threshold
*/
/**************************************************************************/
void ADS1115_startComparator_SingleEnded(ADS1115 *ads1115_module, uint8_t channel, int16_t threshold){
	// Start with default values
  uint16_t config =
      ADS1115_REG_CONFIG_CQUE_1CONV |   // Comparator enabled and asserts on 1 match
      ADS1115_REG_CONFIG_CLAT_LATCH |   // Latching mode
      ADS1115_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
      ads1115_module->m_compMode |							// Comparator Mode
      ads1115_module->m_samplingRate |					// Sampling Rate
			ads1115_module->m_gain |									// ADC gain setting
      ADS1115_REG_CONFIG_MODE_CONTIN;   // Continuous conversion mode

  // Set single-ended input channel
  switch (channel) {
  case (0):
    config |= ADS1115_REG_CONFIG_MUX_SINGLE_0;
    break;
  case (1):
    config |= ADS1115_REG_CONFIG_MUX_SINGLE_1;
    break;
  case (2):
    config |= ADS1115_REG_CONFIG_MUX_SINGLE_2;
    break;
  case (3):
    config |= ADS1115_REG_CONFIG_MUX_SINGLE_3;
    break;
  }

	ads1115_module->config = config;

  // Set the high threshold register
	ADS1115_WriteRegister(ads1115_module, ADS1115_REG_POINTER_HITHRESH, threshold);

  // Write config register to the ADC
  ADS1115_WriteRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG, config);
}

/**************************************************************************/
/*!
    @brief  In order to clear the comparator, we need to read the
            conversion results.  This function reads the last conversion
            results without changing the config value.
    @return the last ADC reading
*/
/**************************************************************************/
float ADS1115_getLastConversionResults(ADS1115 *ads1115_module){
	uint16_t ret_val = ADS1115_REG_CONFIG_OS_BUSY;
  // Wait for the conversion to complete
	ads1115_module->_delay_ms(ads1115_module->m_conversionDelay);
	do{
		ret_val = ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONFIG);
	}
	while( (ret_val & ADS1115_REG_CONFIG_OS_MASK) == ADS1115_REG_CONFIG_OS_BUSY);

  // Read the conversion results
	return (float)ADS1115_ReadRegister(ads1115_module, ADS1115_REG_POINTER_CONVERT) * ads1115_module->m_lsbMultiplier;
}

/************************************************************************/

