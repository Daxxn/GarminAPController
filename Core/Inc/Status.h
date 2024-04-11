/*
 * Status.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_STATUS_H_
#define INC_STATUS_H_

#include "main.h"
#include "Options.h"

typedef enum : uint8_t {
	STATE_RUNNING = 1,
	STATE_PAUSED  = 2,
	STATE_WAITING = 3,
	STATE_ERROR   = 0,
} State;

typedef enum : uint8_t {
	AUX_DEV_OFF,
	AUX_DEV_CONNECTED,
	AUX_DEV_PAUSED,
	AUX_DEV_RUNNING,
	AUX_DEV_DISCONNECTED,
} AuxDeviceState;

typedef struct {
	State state;
	AuxDeviceState auxState;
	OptionStatesUnion options;
} Status;

typedef union {
	Status obj;
	uint8_t bytes[3];
} StatusUnion;

#endif /* INC_STATUS_H_ */
