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
uint16_t* p_audio;
uint32_t audioIndex = 0;

uint8_t flag_audio = 0;
T_SONIDO statusSonido = SILENCIO;

const uint16_t* buff_audio[3]; //buffer que almacena los punteros de los sonidos
uint8_t buff_audioIndex = 0; //valor máximo 2 (3 sonidos buffereados)
uint8_t buff_audioSize = 0; //cantidad de punteros almacenados en el buffer

uint32_t buff_duracion[3]; //buffer que almacena los tamaños de los sonidos

T_NUMERO buff_numero[3];
uint8_t cant_numero = 0;
uint8_t indice_numero = 0;

void init_sonido (void){



	asm volatile ("nop");
}


void updatePWM (void){

	if (!flag_audio){
		ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 512);
		ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
		return;
	}

	ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, p_audio[audioIndex]);
	ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);



	switch (statusSonido){
		case SONIDO:

			if (!flag_audio){
				statusSonido = SILENCIO;
				break;
			}




			gpio_set_level(PIN_LED, 1); //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
			//TIM2->CCR1 = p_audio [audioIndex];
			ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, p_audio[audioIndex]);
			ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
			audioIndex++;

			if (audioIndex > (audioIndex - 1)){

				if (buff_audioIndex < buff_audioSize){
					buff_audioIndex++;
				}else{
					statusSonido = SILENCIO;
					flag_audio = 0;
				}

				audioIndex = 0;
			}
		break;
		case SILENCIO:

			gpio_set_level(PIN_LED, 0); //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
			//TIM2->CCR1 = 82;
			if (flag_audio != 0){
				audioIndex = 0;
				buff_audioIndex = 0;
				statusSonido = SONIDO;
			}

		break;
		default:
		break;
	} //end switch statusSonido

} //fin updatePWM()


