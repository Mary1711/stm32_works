#include "gpio.h"

void GPIOA_tackt(void)
{
	/* write bit to regiter RCC for tackting  */
    *((uint32_t *)((uint32_t)RCC_AHB1_BASE + RCC_AHB1_ENR_OFFSET)) |= (1 << RCC_AHB1_GPIOA_CLK_BIT);
    return;
}

void GPIOD_tackt(void)
{
	/*  write bit to regiter RCC for tackting */
    *((uint32_t *)((uint32_t)RCC_AHB1_BASE + RCC_AHB1_ENR_OFFSET)) |= (1 << RCC_AHB1_GPIOD_CLK_BIT);
    return;
}

void GPIOA_cfg_pin(uint32_t mode, uint16_t pin)
{
	/* конфігурувати пін; mode = 00 - input, 01 - output */
    *((uint32_t *)((uint32_t)GPIOA_BASE + GPIO_MODER)) |= (mode << (2 * pin));
    return;
}

void GPIOD_cfg_pin(uint32_t mode, uint16_t pin)
{
	/* конфігурація піна,  mode = 00 - input, 01 - output */
    *((uint32_t *)((uint32_t)GPIOD_BASE + GPIO_MODER)) |= (mode << (2 * pin));
    return;
}

void GPIOD_wr_pin(uint16_t pin, uint8_t value)
{
	/* value = TRUE, write to pin "1" */
    if (value)
        *((uint32_t *)((uint32_t)GPIOD_BASE + GPIO_ODR)) |= (1 << pin);
	/* value = FALSE, write to pin "0" */
    else
        *((uint32_t *)((uint32_t)GPIOD_BASE + GPIO_ODR)) &= ~(1 << pin);
    
    return;
}

uint8_t GPIOA_rd_pin(uint16_t pin_no)
{
	/*  value - результат */
    uint8_t value;
	value = ((*((uint32_t *)((uint32_t)GPIOA_BASE + GPIO_IDR)) >> pin_no)) & 0x00000001 ;
	return value;
}


void delay(uint32_t clocks)
{
	/* цикл поки таймер не буде 0 */
    while(clocks)
        clocks--;
}
