/*
 * MainWrapper.cpp
 *
 *  Created on: Mar 9, 2024
 *      Author: Daxxn
 */

#include "main.h"
#include "usb_device.h"
#include "STPLEDDriver.h"
#include "UsbManager.h"
#include "IndicatorManager.h"
#include "ButtonManager.h"
#include "RotaryEncoder.h"
#include "EncoderManager.h"
#include "Status.h"
#include "Options.h"
#include "Utils.h"

OptionStatesUnion optionStates;
Options options;

StatusUnion status;

UsbManager usbManager;

ADC_HandleTypeDef  *h_adc;
SPI_HandleTypeDef  *h_spi;
TIM_HandleTypeDef  *h_brgt_tim;
TIM_HandleTypeDef  *h_stream_tim;
UART_HandleTypeDef *h_serial;

Pin alt_a_pin;
Pin alt_b_pin;
Pin crs1_a_pin;
Pin crs1_b_pin;
Pin crs2_a_pin;
Pin crs2_b_pin;
Pin hdg_a_pin;
Pin hdg_b_pin;
Pin whl_a_pin;
Pin whl_b_pin;

Pin alt_sw_pin;
Pin crs1_sw_pin;
Pin crs2_sw_pin;
Pin hdg_sw_pin;

Pin alt_btn_pin;
Pin apr_btn_pin;
Pin bank_btn_pin;
Pin bc_btn_pin;
Pin fd_btn_pin;
Pin flc_btn_pin;
Pin hdg_btn_pin;
Pin nav_btn_pin;
Pin ap_btn_pin;
Pin spd_btn_pin;
Pin vnv_btn_pin;
Pin vs_btn_pin;
Pin xfr_btn_pin;
Pin yd_btn_pin;

ButtonPins btnPins;
ButtonManager btnManager;

// Encoder Variables
RotaryEncoder hdgEncoder;
RotaryEncoder altEncoder;
RotaryEncoder whlEncoder;
RotaryEncoder crs1Encoder;
RotaryEncoder crs2Encoder;

RotaryEncoder encoders[ENCODER_COUNT];
EncoderManager encManager;

Pin status_ind_pin;
Pin usart_inval_pin;
Pin usb_usart_sel_pin;

Pin brgt_cs_pin;
Pin brgt_ud_pin;

Pin ind_la_pin;

PWMPin backlight;

Pin aux_in_pin;
Pin aux_out_pin;
Pin bklgt_in_pin;
Pin bklgt_out_pin;

// Indicator Variables
MCP4023Driver indBlDriver;
STPLEDDriver indDriver;
IndicatorManager indManager;

// Testing Variables
uint8_t indicatorCount = 0;
uint16_t indicatorBright = 0;

// Function definitions:
static void StartupTest();
static void InitEncoders();
static void InitButtons();
static void InitControlPins();
static void InitIndicators();
static void InitEncoders();
static void InitAuxIO();
static void HandleOptionsCallback(OptionStatesUnion *options);

void EncInterruptCallback(uint16_t pinNumber)
{
	switch (pinNumber) {
		case CRS1_A_Pin:
			crs1Encoder.OnInterrupt();
			break;
		case CRS2_A_Pin:
			crs2Encoder.OnInterrupt();
			break;
		case HDG_A_Pin:
			hdgEncoder.OnInterrupt();
			break;
		case ALT_A_Pin:
			altEncoder.OnInterrupt();
			break;
		case WHEEL_A_Pin:
			whlEncoder.OnInterrupt();
			break;
		default:
			break;
	}
}

void UsbReceiveCallback(uint8_t *buffer, uint32_t *len)
{
	// Ive simplified like mad. Its all done through the basic virtual COM port.
	// In the future, i want to convert it over to either a HID device or some kind of
	// custom interface. Possibly with a custom driver.
	usbManager.UsbReceivedCallback(buffer, len);
}

void TimerElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == h_stream_tim) {
		usbManager.StreamDataCallback();
	}
}

