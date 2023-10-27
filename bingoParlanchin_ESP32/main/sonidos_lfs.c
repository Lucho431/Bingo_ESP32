/*
 * sonido_lfs.c
 *
 *  Created on: 12 dic. 2022
 *      Author: Luciano Salvatore
 */

#include <stdint.h>
#include "sonidos_lfs.h"
#include "driver/gpio.h"
#include "pines_esp32_lfs.h"


//// CONSTANTES ////



//variables de reproduccion de WAV
char* p_audio;
uint16_t audioIndex = 0;
uint16_t audioSize;

uint8_t flag_audio = 0;
T_SONIDO statusSonido = SILENCIO;

char* buff_audio[3]; //buffer que almacena los punteros de los sonidos
uint8_t buff_audioIndex = 0; //valor máximo 2 (3 sonidos buffereados)
uint8_t buff_audioSize = 0; //cantidad de punteros almacenados en el buffer


void init_sonido (void){
	asm volatile ("nop");
}


void updatePWM (void){

	switch (statusSonido){
		case SONIDO:

			if (!flag_audio){
				statusSonido = SILENCIO;
				break;
			}

			gpio_set_level(PIN_LED, 1); //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
			//TIM2->CCR1 = p_audio [audioIndex];
			audioIndex++;

			if (audioIndex > (audioSize - 1)){

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
					//buff_audio[buff_audioSize] = "diez";
				break;
				case 11:
					//buff_audio[buff_audioSize] = "once";
				break;
				case 12:
					//buff_audio[buff_audioSize] = "doce";
				break;
				case 13:
					//buff_audio[buff_audioSize] = "trece";
				break;
				case 14:
					//buff_audio[buff_audioSize] = "catorce";
				break;
				case 15:
					//buff_audio[buff_audioSize] = "quince";
				break;
				default:
					//buff_audio[buff_audioSize] = "dieci...";
					buff_audioSize++;
				break;
			} //fin switch n

		break;
		case 2:
			if (n == 20){
				//buff_audio[buff_audioSize] = "veinte";
			}else{
				//buff_audio[buff_audioSize] = "veinti...";
				buff_audioSize++;
			}

		break;
		case 3:
			//buff_audio[buff_audioSize] = "treinta";
			if (n > 30){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		case 4:
			//buff_audio[buff_audioSize] = "cuarenta";
			if (n > 40){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		case 5:
			//buff_audio[buff_audioSize] = "cincuenta";
			if (n > 50){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		case 6:
			//buff_audio[buff_audioSize] = "secenta";
			if (n > 60){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		case 7:
			//buff_audio[buff_audioSize] = "setenta";
			if (n > 70){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		case 8:
			//buff_audio[buff_audioSize] = "ochenta";
			if (n > 80){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		case 9:
			//buff_audio[buff_audioSize] = "noventa";
			if (n > 90){
				buff_audioSize++;
				//buff_audio[buff_audioSize] = "y...";
				buff_audioSize++;
			}
		break;
		default:
		break;
	}

	switch (unidad) {
		case 0:
			if (n < 10){
				//buff_audio[buff_audioSize] = "cero";
			}
		break;
		case 1:
			if (n != 11){
				//buff_audio[buff_audioSize] = "uno";
			}
		break;
		case 2:
			if (n != 12){
				//buff_audio[buff_audioSize] = "dos";
			}
		break;
		case 3:
			if (n != 13){
				//buff_audio[buff_audioSize] = "tres";
			}
		break;
		case 4:
			if (n != 14){
				//buff_audio[buff_audioSize] = "cuatro";
			}
		break;
		case 5:
			if (n != 15){
				//buff_audio[buff_audioSize] = "cinco";
			}
		break;
		case 6:
			//buff_audio[buff_audioSize] = "seis";
		break;
		case 7:
			//buff_audio[buff_audioSize] = "siete";
		break;
		case 8:
			//buff_audio[buff_audioSize] = "ocho";
		break;
		case 9:
			//buff_audio[buff_audioSize] = "nueve";
		break;
		default:
		break;
	}

	flag_audio = 1;

} //fin enunciaNumero()
