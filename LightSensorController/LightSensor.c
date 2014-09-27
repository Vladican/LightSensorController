/*
 * LightSensor.c
 *
 * Created: 7/30/2014 3:44:21 PM
 *  Author: VLAD
 */ 
#include "LightSensor.h"
#include "USI_TWI_Master.h"

//initialize I2C bus and power on the sensor
void init_sensor(){
	
	unsigned char message[2];
	USI_TWI_Master_Initialise();
	message[0] = 0x90;
	message[1] = 0x03;
	I2C_write(LIGHT_SENSOR_ADDR, message, 2, TRUE);
}

//read value of channel 0 of the light sensor
uint16_t read_ch0(){
	
	unsigned char message[2];
	message[0] = 0x9C;
	I2C_write(LIGHT_SENSOR_ADDR, message, 1, FALSE);
	do{
		I2C_read(LIGHT_SENSOR_ADDR, message, 2, TRUE);
	} while(USI_TWI_Get_State_Info() == USI_TWI_NO_ACK_ON_ADDRESS);
	return (*((uint16_t*)message));		
}

//read value of channel 1 of the light sensor
uint16_t read_ch1(){
	
	unsigned char message[2];
	message[0] = 0x9E;
	I2C_write(LIGHT_SENSOR_ADDR, message, 1, FALSE);
	do{
		I2C_read(LIGHT_SENSOR_ADDR, message, 2, TRUE);
	} while(USI_TWI_Get_State_Info() == USI_TWI_NO_ACK_ON_ADDRESS);
	return (*((uint16_t*)message));
}

unsigned long ch0;
unsigned long ch1;

//read the channel 1 and 0 values of the light sensor and convert them to a lux reading
unsigned long read_lux(){
	
	unsigned long chScale;
	unsigned long ratio1;
	unsigned long ratio;
	unsigned long temp;
	unsigned long lux;
	unsigned int b, m;
		
	ch0 = (unsigned long)(read_ch0());
	ch1 = (unsigned long)(read_ch1());
	chScale = (1 << CH_SCALE);
			
	// scale the channel values
	ch0 = (ch0 * chScale) >> CH_SCALE;
	ch1 = (ch1 * chScale) >> CH_SCALE;

	// find the ratio of the channel values (Channel1/Channel0)
	// protect against divide by zero
	ratio1 = 0;
	if (ch0 != 0){ 
		ratio1 = (ch1 << (RATIO_SCALE+1)) / ch0;
	} else {
		return 0;
	}		
	// round the ratio value
	ratio = (ratio1 + 1) >> 1;
	// is ratio <= eachBreak ?
		
	if ((ratio >= 0) && (ratio <= K1T)){
		b=B1T; 
		m=M1T;
	} else if (ratio <= K2T){
		b=B2T; 
		m=M2T;
	} else if (ratio <= K3T){
		b=B3T; 
		m=M3T;
	} else if (ratio <= K4T){
		b=B4T; 
		m=M4T;
	} else if (ratio <= K5T){
		b=B5T; 
		m=M5T;
	} else if (ratio <= K6T){
		b=B6T; 
		m=M6T;
	} else if (ratio <= K7T){
		b=B7T; 
		m=M7T;
	} else if (ratio > K8T){
		b=B8T; 
		m=M8T;
	}
		
	temp = ((ch0 * b) - (ch1 * m));
	// do not allow negative lux value
	if (temp < 0) temp = 0;
	// round lsb (2^(LUX_SCALE-1))
	temp += (1 << (LUX_SCALE-1));
	// strip off fractional portion
	lux = temp >> LUX_SCALE;
	return(lux);
}