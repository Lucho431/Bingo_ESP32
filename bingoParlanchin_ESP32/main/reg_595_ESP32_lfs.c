/*
 * reg_595_ESP32_lfs.c
 *
 *  Created on: 24 may 2023
 *      Author: Luciano Salvatore
 */

#include "reg_595_ESP32_lfs.h"

static uint8_t puertoSPI;
static spi_bus_config_t *busSPI;
static spi_device_interface_config_t *diviceSPI;
static spi_device_handle_t spi_device_handle;

static uint16_t pinST;

int8_t error;

void reg_595_init (spi_host_device_t puerto, spi_bus_config_t *bus, spi_device_interface_config_t *divice, uint8_t STpin){

	//inicialización del periferico SPI:
	puertoSPI = puerto;
	busSPI = bus;
	diviceSPI = divice;
//	spi_bus_initialize(puertoSPI, busSPI, SPI_DMA_CH_AUTO);
//	spi_bus_add_device(puertoSPI, diviceSPI, &spi_device_handle);

	//del 595
	pinST = STpin; //"store", o "latch clock"

	gpio_set_level(pinST, 1);

	return;

} //fin reg_595_init()

void reg_595_startTx (spi_transaction_t *spi_transaction){

	error = spi_device_transmit(spi_device_handle, spi_transaction);
	gpio_set_level(pinST, 0);
	vTaskDelay(1/portTICK_PERIOD_MS);
	gpio_set_level(pinST, 1);

} //fin reg_595_165_startTxRx()
