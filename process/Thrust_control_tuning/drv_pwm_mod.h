/*
 *  drv_pwm.h
 *
 *  Created on: 2016. 7.12.
 *      Author: Baram, PBHP
 */

#ifndef DRV_PWM_MOD_H
#define DRV_PWM_MOD_H


#ifdef __cplusplus
 extern "C" {
#endif


#include "def.h"
#include "bsp.h"

extern TIM_HandleTypeDef    hTIM1;
extern TIM_HandleTypeDef    hTIM2;
extern TIM_HandleTypeDef    hTIM3;
extern TIM_HandleTypeDef    hTIM4;


void drv_pwm_set_duty_mod(uint32_t ulPin, uint32_t res, uint32_t ulDuty );

void drv_pwm_set_data_mod(uint32_t ulPin, uint32_t pwm_data );






#ifdef __cplusplus
}
#endif


#endif
