#include "canbus.h"

#include <stdint.h>

#include "stm32f1xx_hal_can.h"
#include "stm32f1xx_hal_def.h"
// #include "structs.h"

uint16_t            readValue;
CAN_TxHeaderTypeDef TxHeader;
uint32_t            TxMailbox;
uint8_t             TxData[8];

CAN_FilterTypeDef   sFilterConfig;
CAN_RxHeaderTypeDef RxHeader;
uint8_t             RxData[8];

void can_init(CAN_HandleTypeDef* hcan) {
    HAL_CAN_Start(hcan);

    TxHeader.IDE   = CAN_ID_STD;
    TxHeader.RTR   = CAN_RTR_DATA;
    TxHeader.DLC   = 8;
    TxHeader.StdId = CAN_ID_STA;

    CAN_FilterTypeDef filter;
    filter.FilterActivation     = CAN_FILTER_ENABLE;
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO1;
    filter.FilterMode           = CAN_FILTERMODE_IDMASK;
    filter.FilterScale          = CAN_FILTERSCALE_32BIT;

    filter.FilterBank = 0;

    // Base ID = 0x400
    filter.FilterIdHigh = (0x400 << 5);
    filter.FilterIdLow  = 0;

    // Mask = 0x700 → match only upper 8 bits (0x4xx)
    filter.FilterMaskIdHigh = (0x700 << 5);
    filter.FilterMaskIdLow  = 0;

    HAL_CAN_ConfigFilter(hcan, &filter);
    HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO1_MSG_PENDING);
}

HAL_StatusTypeDef can_transmit(uint32_t txID) {
    TxHeader.StdId = txID;
    switch (txID) {
        case CAN_ID_STA:
            TxHeader.DLC = 4;
            break;
        case CAN_ID_ENC:
            TxHeader.DLC = 8;
            break;
        default:
            TxHeader.DLC = 8;
            break;
    }

    if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
        HAL_Delay(1);
    HAL_StatusTypeDef status = HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox);
    return status;
}

HAL_StatusTypeDef can_transmit_sta(MotorController* mc) {
    TxData[0] = (mc->state.raw >> 0) & 0xFF;
    TxData[1] = (mc->state.raw >> 8) & 0xFF;
    TxData[2] = (mc->tmp.t_reg >> 0) & 0xFF;
    TxData[3] = (mc->tmp.t_reg >> 8) & 0xFF;
    return can_transmit(CAN_ID_STA);
}
