#include <stdio.h>
#include "./driver/gpio.h"
#include "./freertos/FreeRTOS.h"
#include "./freertos/task.h"
#include "./driver/adc.h"
#include "./driver/uart.h"

#define Moisture_Sensor_Pin GPIO_NUM_4

void app_main(void)
{
    // INITIALIZING GPIO16 AS INPUT PULL_UP MODE
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_16, GPIO_PULLUP_ONLY);

    // INITIALIZING GPIO2 AS OUTPUT MODE
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    int led_state = 0;

    while (true)
    {
        if (isButton1Pressed()) // pressed
        {
            printf("Hello world!\n");
            if (led_state == 1)
            {
                led_state = 0;
            }
            else
                led_state = 1;
        }
        gpio_set_level(GPIO_NUM_2, led_state);

        getKeyInput();
        vTaskDelay(1);
    }
}