HAL_StatusTypeDef Init(
		ADC_HandleTypeDef  *hadc,
		SPI_HandleTypeDef  *hspi1,
		TIM_HandleTypeDef  *htim15,
		UART_HandleTypeDef *huart3,
		TIM_HandleTypeDef  *htim7
	)
{
	h_adc        = hadc;
	h_spi        = hspi1;
	h_brgt_tim   = htim15;
	h_serial     = huart3;
	h_stream_tim = htim7;

	options = Options(&optionStates);

	InitAuxIO();

	InitControlPins();

	InitEncoders();

	InitButtons();

	InitIndicators();

	usbManager = UsbManager(
			h_stream_tim,
			&status,
			&btnManager,
			&indManager,
			&encManager,
			HandleOptionsCallback
		);

	RegisterUSBReceiveCallback(UsbReceiveCallback);

	if (indDriver.Init() != HAL_OK) {
		return HAL_ERROR;
	}

	indDriver.SetBrightness(UINT16_MAX);
	indManager.SetBacklight(0);

	HandleOptionsCallback(&(status.obj.options));

	StartupTest();

	return HAL_OK;
}

void Main()
{
	status_ind_pin.Toggle();

	btnManager.Update();
	usbManager.Update();

	// Not working right.
	// It doesnt ever change the position.
//	crs2Encoder.Update();

//	HAL_Delay(20);
}

