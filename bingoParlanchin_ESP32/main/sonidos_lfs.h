/*
 * sonidos_lfs.h
 *
 *  Created on: 12 dic. 2022
 *      Author: Luciano Salvatore
 */

#ifndef INC_SONIDOS_LFS_H_
#define INC_SONIDOS_LFS_H_


//// TIPOS DE DATOS ////
typedef enum{
	SONIDO,
	SILENCIO,
}T_SONIDO;

typedef enum{
	SILENCIO_CORTO,
	SILENCIO_LARGO,
}T_PERIODO;


//// DEFINICIONES ////
#define SILENCIO_CORTO 22050
#define SILENCIO_LARGO 44100

//// FUNCIONES ////
//void init_sonido (void);
void updatePWM (void);
void setNumero(uint8_t);

#endif /* INC_SONIDOS_LFS_H_ */
