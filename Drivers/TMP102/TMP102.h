#ifndef TMP102_H
#define TMP102_H

#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"

#define TMP_VAL_ADDR 0x00

typedef struct TMP102_t {
    // Device
    I2C_HandleTypeDef* i2c;
    uint8_t            address;
    HAL_StatusTypeDef  status;

    // Config
    uint8_t timeout;

    // Outputs
    int16_t t_reg;

    // Test
    float t_val;  // C

} TMP102_t;

HAL_StatusTypeDef TMP102_init(TMP102_t* dev, I2C_HandleTypeDef* hi2c, uint8_t addr);
HAL_StatusTypeDef TMP102_getVal(TMP102_t* dev);

#endif