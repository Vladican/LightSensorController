/*
 * LightSensorController.c
 *
 * Created: 7/29/2014 10:00:36 AM
 *  Author: VLAD
 */ 
#include "LightSensor.h"

unsigned long data=0;
uint16_t chan0, chan1;

int main(){

	init_sensor();
	while(1){
		data = read_lux();
		asm("nop");
	}		
}