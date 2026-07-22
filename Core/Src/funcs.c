#include "structs.h"

void mc_init(MotorController* mc, TIM_HandleTypeDef* tim) {
    mc->tim = tim;

    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, 0);
}

void set_motor_vals(Motor_t* mt) {
    if (mt->en_uns > EN_MAX_ZONE || mt->en_uns < -EN_MAX_ZONE) {
        mt->en_a = 0xFFFF;
        mt->en_b = 0xFFFF;
        return;
    }
    if (mt->en_uns > EN_DEAD_ZONE) {
        mt->en_a = (uint16_t) (mt->en_uns);
        mt->en_b = 0;
        return;
    }
    if (mt->en_uns < -EN_DEAD_ZONE) {
        mt->en_a = 0;
        mt->en_b = (uint16_t) (-mt->en_uns);
        return;
    }
    mt->en_a = 0;
    mt->en_b = 0;
}

void mc_set_motors(MotorController* mc) {
    set_motor_vals(&mc->motor_l);
    set_motor_vals(&mc->motor_r);

    __HAL_TIM_SET_COMPARE(mc->tim, TIM_CHANNEL_1, mc->motor_l.en_a);
    __HAL_TIM_SET_COMPARE(mc->tim, TIM_CHANNEL_2, mc->motor_l.en_b);
    __HAL_TIM_SET_COMPARE(mc->tim, TIM_CHANNEL_3, mc->motor_r.en_a);
    __HAL_TIM_SET_COMPARE(mc->tim, TIM_CHANNEL_4, mc->motor_r.en_b);
}
