#ifndef STRUCTS
#define STRUCTS

#include <stdint.h>

#include "TMP102.h"
#include "stm32f1xx_hal_tim.h"

#define EN_DEAD_ZONE 10
#define EN_MAX_ZONE  400

typedef struct Motor_t {
    int16_t  en_uns;
    uint16_t en_a;
    uint16_t en_b;

    uint32_t enc;
} Motor_t;

typedef struct MotorController {
    union {
        struct {
            uint16_t mode : 2;

            uint16_t req_stat : 1;
            uint16_t req_enc : 1;
            uint16_t req_all : 1;
            uint16_t req : 2;
        } bits;
        uint16_t raw;
    } state;

    TIM_HandleTypeDef* tim;

    Motor_t motor_r;
    Motor_t motor_l;

    TMP102_t tmp;
} MotorController;

void mc_init(MotorController* mc, TIM_HandleTypeDef* tim);
void mc_set_motors(MotorController* mc);

#endif