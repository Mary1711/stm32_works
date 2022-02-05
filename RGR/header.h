#include "stm32f4xx.h" //підключення бібліотеки CMSIS

void delay(uint32_t ms); //функція затримки
void seg_send (int8_t num); //функція надсилання сигналу на сегменти індикатора 
int8_t sum(int8_t num1, int8_t num2, int8_t min_num1, int8_t min_num2); //функція суми
void SysTick_Handler(void); // функція обробникa переривань таймеру 
void display(uint32_t num);// функція динамічної індикації
