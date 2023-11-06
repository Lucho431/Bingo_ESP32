/*
 * reg_595_ESP32_lfs.h
 *
 *  Created on: 24 may 2023
 *      Author: Luciano Salvatore
 */

#ifndef MAIN_REG_595_ESP32_LFS_H_
#define MAIN_REG_595_ESP32_LFS_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

void reg_595_init (spi_host_device_t, spi_bus_config_t*, spi_device_interface_config_t*, uint8_t);
void reg_595_startTx (spi_transaction_t*);


#endif /* MAIN_REG_595_ESP32_LFS_H_ */
