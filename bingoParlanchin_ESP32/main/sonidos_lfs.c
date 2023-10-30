/*
 * sonido_lfs.c
 *
 *  Created on: 12 dic. 2022
 *      Author: Luciano Salvatore
 */

#include <stdint.h>
#include "sonidos_lfs.h"
#include "audios_lfs.h"
#include "driver/gpio.h"
#include "pines_esp32_lfs.h"
#include "driver/ledc.h"


//// CONSTANTES ////



//variables de reproduccion de WAV
const uint16_t* p_audio;
uint32_t duracion;
uint32_t indice_duracion;

uint8_t flag_audio = 0;

//variables de setNumero
T_NUMERO buff_numero[3];
uint8_t cant_numero = 0; //valor maximo del indice del buffer en esta reproduccion
uint8_t indice_numero = 0;

void init_sonido (void){
	p_audio = setAudio(buff_numero[0]);
	duracion = setDuracionAudio(buff_numero[0]);

	indice_duracion = 0;
	flag_audio = 1;
}


void updatePWM (void){

	if (!flag_audio){
		ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 512);
		ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
		return;
	}

	//reproduce la siguiente muestra
	ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, p_audio[indice_duracion]);
	ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
	indice_duracion++;

	if (indice_duracion > duracion - 1){ //si se alcanzo la duracion del wav
		indice_numero++;

		if (indice_numero > cant_numero){ //si se pasó el tamaño actual del buffer
			flag_audio = 0;
			return;
		} //fin if indice_numero

		p_audio = setAudio(buff_numero[indice_numero]);
		duracion = setDuracionAudio(buff_numero[indice_numero]);
		indice_duracion = 0;

	} //fin if indice_duracion...
} //fin updatePWM()




void setNumero (uint8_t n){

	if (n > 90) return;

	uint8_t decena = n / 10;
	uint8_t unidad = n % 10;

	cant_numero = 0;
	indice_numero = 0;

	switch (decena) {
		case 1:
			switch (n) {
				case 10:
					buff_numero[cant_numero] = DIEZ;
				break;
				case 11:
					buff_numero[cant_numero] = ONCE;
				break;
				case 12:
					buff_numero[cant_numero] = DOCE;
				break;
				case 13:
					buff_numero[cant_numero] =  TRECE;
				break;
				case 14:
					buff_numero[cant_numero] = CATORCE;
				break;
				case 15:
					buff_numero[cant_numero] = QUINCE;
				break;
				default:
					buff_numero[cant_numero] = DIECI;
					cant_numero++;
				break;
			} //fin switch n

		break;
		case 2:
			if (n == 20){
				buff_numero[cant_numero] = VEINTE;
			}else{
				buff_numero[cant_numero] = VEINTI;
				cant_numero++;
			}

		break;
		case 3:
			buff_numero[cant_numero] = TREINTA;
			if (n > 30){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		case 4:
			buff_numero[cant_numero] = CUARENTA;
			if (n > 40){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		case 5:
			buff_numero[cant_numero] = CINCUENTA;
			if (n > 50){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		case 6:
			buff_numero[cant_numero] = SESENTA;
			if (n > 60){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		case 7:
			buff_numero[cant_numero] = SETENTA;
			if (n > 70){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		case 8:
			buff_numero[cant_numero] = OCHENTA;
			if (n > 80){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		case 9:
			buff_numero[cant_numero] = NOVENTA;
			if (n > 90){
				cant_numero++;
				buff_numero[cant_numero] = _Y;
				cant_numero++;
			}
		break;
		default:
		break;
	} //switch decena

	switch (unidad) {
		case 0:
			if (n < 10){
				buff_numero[cant_numero] = CERO;
			}
		break;
		case 1:
			if (n != 11){
				buff_numero[cant_numero] = UNO;
			}
		break;
		case 2:
			if (n != 12){
				buff_numero[cant_numero] = DOS;
			}
		break;
		case 3:
			if (n != 13){
				buff_numero[cant_numero] = TRES;
			}
		break;
		case 4:
			if (n != 14){
				buff_numero[cant_numero] = CUATRO;
			}
		break;
		case 5:
			if (n != 15){
				buff_numero[cant_numero] = CINCO;
			}
		break;
		case 6:
			buff_numero[cant_numero] = SEIS;
		break;
		case 7:
			buff_numero[cant_numero] = SIETE;
		break;
		case 8:
			buff_numero[cant_numero] = OCHO;
		break;
		case 9:
			buff_numero[cant_numero] = NUEVE;
		break;
		default:
		break;
	} //switch unidad
	init_sonido();
} //fin setNumero()
