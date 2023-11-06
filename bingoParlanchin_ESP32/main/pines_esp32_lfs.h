/*
 * pines_esp32_lfs.h
 *
 *  Created on: 3 oct 2023
 *      Author: luciano
 */

#ifndef MAIN_PINES_ESP32_LFS_H_
#define MAIN_PINES_ESP32_LFS_H_


//definiciones de pines
#define PIN_LED 		GPIO_NUM_2
//#define PIN_I2C1_SDA 	GPIO_NUM_17
//#define PIN_I2C1_SCL 	GPIO_NUM_5
//#define PIN_I2C0_SDA 	GPIO_NUM_21
#define PIN_SPI_MOSI	GPIO_NUM_23
//#define PIN_SPI_MISO	GPIO_NUM_19
#define PIN_SPI_SCLK	GPIO_NUM_22
//#define PIN_SPI_CS		GPIO_NUM_4
#define PIN_595_ST		GPIO_NUM_4
#define PIN_PWM			GPIO_NUM_26

#define PIN_IN_START_STOP	GPIO_NUM_18
#define PIN_IN_ATRAS		GPIO_NUM_17
#define PIN_IN_ADELANTE		GPIO_NUM_19
#define PIN_IN_MODO			GPIO_NUM_5
#define PIN_OUT_ST			GPIO_NUM_32
#define PIN_OUT_MANUAL		GPIO_NUM_33
#define PIN_OUT_AUTO		GPIO_NUM_25

#endif /* MAIN_PINES_ESP32_LFS_H_ */
