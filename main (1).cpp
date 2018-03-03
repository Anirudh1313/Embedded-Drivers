/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 */

#include <stdio.h>
#include "utilities.h"
#include "io.hpp"
#include "gpio.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "uart0_min.h"
#include "labgpio.h"

//GPIO gp(P1_22);
//GPIO in(P2_0);
labGPIO_0 gp(1, 22);
labGPIO_0 in(2, 0);

uint32_t ENABLED = 0;
uint32_t ENABLED_int = 0;

//typedef struct
//{
//	uint8_t port_num;
//	uint8_t pin_num;
//}pp;

void vTaskOneCode(void* a)
{
	//uint32_t
	while(1)
	{
		if(in.getLevel())
		{
			ENABLED = 1;
			//gp.setHigh();
		}
		else
		{
			ENABLED = 0;
		}
		delay_ms(10);
	}

	//xTaskDelete(NULL);

}

void vTaskTwoCode(void* b)
{
	while(1)
	{
		if(ENABLED)
		{
			gp.setHigh();
		}
		else
		{
			gp.setLow();
		}
		//uart0_puts("bbbbbbbbbbbbbbbbbbbb");
		delay_ms(10);
	}
}

void vTaskThreeCode(void* a)
{
	while(1)
	{
		if(SW.getSwitch(1))
		{
			ENABLED_int = 1;
			//gp.setHigh();
		}
		else
		{
			ENABLED_int = 0;
		}
		delay_ms(10);
	}
}

void vTaskFourCode(void* b)
{
	while(1)
	{
		if(ENABLED_int)
		{
			LE.on(1);
		}
		else
		{
			LE.off(1);
		}
		//uart0_puts("bbbbbbbbbbbbbbbbbbbb");
		delay_ms(10);
	}
}

int main(int argc, char const *argv[])
{
//    int count = 0;


    const uint32_t ST = 1024;

    gp.setAsOutput();
    in.setAsInput();
    in.enablePullDown();

    //GPIO *out = gp;
    //GPIO *i = in;

//    while(1)
//    {
//        //count = count + 1;
//        //printf("%3u: Temperature: %0.2f    Light: %u%%\n", count, TS.getFarenheit(), LS.getPercentValue());
//
//        if(in.read())
//        {
//        	gp.setHigh();
//        	printf("pressed\n");
//        }
//        else
//        {
//        	gp.setLow();
//        }
//
//        delay_ms(10);
//    }

    xTaskCreate(vTaskOneCode, (const char*)"task_switch_input", ST, (void*)1, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTaskTwoCode, (const char*)"task_led_op", ST, (void*)1, tskIDLE_PRIORITY, NULL);

    xTaskCreate(vTaskThreeCode, (const char*)"task_internal_switch_input", ST, (void*)1, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTaskFourCode, (const char*)"task_internal_led_op", ST, (void*)1, tskIDLE_PRIORITY, NULL);


    vTaskStartScheduler();


    return 0;


}


