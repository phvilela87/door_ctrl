/*
 * door_ctrl.c
 *
 *  Created on: Nov 7, 2022
 *      Author: pe055589
 */

#include <stdbool.h>

#include "door_ctrl.h"
#include "main.h"

typedef enum {
	IDLE = 0,
	OPEN,
	WAIT,
	CLOSE
} step;

static step st = IDLE;
static bool idle = true;
static uint8_t openning_time = 3; /** default - 3 seconds */

void door_ctrl_process(void)
{
	static uint32_t ref_time = 0;

	switch (st) {
	case IDLE:
		break;
	case OPEN:
		idle = false;
		HAL_GPIO_WritePin(OUTPUT_GPIO_Port, OUTPUT_Pin, GPIO_PIN_RESET);
		ref_time = HAL_GetTick();
		st = WAIT;
		break;
	case WAIT:
		((ref_time > HAL_GetTick()) ? (ref_time = HAL_GetTick()) : (((HAL_GetTick() - ref_time) >= (openning_time * 1000)) ? (st = CLOSE) : (UNUSED(1))));
		break;
	case CLOSE:
		HAL_GPIO_WritePin(OUTPUT_GPIO_Port, OUTPUT_Pin, GPIO_PIN_SET);
		idle = true;
		st = IDLE;
		break;
	default:
		break;
	}
}

void read_config(void)
{
	if (HAL_GPIO_ReadPin(TIME_1_GPIO_Port, TIME_1_Pin) == GPIO_PIN_RESET) {
		openning_time = 1;
	} else if (HAL_GPIO_ReadPin(TIME_3_GPIO_Port, TIME_3_Pin) == GPIO_PIN_RESET) {
		openning_time = 3;
	} else if (HAL_GPIO_ReadPin(TIME_5_GPIO_Port, TIME_5_Pin) == GPIO_PIN_RESET) {
		openning_time = 5;
	} else if (HAL_GPIO_ReadPin(TIME_10_GPIO_Port, TIME_10_Pin) == GPIO_PIN_RESET) {
		openning_time = 10;
	} else {
		openning_time = 3;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (idle) st = OPEN;
}

