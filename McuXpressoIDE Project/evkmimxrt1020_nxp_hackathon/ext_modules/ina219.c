/*!
 * @file ina219.c
 *
 * twitter: @ArduinoEasy
 */

#include "ina219.h"
#include <stdio.h>
#include "fsl_common.h"

AT_NONCACHEABLE_SECTION_INIT(uint8_t ina219_txBuff[3]);
AT_NONCACHEABLE_SECTION_INIT(uint8_t ina219_rxBuff[2]);

static void ina219_wireWriteRegister(INA219 *ina219_module, uint8_t reg, uint16_t value);
static void ina219_wireReadRegister(INA219 *ina219_module, uint8_t reg, uint16_t *value);
static int16_t ina219_getBusVoltage_raw(INA219 *ina219_module);
static int16_t ina219_getShuntVoltage_raw(INA219 *ina219_module);
static int16_t ina219_getCurrent_raw(INA219 *ina219_module);
static int16_t ina219_getPower_raw(INA219 *ina219_module);


void ina219_wireWriteRegister (INA219 *ina219_module, uint8_t reg, uint16_t value){
	ina219_txBuff[0] = reg;
	ina219_txBuff[1] = (value >> 8);
	ina219_txBuff[2] = (value & 0xFF);

	ina219_module->_i2cwrite(ina219_module->_i2caddr, ina219_txBuff, 3);
}

void ina219_wireReadRegister(INA219 *ina219_module, uint8_t reg, uint16_t *value){
	ina219_txBuff[0] = reg;

	ina219_module->_i2cwrite(ina219_module->_i2caddr, ina219_txBuff, 1);
	ina219_module->_i2cread(ina219_module->_i2caddr, ina219_rxBuff, 2);
	*value = (ina219_rxBuff[0] << 8) | ina219_rxBuff[1];
}

void ina219_setCalibration_32V_2A(INA219 *ina219_module){
  ina219_module->_calValue = 4096;
  ina219_module->_currentDivider_mA = 10;  // Current LSB = 100uA per bit (1000/100 = 10)
  ina219_module->_powerMultiplier_mW = 2;     // Power LSB = 1mW per bit (2/1)

  ina219_wireWriteRegister(ina219_module, INA219_REG_CALIBRATION, ina219_module->_calValue);
  
  uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
  ina219_wireWriteRegister(ina219_module, INA219_REG_CONFIG, config);
}

void ina219_setCalibration_32V_1A(INA219 *ina219_module){
  ina219_module->_calValue = 10240;
  ina219_module->_currentDivider_mA = 25;      // Current LSB = 40uA per bit (1000/40 = 25)
  ina219_module->_powerMultiplier_mW = 1;         // Power LSB = 800mW per bit

  ina219_wireWriteRegister(ina219_module, INA219_REG_CALIBRATION, ina219_module->_calValue);

  uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
  ina219_wireWriteRegister(ina219_module, INA219_REG_CONFIG, config);
}

void ina219_setCalibration_16V_400mA(INA219 *ina219_module) {
  ina219_module->_calValue = 8192;
  ina219_module->_currentDivider_mA = 20;  // Current LSB = 50uA per bit (1000/50 = 20)
  ina219_module->_powerMultiplier_mW = 1;     // Power LSB = 1mW per bit

  ina219_wireWriteRegister(ina219_module, INA219_REG_CALIBRATION, ina219_module->_calValue);
  
  uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
                    INA219_CONFIG_GAIN_1_40MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
  ina219_wireWriteRegister(ina219_module, INA219_REG_CONFIG, config);
}


uint8_t _i2caddr;
uint32_t _calValue;
uint32_t _currentDivider_mA;
uint32_t _powerMultiplier_mW;
float _result;

void ina219_getconfig(INA219 *ina219_module){
	ina219_module->_i2caddr = INA219_ADDRESS;
	ina219_module->_calValue = 0;
	ina219_module->_currentDivider_mA = 0;
	ina219_module->_powerMultiplier_mW = 0;
	ina219_module->_result = 0.0;
}

void ina219_init(INA219 *ina219_module) {
	ina219_setCalibration_32V_2A(ina219_module);
}

static int16_t ina219_getBusVoltage_raw(INA219 *ina219_module) {
  uint16_t value;
  ina219_wireReadRegister(ina219_module,  INA219_REG_BUSVOLTAGE, &value);
  return (int16_t)((value >> 3) * 4);
}

static int16_t ina219_getShuntVoltage_raw(INA219 *ina219_module) {
  uint16_t value;
  ina219_wireReadRegister(ina219_module, INA219_REG_SHUNTVOLTAGE, &value);
  return (int16_t)value;
}

static int16_t ina219_getCurrent_raw(INA219 *ina219_module) {
  uint16_t value;
  ina219_wireWriteRegister(ina219_module, INA219_REG_CALIBRATION, ina219_module->_calValue);
  ina219_module->_delay_ms(1);
  ina219_wireReadRegister(ina219_module, INA219_REG_CURRENT, &value);
  return (int16_t)value;
}

static int16_t ina219_getPower_raw(INA219 *ina219_module) {
  uint16_t value;
  ina219_wireWriteRegister(ina219_module, INA219_REG_CALIBRATION, ina219_module->_calValue);
  ina219_module->_delay_ms(1);
  ina219_wireReadRegister(ina219_module, INA219_REG_POWER, &value);
  return (int16_t)value;
}

float ina219_getShuntVoltage_mV(INA219 *ina219_module) {
  int16_t value;
  value = ina219_getShuntVoltage_raw(ina219_module);
  ina219_module->_result = value;
  return value * 0.01;
}

float ina219_getBusVoltage_V(INA219 *ina219_module) {
  int16_t value = ina219_getBusVoltage_raw(ina219_module);
  ina219_module->_result = value;
  return value * 0.001;
}

float ina219_getCurrent_mA(INA219 *ina219_module) {
  float valueDec = ina219_getCurrent_raw(ina219_module);
  ina219_module->_result = valueDec;
  valueDec /= ina219_module->_currentDivider_mA;
  return valueDec;
}

float ina219_getPower_mW(INA219 *ina219_module) {
  float valueDec = ina219_getPower_raw(ina219_module);
  ina219_module->_result = valueDec;
  valueDec *= ina219_module->_powerMultiplier_mW;
  return valueDec;
}

