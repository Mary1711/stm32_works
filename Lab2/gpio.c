#include "gpio.h"

void GPIOA_enable(void)
{
	/* записати біт у RCC для включення тактування */
    *((uint32_t *)((uint32_t)RCC_AHB1_BASE + RCC_AHB1_ENR_OFFSET)) |= (1 << RCC_AHB1_GPIOA_CLK_BIT);
    return;
}

void GPIOD_enable(void)
{
	/* записати біт у RCC для включення тактування */
    *((uint32_t *)((uint32_t)RCC_AHB1_BASE + RCC_AHB1_ENR_OFFSET)) |= (1 << RCC_AHB1_GPIOD_CLK_BIT);
    return;
}

void GPIOA_cfg_pin(uint32_t mode, uint16_t pin)
{
	/* конфігуровати пін, де mode = 00 - input, 01 - output */
    *((uint32_t *)((uint32_t)GPIOA_BASE + GPIO_MODER)) |= (mode << (2 * pin));
    return;
}

void GPIOD_cfg_pin(uint32_t mode, uint16_t pin)
{
	/* конфігуровати пін, де mode = 00 - input, 01 - output */
    *((uint32_t *)((uint32_t)GPIOD_BASE + GPIO_MODER)) |= (mode << (2 * pin));
    return;
}

void GPIOD_wr_pin_bit(uint16_t pin, uint8_t value)
{
	/* якщо value = TRUE, то записати в пін "1" */
    if (value)
        *((uint32_t *)((uint32_t)GPIOD_BASE + GPIO_ODR)) |= (1 << pin);
	/* якщо value = FALSE, то записати в пін "0" */
    else
        *((uint32_t *)((uint32_t)GPIOD_BASE + GPIO_ODR)) &= ~(1 << pin);
    
    return;
}

uint8_t GPIOA_rd_pin(uint16_t pin_no)
{
	/* зчитати з піна, де value - результат */
    uint8_t value;
	value = ((*((uint32_t *)((uint32_t)GPIOA_BASE + GPIO_IDR)) >> pin_no)) & 0x00000001 ;
	return value;
}


void sys_wait(uint32_t clocks)
{
	/* виконувати цикл доти змінна таймеру не стане 0 */
    while(clocks)
        clocks--;
}
