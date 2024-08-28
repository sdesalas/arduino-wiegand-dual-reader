#ifndef _WIEGAND_MULTI_H_
#define _WIEGAND_MULTI_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class WIEGAND {

public:
	WIEGAND();
	bool available();
  void ReadD0();
	void ReadD1();
	unsigned long getCode();
	int getWiegandType();
	
private:
	bool DoWiegandConversion ();
	unsigned long GetCardId (volatile unsigned long *codehigh, volatile unsigned long *codelow, char bitlength);
	
	volatile unsigned long 	_cardTempHigh;
	volatile unsigned long 	_cardTemp;
	volatile unsigned long 	_lastWiegand;
	volatile int				_bitCount;	
	int				_wiegandType;
	unsigned long	_code;
};

#endif
