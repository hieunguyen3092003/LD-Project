#include <stdio.h>
#include "./driver/gpio.h"
#include "./freertos/FreeRTOS.h"
#include "./freertos/task.h"
#include "./driver/adc.h"
#include "./driver/uart.h"

#define Moisture_Sensor_Pin GPIO_NUM_4

void app_main(void)
{
    // INITIALIZING GPIO22 AS INPUT PULL_UP MODE
    // gpio_set_direction(GPIO_NUM_16, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(GPIO_NUM_16, GPIO_PULLUP_ONLY);

    // // INITIALIZING GPIO22 AS OUTPUT MODE
    // gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    // int led_state = 0;

    // while (true)
    // {
    //     if (isButton1Pressed()) // not pressed
    //     {
    //         printf("Hello world!\n");
    //         if (led_state == 1)
    //         {
    //             led_state = 0;
    //         }
    //         else
    //             led_state = 1;
    //     }
    //     gpio_set_level(GPIO_NUM_2, led_state);

    //     getKeyInput();
    //     vTaskDelay(1);
    // }

    // const int AirValue = 520;
    // const int WaterValue = 260;
    int soilMoistureValue = 0;

    uart_set_baudrate(UART_NUM_0, 9600);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(Moisture_Sensor_Pin, ADC_ATTEN_DB_11);

    while (1)
    {
        soilMoistureValue = adc1_get_raw(ADC1_CHANNEL_2);

        printf("Gia tri analog tu cam bien dat: %d\n", soilMoistureValue);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // gpio_set_direction(Moisture_Sensor_Pin, GPIO_MODE_INPUT);
}
