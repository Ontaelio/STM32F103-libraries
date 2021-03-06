/*
 * STM32F103 ADC functions header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */
#ifndef STM32F103_ADC_H_
#define STM32F103_ADC_H_

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stm32f103_adc_reg.h>
#include <stm32f103_dma.h>
#include <stm32f103_dma_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_gpio.h>
#include <stm32f103_timers.h>

#define ADC_EXT_T1CC1	0
#define ADC_EXT_T1CC2	1
#define ADC_EXT_T1CC3	2
#define ADC_EXT_T2CC2	3
#define ADC_EXT_T3TRGO	4
#define ADC_EXT_T4CC4	5
#define ADC_EXT_EXTI11	6
#define ADC_EXT_SW		7

#define ADC_JEXT_T1TRGO	0
#define ADC_JEXT_T1CC4 	1
#define ADC_JEXT_T2TRGO	2
#define ADC_JEXT_T2CC1	3
#define ADC_JEXT_T3CC4	4
#define ADC_JEXT_T4TRGO	5
#define ADC_JEXT_EXTI15	6
#define ADC_JEXT_SW		7


class analog_pin
{
public:
	analog_pin(uint_fast8_t cha) : cnum (cha) {}
	void init(uint8_t cycles = 0);
	uint16_t read();
	operator uint16_t() {return read();}

protected:
	uint_fast8_t cnum;
};

class analog_cont
{
public:
	analog_cont(uint_fast8_t adg, uint_fast8_t cha) :
			cnum (cha), adc ((volatile uint32_t *)(0x40012400 + 0x0000400 * (adg - 1))) {}
	void init(uint8_t cycles = 0);
	void start();
	void stop() {*(adc + ADC_CR2/4) &= ~ADC_CR2_CONT;}
	uint16_t read() {return *(adc + 19);}
	operator uint16_t() {return *(adc + 19);}

	void injectInit(uint8_t jtrigger = 7); //start triggered
	void injectAuto() {*(adc + ADC_CR2/4) &= ~(ADC_CR2_JEXTTRIG); *(adc + ADC_CR1/4) |= ADC_CR1_JAUTO;} //start auto
	void injectTriggered() {*(adc + ADC_CR2/4) |= ADC_CR2_JEXTTRIG; *(adc + ADC_CR1/4) &= ~(ADC_CR1_JAUTO);} //turn off auto
	void inject(uint8_t cha1);
	void inject(uint8_t cha1, uint8_t cha2);
	void inject(uint8_t cha1, uint8_t cha2, uint8_t cha3);
	void inject(uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4);
	void injectStart(uint_fast8_t dowait = 1); //manually trigger with JSWSTART and wait for result with dowait==1
	void injectClear() {*(adc + ADC_SR/4) &= ~ADC_SR_JEOC;}
	uint16_t injectRead(uint_fast8_t jcha);

	void DMAenable(){_ADC1_(ADC_CR2) |= ADC_CR2_DMA;}
	void DMAdisable(){_ADC1_(ADC_CR2) &= ~ADC_CR2_DMA;}

private:
	void injectWaitForResult();

protected:
	uint_fast8_t cnum;
	volatile uint32_t* adc;
};

class analog_scan
{
public:
	//analog_scan();
	void init(uint16_t* targ, uint_fast8_t num, ...); // DMA1 channel 1
	void start() {_ADC1_(ADC_CR2) |= ADC_CR2_CONT;	_ADC1_(ADC_CR2) |= ADC_CR2_ADON;}
	void stop() {_ADC1_(ADC_CR2) &= ~ADC_CR2_CONT;}
	void read() {_ADC1_(ADC_CR2) |= ADC_CR2_ADON;} //convert once
	void speed(uint_fast8_t cha, uint8_t cycles);
	void priority(uint8_t pri) {_DMA1_(DMA_CCR1) &= ~DMA_CCR_PL; _DMA1_(DMA_CCR1) |= (pri << 12);}

	//external trigger on regular channels
	void exti(uint8_t regtrig);
	//these for use only in mode 7 (SWSTART)
	void extiStart() {_ADC1_(ADC_CR2) |= ADC_CR2_CONT; _ADC1_(ADC_CR2) |= ADC_CR2_SWSTART;}
	void extiRead() { _ADC1_(ADC_CR2) |= ADC_CR2_SWSTART;}

	void injectInit(uint8_t jtrigger = 7); //start triggered
	void injectAuto() {_ADC1_(ADC_CR2) &= ~(ADC_CR2_JEXTTRIG); _ADC1_(ADC_CR1) |= ADC_CR1_JAUTO;} //start auto
	void injectTriggered() {_ADC1_(ADC_CR2) |= ADC_CR2_JEXTTRIG; _ADC1_(ADC_CR1) &= ~(ADC_CR1_JAUTO);} //turn off auto
	void inject(uint8_t cha1);
	void inject(uint8_t cha1, uint8_t cha2);
	void inject(uint8_t cha1, uint8_t cha2, uint8_t cha3);
	void inject(uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4);
	void injectStart(uint_fast8_t dowait = 1); //manually trigger with JSWSTART and wait for result with dowait==1
	void injectClear() {_ADC1_(ADC_SR) &= ~ADC_SR_JEOC;}
	uint16_t injectRead(uint_fast8_t jcha);

private:
	void injectWaitForResult();
};

void adc1_init();
void adc2_init();

