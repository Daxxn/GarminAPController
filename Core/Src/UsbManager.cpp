/*
 * UsbManager.cpp
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#include <UsbManager.h>
#include "usb_device.h"

UsbManager::UsbManager(
		TIM_HandleTypeDef     *htim,
		StatusUnion           *status,
		ButtonManager         *buttons,
		IndicatorManager      *indicators,
		EncoderManager        *encoders,
		OptionsChangedCallback optionsCallback
	)
{
	this->htim       = htim;
	this->buttons    = buttons;
	this->indicators = indicators;
	this->encoders   = encoders;
	this->txBuffer   = new uint8_t[USB_TXBUFFER_LEN]();
	this->rxBuffer   = new uint8_t[USB_RXBUFFER_LEN]();
	this->status     = status;
	this->optionsCallback = optionsCallback;
}

UsbManager::~UsbManager()
{
	delete[] this->txBuffer;
	delete[] this->rxBuffer;
}

void UsbManager::UsbReceivedCallback(uint8_t *buffer, uint32_t *len)
{
	for (uint32_t i = 0; i < *len; ++i) {
		this->rxBuffer[i] = buffer[i];
	}
	this->rxLen = *len;
	this->dataReceivedFlag = true;
}

void UsbManager::Update()
{
	if (this->dataReceivedFlag) {
		this->ParseCommand();
		this->dataReceivedFlag = false;
	}
}

void UsbManager::StreamDataCallback()
{
	if (!this->streamFlag) return;

	// If it takes too long in the callback, I can just
	// set the flag and move this to the update method.
	if (this->buttons->GetStateChanged() || this->encoders->GetStateChanged()) {
		this->txBuffer[0] = (uint8_t)RX_STREAM;
		this->buttons->GetButtons(this->txBuffer + 1);
//		this->encoders->GetPositions(this->txBuffer + 4);
		this->encoders->GetDirections(this->txBuffer + 4);
		UsbTransmitData(this->txBuffer, RX_STREAM_LEN + 1);
	}
}

void UsbManager::ParseCommand()
{
	this->currentCmd = (UsbCommand)this->rxBuffer[0];

	switch (this->currentCmd) {
		case TX_START_STREAM:
			if (HAL_TIM_Base_Start_IT(this->htim) != HAL_OK) {
				this->streamFlag = false;
			}
			this->streamFlag = true;
			break;
		case TX_STOP_STREAM:
			HAL_TIM_Base_Stop_IT(this->htim);
			this->streamFlag = false;
			break;
		case RX_BUTTONS:
			if (this->streamFlag) {
				this->SendError();
				break;
			}
			this->txBuffer[0] = (uint8_t)RX_BUTTONS;
			this->buttons->GetButtons(this->txBuffer + 1);
			UsbTransmitData(this->txBuffer, RX_BUTTONS_LEN + 1);
			break;
		case RX_ENC_POS:
			if (this->streamFlag) {
				this->SendError();
				break;
			}
			this->txBuffer[0] = (uint8_t)RX_ENC_POS;
			this->encoders->GetPositions(this->txBuffer + 1);
			UsbTransmitData(this->txBuffer, RX_ENCODERS_LEN + 1);
			break;
		case RX_ENC_DIR:
			this->txBuffer[0] = (uint8_t)RX_ENC_DIR;
			this->encoders->GetDirections(this->txBuffer + 1);
			UsbTransmitData(this->txBuffer, RX_ENC_DIR_LEN + 1);
			break;
		case TX_INDICATORS:
			this->indicators->ParseIndicators(this->rxBuffer + 1);
			break;
		case TX_BACKLIGHT:
			this->u16UnionTemp.bytes[0] = this->rxBuffer[1];
			this->u16UnionTemp.bytes[1] = this->rxBuffer[2];
			this->indicators->SetBacklight(this->u16UnionTemp.integer);
			break;
		case TX_IND_BRIGHT:
			this->u16UnionTemp.bytes[0] = this->rxBuffer[1];
			this->u16UnionTemp.bytes[1] = this->rxBuffer[2];
			this->indicators->SetIndBrightness(this->u16UnionTemp.integer);
			break;
		case TX_MAX_IND_BRIGHT:
			this->indicators->SetMaxIndBrightness(this->rxBuffer[1]);
			break;
		case TX_OPTIONS:
			this->status->obj.options.byte = this->rxBuffer[1];
			if (this->optionsCallback != NULL) {
				this->optionsCallback(&this->status->obj.options);
			}
			break;
		case RX_STATUS:
			if (this->streamFlag) break;
			this->txBuffer[0] = (uint8_t)RX_STATUS;
			this->txBuffer[1] = this->status->bytes[0];
			this->txBuffer[2] = this->status->bytes[1];
			this->txBuffer[3] = this->status->bytes[2];
			UsbTransmitData(this->txBuffer, RX_BUTTONS_LEN + 1);
			break;
		case RX_HELLO:
			this->txBuffer[0] = (uint8_t)RX_HELLO;
			this->streamFlag = false;
			UsbTransmitData(this->txBuffer, 1);
		default:
			break;
	}
}

void UsbManager::SendError()
{
	this->txBuffer[0] = (uint8_t)RX_TX_ERROR;
	UsbTransmitData(txBuffer, 1);
}
