/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "esp_random.h"
#include "bootloader_random.h"
#include "sdkconfig.h"
#include "esp_timer.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "pines_esp32_lfs.h"
#include "IOports_lfs.h"
#include "sonidos_lfs.h"


typedef enum{
	SIN_MODO,
	PAUSA,
	AUTO,
	MANUAL,
}T_MODO;

//////////////VARIABLES/////////////////
//constante de tag del log
static const char *TAG = "DEBUGGING";
//variable del led onboard
uint8_t ledPin = 0;
//variables de los timers
uint8_t flag_tim2 = 0; //timer del sonido
uint8_t flag_tim3 = 0; //timer de 10 ms.
//variables de estado
T_MODO status_funcionamiento = SIN_MODO;
T_MODO selec_funcionamiento = SIN_MODO;
//variables de numeros
uint8_t flag_numero = 0;
uint8_t cuentaNumeros = 0; //cantidad de numeros ya anunciados
uint8_t indiceNumeros = 0;
uint8_t repiteNumeros [91] = {0}; //lista de numeros repetidos
uint8_t listaNumeros [91] = {0}; //lista de numeros ordenados en la secuencia que salieron
uint8_t numero = 0;
uint16_t periodo_numero = 700; // 7 segundos (700 * 10 ms).
uint16_t randomSeed;
//variables botones
uint8_t periodo_botones = 1; // 1 equivale a 20 ms.
//variables del timer
TimerHandle_t xTimer;
esp_timer_handle_t hTimer;
uint32_t timerId = 1;
uint8_t flag_timerControl = 0; //timer de 10 ms.
uint8_t flag_timer22us = 0;


//declaracion de funciones
void config_gpio(void);
void vTimerCallback (TimerHandle_t pxTimer);
esp_err_t set_timers (void);
void set_pwm (void);
//esp_err_t uart_init (void);
//esp_err_t i2c_init (void);
//esp_err_t spi_init (void);
//static void uartTx_task(void*);
//static void uartRx_task(void*);