// status bits: check for event, clear event
inline uint8_t adc1_Start() {return ((_ADC1_(ADC_SR) & (ADC_SR_STRT))>>4);}
inline uint8_t adc1_JStart() {return ((_ADC1_(ADC_SR) & (ADC_SR_JSTRT))>>3);}
inline uint8_t adc1_JEOC() {return ((_ADC1_(ADC_SR) & (ADC_SR_JEOC))>>2);}
inline uint8_t adc1_EOC() {return ((_ADC1_(ADC_SR) & (ADC_SR_EOC))>>1);}
inline uint8_t adc1_WD() {return ((_ADC1_(ADC_SR) & (ADC_SR_AWD)));}
inline void adc1_clearStart() {_ADC1_(ADC_SR) &= ~(ADC_SR_STRT);}
inline void adc1_clearJStart() {_ADC1_(ADC_SR) &= ~(ADC_SR_JSTRT);}
inline void adc1_clearJEOC() {_ADC1_(ADC_SR) &= ~(ADC_SR_JEOC);}
inline void adc1_clearEOC() {_ADC1_(ADC_SR) &= ~(ADC_SR_EOC);}
inline void adc1_clearWD() {_ADC1_(ADC_SR) &= ~(ADC_SR_AWD);}

inline uint8_t adc2_Start() {return ((_ADC2_(ADC_SR) & (ADC_SR_STRT))>>4);}
inline uint8_t adc2_JStart() {return ((_ADC2_(ADC_SR) & (ADC_SR_JSTRT))>>3);}
inline uint8_t adc2_JEOC() {return ((_ADC2_(ADC_SR) & (ADC_SR_JEOC))>>2);}
inline uint8_t adc2_EOC() {return ((_ADC2_(ADC_SR) & (ADC_SR_EOC))>>1);}
inline uint8_t adc2_WD() {return ((_ADC2_(ADC_SR) & (ADC_SR_AWD)));}
inline void adc2_clearStart() {_ADC2_(ADC_SR) &= ~(ADC_SR_STRT);}
inline void adc2_clearJStart() {_ADC2_(ADC_SR) &= ~(ADC_SR_JSTRT);}
inline void adc2_clearJEOC() {_ADC2_(ADC_SR) &= ~(ADC_SR_JEOC);}
inline void adc2_clearEOC() {_ADC2_(ADC_SR) &= ~(ADC_SR_EOC);}
inline void adc2_clearWD() {_ADC2_(ADC_SR) &= ~(ADC_SR_AWD);}

//watchdogs
void adc1_watchdog(uint32_t low, uint32_t high);
void adc1_watchdog(uint8_t cha, uint32_t low, uint32_t high);
void adc1_injectWatchdog(uint32_t low, uint32_t high);
void adc1_injectWatchdog(uint8_t cha, uint32_t low, uint32_t high);
inline void adc1_watchdog() {_ADC1_(ADC_CR1) &= ~(ADC_CR1_AWDEN);}
inline void adc1_injectWatchdog() {_ADC1_(ADC_CR1) &= ~(ADC_CR1_JAWDEN);}
inline void adc1_watchdogHigh(uint32_t high) {_ADC1_(ADC_HTR) = high;}
inline void adc1_watchdogLow(uint32_t low) {_ADC1_(ADC_LTR) = low;}
inline void adc1_watchdogLowHigh(uint32_t low, uint32_t high) {_ADC1_(ADC_LTR) = low; _ADC1_(ADC_HTR) = high;}

void adc2_watchdog(uint32_t low, uint32_t high);
void adc2_watchdog(uint8_t cha, uint32_t low, uint32_t high);
void adc2_injectWatchdog(uint32_t low, uint32_t high);
void adc2_injectWatchdog(uint8_t cha, uint32_t low, uint32_t high);
inline void adc2_watchdog() {_ADC2_(ADC_CR1) &= ~(ADC_CR1_AWDEN);}
inline void adc2_injectWatchdog() {_ADC2_(ADC_CR1) &= ~(ADC_CR1_JAWDEN);}
inline void adc2_watchdogHigh(uint32_t high) {_ADC2_(ADC_HTR) = high;}
inline void adc2_watchdogLow(uint32_t low) {_ADC2_(ADC_LTR) = low;}
inline void adc2_watchdogLowHigh(uint32_t low, uint32_t high) {_ADC2_(ADC_LTR) = low; _ADC1_(ADC_HTR) = high;}


//interrupts - global
inline void adc_IRQenable() {IRQ_0TO31_SER |= IRQ_BITMASK_ADC1_2;}
inline void adc_IRQdisable() {IRQ_0TO31_CER |= IRQ_BITMASK_ADC1_2;}

//interrupts - STM, bit banding
inline void adc1_WDinterrupt(uint8_t bit) {BB_ADC1_CR1_AWDIE = bit;}
inline void adc1_EOCinterrupt(uint8_t bit) {BB_ADC1_CR1_EOCIE = bit;}
inline void adc1_JEOCinterrupt(uint8_t bit) {BB_ADC1_CR1_JEOCIE = bit;}
inline void adc2_WDinterrupt(uint8_t bit) {BB_ADC2_CR1_AWDIE = bit;}
inline void adc2_EOCinterrupt(uint8_t bit) {BB_ADC2_CR1_EOCIE = bit;}
inline void adc2_JEOCinterrupt(uint8_t bit) {BB_ADC2_CR1_JEOCIE = bit;}

//temperature sensor
inline void adc_temperature() {_ADC1_(ADC_CR2) |= ADC_CR2_TSVREFE;}

//dual mode
inline void adc_dualMode(uint8_t dmode) {_ADC1_(ADC_CR1) &= ~(ADC_CR1_DUALMOD); _ADC1_(ADC_CR1) |= dmode << 16;}




#endif /* STM32F103_ADC_H_ */
