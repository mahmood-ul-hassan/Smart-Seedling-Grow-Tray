/**
 * @file    apds9930.c
 *
 * APDS-9930 current draw tests (default parameters):
 *   Off:                   1mA
 *   Waiting for gesture:   14mA
 *   Gesture in progress:   35mA
 */
 
#include <apds9930.h>

#include "fsl_common.h"

AT_NONCACHEABLE_SECTION_INIT(uint8_t apds9930_txBuff[2]);
AT_NONCACHEABLE_SECTION_INIT(uint8_t apds9930_rxBuff[1]);

static I2C_read_t HAL_I2C_Read;
static I2C_write_t HAL_I2C_Write;


static bool read_byte(uint8_t reg, uint8_t *val);
static bool write_byte(uint8_t reg, uint8_t val);
static bool write_cmd(uint8_t val);


/************************************************************************/
bool APDS9930_init(I2C_read_t _i2cread, I2C_write_t _i2cwrite){

	HAL_I2C_Read = _i2cread;
	HAL_I2C_Write = _i2cwrite;

	uint8_t id;
	
	if( !read_byte(APDS9930_ID, &id) ) {
		return false;
	}
	if( !(id == APDS9930_ID_1 || id == APDS9930_ID_2) ) {
			return false;
	}
	if( !setMode(ALL, OFF) ) {
			return false;
	}
	/* Set default values for ambient light and proximity registers */
	if( !write_byte(APDS9930_ATIME, DEFAULT_ATIME) ) {
			return false;
	}
	if( !write_byte(APDS9930_WTIME, DEFAULT_WTIME) ) {
			return false;
	}
	if( !write_byte(APDS9930_PPULSE, DEFAULT_PPULSE) ) {
			return false;
	}
	if( !write_byte(APDS9930_POFFSET, DEFAULT_POFFSET) ) {
			return false;
	}
	if( !write_byte(APDS9930_CONFIG, DEFAULT_CONFIG) ) {
			return false;
	}
	if( !setLEDDrive(DEFAULT_PDRIVE) ) {
			return false;
	}
	if( !setProximityGain(DEFAULT_PGAIN) ) {
			return false;
	}
	if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
			return false;
	}
	if( !setProximityDiode(DEFAULT_PDIODE) ) {
			return false;
	}
	if( !setLightIntLowThreshold(DEFAULT_AILT) ) {
			return false;
	}
	if( !setLightIntHighThreshold(DEFAULT_AIHT) ) {
			return false;
	}
	if( !setProximityIntLowThreshold(DEFAULT_PILT) ) {
			return false;
	}
	if( !setProximityIntHighThreshold(DEFAULT_PIHT) ) {
			return false;
	}
	if( !write_byte(APDS9930_PERS, DEFAULT_PERS) ) {
			return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool setMode(uint8_t mode, uint8_t enable){
	uint8_t reg_val;

	/* Read current ENABLE register */
	reg_val = getMode();
	if( reg_val == ERROR ) {
			return false;
	}
	
	/* Change bit(s) in ENABLE register */
	enable = enable & 0x01;
	if( mode <= 6 ) {
		if (enable) {
				reg_val |= (1 << mode);
		} else {
				reg_val &= ~(1 << mode);
		}
	}
	else if( mode == ALL ) {
		if (enable) {
				reg_val = 0x7F;
		} else {
				reg_val = 0x00;
		}
	}
			
	/* Write value back to ENABLE register */
	if( !write_byte(APDS9930_ENABLE, reg_val) ) {
			return false;
	}
			
	return true;
}

//////////////////////////////////////////////////////////////////////////
uint8_t getMode(){
	uint8_t enable_value;
	/* Read current ENABLE register */
	if( !read_byte(APDS9930_ENABLE, &enable_value) ) {
			return ERROR;
	}
	return enable_value;
}

/************************************************************************/

/************************************************************************/
bool enablePower(void){
	if( !setMode(POWER, 1) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool disablePower(void){
	if( !setMode(POWER, 0) ) {
		return false;
	}
	return true;
}
/************************************************************************/

/************************************************************************/
bool enableLightSensor(bool interrupts){
	/* Set default gain, interrupts, enable power, and enable sensor */
	if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
		return false;
	}
	if( interrupts ) {
		if( !setAmbientLightIntEnable(1) ) {
			return false;
		}
	}
	else {
		if( !setAmbientLightIntEnable(0) ) {
			return false;
		}
	}
	if( !enablePower() ){
		return false;
	}
	if( !setMode(AMBIENT_LIGHT, 1) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool disableLightSensor(void){
	if( !setAmbientLightIntEnable(0) ) {
		return false;
	}
	if( !setMode(AMBIENT_LIGHT, 0) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool enableProximitySensor(bool interrupts){
	/* Set default gain, LED, interrupts, enable power, and enable sensor */
	if( !setProximityGain(DEFAULT_PGAIN) ) {
		return false;
	}
	if( !setLEDDrive(DEFAULT_PDRIVE) ) {
		return false;
	}
	if( interrupts ) {
		if( !setProximityIntEnable(1) ) {
			return false;
		}
	}
	else {
		if( !setProximityIntEnable(0) ) {
			return false;
		}
	}
	if( !enablePower() ){
		return false;
	}
	if( !setMode(PROXIMITY, 1) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool disableProximitySensor(void){
	if( !setProximityIntEnable(0) ) {
		return false;
	}
	if( !setMode(PROXIMITY, 0) ) {
		return false;
	}
	return true;
}
/************************************************************************/

/************************************************************************/
uint8_t getLEDDrive(){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return ERROR;
	}
	
	/* Shift and mask out LED drive bits */
//	val = (val >> 6) & 0b00000011;
	val = (val >> 6) & 0x03;
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setLEDDrive(uint8_t drive){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return false;
	}
	
	/* Set bits in register to given value */
//	drive &= 0b00000011;
	drive &= 0x03;
	drive = drive << 6;
//	val &= 0b00111111;
	val &= 0x3F;
	val |= drive;
	
	/* Write register value back into CONTROL register */
	if( !write_byte(APDS9930_CONTROL, val) ) {
		return false;
	}
	return true;
}
/************************************************************************/

/************************************************************************/
bool setProximityGain(uint8_t gain){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return false;
	}
	
	/* Set bits in register to given value */
//	drive &= 0b00000011;
	gain &= 0x03;
	gain = gain << 2;
//	val &= 0b11110011;
	val &= 0xF3;
	val |= gain;
	
	/* Write register value back into CONTROL register */
	if( !write_byte(APDS9930_CONTROL, val) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
uint8_t getProximityGain(){
	uint8_t val;

	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return ERROR;
	}

	/* Shift and mask out PDRIVE bits */
//	val = (val >> 2) & 0b00000011;
	val = (val >> 2) & 0x03;
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setAmbientLightGain(uint8_t gain){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return false;
	}
	
	/* Set bits in register to given value */
//	gain &= 0b00000011;
	gain &= 0x03;
//	val &= 0b11111100;
	val &= 0xFC;
	val |= gain;
	
	/* Write register value back into CONTROL register */
	if( !write_byte(APDS9930_CONTROL, val) ) {
		return false;
	}
	
	return true;
}
//////////////////////////////////////////////////////////////////////////
uint8_t getAmbientLightGain(){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
			return ERROR;
	}
	
	/* Shift and mask out ADRIVE bits */
//	val &= 0b00000011;
	val &= 0x03;
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setProximityDiode(uint8_t gain){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return false;
	}
	
	/* Set bits in register to given value */
//	gain &= 0b00000011;
	gain &= 0x03;
	gain = gain << 4;
//	val &= 0b11001111;
	val &= 0xCF;
	val |= gain;
	
	/* Write register value back into CONTROL register */
	if( !write_byte(APDS9930_CONTROL, val) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
uint8_t getProximityDiode(){
	uint8_t val;
	
	/* Read value from CONTROL register */
	if( !read_byte(APDS9930_CONTROL, &val) ) {
		return ERROR;
	}
	
	/* Shift and mask out PDRIVE bits */
//	val = (val >> 4) & 0b00000011;
	val = (val >> 4) & 0x03;
	return val;
}

/************************************************************************/

/************************************************************************/
uint8_t getAmbientLightIntEnable(void){
	uint8_t val;
	
	/* Read value from ENABLE register */
	if( !read_byte(APDS9930_ENABLE, &val) ) {
		return ERROR;
	}
	/* Shift and mask out AIEN bit */
//	val = (val >> 4) & 0b00000001;
	val = (val >> 4) & 0x01;
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setAmbientLightIntEnable(uint8_t enable){
	uint8_t val;
	
	/* Read value from ENABLE register */
	if( !read_byte(APDS9930_ENABLE, &val) ) {
		return false;
	}
	
	/* Set bits in register to given value */
//	enable &= 0b00000001;
	enable &= 0x01;
	enable = enable << 4;
//  val &= 0b11101111;
	val &= 0xEF;
	val |= enable;
	
	/* Write register value back into ENABLE register */
	if( !write_byte(APDS9930_ENABLE, val) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
uint8_t getProximityIntEnable(void){
	uint8_t val;
	
	/* Read value from ENABLE register */
	if( !read_byte(APDS9930_ENABLE, &val) ) {
		return ERROR;
	}
	/* Shift and mask out AIEN bit */
//	val = (val >> 5) & 0b00000001;
	val = (val >> 5) & 0x01;
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setProximityIntEnable(uint8_t enable){
	uint8_t val;
	
	/* Read value from ENABLE register */
	if( !read_byte(APDS9930_ENABLE, &val) ) {
		return false;
	}
	
	/* Set bits in register to given value */
//	enable &= 0b00000001;
	enable &= 0x01;
	enable = enable << 5;
//  val &= 0b11011111;
	val &= 0xDF;
	val |= enable;
	
	/* Write register value back into ENABLE register */
	if( !write_byte(APDS9930_ENABLE, val) ) {
		return false;
	}
	return true;
}
/************************************************************************/

/************************************************************************/
bool clearAmbientLightInt(void){
	if( !write_cmd(CLEAR_ALS_INT) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool clearProximityInt(void){
	if( !write_cmd(CLEAR_PROX_INT) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool clearAllInts(void){
	if( !write_cmd(CLEAR_ALL_INTS) ) {
		return false;
	}
	return true;
}
/************************************************************************/

/************************************************************************/
bool setLightIntLowThreshold(uint16_t threshold){
	uint8_t val_low;
	uint8_t val_high;
	
	/* Break 16-bit threshold into 2 8-bit values */
	val_low = threshold & 0x00FF;
	val_high = (threshold & 0xFF00) >> 8;
	
	/* Write low byte */
	if( !write_byte(APDS9930_AILTL, val_low) ) {
		return false;
	}
	
	/* Write high byte */
	if( !write_byte(APDS9930_AILTH, val_high) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool getLightIntLowThreshold(uint16_t *threshold){
	uint8_t val_byte;
	*threshold = 0;
	
	/* Read value from ambient light low threshold, low byte register */
	if( !read_byte(APDS9930_AILTL, &val_byte) ) {
		return false;
	}
	*threshold = val_byte;
	
	/* Read value from ambient light low threshold, high byte register */
	if( !read_byte(APDS9930_AILTH, &val_byte) ) {
		return false;
	}
	*threshold = *threshold + ((uint16_t)val_byte << 8);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool setLightIntHighThreshold(uint16_t threshold){
	uint8_t val_low;
	uint8_t val_high;
	
	/* Break 16-bit threshold into 2 8-bit values */
	val_low = threshold & 0x00FF;
	val_high = (threshold & 0xFF00) >> 8;
	
	/* Write low byte */
	if( !write_byte(APDS9930_AIHTL, val_low) ) {
		return false;
	}
	
	/* Write high byte */
	if( !write_byte(APDS9930_AIHTH, val_high) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool getLightIntHighThreshold(uint16_t *threshold){
	uint8_t val_byte;
	*threshold = 0;
	
	/* Read value from ambient light low threshold, low byte register */
	if( !read_byte(APDS9930_AIHTL, &val_byte) ) {
		return false;
	}
	*threshold = val_byte;
	
	/* Read value from ambient light low threshold, high byte register */
	if( !read_byte(APDS9930_AIHTH, &val_byte) ) {
		return false;
	}
	*threshold = *threshold + ((uint16_t)val_byte << 8);
	return true;
}
/************************************************************************/

/************************************************************************/
uint16_t getProximityIntLowThreshold(void){
	uint16_t val;
	uint8_t val_byte;
	
	/* Read value from PILT register */
	if( !read_byte(APDS9930_PILTL, &val_byte) ) {
		val = 0;
	}
	val = val_byte;
	if( !read_byte(APDS9930_PILTH, &val_byte) ) {
		val = 0;
	}
	val |= ((uint16_t)val_byte << 8);    
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setProximityIntLowThreshold(uint16_t threshold){
	uint8_t lo;
	uint8_t hi;
	hi = threshold >> 8;
	lo = threshold & 0x00FF;

	if( !write_byte(APDS9930_PILTL, lo) ) {
		return false;
	}
	if( !write_byte(APDS9930_PILTH, hi) ) {
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
uint16_t getProximityIntHighThreshold(void){
	uint16_t val;
	uint8_t val_byte;
	
	/* Read value from PILT register */
	if( !read_byte(APDS9930_PIHTL, &val_byte) ) {
		val = 0;
	}
	val = val_byte;
	if( !read_byte(APDS9930_PIHTH, &val_byte) ) {
		val = 0;
	}
	val |= ((uint16_t)val_byte << 8);    
	return val;
}
//////////////////////////////////////////////////////////////////////////
bool setProximityIntHighThreshold(uint16_t threshold){
	uint8_t lo;
	uint8_t hi;
	hi = threshold >> 8;
	lo = threshold & 0x00FF;

	if( !write_byte(APDS9930_PIHTL, lo) ) {
		return false;
	}
	if( !write_byte(APDS9930_PIHTH, hi) ) {
		return false;
	}
	return true;
}
/************************************************************************/

/************************************************************************/
bool readProximity(uint16_t *val){
	*val = 0;
	uint8_t val_byte;

	/* Read value from proximity data register */
	if( !read_byte(APDS9930_PDATAL, &val_byte) ) {
		return false;
	}
	*val = val_byte;
	if( !read_byte(APDS9930_PDATAH, &val_byte) ) {
		return false;
	}
	*val += ((uint16_t)val_byte << 8);
	return true;
}
/************************************************************************/

/************************************************************************/
bool readCh0Light(uint16_t *val){
	uint8_t val_byte;
	*val = 0;
	
	/* Read value from channel 0 */
	if( !read_byte(APDS9930_Ch0DATAL, &val_byte) ) {
		return false;
	}
	*val = val_byte;
	if( !read_byte(APDS9930_Ch0DATAH, &val_byte) ) {
		return false;
	}
	*val += ((uint16_t)val_byte << 8);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool readCh1Light(uint16_t *val){
	uint8_t val_byte;
	*val = 0;
	
	/* Read value from channel 0 */
	if( !read_byte(APDS9930_Ch1DATAL, &val_byte) ) {
		return false;
	}
	*val = val_byte;
	if( !read_byte(APDS9930_Ch1DATAH, &val_byte) ) {
		return false;
	}
	*val += ((uint16_t)val_byte << 8);
	return true;
}
//////////////////////////////////////////////////////////////////////////
float floatAmbientToLux(uint16_t Ch0, uint16_t Ch1)
{
	uint8_t x[4]={1,8,16,120};
    float ALSIT = 2.73 * (256 - DEFAULT_ATIME);
    float iac  = max_value(Ch0 - ALS_B * Ch1, ALS_C * Ch0 - ALS_D * Ch1);
    if (iac < 0) iac = 0;
	float lpc  = GA * DF / (ALSIT * x[getAmbientLightGain()]);
    return iac * lpc;
}
//////////////////////////////////////////////////////////////////////////
unsigned long ulongAmbientToLux(uint16_t Ch0, uint16_t Ch1)
{
	uint8_t x[4]={1,8,16,120};
    unsigned long ALSIT = 2.73 * (256.0 - DEFAULT_ATIME);
    unsigned long iac  = max_value(Ch0 - ALS_B * Ch1, ALS_C * Ch0 - ALS_D * Ch1);
	if (iac < 0) iac = 0;
    unsigned long lpc  = GA * DF / (ALSIT * x[getAmbientLightGain()]);
    return iac * lpc;
}
//////////////////////////////////////////////////////////////////////////
bool readAmbientLightLuxF(float *val){
	uint16_t Ch0;
	uint16_t Ch1;
	
	/* Read value from channel 0 */
	if( !readCh0Light(&Ch0) ) {
		return false;
	}

	/* Read value from channel 1 */
	if( !readCh1Light(&Ch1) ) {
		return false;
	}

	*val = floatAmbientToLux(Ch0, Ch1);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool readAmbientLightLuxUL(unsigned long *val){
	uint16_t Ch0;
	uint16_t Ch1;
	
	/* Read value from channel 0 */
	if( !readCh0Light(&Ch0) ) {
		return false;
	}

	/* Read value from channel 1 */
	if( !readCh1Light(&Ch1) ) {
		return false;
	}

	*val = ulongAmbientToLux(Ch0, Ch1);
	return true;
}
/************************************************************************/

/************************************************************************/
float max_value(float x, float y){
	return (x>y)? x: y;
}

/************************************************************************/

/************************************************************************/
bool read_byte(uint8_t reg, uint8_t *val){
	apds9930_txBuff[0] = reg | AUTO_INCREMENT;

	HAL_I2C_Write(APDS9930_I2C_ADDR, apds9930_txBuff, 1);
	HAL_I2C_Read(APDS9930_I2C_ADDR, val, 1);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool write_byte(uint8_t reg, uint8_t val){
	apds9930_txBuff[0] = reg | AUTO_INCREMENT;
	apds9930_txBuff[1] = val;

	HAL_I2C_Write(APDS9930_I2C_ADDR, apds9930_txBuff, 2);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool write_cmd(uint8_t val){
	apds9930_txBuff[0] = val;

	HAL_I2C_Write(APDS9930_I2C_ADDR, apds9930_txBuff, 1);
	return true;
}
/************************************************************************/
