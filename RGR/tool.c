#include "header.h"

uint32_t timeZero = 0;
uint32_t timeToWait = 0;

void delay(uint32_t ms) //функція затримки
{
	timeToWait = ms + timeZero;
	while(timeZero < timeToWait){}
}

void seg_send (int8_t num)
{
	switch (num)
	{
		case 0x00:      
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A     // розподіл загорання певних сегментів у відповідності до числа
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR |= GPIO_ODR_OD5; //E
			GPIOD->ODR |= GPIO_ODR_OD6; //F
			GPIOD->ODR &= ~GPIO_ODR_OD7; //G
			break;
		}
		case 0x01:
		{
			GPIOD->ODR &= ~GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR &= ~GPIO_ODR_OD4; //D
			GPIOD->ODR &= ~GPIO_ODR_OD5; //E
			GPIOD->ODR &= ~GPIO_ODR_OD6; //F
			GPIOD->ODR &= ~GPIO_ODR_OD7; //G
			break;
		}
		case 0x02:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR &= ~GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR |= GPIO_ODR_OD5; //E
			GPIOD->ODR &= ~GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
		case 0x03:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR &= ~GPIO_ODR_OD5; //E
			GPIOD->ODR &= ~GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
		case 0x04:
		{
			GPIOD->ODR &= ~GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR &= ~GPIO_ODR_OD4; //D
			GPIOD->ODR &= ~GPIO_ODR_OD5; //E
			GPIOD->ODR |= GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
		case 0x05:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR &= ~GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR &= ~GPIO_ODR_OD5; //E
			GPIOD->ODR |= GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
		case 0x06:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR &= ~GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR |= GPIO_ODR_OD5; //E
			GPIOD->ODR |= GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
		case 0x07:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR &= ~GPIO_ODR_OD4; //D
			GPIOD->ODR &= ~GPIO_ODR_OD5; //E
			GPIOD->ODR &= ~GPIO_ODR_OD6; //F
			GPIOD->ODR &= ~GPIO_ODR_OD7; //G
			break;
		}
		case 0x08:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR |= GPIO_ODR_OD5; //E
			GPIOD->ODR |= GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
		case 0x09:
		{
			GPIOD->ODR |= GPIO_ODR_OD1; //A
			GPIOD->ODR |= GPIO_ODR_OD2; //B
			GPIOD->ODR |= GPIO_ODR_OD3; //C
			GPIOD->ODR |= GPIO_ODR_OD4; //D
			GPIOD->ODR &= ~GPIO_ODR_OD5; //E
			GPIOD->ODR |= GPIO_ODR_OD6; //F
			GPIOD->ODR |= GPIO_ODR_OD7; //G
			break;
		}
	}
}

int8_t sum(int8_t num1, int8_t num2, int8_t min_num1, int8_t min_num2)
// функція, що додає двозначні десяткові числа з урахуванням знаку
{
	int8_t min_res; //змінна від'ємного результату
	int8_t res = 0; //змінна результату
		if (min_num1 == 0 && min_num2 == 0) //додатні операнди
		{
			res=num1+num2;
			min_res = 0;
		}
		if (min_num1 == 1 && min_num2 == 0) //перше число від'ємне, а друге - додатнє
		{
			if (num1>num2) // за правилами математики - щоб від одного числа відняти інше, потрібно від більшого модуля числа відняти менший і поставити знак більшого модуля
			{
				res=num1-num2;
				min_res = 1;
			}
			else
			{
				res=num2-num1;
				min_res = 0;
			}
		}
		if (min_num1 == 0 && min_num2 == 1) //перше додатнє, друге від'ємне
		{
			if (num1>num2)  
			{
				res=num1-num2;
				min_res = 0;
			}
			else
			{
				res=num2-num1;
				min_res = 1;
			}
		}
		if (min_num1 == 1 && min_num2 == 1) //два числа від'ємні
		{
			res=num1+num2;
			min_res = 1;
		}
		
		
		if ((res & 0x0f) > 9)
		{
			res = res - 10;
			res = res + 0x10;
		}
		
		GPIOD->ODR |= GPIO_ODR_OD15; //індикація результату
		if (min_res == 1) GPIOD->ODR |= GPIO_ODR_OD13;  //індикація від'ємного числа
		else GPIOD->ODR &= ~GPIO_ODR_OD13;
		
		if(res > 0x99) GPIOD->ODR |= GPIO_ODR_OD14; //індикація переповнення розряду
		return res;
}

void SysTick_Handler(void)
{
	timeZero++;
}

void display(uint32_t num)
{
	GPIOC->ODR |= GPIO_ODR_OD7; //виведення старшого розряду числа на індикатор
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	seg_send((num&0xf0)>>4);
	delay(5);
	GPIOC->ODR &= ~GPIO_ODR_OD7;  //виведення молодшого розряду числа на індикатор
	GPIOC->ODR |= GPIO_ODR_OD8;
	seg_send((num)&0x0f);
}