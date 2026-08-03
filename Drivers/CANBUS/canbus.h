#ifndef CANBUS_H
#define CANBUS_H

#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_can.h"
#include "stm32f1xx_hal_def.h"
#include "structs.h"

typedef enum {
    CAN_ID_STA = 0x300,
    CAN_ID_ENC = 0x301
} Txid_t;

typedef enum {
    SET_MODE = 0x400,
    DATA_REQ = 0x401,
    CMD_VEL  = 0x402
}
Rxid_t;

typedef enum {
    GET_STAT    = 0x00,
    GET_ENC     = 0x01,
    GET_ALL     = 0x02,
    SET_PWR_ON  = 0x03,
    SET_PWR_SAV = 0x04
} Req_t;

extern CAN_HandleTypeDef   hcan;
extern uint8_t             TxData[8];
extern CAN_RxHeaderTypeDef RxHeader;
extern uint8_t             RxData[8];

void              can_init(CAN_HandleTypeDef* hcan);
HAL_StatusTypeDef can_transmit(uint32_t txID);
HAL_StatusTypeDef can_transmit_sta(MotorController* mc);
// HAL_StatusTypeDef can_transmit_enc(MotorController* mc);

#endif