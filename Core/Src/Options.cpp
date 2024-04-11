/*
 * Options.cpp
 *
 *  Created on: Apr 5, 2024
 *      Author: Daxxn
 */

#include "Options.h"

const uint32_t _options_page_start = 0x0801F3F9;

void Options::SaveOptions()
{
	  FLASH_EraseInitTypeDef eraseInit;
	  eraseInit.NbPages = 1;
	  eraseInit.PageAddress = 0x00;
	  eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	  uint32_t eraseResult = 0;
	  HAL_FLASH_Unlock();
	  HAL_FLASHEx_Erase(&eraseInit, &eraseResult);
	  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, OPTIONS_FLASH_ADDRESS, this->states->byte);
	  HAL_FLASH_Lock();
}

void Options::ReadOptions()
{
}
