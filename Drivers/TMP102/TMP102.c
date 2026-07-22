#include "TMP102.h"

#include <stdint.h>

#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_i2c.h"

HAL_StatusTypeDef TMP102_init(TMP102_t* dev, I2C_HandleTypeDef* hi2c, uint8_t addr) {
    dev->i2c     = hi2c;
    dev->address = addr;

    dev->timeout = 100;

    HAL_StatusTypeDef status = HAL_OK;
    return status;
}

HAL_StatusTypeDef TMP102_getVal(TMP102_t* dev) {
    uint8_t           buf[2];
    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Read(dev->i2c, dev->address, TMP_VAL_ADDR, I2C_MEMADD_SIZE_8BIT, buf, 2, dev->timeout);

    if (status != HAL_OK) {
        dev->status = HAL_ERROR;
        return HAL_ERROR;
    }

    dev->t_reg = ((buf[0] << 4) | buf[1] >> 4);
    dev->t_val = (float) (dev->t_reg * 0.0625f);

    return status;
}
