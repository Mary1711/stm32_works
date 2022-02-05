
#include "header.h"

int main ()
{
	volatile uint32_t time1 = 150; //delay
	volatile uint32_t time2 = 12; //delay
	volatile int8_t num1 = 0; //перше число
	volatile int8_t num2 = 0; //друге число
	volatile int8_t res = 0; //змінна результату
	volatile uint32_t temp = 0; //тимчасова змінна
	volatile uint8_t min_num1 = 0; // змінна знаку першого операнду ( від'ємного)
	volatile uint8_t min_num2 = 0; // // змінна знаку другого операнду ( від'ємного)

	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN; // увімкнення тактування порту GPIOD
	
	/* налаштувати на вихід портів, що відповідають за сегменти індикатора -  PD1 за сегмент A, PD2 - B, PD3 - C, PD4 - D, PD5 - E
	PD6 - F, PD7 - G
	PD13 - PD15 на вихід, світлодіоди*/
	
	GPIOD->MODER |= GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | 
					GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 |
					GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 |
					GPIO_MODER_MODE7_0;
	GPIOD->MODER &= ~(GPIO_MODER_MODE1_1 | GPIO_MODER_MODE2_1 | 
					GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 |
					GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 |
					GPIO_MODER_MODE7_1);
					
	GPIOD->MODER |= GPIO_MODER_MODE13_0 | GPIO_MODER_MODE14_0 | 
					GPIO_MODER_MODE15_0;
	GPIOD->MODER &= ~ (GPIO_MODER_MODE15_1 | GPIO_MODER_MODE14_1 | 
					  GPIO_MODER_MODE13_1);

	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; // увімкнення тактування порту GPIOА
	
	// налаштувати на вхід PA0 - синя кнопка підтвердження.
	GPIOA->MODER &= ~GPIO_MODER_MODE0_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_1;
	
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN; // увімкнення тактування порту GPIOС
	
	/* налаштувати на вхід PC9 - кнопка МЕНШЕ.
	PC11 - кнопка БІЛЬШЕ
	PC6 - переключення знаку
	налаштування на вихід : PC7 - індикатор 1(перший індикатор подвійного семисегментника, PC8 - другий індикатор */
	GPIOC->MODER &= ~(GPIO_MODER_MODE9_0 | GPIO_MODER_MODE11_0 |
					GPIO_MODER_MODE6_0); 
	GPIOC->MODER &= ~(GPIO_MODER_MODE9_1 | GPIO_MODER_MODE11_1 |
					GPIO_MODER_MODE6_1);
					
	GPIOC->MODER |= GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0; 
	GPIOC->MODER &= ~(GPIO_MODER_MODE7_1 | GPIO_MODER_MODE8_1);
	
	SysTick_Config(SystemCoreClock/1000); // конфігурація таймеру SysTick
	
	while(1) //нескінченний цикл обробки чисел
	{
		GPIOD->ODR &= ~GPIO_ODR_OD13; 
		GPIOD->ODR &= ~GPIO_ODR_OD14;    // налаштування світлодіодів на вихід 
		GPIOD->ODR &= ~GPIO_ODR_OD15;
		
		while (GPIOA->IDR & GPIO_IDR_ID15) // вводимо значення першого операнду - перше число
		
		{
			if (min_num1 == 1) GPIOD->ODR |= GPIO_ODR_OD13; // індикація від'ємного числа
			else GPIOD->ODR &= ~GPIO_ODR_OD13;
			display(num1);
			if (!(GPIOC->IDR & GPIO_IDR_ID6)) 
			{
				if (min_num1 == 0) min_num1 = 1;
				else min_num1 = 0;
				while (!(GPIOC->IDR & GPIO_IDR_ID6));
			}
			if (!(GPIOC->IDR & GPIO_IDR_ID9)) 
			{
				if((num1 & 0x0f) == 0) //корекція шістнадцяткового числа у десяткове
				{
					num1 = num1 + 0x09;
					num1 = num1 - 0x10;
				}
				num1--;
				
				while (!(GPIOC->IDR & GPIO_IDR_ID9));
			}
			if (!(GPIOC->IDR & GPIO_IDR_ID11)) 
			{
				if((num1 & 0x0f) == 9) 
				{
					num1 = num1 & 0xf0;
					num1 = num1 + 0x10;
				}
				num1++;
				while (!(GPIOC->IDR & GPIO_IDR_ID11));
			}
		delay(time2);
		}
		while (!(GPIOA->IDR & GPIO_IDR_ID0)); //натиск кнопки підтвердження
		GPIOD->ODR &= ~GPIO_ODR_OD14;
		
		
		while (GPIOA->IDR & GPIO_IDR_ID0)  //введення значення другого операнду - другого числа
		{		
			if (min_num2 == 1) GPIOD->ODR |= GPIO_ODR_OD13; //індикація від'ємнго числа
			else GPIOD->ODR &= ~GPIO_ODR_OD13;
			display(num2);
			GPIOD->ODR &= ~GPIO_ODR_OD14;
			if (!(GPIOC->IDR & GPIO_IDR_ID6)) 
			{
				if (min_num2 == 0) min_num2 = 1;
				else min_num2 = 0;
			while (!(GPIOC->IDR & GPIO_IDR_ID6));
			}
			if (!(GPIOC->IDR & GPIO_IDR_ID9)) 
			{
				if((num2 & 0x0f) == 0) 
				{
					num2 = num2 + 0x09;
					num2 = num2 - 0x10;
				}
				num2--;
				while (!(GPIOC->IDR & GPIO_IDR_ID9));
			}
			if (!(GPIOC->IDR & GPIO_IDR_ID11)) 
			{
				if((num2 & 0x0f) == 9) 
				{
					num2 = num2 & 0xf0; 
					num2 = num2 + 0x10;
				}
				num2++;
				while (!(GPIOC->IDR & GPIO_IDR_ID11));
			}
			delay(time2);
		}
		while (!(GPIOA->IDR & GPIO_IDR_ID15)); 
		
		res = sum(num1, num2, min_num1, min_num2); //додавання чисел 
		
		temp = time1;
		while(temp--) //відображення результату 
		{
			display(res);
			delay(time2);
		}
	}
}
