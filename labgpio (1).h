/*
 * labgpio.h
 *
 *  Created on: Feb 20, 2018
 *      Author: Anirudh
 */

#ifndef L4_IO_LABGPIO_H_
#define L4_IO_LABGPIO_H_

#include "LPC17xx.h"
#include <stdint.h>

class labGPIO_0
{
public:
	labGPIO_0(uint8_t port_num, uint8_t pin_num);

	~labGPIO_0();

	void setAsInput(void);
	void setAsOutput(void);
	void setDirection(bool output);
	void setHigh();
	void setLow();
	void set(bool high);
	bool getLevel();
	void enablePullDown();


private:
	labGPIO_0();   //default constructor shouldn't be called without any pin number

	const uint8_t pin_num;
	const uint8_t port_num;
    volatile LPC_GPIO_TypeDef *OurGpio;


};



#endif /* L4_IO_LABGPIO_H_ */
