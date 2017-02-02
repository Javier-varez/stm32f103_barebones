
#include <stdint.h>

#define GPIOC_BASE		0x40011000
#define GPIO_CRL_OFFSET		0x00
#define GPIO_CRH_OFFSET		0x04
#define GPIO_IDR_OFFSET		0x08
#define GPIO_ODR_OFFSET		0x0C
#define GPIO_BSRR_OFFSET	0x10
#define GPIO_BRR_OFFSET		0x14
#define GPIO_LCKR_OFFSET	0x18

#define RCC_BASE   		0x40021000
#define RCC_APB2ENR_OFFSET 	0x18

void led_flash() {
	*(uint32_t*)(RCC_BASE + RCC_APB2ENR_OFFSET) = (1<<4); // EN CLK FOR GPIO C
	*(uint32_t*)(GPIOC_BASE + GPIO_CRH_OFFSET) = (0x00 << 22) | (0x02 << 20) | 0x44044444;
	*(uint32_t*)(GPIOC_BASE + GPIO_BSRR_OFFSET) = (0x01<<13); // Turn on LED

	while(1) {
		for(int i = 0; i < 1000000; i++);
		*(uint32_t*)(GPIOC_BASE + GPIO_BSRR_OFFSET) = (0x01<<29); // Turn off LED's
		for(int i = 0; i < 1000000; i++);
		*(uint32_t*)(GPIOC_BASE + GPIO_BSRR_OFFSET) = (0x01<<13); // Turn on LED's
	}
}

void main()
{
	led_flash();
}
