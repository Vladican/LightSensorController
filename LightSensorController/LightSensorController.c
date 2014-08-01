/*
 * LightSensorController.c
 *
 * Created: 7/29/2014 10:00:36 AM
 *  Author: VLAD
 */ 
/*

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USI_TWI_Master.h"

#define SLAVE_ADDR  0x10

#define MESSAGEBUF_SIZE       10

#define TWI_GEN_CALL         0x00  // The General Call address is 0

// Sample TWI transmission commands
#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

// Sample TWI transmission states, used in the main application.
#define SEND_DATA             0x01
#define REQUEST_DATA          0x02
#define READ_DATA_FROM_BUFFER 0x03

#define LIGHT_SENSOR_ADDR	0x39

uint16_t data = 0;

int main(void){
	
	unsigned char messageBuf[MESSAGEBUF_SIZE];
	unsigned char temp;
    USI_TWI_Master_Initialise();
	//power up the light sensor
	messageBuf[0] = (LIGHT_SENSOR_ADDR<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	messageBuf[1] = 0x90;             // The first byte is used for commands.
	//messageBuf[2] = 0x01;				//number of bytes to write
	messageBuf[2] = 0x03;                        // The second byte is used for the data.
	temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 3, TRUE);
	//read the value of light sensor control register
// 	messageBuf[0] = (LIGHT_SENSOR_ADDR<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
// 	messageBuf[1] = 0x90;             // The first byte is used for commands.
// 	temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 2 );
	
	// Send the request-for-data command to the Slave
	messageBuf[0] = (LIGHT_SENSOR_ADDR<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	messageBuf[1] = 0x90;             // The first byte is used for commands.
	temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 2, FALSE);

	// One might need to delay before proceeding to enable the slave to interpret the last message,
	// and prepare the next request. Or as in this simple sample rerun the request until he responds.

	// Transmit request and get the received data from the transceiver buffer
	messageBuf[0] = (LIGHT_SENSOR_ADDR<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	do{
		temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 2, TRUE);
	} while (USI_TWI_Get_State_Info() == USI_TWI_NO_ACK_ON_ADDRESS);
	asm("nop");
	
	while(1){
		//read ch0 data
		// Send the request-for-data command to the Slave
		messageBuf[0] = (LIGHT_SENSOR_ADDR<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
		messageBuf[1] = 0x9C;             // The first byte is used for commands.
		temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 2, FALSE);

		// One might need to delay before proceeding to enable the slave to interpret the last message,
		// and prepare the next request. Or as in this simple sample rerun the request until he responds.

		// Transmit request and get the received data from the transceiver buffer
		messageBuf[0] = (LIGHT_SENSOR_ADDR<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
		do{
			temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 3, TRUE);
		} while (USI_TWI_Get_State_Info() == USI_TWI_NO_ACK_ON_ADDRESS);
		data = *((uint16_t*)(messageBuf+1));
		asm("nop");
	}
	
}*/


#include "LightSensor.h"

unsigned long data=0;
uint16_t chan0, chan1;

int main(){

	init_sensor();
	while(1){
		data = read_lux();
		//chan0 = read_ch0();
		//chan1 = read_ch1();
		asm("nop");
	}		
}