// Initialization Functions:
static void InitButtons()
{
	btnPins = ButtonPins();
	// Rotary Encoder Push Buttons
	alt_sw_pin       = Pin(ALT_SW_GPIO_Port,  ALT_SW_Pin,  ACTIVE_LOW, false);
	btnPins.alt_enc  = alt_sw_pin;
	crs1_sw_pin      = Pin(CRS1_SW_GPIO_Port, CRS1_SW_Pin, ACTIVE_LOW, false);
	btnPins.crs1_enc = crs1_sw_pin;
	crs2_sw_pin      = Pin(CRS2_SW_GPIO_Port, CRS2_SW_Pin, ACTIVE_LOW, false);
	btnPins.crs2_enc = crs2_sw_pin;
	hdg_sw_pin       = Pin(HDG_SW_GPIO_Port,  HDG_SW_Pin,  ACTIVE_LOW, false);
	btnPins.hdg_enc  = hdg_sw_pin;

	// Front Panel Input Buttons
	alt_btn_pin  = Pin(ALT_BTN_GPIO_Port,  ALT_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.alt  = alt_btn_pin;
	apr_btn_pin  = Pin(APR_BTN_GPIO_Port,  APR_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.apr  = apr_btn_pin;
	bank_btn_pin = Pin(BANK_BTN_GPIO_Port, BANK_BTN_Pin, ACTIVE_LOW, false);
	btnPins.bank = bank_btn_pin;
	bc_btn_pin   = Pin(BC_BTN_GPIO_Port,   BC_BTN_Pin,   ACTIVE_LOW, false);
	btnPins.bc   = bc_btn_pin;
	fd_btn_pin   = Pin(FD_BTN_GPIO_Port,   FD_BTN_Pin,   ACTIVE_LOW, false);
	btnPins.fd   = fd_btn_pin;
	flc_btn_pin  = Pin(FLC_BTN_GPIO_Port,  FLC_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.flc  = flc_btn_pin;
	hdg_btn_pin  = Pin(HDG_BTN_GPIO_Port,  HDG_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.hdg  = hdg_btn_pin;
	nav_btn_pin  = Pin(NAV_BTN_GPIO_Port,  NAV_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.nav  = nav_btn_pin;
	ap_btn_pin   = Pin(AP_BTN_GPIO_Port,   AP_BTN_Pin,   ACTIVE_LOW, false);
	btnPins.ap   = ap_btn_pin;
	spd_btn_pin  = Pin(SPD_BTN_GPIO_Port,  SPD_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.spd  = spd_btn_pin;
	vnv_btn_pin  = Pin(VNV_BTN_GPIO_Port,  VNV_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.vnv  = vnv_btn_pin;
	vs_btn_pin   = Pin(VS_BTN_GPIO_Port,   VS_BTN_Pin,   ACTIVE_LOW, false);
	btnPins.vs   = vs_btn_pin;
	xfr_btn_pin  = Pin(XFR_BTN_GPIO_Port,  XFR_BTN_Pin,  ACTIVE_LOW, false);
	btnPins.xfr  = xfr_btn_pin;
	yd_btn_pin   = Pin(YD_BTN_GPIO_Port,   YD_BTN_Pin,   ACTIVE_LOW, false);
	btnPins.yd   = yd_btn_pin;
	btnManager   = ButtonManager(btnPins);
}

static void InitControlPins()
{
	status_ind_pin    = Pin(STATUS_IND_GPIO_Port, STATUS_IND_Pin);
	usart_inval_pin   = Pin(USART_INVALID_GPIO_Port, USART_INVALID_Pin, ACTIVE_LOW, false);
	usb_usart_sel_pin = Pin(USB_SER_SEL_GPIO_Port, USB_SER_SEL_Pin, false);
}

static void InitIndicators()
{
	backlight = PWMPin(h_brgt_tim, BACKLIGHT_PWM_CH);
	backlight.Init();

	brgt_cs_pin = Pin(BRGT_CS_GPIO_Port, BRGT_CS_Pin, ACTIVE_LOW);
	brgt_ud_pin = Pin(BRGT_UD_GPIO_Port, BRGT_UD_Pin);

	ind_la_pin  = Pin(IND_LATCH_GPIO_Port, IND_LATCH_Pin);

	STP_PWM_Pin ind_oe_pin = { .htim  = h_brgt_tim, .ch = TIM_CHANNEL_1 };
	STP_Pins    stpPins    = { .lePin = ind_la_pin, .oePin = ind_oe_pin };

	indBlDriver = MCP4023Driver(brgt_ud_pin, brgt_cs_pin, MCP4023_10K);
	indDriver   = STPLEDDriver(h_spi, stpPins, &indBlDriver);
	indManager  = IndicatorManager(&indDriver, &backlight);
}

static void InitEncoders()
{
	hdg_a_pin   = Pin(HDG_A_GPIO_Port, HDG_A_Pin, false);
	hdg_b_pin   = Pin(HDG_B_GPIO_Port, HDG_B_Pin, false);
	hdgEncoder  = RotaryEncoder(&hdg_a_pin, &hdg_b_pin);
	alt_a_pin   = Pin(ALT_A_GPIO_Port, ALT_A_Pin, false);
	alt_b_pin   = Pin(ALT_B_GPIO_Port, ALT_B_Pin, false);
	altEncoder  = RotaryEncoder(&alt_a_pin, &alt_b_pin);
	whl_a_pin   = Pin(WHEEL_A_GPIO_Port, WHEEL_A_Pin, false);
	whl_b_pin   = Pin(WHEEL_B_GPIO_Port, WHEEL_B_Pin, false);
	whlEncoder  = RotaryEncoder(&whl_a_pin, &whl_b_pin);
	crs1_a_pin  = Pin(CRS1_A_GPIO_Port, CRS1_A_Pin, false);
	crs1_b_pin  = Pin(CRS1_B_GPIO_Port, CRS1_B_Pin, false);
	crs1Encoder = RotaryEncoder(&crs1_a_pin, &crs1_b_pin);
	crs2_a_pin  = Pin(CRS2_A_GPIO_Port, CRS2_A_Pin, false);
	crs2_b_pin  = Pin(CRS2_B_GPIO_Port, CRS2_B_Pin, false);
	crs2Encoder = RotaryEncoder(&crs2_a_pin, &crs2_b_pin);
	encManager  = EncoderManager(&hdgEncoder, &altEncoder, &whlEncoder, &crs1Encoder, &crs2Encoder);
}

static void HandleOptionsCallback(OptionStatesUnion *options)
{
	status_ind_pin.Enable(options->obj.enStatusInd);
	aux_in_pin.Enable(options->obj.enAuxIn);
	aux_out_pin.Enable(options->obj.enAuxOut);
}

static void InitAuxIO()
{
	aux_in_pin  = Pin(GPIO_IN_GPIO_Port, GPIO_IN_Pin, false);
	aux_out_pin = Pin(GPIO_OUT_GPIO_Port, GPIO_OUT_Pin);
}

static void StartupTest()
{
	indDriver.SetAllIndicators(0xFFFF);
	HAL_Delay(500);
	indDriver.SetAllIndicators(0);
	HAL_Delay(500);
	backlight.Set(0xFFFF);
	HAL_Delay(500);
	backlight.Set(0);
}
