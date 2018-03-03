/*

 * labgpio.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: Anirudh
 */

#include "labgpio.h"

labGPIO_0::labGPIO_0(uint8_t port, uint8_t pin) : port_num(port), pin_num(pin)
{
	uint32_t port_memory_bases[] = {LPC_GPIO0_BASE, LPC_GPIO1_BASE, LPC_GPIO2_BASE, LPC_GPIO3_BASE, LPC_GPIO4_BASE};

	OurGpio = (LPC_GPIO_TypeDef*) port_memory_bases[port_num];

    volatile uint32_t *pinsel = &(LPC_PINCON->PINSEL0);
    pinsel += 2*port_num;
    *pinsel &= ~(3 << 2*pin_num);

}


void labGPIO_0::setAsInput(void)
{
	OurGpio->FIODIR &= ~(1 << pin_num);
}

void labGPIO_0::setAsOutput(void)
{
	OurGpio->FIODIR |= (1 << pin_num);
}

void labGPIO_0::setDirection(bool output)
{
	if(output)
	{
		OurGpio->FIODIR |= (1 << pin_num);
	}
	else
	{
		OurGpio->FIODIR &= ~(1 << pin_num);
	}
}

bool labGPIO_0::getLevel()
{
	return OurGpio->FIOPIN & (1 << pin_num);
}

void labGPIO_0::setHigh()
{
	OurGpio->FIOPIN |= (1 << pin_num);
}

void labGPIO_0::setLow()
{
	OurGpio->FIOPIN &= ~(1 << pin_num);
}

void labGPIO_0::set(bool high)
{
	if(high)
	{
		OurGpio->FIOPIN |= (1 << pin_num);
	}
	else
	{
		OurGpio->FIOPIN &= ~(1 << pin_num);
	}
}

void labGPIO_0::enablePullDown()
{
    volatile uint32_t *pinmode = &(LPC_PINCON->PINMODE0);
    pinmode += (2 * port_num);
    *pinmode |= (3 << (2*pin_num));
}

labGPIO_0::~labGPIO_0()
{
    setAsInput();
   // enableOpenDrainMode(false);
   // enablePullUp();
}