void enunciaNumero(uint8_t n){

	if (n > 90) return;

	uint8_t decena = n / 10;
	uint8_t unidad = n % 10;

	buff_audioSize = 0;
	audioIndex = 0;

	switch (decena) {
		case 1:
			switch (n) {
				case 10:

					buff_duracion[buff_audioSize] = setDuracionAudio(DIEZ);
					buff_audio[buff_audioSize] = setAudio(DIEZ);
				break;
				case 11:
					buff_duracion[buff_audioSize] = setDuracionAudio(ONCE);
					buff_audio[buff_audioSize] = setAudio(ONCE);
				break;
				case 12:
					buff_duracion[buff_audioSize] = setDuracionAudio(DOCE);
					buff_audio[buff_audioSize] = setAudio(DOCE);
				break;
				case 13:
					buff_duracion[buff_audioSize] = setDuracionAudio(TRECE);
					buff_audio[buff_audioSize] = setAudio(TRECE);
				break;
				case 14:
					buff_duracion[buff_audioSize] = setDuracionAudio(CATORCE);
					buff_audio[buff_audioSize] = setAudio(CATORCE);
				break;
				case 15:
					buff_duracion[buff_audioSize] = setDuracionAudio(QUINCE);
					buff_audio[buff_audioSize] = setAudio(QUINCE);
				break;
				default:
					buff_duracion[buff_audioSize] = setDuracionAudio(DIECI);
					buff_audio[buff_audioSize] = setAudio(DIECI);
					buff_audioSize++;
				break;
			} //fin switch n

		break;
		case 2:
			if (n == 20){
				buff_duracion[buff_audioSize] = setDuracionAudio(VEINTE);
				buff_audio[buff_audioSize] = setAudio(VEINTE);
			}else{

				buff_duracion[buff_audioSize] = setDuracionAudio(VEINTI);
				buff_audio[buff_audioSize] = setAudio(VEINTI);
				buff_audioSize++;
			}

		break;
		case 3:
			buff_duracion[buff_audioSize] = setDuracionAudio(TREINTA);
			buff_audio[buff_audioSize] = setAudio(TREINTA);
			if (n > 30){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		case 4:
			buff_duracion[buff_audioSize] = setDuracionAudio(CUARENTA);
			buff_audio[buff_audioSize] = setAudio(CUARENTA);
			if (n > 40){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		case 5:
			buff_duracion[buff_audioSize] = setDuracionAudio(CINCUENTA);
			buff_audio[buff_audioSize] = setAudio(CINCUENTA);
			if (n > 50){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		case 6:
			buff_duracion[buff_audioSize] = setDuracionAudio(SESENTA);
			buff_audio[buff_audioSize] = setAudio(SESENTA);
			if (n > 60){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		case 7:
			buff_duracion[buff_audioSize] = setDuracionAudio(SETENTA);
			buff_audio[buff_audioSize] = setAudio(SETENTA);
			if (n > 70){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		case 8:
			buff_duracion[buff_audioSize] = setDuracionAudio(OCHENTA);
			buff_audio[buff_audioSize] = setAudio(OCHENTA);
			if (n > 80){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		case 9:
			buff_duracion[buff_audioSize] = setDuracionAudio(NOVENTA);
			buff_audio[buff_audioSize] = setAudio(NOVENTA);
			if (n > 90){
				buff_audioSize++;
				buff_duracion[buff_audioSize] = setDuracionAudio(_Y);
				buff_audio[buff_audioSize] = setAudio(_Y);
				buff_audioSize++;
			}
		break;
		default:
		break;
	}

	switch (unidad) {
		case 0:
			if (n < 10){
				buff_duracion[buff_audioSize] = setDuracionAudio(CERO);
				buff_audio[buff_audioSize] = setAudio(CERO);
			}
		break;
		case 1:
			if (n != 11){
				buff_duracion[buff_audioSize] = setDuracionAudio(UNO);
				buff_audio[buff_audioSize] = setAudio(UNO);
			}
		break;
		case 2:
			if (n != 12){
				buff_duracion[buff_audioSize] = setDuracionAudio(DOS);
				buff_audio[buff_audioSize] = setAudio(DOS);
			}
		break;
		case 3:
			if (n != 13){
				buff_duracion[buff_audioSize] = setDuracionAudio(TRES);
				buff_audio[buff_audioSize] = setAudio(TRES);
			}
		break;
		case 4:
			if (n != 14){
				buff_duracion[buff_audioSize] = setDuracionAudio(CUATRO);
				buff_audio[buff_audioSize] = setAudio(CUATRO);
			}
		break;
		case 5:
			if (n != 15){
				buff_duracion[buff_audioSize] = setDuracionAudio(CINCO);
				buff_audio[buff_audioSize] = setAudio(CINCO);
			}
		break;
		case 6:
			buff_duracion[buff_audioSize] = setDuracionAudio(SEIS);
			buff_audio[buff_audioSize] = setAudio(SEIS);
		break;
		case 7:
			buff_duracion[buff_audioSize] = setDuracionAudio(SIETE);
			buff_audio[buff_audioSize] = setAudio(SIETE);
		break;
		case 8:
			buff_duracion[buff_audioSize] = setDuracionAudio(OCHO);
			buff_audio[buff_audioSize] = setAudio(OCHO);
		break;
		case 9:
			buff_duracion[buff_audioSize] = setDuracionAudio(NUEVE);
			buff_audio[buff_audioSize] = setAudio(NUEVE);
		break;
		default:
		break;
	}

	flag_audio = 1;

} //fin enunciaNumero()


void setNumero (uint8_t n){

	if (n > 90) return;

	uint8_t decena = n / 10;
	uint8_t unidad = n % 10;

	cant_numero = 0;
	indice_numero = 0;
	audioIndex = 0;

	switch (decena) {
		case 1:
			switch (n) {
				case 10:
					buff_numero[cant_numero] = DIEZ
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
	}

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
	}

	flag_audio = 1;
	init_sonido();
} //fin setNumero()
