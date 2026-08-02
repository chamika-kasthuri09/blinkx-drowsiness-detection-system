#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "pin_config.h"

// State Variables
static uint32_t eye_closed_start_time = 0;
static uint8_t is_eye_closed = 0;

// Initialize GPIO Hardware for Haptic Motor
void init_actuator(void) {
    gpio_reset_pin(MOTOR_DRIVER_PIN);
    gpio_set_direction(MOTOR_DRIVER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(MOTOR_DRIVER_PIN, 0); // Initially OFF
}

// Initialize ADC Hardware for TCRT5000 IR Sensor
void init_adc(void) {
    adc1_config_width(ADC_WIDTH_BIT_12); // 0 to 4095 raw range
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
}

// Control Haptic Vibration Motor
void set_haptic_alert(uint8_t enable) {
    gpio_set_level(MOTOR_DRIVER_PIN, enable ? 1 : 0);
}

// Main Edge Safety Loop (FreeRTOS Task in C)
void app_main(void) {
    printf("[BlinkX Edge Firmware] Initializing C Safety Core...\n");
    
    init_actuator();
    init_adc();

    printf("[BlinkX Edge Firmware] Core Running successfully.\n");

    while (1) {
        // Read raw 12-bit ADC value from TCRT5000 IR sensor
        int raw_adc = adc1_get_raw(ADC1_CHANNEL_3);
        uint32_t current_time_ms = xTaskGetTickCount() * portTICK_PERIOD_MS;

        // Eyelid Closure Logic State Machine
        if (raw_adc >= EYELID_CLOSED_ADC_MIN) {
            if (!is_eye_closed) {
                is_eye_closed = 1;
                eye_closed_start_time = current_time_ms;
            } 
            else if ((current_time_ms - eye_closed_start_time) >= BLINK_TIME_LIMIT_MS) {
                // Micro-sleep detected! Trigger tactile warning immediately
                set_haptic_alert(1);
                printf("CRITICAL ALERT: Micro-sleep detected (>350ms)! ADC: %d\n", raw_adc);
            }
        } else {
            is_eye_closed = 0;
            set_haptic_alert(0); // Reset haptic motor
        }

        // Run loop at 50Hz (20ms polling interval for low latency)
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
