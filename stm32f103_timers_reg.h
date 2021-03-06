/*
 * STM32F103 Timers and IRQ register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_TIMERS_REG_H_
#define STM32F103_TIMERS_REG_H_

#include <stdio.h>
#include <stdint.h>

//SysTick registers and values
#define SYSTICK_CSR		*(volatile uint32_t *) 0xE000E010
#define SYSTICK_RVR		*(volatile uint32_t *) 0xE000E014
#define SYSTICK_CURVAL	*(volatile uint32_t *) 0xE000E018
#define SYSTICK_CALIB	*(volatile uint32_t *) 0xE000E01C

#define SYSTICK_CSR_COUNTFLAG	0x00010000
#define SYSTICK_CSR_CLKSOURCE	0x00000004
#define SYSTICK_CSR_TICKINT		0x00000002
#define SYSTICK_CSR_ENABLE		0x00000001

//interrupt set-enable registers
#define IRQ_0TO31_SER	*(volatile uint32_t *) 0xE000E100
#define IRQ_32TO63_SER	*(volatile uint32_t *) 0xE000E104
#define IRQ_0TO31_CER	*(volatile uint32_t *) 0xE000E180
#define IRQ_32TO63_CER	*(volatile uint32_t *) 0xE000E184

//interrupt priority registers base address
#define IRQ_PRIORITY(mem_offset) (*(volatile uint32_t *)(0xE000E400 + (mem_offset)))

//interrupt set-enable values
#define IRQ_BITMASK_WWDG			0x00000001
#define IRQ_BITMASK_PVD				0x00000002
#define IRQ_BITMASK_TAMPER			0x00000004
#define IRQ_BITMASK_RTC				0x00000008
#define IRQ_BITMASK_FLASH			0x00000010
#define IRQ_BITMASK_RCC				0x00000020
#define IRQ_BITMASK_EXTI0			0x00000040
#define IRQ_BITMASK_EXTI1			0x00000080
#define IRQ_BITMASK_EXTI2			0x00000100
#define IRQ_BITMASK_EXTI3			0x00000200
#define IRQ_BITMASK_EXTI4			0x00000400
#define IRQ_BITMASK_DMA1_Channel1	0x00000800
#define IRQ_BITMASK_DMA1_Channel2	0x00001000
#define IRQ_BITMASK_DMA1_Channel3	0x00002000
#define IRQ_BITMASK_DMA1_Channel4	0x00004000
#define IRQ_BITMASK_DMA1_Channel5	0x00008000
#define IRQ_BITMASK_DMA1_Channel6	0x00010000
#define IRQ_BITMASK_DMA1_Channel7	0x00020000
#define IRQ_BITMASK_ADC1_2			0x00040000
#define IRQ_BITMASK_USB_HP_CAN_TX	0x00080000
#define IRQ_BITMASK_USB_HP_CAN_RX0	0x00100000
#define IRQ_BITMASK_CAN_RX1			0x00200000
#define IRQ_BITMASK_CAN_SCE			0x00400000
#define IRQ_BITMASK_EXTI9_5			0x00800000
#define IRQ_BITMASK_TIM1_BRK		0x01000000
#define IRQ_BITMASK_TIM1_UP			0x02000000
#define IRQ_BITMASK_TIM1_TRG_COM	0x04000000
#define IRQ_BITMASK_TIM1_CC			0x08000000
#define IRQ_BITMASK_TIM2			0x10000000
#define IRQ_BITMASK_TIM3			0x20000000
#define IRQ_BITMASK_TIM4			0x40000000
#define IRQ_BITMASK_I2C1_EV			0x80000000
#define IRQ_BITMASK_I2C1_ER			0x00000001
#define IRQ_BITMASK_I2C2_EV			0x00000002
#define IRQ_BITMASK_I2C2_ER			0x00000004
#define IRQ_BITMASK_SPI1			0x00000008
#define IRQ_BITMASK_SPI2			0x00000010
#define IRQ_BITMASK_USART1			0x00000020
#define IRQ_BITMASK_USART2			0x00000040
#define IRQ_BITMASK_USART3			0x00000080
#define IRQ_BITMASK_EXTI15_10		0x00000100
#define IRQ_BITMASK_RTCAlarm		0x00000200
#define IRQ_BITMASK_USBWakeup		0x00000400
#define IRQ_BITMASK_TIM8_BRK		0x00000800
#define IRQ_BITMASK_TIM8_UP			0x00001000
#define IRQ_BITMASK_TIM8_TRG_COM	0x00002000
#define IRQ_BITMASK_TIM8_CC			0x00004000
#define IRQ_BITMASK_ADC3			0x00008000
#define IRQ_BITMASK_FSMC			0x00010000
#define IRQ_BITMASK_SDIO			0x00020000
#define IRQ_BITMASK_TIM5			0x00040000
#define IRQ_BITMASK_SPI3			0x00080000
#define IRQ_BITMASK_UART4			0x00100000
#define IRQ_BITMASK_UART5			0x00200000
#define IRQ_BITMASK_TIM6			0x00400000
#define IRQ_BITMASK_TIM7			0x00800000
#define IRQ_BITMASK_DMA2_Channel1	0x01000000
#define IRQ_BITMASK_DMA2_Channel2	0x02000000
#define IRQ_BITMASK_DMA2_Channel3	0x04000000
#define IRQ_BITMASK_DMA2_Channel4_5	0x08000000


//IRQs
#define WWDG_IRQ 			0
#define PVD_IRQ 			1
#define TAMPER_IRQ 			2
#define RTC_IRQ 			3
#define FLASH_IRQ 			4
#define RCC_IRQ 			5
#define EXTI0_IRQ 			6
#define EXTI1_IRQ 			7
#define EXTI2_IRQ 			8
#define EXTI3_IRQ 			9
#define EXTI4_IRQ 			10
#define DMA1_Channel1_IRQ 	11
#define DMA1_Channel2_IRQ 	12
#define DMA1_Channel3_IRQ 	13
#define DMA1_Channel4_IRQ 	14
#define DMA1_Channel5_IRQ 	15
#define DMA1_Channel6_IRQ 	16
#define DMA1_Channel7_IRQ 	17
#define ADC1_2_IRQ 			18
#define USB_HP_CAN1_TX_IRQ 	19
#define USB_LP_CAN1_RX0_IRQ 20
#define CAN1_RX1_IRQ 		21
#define CAN1_SCE_IRQ 		22
#define EXTI9_5_IRQ 		23
#define TIM1_BRK_IRQ 		24
#define TIM1_UP_IRQ 		25
#define TIM1_TRG_COM_IRQ 	26
#define TIM1_CC_IRQ 		27
#define TIM2_IRQ 			28
#define TIM3_IRQ 			29
#define TIM4_IRQ 			30
#define I2C1_EV_IRQ 		31
#define I2C1_ER_IRQ 		32
#define I2C2_EV_IRQ 		33
#define I2C2_ER_IRQ 		34
#define SPI1_IRQ 			35
#define SPI2_IRQ 			36
#define USART1_IRQ 			37
#define USART2_IRQ 			38
#define USART3_IRQ 			39
#define EXTI15_10_IRQ 		40
#define RTCAlarm_IRQ 		41
#define USBWakeUp_IRQ 		42
#define TIM8_BRK_IRQ		43
#define TIM8_UP_IRQ			44
#define TIM8_TRG_COM_IRQ	45
#define TIM8_CC_IRQ			46
#define ADC3_IRQ			47
#define FSMC_IRQ			48
#define SDIO_IRQ			49
#define TIM5_IRQ			50
#define SPI3_IRQ			51
#define UART4_IRQ			52
#define UART5_IRQ			53
#define TIM6_IRQ			54
#define TIM7_IRQ			55
#define DMA2_Channel1_IRQ	56
#define DMA2_Channel2_IRQ	57
#define DMA2_Channel3_IRQ	58
#define DMA2_Channel4_5_IRQ	59

//base addresses
#define _TIM1_(mem_offset) (*(volatile uint32_t *)(0x40012C00 + (mem_offset)))
#define _TIM2_(mem_offset) (*(volatile uint32_t *)(0x40000000 + (mem_offset)))
#define _TIM3_(mem_offset) (*(volatile uint32_t *)(0x40000400 + (mem_offset)))
#define _TIM4_(mem_offset) (*(volatile uint32_t *)(0x40000800 + (mem_offset)))
#define _TIM5_(mem_offset) (*(volatile uint32_t *)(0x40000C00 + (mem_offset)))
#define _TIM6_(mem_offset) (*(volatile uint32_t *)(0x40001000 + (mem_offset)))
#define _TIM7_(mem_offset) (*(volatile uint32_t *)(0x40001400 + (mem_offset)))
#define _TIM8_(mem_offset) (*(volatile uint32_t *)(0x40013400 + (mem_offset)))
#define _TIM9_(mem_offset) (*(volatile uint32_t *)(0x40014C00 + (mem_offset)))
#define _TIM10_(mem_offset) (*(volatile uint32_t *)(0x40015000 + (mem_offset)))
#define _TIM11_(mem_offset) (*(volatile uint32_t *)(0x40015400 + (mem_offset)))
#define _TIM12_(mem_offset) (*(volatile uint32_t *)(0x40001800 + (mem_offset)))
#define _TIM13_(mem_offset) (*(volatile uint32_t *)(0x40001C00 + (mem_offset)))
#define _TIM14_(mem_offset) (*(volatile uint32_t *)(0x40002000 + (mem_offset)))

//Bit-band aliases (atomic access to select registers)

//enable counter (and the base address too)
#define BB_TIM1_CR1_CEN     *(volatile uint32_t *) 0x42258000
#define BB_TIM2_CR1_CEN     *(volatile uint32_t *) 0x42000000
#define BB_TIM3_CR1_CEN     *(volatile uint32_t *) 0x42008000
#define BB_TIM4_CR1_CEN     *(volatile uint32_t *) 0x42010000

//Update disable (UDIS)
#define BB_TIM1_CR1_UDIS	*(volatile uint32_t *) 0x42258004
#define BB_TIM2_CR1_UDIS	*(volatile uint32_t *) 0x42000004
#define BB_TIM3_CR1_UDIS	*(volatile uint32_t *) 0x42008004
#define BB_TIM4_CR1_UDIS	*(volatile uint32_t *) 0x42010004

//one pulse mode
#define BB_TIM1_CR1_OPM     *(volatile uint32_t *) 0x4225800C
#define BB_TIM2_CR1_OPM     *(volatile uint32_t *) 0x4200000C
#define BB_TIM3_CR1_OPM     *(volatile uint32_t *) 0x4200800C
#define BB_TIM4_CR1_OPM     *(volatile uint32_t *) 0x4201000C

//Capture/Compare output enables
#define BB_TIM1_CCER_CC1E	*(volatile uint32_t *) 0x42258400
#define BB_TIM1_CCER_CC2E	*(volatile uint32_t *) 0x42258410
#define BB_TIM1_CCER_CC3E	*(volatile uint32_t *) 0x42258420
#define BB_TIM1_CCER_CC4E	*(volatile uint32_t *) 0x42258430

#define BB_TIM2_CCER_CC1E	*(volatile uint32_t *) 0x42000400
#define BB_TIM2_CCER_CC2E	*(volatile uint32_t *) 0x42000410
#define BB_TIM2_CCER_CC3E	*(volatile uint32_t *) 0x42000420
#define BB_TIM2_CCER_CC4E	*(volatile uint32_t *) 0x42000430

#define BB_TIM3_CCER_CC1E	*(volatile uint32_t *) 0x42008400
#define BB_TIM3_CCER_CC2E	*(volatile uint32_t *) 0x42008410
#define BB_TIM3_CCER_CC3E	*(volatile uint32_t *) 0x42008420
#define BB_TIM3_CCER_CC4E	*(volatile uint32_t *) 0x42008430

#define BB_TIM4_CCER_CC1E	*(volatile uint32_t *) 0x42010400
#define BB_TIM4_CCER_CC2E	*(volatile uint32_t *) 0x42010410
#define BB_TIM4_CCER_CC3E	*(volatile uint32_t *) 0x42010420
#define BB_TIM4_CCER_CC4E	*(volatile uint32_t *) 0x42010430

//timer1 interrupts
#define BB_TIM1_DIER_UIE 	*(volatile uint32_t *) 0x42258180
#define BB_TIM1_DIER_CC1IE	*(volatile uint32_t *) 0x42258184
#define BB_TIM1_DIER_CC2IE	*(volatile uint32_t *) 0x42258188
#define BB_TIM1_DIER_CC3IE	*(volatile uint32_t *) 0x4225818C
#define BB_TIM1_DIER_CC4IE	*(volatile uint32_t *) 0x42258190
#define BB_TIM1_DIER_COMIE	*(volatile uint32_t *) 0x42258194
#define BB_TIM1_DIER_TIE	*(volatile uint32_t *) 0x42258198
#define BB_TIM1_DIER_BIE	*(volatile uint32_t *) 0x4225819C

//timer1 clear interrupt flags
#define BB_TIM1_SR_UIF		*(volatile uint32_t *) 0x42258200
#define BB_TIM1_SR_CC1IF	*(volatile uint32_t *) 0x42258204
#define BB_TIM1_SR_CC2IF	*(volatile uint32_t *) 0x42258208
#define BB_TIM1_SR_CC3IF	*(volatile uint32_t *) 0x4225820C
#define BB_TIM1_SR_CC4IF	*(volatile uint32_t *) 0x42258210
#define BB_TIM1_SR_COMIF	*(volatile uint32_t *) 0x42258214
#define BB_TIM1_SR_TIF		*(volatile uint32_t *) 0x42258218
#define BB_TIM1_SR_BIF		*(volatile uint32_t *) 0x4225821C

//timer1 event generators
#define BB_TIM1_EGR_UG		*(volatile uint32_t *) 0x42258280
#define BB_TIM1_EGR_CC1G	*(volatile uint32_t *) 0x42258284
#define BB_TIM1_EGR_CC2G	*(volatile uint32_t *) 0x42258288
#define BB_TIM1_EGR_CC3G	*(volatile uint32_t *) 0x4225828C
#define BB_TIM1_EGR_CC4G	*(volatile uint32_t *) 0x42258290
#define BB_TIM1_EGR_COMG	*(volatile uint32_t *) 0x42258294
#define BB_TIM1_EGR_TG		*(volatile uint32_t *) 0x42258298
#define BB_TIM1_EGR_BG		*(volatile uint32_t *) 0x4225829C

//timer2 interrupts
#define BB_TIM2_DIER_UIE 	*(volatile uint32_t *) 0x42000180
#define BB_TIM2_DIER_CC1IE	*(volatile uint32_t *) 0x42000184
#define BB_TIM2_DIER_CC2IE	*(volatile uint32_t *) 0x42000188
#define BB_TIM2_DIER_CC3IE	*(volatile uint32_t *) 0x4200018C
#define BB_TIM2_DIER_CC4IE	*(volatile uint32_t *) 0x42000190
#define BB_TIM2_DIER_TIE	*(volatile uint32_t *) 0x42000198

//timer2 clear interrupt flags
#define BB_TIM2_SR_UIF		*(volatile uint32_t *) 0x42000200
#define BB_TIM2_SR_CC1IF	*(volatile uint32_t *) 0x42000204
#define BB_TIM2_SR_CC2IF	*(volatile uint32_t *) 0x42000208
#define BB_TIM2_SR_CC3IF	*(volatile uint32_t *) 0x4200020C
#define BB_TIM2_SR_CC4IF	*(volatile uint32_t *) 0x42000210
#define BB_TIM2_SR_TIF		*(volatile uint32_t *) 0x42000218

//timer2 event generators
#define BB_TIM2_EGR_UG		*(volatile uint32_t *) 0x42000280
#define BB_TIM2_EGR_CC1G	*(volatile uint32_t *) 0x42000284
#define BB_TIM2_EGR_CC2G	*(volatile uint32_t *) 0x42000288
#define BB_TIM2_EGR_CC3G	*(volatile uint32_t *) 0x4200028C
#define BB_TIM2_EGR_CC4G	*(volatile uint32_t *) 0x42000290
#define BB_TIM2_EGR_TG		*(volatile uint32_t *) 0x42000298

//timer3 interrupts
#define BB_TIM3_DIER_UIE 	*(volatile uint32_t *) 0x42008180
#define BB_TIM3_DIER_CC1IE	*(volatile uint32_t *) 0x42008184
#define BB_TIM3_DIER_CC2IE	*(volatile uint32_t *) 0x42008188
#define BB_TIM3_DIER_CC3IE	*(volatile uint32_t *) 0x4200818C
#define BB_TIM3_DIER_CC4IE	*(volatile uint32_t *) 0x42008190
#define BB_TIM3_DIER_TIE	*(volatile uint32_t *) 0x42008198

//timer3 clear interrupt flags
#define BB_TIM3_SR_UIF		*(volatile uint32_t *) 0x42008200
#define BB_TIM3_SR_CC1IF	*(volatile uint32_t *) 0x42008204
#define BB_TIM3_SR_CC2IF	*(volatile uint32_t *) 0x42008208
#define BB_TIM3_SR_CC3IF	*(volatile uint32_t *) 0x4200820C
#define BB_TIM3_SR_CC4IF	*(volatile uint32_t *) 0x42008210
#define BB_TIM3_SR_TIF		*(volatile uint32_t *) 0x42008218

//timer3 event generators
#define BB_TIM3_EGR_UG		*(volatile uint32_t *) 0x42008280
#define BB_TIM3_EGR_CC1G	*(volatile uint32_t *) 0x42008284
#define BB_TIM3_EGR_CC2G	*(volatile uint32_t *) 0x42008288
#define BB_TIM3_EGR_CC3G	*(volatile uint32_t *) 0x4200828C
#define BB_TIM3_EGR_CC4G	*(volatile uint32_t *) 0x42008290
#define BB_TIM3_EGR_TG		*(volatile uint32_t *) 0x42008298

//timer4 interrupts
#define BB_TIM4_DIER_UIE 	*(volatile uint32_t *) 0x42010180
#define BB_TIM4_DIER_CC1IE	*(volatile uint32_t *) 0x42010184
#define BB_TIM4_DIER_CC2IE	*(volatile uint32_t *) 0x42010188
#define BB_TIM4_DIER_CC3IE	*(volatile uint32_t *) 0x4201018C
#define BB_TIM4_DIER_CC4IE	*(volatile uint32_t *) 0x42010190
#define BB_TIM4_DIER_TIE	*(volatile uint32_t *) 0x42010198

//timer4 clear interrupt flags
#define BB_TIM4_SR_UIF		*(volatile uint32_t *) 0x42010200
#define BB_TIM4_SR_CC1IF	*(volatile uint32_t *) 0x42010204
#define BB_TIM4_SR_CC2IF	*(volatile uint32_t *) 0x42010208
#define BB_TIM4_SR_CC3IF	*(volatile uint32_t *) 0x4201020C
#define BB_TIM4_SR_CC4IF	*(volatile uint32_t *) 0x42010210
#define BB_TIM4_SR_TIF		*(volatile uint32_t *) 0x42010218

//timer4 event generators
#define BB_TIM4_EGR_UG		*(volatile uint32_t *) 0x42010280
#define BB_TIM4_EGR_CC1G	*(volatile uint32_t *) 0x42010284
#define BB_TIM4_EGR_CC2G	*(volatile uint32_t *) 0x42010288
#define BB_TIM4_EGR_CC3G	*(volatile uint32_t *) 0x4201028C
#define BB_TIM4_EGR_CC4G	*(volatile uint32_t *) 0x42010290
#define BB_TIM4_EGR_TG		*(volatile uint32_t *) 0x42010298


//#define _BBTIM2_(mem_offset) (*(volatile uint32_t *)(0x42260000 + (mem_offset)))
//#define BB_SPI_CR1  0x0000

//register offsets
#define TIMX_CR1	0x00
#define TIMX_CR2	0x04
#define TIMX_SMCR	0x08
#define TIMX_DIER	0x0C
#define TIMX_SR		0x10
#define TIMX_EGR	0x14
#define TIMX_CCMR1	0x18
#define TIMX_CCMR2	0x1C
#define TIMX_CCER	0x20
#define TIMX_CNT	0x24
#define TIMX_PSC	0x28
#define TIMX_ARR	0x2C
#define TIMX_RCR	0x30
#define TIMX_CCR1	0x34
#define TIMX_CCR2	0x38
#define TIMX_CCR3	0x3C
#define TIMX_CCR4	0x40
#define TIMX_BDTR	0x44
#define TIMX_DCR	0x48
#define TIMX_DMAR	0x4C

//bits
//CR1
#define TIMX_CR1_CEN	0x0001
#define TIMX_CR1_UDIS	0x0002
#define TIMX_CR1_URS	0x0004
#define TIMX_CR1_OPM	0x0008
#define TIMX_CR1_DIR	0x0010
#define TIMX_CR1_CMS	0x0060 //mask
#define TIMX_CR1_ARPE	0x0080
#define TIMX_CR1_CKD	0x0300 //mask
//rest reserved

#define TIMX_CR2_CCPC	0x0001
//reserved 0x0002
#define TIMX_CR2_CCUS	0x0004
#define TIMX_CR2_CCDS	0x0008
#define TIMX_CR2_MMS	0x0070 //mask
#define TIMX_CR2_TI1S	0x0080
#define TIMX_CR2_OIS1	0x0100
#define TIMX_CR2_OIS1N	0x0200
#define TIMX_CR2_OIS2	0x0400
#define TIMX_CR2_OIS2N	0x0800
#define TIMX_CR2_OIS3	0x1000
#define TIMX_CR2_OIS3N	0x2000
#define TIMX_CR2_OIS4	0x4000
//reserved 0x8000

#define TIMX_SMCR_SMS	0x0007 //mask
//reserved 0x0008
#define TIMX_SMCR_TS	0x0070 //mask
#define TIMX_SMCR_MSM	0x0080
#define TIMX_SMCR_ETF	0x0F00 //mask
#define TIMX_SMCR_ETPS	0x3000 //mask
#define TIMX_SMCR_ECE	0x4000
#define TIMX_SMCR_ETP	0x8000

#define TIMX_DIER_UIE	0x0001
#define TIMX_DIER_CC1IE	0x0002
#define TIMX_DIER_CC2IE	0x0004
#define TIMX_DIER_CC3IE	0x0008
#define TIMX_DIER_CC4IE	0x0010
#define TIMX_DIER_COMIE	0x0020
#define TIMX_DIER_TIE	0x0040
#define TIMX_DIER_BIE	0x0080
#define TIMX_DIER_UDE	0x0100
#define TIMX_DIER_CC1DE	0x0200
#define TIMX_DIER_CC2DE	0x0400
#define TIMX_DIER_CC3DE	0x0800
#define TIMX_DIER_CC4DE	0x1000
#define TIMX_DIER_CCDE	0x1E00 //mask
#define TIMX_DIER_COMDE	0x2000
#define TIMX_DIER_TDE	0x4000
//reserved

#define TIMX_SR_UIF		0x0001
#define TIMX_SR_CC1IF	0x0002
#define TIMX_SR_CC2IF	0x0004
#define TIMX_SR_CC3IF	0x0008
#define TIMX_SR_CC4IF	0x0010
#define TIMX_SR_COMIF	0x0020
#define TIMX_SR_TIF		0x0040
#define TIMX_SR_BIF		0x0080
//reserved	0x0100
#define TIMX_SR_CC1OF	0x0200
#define TIMX_SR_CC2OF	0x0400
#define TIMX_SR_CC3OF	0x0800
#define TIMX_SR_CC4OF	0x1000
//reserved x3

#define TIMX_EGR_UG		0x0001
#define TIMX_EGR_CC1G	0x0002
#define TIMX_EGR_CC2G	0x0004
#define TIMX_EGR_CC3G	0x0008
#define TIMX_EGR_CC4G	0x0010
#define TIMX_EGR_COMG	0x0020
#define TIMX_EGR_TG		0x0040
#define TIMX_EGR_BG		0x0080
//upper byte reserved

#define TIMX_CCMR1_CC1S		0x0003 //mask
#define TIMX_CCMR1_OC1FE	0x0004
#define TIMX_CCMR1_OC1PE	0x0008
#define TIMX_CCMR1_OC1M		0x0070 //mask
#define TIMX_CCMR1_OC1CE	0x0080
#define TIMX_CCMR1_CC2S		0x0300 //mask
#define TIMX_CCMR1_OC2FE	0x0400
#define TIMX_CCMR1_OC2PE	0x0800
#define TIMX_CCMR1_OC2M		0x7000 //mask
#define TIMX_CCMR1_OC2CE	0x8000

//masks
#define TIMX_CCMR1_IC1PSC	0x0006
#define TIMX_CCMR1_IC1F		0x00F0
#define TIMX_CCMR1_IC2PSC	0x0600
#define TIMX_CCMR1_IC2F		0xF000

#define TIMX_CCMR2_CC3S		0x0003 //mask
#define TIMX_CCMR2_OC3FE	0x0004
#define TIMX_CCMR2_OC3PE	0x0008
#define TIMX_CCMR2_OC3M		0x0070 //mask
#define TIMX_CCMR2_OC3CE	0x0080
#define TIMX_CCMR2_CC4S		0x0300 //mask
#define TIMX_CCMR2_OC4FE	0x0400
#define TIMX_CCMR2_OC4PE	0x0800
#define TIMX_CCMR2_OC4M		0x7000 //mask
#define TIMX_CCMR2_OC4CE	0x8000

//masks
#define TIMX_CCMR2_IC3PSC	0x0006
#define TIMX_CCMR2_IC3F		0x00F0
#define TIMX_CCMR2_IC4PSC	0x0600
#define TIMX_CCMR2_IC4F		0xF000

#define TIMX_CCER_CC1E	0x0001
#define TIMX_CCER_CC1P	0x0002
#define TIMX_CCER_CC1NE	0x0004
#define TIMX_CCER_CC1NP	0x0008
#define TIMX_CCER_CC2E	0x0010
#define TIMX_CCER_CC2P	0x0020
#define TIMX_CCER_CC2NE	0x0040
#define TIMX_CCER_CC2NP	0x0080
#define TIMX_CCER_CC3E	0x0100
#define TIMX_CCER_CC3P	0x0200
#define TIMX_CCER_CC3NE	0x0400
#define TIMX_CCER_CC3NP	0x0800
#define TIMX_CCER_CC4E	0x1000
#define TIMX_CCER_CC4P	0x2000

#define TIMX_RCR_REP	0x00FF //mask

#define TIMX_BDTR_DTG	0x00FF //mask
#define TIMX_BDTR_LOCK	0x0300 //mask
#define TIMX_BDTR_OSSI	0x0400
#define TIMX_BDTR_OSSR	0x0800
#define TIMX_BDTR_BKE	0x1000
#define TIMX_BDTR_BKP	0x2000
#define TIMX_BDTR_AOE	0x4000
#define TIMX_BDTR_MOE	0x8000

#define TIMX_DCR_DBA	0x001F //mask
#define TIMX_DCR_DBL	0x1F00 //mask

//EXTI registers
//#define EXTI_IMR	*(volatile uint32_t *) 0x40010400
//#define EXTI_EMR	*(volatile uint32_t *) 0x40010404
//#define EXTI_RTSR	*(volatile uint32_t *) 0x40010408
//#define EXTI_FTSR	*(volatile uint32_t *) 0x4001040C
//#define EXTI_SWIER	*(volatile uint32_t *) 0x40010410
//#define EXTI_PR		*(volatile uint32_t *) 0x40010414

#endif /* STM32F103_TIMERS_REG_H_ */
