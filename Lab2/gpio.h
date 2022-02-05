#include <stdint.h>

#define RCC_AHB1_BASE           ((uint32_t *)0x40023800)
#define GPIOA_BASE              ((uint32_t *)0x40020000)
#define GPIOD_BASE              ((uint32_t *)0x40020C00)
    
#define RCC_AHB1_ENR_OFFSET     ((uint32_t)0x30)
#define RCC_AHB1_GPIOA_CLK_BIT  ((uint32_t)0x00)
#define RCC_AHB1_GPIOD_CLK_BIT  ((uint32_t)0x03)
/* зміщення */
#define GPIO_MODER              ((uint32_t)0x00)
#define GPIO_IDR                ((uint32_t)0x10)
#define GPIO_ODR                ((uint32_t)0x14)

void GPIOA_enable(void); //запуск тактування GPIO_A
void GPIOD_enable(void); //запуск тактування GPIO_D
void GPIOD_cfg_pin(uint32_t mode, uint16_t pin); //конфігурація піна для порту GPIOD
void GPIOA_cfg_pin(uint32_t mode, uint16_t pin); //конфігурація піна для порту GPIOA
void GPIOD_wr_pin_bit(uint16_t pin_no, uint8_t value); //записати значення у пін
uint8_t GPIOA_rd_pin(uint16_t pin_no); //зчитати значення з піна
void sys_wait(uint32_t clocks); //функція - таймер
