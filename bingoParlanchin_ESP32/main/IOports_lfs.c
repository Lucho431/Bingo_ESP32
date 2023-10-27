/*
 * IOports_lfs.c
 *
 *  Created on: Jul 25, 2023
 *      Author: Luciano Salvatore
 */

#include <IOports_lfs.h>
#include "driver/gpio.h"
#include "pines_esp32_lfs.h"


//variables
uint8_t flag_lecturas = 1;
uint8_t flag_salidas = 1;

uint8_t read_teclas [SIZEOF_POS_INPUT];
uint8_t last_teclas [SIZEOF_POS_INPUT];
T_INPUT status_teclas [SIZEOF_POS_INPUT];

uint16_t write_output;



void lecturaTeclas (void){

	read_teclas[IN_MODO] = gpio_get_level(PIN_IN_MODO);
	read_teclas[IN_START_STOP] = gpio_get_level(PIN_IN_START_STOP);
	read_teclas[IN_ATRAS] = gpio_get_level(PIN_IN_ATRAS);
	read_teclas[IN_ADELANTE] = gpio_get_level(PIN_IN_ADELANTE);

} //end lecturaTeclas()


void update_teclas(void){ //ESTADO DE LAS TECLAS CON LOGICA NEGATIVA

	last_teclas[IN_MODO] = read_teclas[IN_MODO];
	last_teclas[IN_START_STOP] = read_teclas[IN_START_STOP];
	last_teclas[IN_ATRAS] = read_teclas[IN_ATRAS];
	last_teclas[IN_ADELANTE] = read_teclas[IN_ADELANTE];

} //end update_teclas()


T_INPUT getStatBoton (T_POS_INPUT b){

	if (read_teclas[b] != 0){
		if (last_teclas[b] != 0){
			return HIGH_L;
		}
		return RISE;
	}else{
		if (last_teclas[b] != 0){
			return FALL;
		}
		return LOW_L;
	}

} //end getStatBoton()


void setOutput (T_POS_OUTPUT s, uint8_t val){

	if (val != 0){
		write_output |= (uint16_t)(1 << s);
		return;
	}else{
		write_output &= ~( (uint16_t)(1 << s) );
	}

} //end setOutput()


void toggleOutput (T_POS_OUTPUT s){

	write_output ^= (uint16_t)(1 << s);

} //end toggleOutput()


void update_outputs (void){

	//spi_74HC595_Transmit( (uint8_t*)&write_output, 2); // 2 bytes.

}
