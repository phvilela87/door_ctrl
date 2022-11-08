/*
 * door_ctrl.h
 *
 *  Created on: Nov 7, 2022
 *      Author: pe055589
 */

#ifndef INC_DOOR_CTRL_H_
#define INC_DOOR_CTRL_H_

#define door_ctrl_IRQHandler		EXTI4_15_IRQHandler

void door_ctrl_process(void);
void read_config(void);

#endif /* INC_DOOR_CTRL_H_ */
