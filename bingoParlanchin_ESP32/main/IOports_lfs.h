/*
 * botones_lfs.h
 *
 *  Created on: Jul 25, 2023
 *      Author: Luciano Salvatore
 */

#ifndef INC_IOPORTS_LFS_H_
#define INC_IOPORTS_LFS_H_

#include <stdint.h>

typedef enum{
    LOW_L,
    HIGH_L,
    FALL,
    RISE,
}T_INPUT;

typedef enum{
	IN_MODO,
	IN_START_STOP,
	IN_ATRAS,
	IN_ADELANTE,
	SIZEOF_POS_INPUT,
}T_POS_INPUT;


typedef enum{
	OUT_MANUAL,
	OUT_AUTO,
	SIZEOF_POS_OUTPUT,
}T_POS_OUTPUT;



//void __turnONFila (uint8_t);
//uint8_t __lecturaColumna (uint8_t);
void lecturaTeclas(void);
void update_teclas (void);
T_INPUT getStatBoton (T_POS_INPUT);
//void botonEXTI_handler(uint16_t);

void setOutput (T_POS_OUTPUT, uint8_t);
void toggleOutput (T_POS_OUTPUT);
void update_outputs (void);

#endif /* INC_IOPORTS_LFS_H_ */