void app_main(void)
{
	bootloader_random_enable();

    /* Configure the peripheral according to the LED type */
    config_gpio();
    set_timers();
    set_pwm();

    bootloader_random_disable();

    while (1) {
//        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
//        /* Toggle the LED state */
//        s_led_state = !s_led_state;
//        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);

  	  if (flag_timerControl != 0){ //cada 10 ms.

  		  if (periodo_numero != 0){
  			  periodo_numero--;
  		  }

  		  if(periodo_botones != 0){
  			  lecturaTeclas();
  			  periodo_botones = 0;
  		  }else{
  			  periodo_botones = 1;
  		  } //fin if flag_boton

  		  flag_timerControl = 0;
  	  } //end if flag_timerControl

  	  if (flag_tim2 != 0){
  		  updatePWM();
  		  flag_tim2 = 0;
  	  } //end flag_tim2

  	  switch (status_funcionamiento){
  		  case SIN_MODO:

  			  if (getStatBoton(IN_MODO) == FALL){
  				  switch(selec_funcionamiento){
  					  case SIN_MODO:
  					  case PAUSA:
  					  case MANUAL:
  						  selec_funcionamiento = AUTO;
  						  gpio_set_level(PIN_OUT_AUTO, 0); //LOGICA NEGATIVA
  						  gpio_set_level(PIN_OUT_MANUAL, 1); //LOGICA NEGATIVA
  						  ESP_LOGI(TAG, "modo AUTO");
					  break;
  					  case AUTO:
  						  selec_funcionamiento = MANUAL;
  						  gpio_set_level(PIN_OUT_AUTO, 1); //LOGICA NEGATIVA
  						  gpio_set_level(PIN_OUT_MANUAL, 0); //LOGICA NEGATIVA
  						  ESP_LOGI(TAG, "modo MANUAL");
  					  default:
					  break;
  				  } //end switch selec_funcionamiento
  			  } //end getStatBoton IN_MODO

  			  if (getStatBoton(IN_START_STOP) == FALL){

  				  indiceNumeros = 0;
  				  cuentaNumeros = 0;

  				  switch(selec_funcionamiento){
  					  case MANUAL:
  					//	  randomSeed = (uint16_t) HAL_ADC_GetValue(&hadc1);
  						  bootloader_random_enable();
  						  bootloader_random_disable();
  						  //srand(randomSeed);
  						  status_funcionamiento = MANUAL;
  						  ESP_LOGI(TAG, "INICIA MANUAL");
  						  break;
  					  case AUTO:
  					//	  randomSeed = (uint16_t) HAL_ADC_GetValue(&hadc1);
  						  bootloader_random_enable();
  						  bootloader_random_disable();
  						  //srand(randomSeed);
  						  status_funcionamiento = AUTO;
  						  ESP_LOGI(TAG, "INICIA AUTO");
  					  default:
  						  break;
  				  } //end switch selec_funcionamiento
  			  } //end getStatBoton IN_START_STOP

  		  break;
  		  case AUTO:
  			  if (getStatBoton(IN_START_STOP) == FALL){
  				  status_funcionamiento = PAUSA;
  				  if (cuentaNumeros != 0){
  					  indiceNumeros = cuentaNumeros - 1;
  				  }else{
  					  indiceNumeros = 0;
  				  }
				  ESP_LOGI(TAG, "modo AUTO en PAUSA");
  				  break;
  			  }

  			  if (cuentaNumeros > 90){
  				  status_funcionamiento = PAUSA;
  				  break;
  			  }

  			  if (periodo_numero != 0) break;

  			  numero = esp_random() % 91;
  			  if (repiteNumeros[numero] != 0){
  				  break;
  			  }

  			  enunciaNumero(numero);
  			  ESP_LOGI(TAG, "numero: %d", numero);
  			  repiteNumeros[numero] = 1;
  			  listaNumeros[cuentaNumeros] = numero;
  			  cuentaNumeros++;

  			  periodo_numero = 700;
  		  break;
  		  case MANUAL:
  			  if (getStatBoton(IN_START_STOP) == FALL){
  				  status_funcionamiento = PAUSA;
  				  if (cuentaNumeros != 0){
  					  indiceNumeros = cuentaNumeros - 1;
  				  }else{
  					  indiceNumeros = 0;
  				  }
  				  ESP_LOGI(TAG, "modo MANUAL en PAUSA");
  				  break;
  			  } //fin if IN_START_STOP

  			  if (cuentaNumeros > 90){
  				  status_funcionamiento = PAUSA;
  				  break;
  			  }

  			  if (periodo_numero != 0) break;

  			  if (getStatBoton(IN_ADELANTE) != FALL) break;

  			  numero = esp_random() % 91;
  			  if (repiteNumeros[numero] != 0){
  				  break;
  			  }

  			  enunciaNumero(numero);
  			  ESP_LOGI(TAG, "numero: %d", numero);
  			  repiteNumeros[numero] = 1;
  			  listaNumeros[cuentaNumeros] = numero;
  			  cuentaNumeros++;

  			  periodo_numero = 300;
  		  break;
  		  case PAUSA:
  			  if (getStatBoton(IN_MODO) == FALL){
  				  switch(selec_funcionamiento){
  					  case SIN_MODO:
  					  case PAUSA:
  					  case MANUAL:
  						  selec_funcionamiento = AUTO;
  						  gpio_set_level(PIN_OUT_AUTO, 0); //LOGICA NEGATIVA
  						  gpio_set_level(PIN_OUT_MANUAL, 1); //LOGICA NEGATIVA
  						  ESP_LOGI(TAG, "modo AUTO");
					  break;
  					  case AUTO:
  						  selec_funcionamiento = MANUAL;
  						  gpio_set_level(PIN_OUT_AUTO, 1); //LOGICA NEGATIVA
  						  gpio_set_level(PIN_OUT_MANUAL, 0); //LOGICA NEGATIVA
  						  ESP_LOGI(TAG, "modo MANUAL");
  					  default:
					  break;
  				  } //end switch selec_funcionamiento
  			  } //end getStatBoton IN_MODO

  			  if (getStatBoton(IN_START_STOP) == FALL){
  				  switch(selec_funcionamiento){
  					  case MANUAL:
  					//	  randomSeed = (uint16_t) HAL_ADC_GetValue(&hadc1);
  						  bootloader_random_enable();
  						  bootloader_random_disable();
  						  //srand(randomSeed);
  						  status_funcionamiento = MANUAL;
  						  ESP_LOGI(TAG, "INICIA MANUAL");
  						  break;
  					  case AUTO:
  					//	  randomSeed = (uint16_t) HAL_ADC_GetValue(&hadc1);
  						  bootloader_random_enable();
  						  bootloader_random_disable();
  						  //srand(randomSeed);
  						  status_funcionamiento = AUTO;
  						  ESP_LOGI(TAG, "INICIA AUTO");
  					  default:
  						  break;
  				  } //end switch selec_funcionamiento
  			  } //end getStatBoton IN_START_STOP

  			  if (getStatBoton(IN_ATRAS) == FALL){
  				  if (!cuentaNumeros) break;

  				  if (indiceNumeros != 0) indiceNumeros--;

  				  enunciaNumero( listaNumeros[indiceNumeros] );
  				  ESP_LOGI(TAG, "ya salio el: %d", listaNumeros[indiceNumeros]);
  			  } //fin if IN_ATRAS

  			  if (getStatBoton(IN_ADELANTE) == FALL){
  				  if (!cuentaNumeros) break;

  				  if (indiceNumeros < (cuentaNumeros - 1) ) indiceNumeros++;

  				  enunciaNumero( listaNumeros[indiceNumeros] );
  				  ESP_LOGI(TAG, "ya salio el: %d", listaNumeros[indiceNumeros]);
  			  } //fin if IN_ADELANTE
		  break;
  		  default:
  		  break;
  	  } //fin switch status_funcionamiento

  	  update_teclas();

    } //fin while 1
} //fin app_main()


