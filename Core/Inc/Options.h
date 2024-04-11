/*
 * Options.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_OPTIONS_H_
#define INC_OPTIONS_H_

#include "main.h"

#define OPTIONS_FLASH_ADDRESS 0x0801F3F9 // <- NOT A VALID FLASH ADDRESS!!!
#define OPTIONS_FLASH_PAGES 8

typedef struct {
	bool enUART;
	bool enStatusInd;
	bool enAuxIn;
	bool enAuxOut;
	bool enBacklightIn;
	bool enBacklightOut;
	uint8_t comPort;
} OptionStates;

typedef union {
	OptionStates obj;
	uint16_t byte;
} OptionStatesUnion;

struct Options {
public:
	Options() { };
	Options(OptionStatesUnion *states) { this->states = states;                 };

	void SetUART(bool en)              { this->states->obj.enUART = en;         };
	void SetAuxIn(bool en)             { this->states->obj.enAuxIn = en;        };
	void SetAuxOut(bool en)            { this->states->obj.enAuxOut = en;       };
	void SetBacklightIn(bool en)       { this->states->obj.enBacklightIn = en;  };
	void SetBacklightOut(bool en)      { this->states->obj.enBacklightOut = en; };

	void SetOptions(uint16_t data)     { this->states->byte = data;             };
	OptionStatesUnion *GetStatesPtr()  { return this->states;                   };

	void SaveOptions();
	void ReadOptions();
private:
	OptionStatesUnion *states;
};

#endif /* INC_OPTIONS_H_ */
