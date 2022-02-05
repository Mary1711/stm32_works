#include "gpio.h"


int main_loop(void)
{
    volatile uint8_t i = 0; //змінна для циклу
    volatile uint8_t num = 0; //режим роботи вогнів
	volatile uint32_t time = 1500000; //delay
    volatile uint32_t mode = 0x01; //виставляємо режим ВИХІД
    
	/* PA0 - кнопка, GPIOD PD12-PD15 - LED */
	GPIOA_enable(); //tackting for ports
    GPIOD_enable();

    for(i = 12; i < 16; i++) //LEDs to exit
        GPIOD_cfg_pin(mode, i);
        
    mode = 0x00; //entrance
    GPIOA_cfg_pin(mode, 0); //exit
    
    while(1) 
    {
        /* active high level */
		if( GPIOA_rd_pin(0) )
        {
             if ( num == 0 ) num = 1;   
                else
                    num = 0;
        }
        /* if num = 0 => light not forward to clock */
		if (num == 0) {
        GPIOD_wr_pin_bit(12, 1); //green
        GPIOD_wr_pin_bit(13, 0); 
        GPIOD_wr_pin_bit(14, 0); 
        GPIOD_wr_pin_bit(15, 0);
		sys_wait(time);
		GPIOD_wr_pin_bit(12, 0);
        GPIOD_wr_pin_bit(13, 1); //orange
		sys_wait(time);
        GPIOD_wr_pin_bit(13, 0);
        GPIOD_wr_pin_bit(14, 1); //red
		sys_wait(time);
        GPIOD_wr_pin_bit(14, 0);
        GPIOD_wr_pin_bit(15, 1); //blue
		}
        /* if num = 1 => light forward to clock */
		else {
        GPIOD_wr_pin_bit(12, 1); //green
        GPIOD_wr_pin_bit(13, 0); 
        GPIOD_wr_pin_bit(14, 0); 
        GPIOD_wr_pin_bit(15, 0);
        sys_wait(time);
        GPIOD_wr_pin_bit(12, 0);
        GPIOD_wr_pin_bit(15, 1); //blue 
        sys_wait(time); 
        GPIOD_wr_pin_bit(14, 1); //red
        GPIOD_wr_pin_bit(15, 0);    
		sys_wait(time);
		GPIOD_wr_pin_bit(14, 0);
        GPIOD_wr_pin_bit(13, 1); //orange
		}
		sys_wait(time);
    }
}
