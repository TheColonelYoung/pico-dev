#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

//#include <FreeRTOS.h>
//#include <task.h>

#include "sensor_test.hpp"

const int LED_PIN = 25;

void LED_ON(void* unused_arg){
    //vTaskDelay(100);
    gpio_put(LED_PIN, 1);
    //vTaskDelay(100);

}

void LED_TOGLE(){
    sleep_ms(100);
    gpio_put(LED_PIN, 1);
    sleep_ms(100);
    gpio_put(LED_PIN, 0);
}

void LED_OFF(void* unused_arg){
    gpio_put(LED_PIN, 0);
    //vTaskDelay(200);
}

int main ()
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    //xTaskCreate(LED_ON, "PICO_LED_TASK_ON", 128, NULL, 1, NULL);
    //xTaskCreate(LED_OFF, "PICO_LED_TASK_OFF", 128, NULL, 1, NULL);

    //vTaskStartScheduler();

    // We should never get here, but just in case...
    while(true) {
        LED_TOGLE();
    };
}