////////////////////////////////////////

//             FUNCIONES              //

///////////////////////////////////////


void vTimerCallback (TimerHandle_t pxTimer){
	flag_timerControl = 1;
} //fin vTimerCallback()

void hardTimer_callback(void *arg){
	flag_timer22us = 1;
//	gpio_set_level(GPIO_NUM_2, ledPin);
//	ledPin = !ledPin;
} //hardTime_callback()


esp_err_t set_timers(void) {

	//RTOS soft-timer:
	xTimer = xTimerCreate(	"Timer_control",  // Just a text name, not used by the kernel.
							pdMS_TO_TICKS(10), // periodo del timer en ticks. La fucion pdMS_TO_TICKS convierte de ms a ticks.
							pdTRUE,  // The timers will auto-reload themselves when they expire.
							(void *)timerId,  // Assign to this timer an unique id.
							vTimerCallback // This timer calls the callback when it expires.
							);

	if (xTimer == NULL) {
		// The timer was not created.
	} else {

		if ( xTimerStart( xTimer, 0 ) != pdPASS) {
			// The timer could not be set into the Active state.
		}
	}

	//ESP32 hard-timer:
	esp_timer_create_args_t timer_args = {
			.callback = hardTimer_callback,
			.arg = NULL,
			.name = "timer_22us"
	};
	esp_timer_create(&timer_args, &hTimer);

	// Inicio del timer periódico
	esp_timer_start_periodic(hTimer, 22);  // 22 microsegundos -> 45454 Hz


	return ESP_OK;

} //fin set_timer ()


void config_gpio(void)
{
    //ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(PIN_LED);
    gpio_reset_pin(PIN_IN_ATRAS);
    gpio_reset_pin(PIN_IN_MODO);
    gpio_reset_pin(PIN_IN_START_STOP);
    gpio_reset_pin(PIN_IN_ADELANTE);

    gpio_set_direction(PIN_IN_ATRAS, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_IN_MODO, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_IN_START_STOP, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_IN_ADELANTE, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT);

    gpio_set_pull_mode(PIN_IN_ATRAS, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_IN_MODO, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_IN_START_STOP, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_IN_ADELANTE, GPIO_PULLUP_ONLY);
} //fin config_gpio()


void set_pwm (void){

    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_10_BIT, // Set duty resolution to 10 bits
        .freq_hz          = 44100,  // Set output frequency at 44,1 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = PIN_PWM,
        .duty           = 511, // Set duty to 50%. ((2 ** 10) - 1) * 50% = 4095
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

} //fin set_pwm()
