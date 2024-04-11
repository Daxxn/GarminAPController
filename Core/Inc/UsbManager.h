/*
 * UsbManager.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_USBMANAGER_H_
#define INC_USBMANAGER_H_

#include "main.h"
#include "ButtonManager.h"
#include "IndicatorManager.h"
#include "EncoderManager.h"
#include "Status.h"
#include "Utils.h"

#define USB_TXBUFFER_LEN 24
#define USB_RXBUFFER_LEN 56

// RX and TX are from the perspective of the host.
typedef enum : uint8_t {
	RX_BUTTONS        = 0x02,
	RX_ENC_DIR        = 0x03,
	RX_ENC_POS        = 0x04,
	RX_STREAM         = 0x05,
	RX_STATUS         = 0xF2,
	TX_INDICATORS     = 0x06,
	TX_BACKLIGHT      = 0x08,
	TX_IND_BRIGHT     = 0x09,
	TX_MAX_IND_BRIGHT = 0x0A,
	TX_START_STREAM   = 0x11,
	TX_STOP_STREAM    = 0x12,
	TX_OPTIONS        = 0xF1,
	RX_TX_ERROR       = 0xFF,
	RX_HELLO          = 0xFE,
} UsbCommand;

typedef enum {
	RX_BUTTONS_LEN    = 3,
	RX_ENCODERS_LEN   = 2,
	RX_ENC_DIR_LEN    = 2,
	RX_STATUS_LEN     = 3,
	RX_STREAM_LEN     = RX_BUTTONS_LEN + RX_ENCODERS_LEN,
//	TX_BRIGHTNESS_LEN = 2,
//	TX_INDICATORS_LEN = 2,
//	TX_OPTIONS_LEN    = 1
} UsbResponseSize;

typedef void (*OptionsChangedCallback) (OptionStatesUnion *options);

/*
 *
 */
class UsbManager
{
public:
	UsbManager() { };
	UsbManager(
			TIM_HandleTypeDef     *htim,
			StatusUnion           *status,
			ButtonManager         *buttons,
			IndicatorManager      *indicators,
			EncoderManager        *encoders,
			OptionsChangedCallback optionsCallback
		);
	virtual ~UsbManager();

	void UsbReceivedCallback(uint8_t *buffer, uint32_t *len);
	void StreamDataCallback();

	void Update();
	void Test();
private:
	TIM_HandleTypeDef *htim;
	ButtonManager     *buttons;
	IndicatorManager  *indicators;
	EncoderManager    *encoders;

	UsbCommand  currentCmd;
	uint8_t    *rxBuffer;
	uint8_t    *txBuffer;
	uint32_t    rxLen;
	bool        dataReceivedFlag = false;
	bool        streamFlag = false;

	UInt16Union  u16UnionTemp;
	StatusUnion *status;

	OptionsChangedCallback optionsCallback;

	void ParseCommand();
	void SendError();
};

#endif /* INC_USBMANAGER_H_ */
