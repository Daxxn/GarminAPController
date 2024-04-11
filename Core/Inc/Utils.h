/*
 * Utils.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "main.h"

typedef enum {
	// Because ACTIVE_HIGH is assigned 0, it sets the default sigal low.
	ACTIVE_HIGH = 0,
	ACTIVE_LOW = 1,
} GPIO_Default_State;

typedef union {
	uint16_t integer;
	uint8_t bytes[2];
} UInt16Union;

typedef union {
	uint32_t integer;
	uint8_t bytes[4];
} UInt32Union;

typedef union {
	uint64_t integer;
	uint8_t bytes[8];
} UInt64Union;

typedef union {
	int16_t integer;
	uint8_t bytes[2];
} Int16Union;

typedef union {
	int32_t integer;
	uint8_t bytes[4];
} Int32Union;

typedef union {
	int64_t integer;
	uint8_t bytes[8];
} Int64Union;

typedef union {
	float number;
	uint8_t bytes[4];
} FloatUnion;

typedef union {
	double number;
	uint8_t bytes[8];
} DoubleUnion;

#if __cplusplus

struct Pin
{
	// Defaults to output pin
	Pin() {};
	// Defaults to output pin
	Pin(GPIO_TypeDef* port, uint16_t pin)
	{
		this->port = port;
		this->pin = pin;
		this->defaultState = ACTIVE_HIGH;
	};
	Pin(GPIO_TypeDef* port, uint16_t pin, bool isOutput)
	{
		this->port = port;
		this->pin = pin;
		this->defaultState = ACTIVE_LOW; // I usually use an active low switch setup.
		this->isOutput = isOutput;
	};
	Pin(GPIO_TypeDef* port, uint16_t pin, GPIO_Default_State defaultState)
	{
		this->port = port;
		this->pin = pin;
		this->defaultState = defaultState;
		this->isOutput = true;
	};
	Pin(GPIO_TypeDef* port, uint16_t pin, GPIO_Default_State defaultState, bool isOutput)
	{
		this->port = port;
		this->pin = pin;
		this->defaultState = defaultState;
		this->isOutput = isOutput;
	};

	void Write(GPIO_PinState state) {
		if (this->enable && this->isOutput)
		{
			this->state = state;
			HAL_GPIO_WritePin(this->port, this->pin, (GPIO_PinState)(state ^ this->defaultState));
		}
	};
	void Write(bool state) {
		this->Write((GPIO_PinState)state);
	};
	GPIO_PinState Read() {
		if (this->enable && !this->isOutput)
		{
			this->state = (GPIO_PinState)(HAL_GPIO_ReadPin(this->port, this->pin) ^ this->defaultState);
		}
		return this->state;
	};
	bool Read(int &&_)
	{
		if (this->enable && !this->isOutput)
		{
			return (bool)(this->Read());
		}
		return (bool)this->state;
	};
	void Toggle() {
		if (this->enable && this->isOutput)
		{
			HAL_GPIO_TogglePin(this->port, this->pin);
			this->state = (GPIO_PinState)!this->state;
		}
	};
	void Clear() {
		if (this->enable && this->isOutput)
		{
			this->state = (GPIO_PinState)this->defaultState;
			HAL_GPIO_WritePin(this->port, this->pin, (GPIO_PinState)this->defaultState);
		}
	};
	GPIO_PinState GetState() {
		return this->state;
	};
	bool GetState(int &&_) {
		return (bool)this->state;
	};
	void Enable(bool en) {
		this->enable = en;
	}
private:
	GPIO_TypeDef      *port;
	uint16_t           pin;
	GPIO_Default_State defaultState;
	GPIO_PinState      state;
	bool               isOutput = true;
	bool               enable   = true;
};

struct PWMPin
{
public:
	PWMPin() {};
	PWMPin(TIM_HandleTypeDef *htim, uint32_t ch) {
		this->htim = htim;
		this->ch = ch;
	}
	HAL_StatusTypeDef Init() {
		return HAL_TIM_PWM_Start(this->htim, this->ch);
	}
	HAL_StatusTypeDef Deinit() {
		return HAL_TIM_PWM_Stop(this->htim, this->ch);
	}
	void Set(uint16_t pwm) {
		__HAL_TIM_SET_COMPARE(this->htim, this->ch, pwm);
	}
private:
	TIM_HandleTypeDef *htim;
	uint32_t           ch;
};

#endif /* __cplusplus */
#endif /* INC_UTILS_H_ */
