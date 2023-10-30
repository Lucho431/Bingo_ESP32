/*
 * audios_lfs.h
 *
 *  Created on: 30 oct 2023
 *      Author: Luciano Salvatore
 */

#ifndef MAIN_AUDIOS_LFS_H_
#define MAIN_AUDIOS_LFS_H_


//// TIPOS DE DATOS ////
typedef enum{
	CERO,
	UNO,
	DOS,
	TRES,
	CUATRO,
	CINCO,
	SEIS,
	SIETE,
	OCHO,
	NUEVE,
	DIEZ,
	ONCE,
	DOCE,
	TRECE,
	CATORCE,
	QUINCE,
	DIECI,
	VEINTE,
	VEINTI,
	TREINTA,
	_Y,
	CUARENTA,
	CINCUENTA,
	SESENTA,
	SETENTA,
	OCHENTA,
	NOVENTA,
}T_NUMERO;

const uint16_t *setAudio (T_NUMERO);
uint32_t setDuracionAudio (T_NUMERO);

#endif /* MAIN_AUDIOS_LFS_H_ */
