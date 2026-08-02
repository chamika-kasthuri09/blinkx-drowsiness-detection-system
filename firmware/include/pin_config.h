#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include <stdint.h>

// GPIO Pin Mappings (ESP32-C3)
#define IR_SENSOR_ADC_PIN   4   // TCRT5000 Analog Out (ADC1_CH3)
#define MOTOR_DRIVER_PIN    5   // NPN Transistor Base Output Pin
#define I2C_SDA_PIN        21   // MPU-6050 SDA
#define I2C_SCL_PIN        22   // MPU-6050 SCL

// Safety Threshold Constants
#define EYELID_CLOSED_ADC_MIN   2500  // ADC reading cutoff for closed eyelid
#define BLINK_TIME_LIMIT_MS      350  // Micro-sleep limit (350 ms)
#define HEAD_PITCH_LIMIT_DEG     -15  // Head nod limit (-15 degrees)

#endif // PIN_CONFIG_H
