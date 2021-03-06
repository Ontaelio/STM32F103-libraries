/*
 * STM32F103 USART functions header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_USART_H_
#define STM32F103_USART_H_

#define APB2SPEED 72000000
#define APB1SPEED 36000000

//#define USE_BUFFER_FOR_INTS
//#define NAN_INFINITY_ENABLED

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <math.h>
#include <stm32f103_usart_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_timers.h>
#include <stm32f103_gpio.h>
#include <stm32f103_dma.h>

#define USART_TX_EMPTY USART_CR1_TXEIE
#define USART_TRANSFER_COMPLETE USART_CR1_TCIE
#define USART_RX_NOT_EMPTY USART_CR1_RXNEIE
#define USART_IDLE_LINE USART_CR1_IDLEIE
#define USART_PARITY_ERROR USART_CR1_PEIE
#define USART_CLEAR_TO_SEND USART_CR3_CTSIE
#define USART_DMAR_ERROR USART_CR3_EIE

class usart
{
public:
	virtual ~usart() {}
	virtual void sendByte(uint8_t dat) =0;
	virtual uint8_t getByte() =0;

	void sendStream(uint8_t* dat, uint32_t size);

	void printString(const char *str);
	void printCPPString(std::string s);
	void printUInt(uint32_t a);
	void printInt(int32_t a);

	void printUInt64(uint64_t a);
	void printInt64(int64_t a);
	void fprintUInt(uint32_t a, uint_fast8_t s);

	void printFloat(long double a, uint_fast8_t s = 2);
	void printHex(unsigned val);

	char getChar();
	void getStream(uint8_t* dat, uint16_t size);
	uint64_t getUInt();
	int64_t getInt();
	long double getFloat();
	void getString(char* arr);
	//void clearInput();

	friend usart& operator << (usart& out, const char* str);

	friend usart& operator << (usart& out, const char ch);
	friend usart& operator << (usart& out, const unsigned dat);
	friend usart& operator << (usart& out, const uint8_t dat);
	friend usart& operator << (usart& out, const uint16_t dat);
	friend usart& operator << (usart& out, const uint32_t dat);
	friend usart& operator << (usart& out, const uint64_t dat);

	friend usart& operator << (usart& out, const int dat);
	friend usart& operator << (usart& out, const int8_t dat);
	friend usart& operator << (usart& out, const int16_t dat);
	friend usart& operator << (usart& out, const int32_t dat);
	friend usart& operator << (usart& out, const int64_t dat);

	friend usart& operator << (usart& out, const float dat);
	friend usart& operator << (usart& out, const double dat);
	friend usart& operator << (usart& out, const long double dat);

	friend usart& operator >> (usart& in, char* str);

	friend usart& operator >> (usart& in, char &dat);
	friend usart& operator >> (usart& in, unsigned &dat);
	friend usart& operator >> (usart& in, uint8_t &dat);
	friend usart& operator >> (usart& in, uint16_t &dat);
	friend usart& operator >> (usart& in, uint32_t &dat);
	friend usart& operator >> (usart& in, uint64_t &dat);

	friend usart& operator >> (usart& in, int &dat);
	friend usart& operator >> (usart& in, int8_t &dat);
	friend usart& operator >> (usart& in, int16_t &dat);
	friend usart& operator >> (usart& in, int32_t &dat);
	friend usart& operator >> (usart& in, int64_t &dat);

	friend usart& operator >> (usart& in, float &dat);
	friend usart& operator >> (usart& in, double &dat);
	friend usart& operator >> (usart& in, long double &dat);
};

class usart_mem : public usart
{
public:
	usart_mem(uint16_t s): size(s), counter(0) {}
	void init(uint8_t* dat) {stream = dat;}
	void sendByte(uint8_t dat);
	uint8_t getByte();

private:
	uint16_t size, counter;
	uint8_t* stream;
};

class usart1 : public usart
{
public:
	void init(uint32_t baud, uint_fast8_t remap = 0);
	void initTX(uint32_t baud, uint_fast8_t remap = 0);
	void initRX(uint32_t baud, uint_fast8_t remap = 0);
	void sendByte(uint8_t dat);
	uint8_t getByte();
	void dump() {while(_USART1_(USART_SR) & USART_SR_RXNE) usart1::readDR();}

	void RXenable() {_USART1_(USART_CR1) |= USART_CR1_RE;}
	void RXdisable() {_USART1_(USART_CR1) &= ~USART_CR1_RE;}
	void TXenable() {_USART1_(USART_CR1) |= USART_CR1_TE;}
	void TXdisable() {_USART1_(USART_CR1) &= ~USART_CR1_TE;}
	void CLKenable(uint8_t cpol = 0, uint8_t cpha = 0, uint8_t lbcl = 0)
		{_USART1_(USART_CR2) |= USART_CR2_CLKEN | (cpha << 9) | (cpol << 10) | (lbcl << 8);}
	void CLKdisable() {_USART1_(USART_CR2) &= ~(USART_CR2_CLKEN | 0x0700);}
	void RTSenable() {_USART1_(USART_CR3) |= USART_CR3_RTSE;}
	void RTSdisable() {_USART1_(USART_CR3) &= ~USART_CR3_RTSE;}
	void CTSenable() {_USART1_(USART_CR3) |= USART_CR3_CTSE;}
	void CTSdisable() {_USART1_(USART_CR3) &= ~USART_CR3_CTSE;}
	void HDenable() {_USART1_(USART_CR3) |= USART_CR3_HDSEL;}
	void HDdisable() {_USART1_(USART_CR3) &= ~USART_CR3_HDSEL;}
	void DMARXenable() {_USART1_(USART_CR3) |= USART_CR3_DMAR;}
	void DMARXdisable() {_USART1_(USART_CR3) &= ~USART_CR3_DMAR;}
	void DMATXenable() {_USART1_(USART_CR3) |= USART_CR3_DMAT;}
	void DMATXdisable() {_USART1_(USART_CR3) &= ~USART_CR3_DMAT;}
	void sendBreak() {_USART1_(USART_CR1) |= USART_CR1_SBK;}

	void wordLength(uint8_t M) {BB_USART1_CR1_M = M&0x01;}
	void stopBits(uint8_t stp) {_USART1_(USART_CR2) &= ~USART_CR2_STOP; _USART1_(USART_CR2) |= stp << 12;}
	void parityEnable(uint8_t ps) {_USART1_(USART_CR1) |= USART_CR1_PCE | (ps<<9);}
	void parityDisable() {_USART1_(USART_CR1) &= ~(USART_CR1_PCE | USART_CR1_PS);}

	void IRQenable(uint16_t irqs);
	void IRQdisable() {IRQ_32TO63_CER |= IRQ_BITMASK_USART1;}

	void clearCTS() {_USART1_(USART_SR) &= ~USART_SR_CTS;}
	uint16_t checkError() {return (_USART1_(USART_SR) & 0x001F);}
	uint16_t checkIdle() {return (_USART1_(USART_SR) & 0x0010);}
	uint16_t readDR() {return _USART1_(USART_DR);}

	void sendStreamDMA(uint8_t* dat, uint16_t size);
	void getStreamDMA(uint8_t* dat, uint16_t size);
	void startTX(uint8_t* dat, uint16_t size, uint16_t pri = 0x1000);
	void stopTX();
	void startRX(uint8_t* dat, uint16_t size, uint16_t pri = 0x1000);
	void stopRX();

private:

};

class usart2 : public usart
{
public:
	void init(uint32_t baud, uint_fast8_t remap = 0);
	void initTX(uint32_t baud, uint_fast8_t remap = 0);
	void initRX(uint32_t baud, uint_fast8_t remap = 0);
	void sendByte(uint8_t dat);
	uint8_t getByte();
	void dump() {while(_USART2_(USART_SR) & USART_SR_RXNE) usart2::readDR();}

	void RXenable() {_USART2_(USART_CR1) |= USART_CR1_RE;}
	void RXdisable() {_USART2_(USART_CR1) &= ~USART_CR1_RE;}
	void TXenable() {_USART2_(USART_CR1) |= USART_CR1_TE;}
	void TXdisable() {_USART2_(USART_CR1) &= ~USART_CR1_TE;}
	void CLKenable(uint8_t cpol = 0, uint8_t cpha = 0, uint8_t lbcl = 0)
		{_USART2_(USART_CR2) |= USART_CR2_CLKEN | (cpha << 9) | (cpol << 10) | (lbcl << 8);}
	void CLKdisable() {_USART2_(USART_CR2) &= ~(USART_CR2_CLKEN | 0x0700);}
	void RTSenable() {_USART2_(USART_CR3) |= USART_CR3_RTSE;}
	void RTSdisable() {_USART2_(USART_CR3) &= ~USART_CR3_RTSE;}
	void CTSenable() {_USART2_(USART_CR3) |= USART_CR3_CTSE;}
	void CTSdisable() {_USART2_(USART_CR3) &= ~USART_CR3_CTSE;}
	void HDenable() {_USART2_(USART_CR3) |= USART_CR3_HDSEL;}
	void HDdisable() {_USART2_(USART_CR3) &= ~USART_CR3_HDSEL;}
	void DMARXenable() {_USART2_(USART_CR3) |= USART_CR3_DMAR;}
	void DMARXdisable() {_USART2_(USART_CR3) &= ~USART_CR3_DMAR;}
	void DMATXenable() {_USART2_(USART_CR3) |= USART_CR3_DMAT;}
	void DMATXdisable() {_USART2_(USART_CR3) &= ~USART_CR3_DMAT;}
	void sendBreak() {_USART2_(USART_CR1) |= USART_CR1_SBK;}

	void wordLength(uint8_t M) {BB_USART2_CR1_M = M&0x01;}
	void stopBits(uint8_t stp) {_USART2_(USART_CR2) &= ~USART_CR2_STOP; _USART2_(USART_CR2) |= stp << 12;}
	void parityEnable(uint8_t ps) {_USART2_(USART_CR1) |= USART_CR1_PCE | (ps<<9);}
	void parityDisable() {_USART2_(USART_CR1) &= ~(USART_CR1_PCE | USART_CR1_PS);}

	void IRQenable(uint16_t irqs);
	void IRQdisable() {IRQ_32TO63_CER |= IRQ_BITMASK_USART2;}

	void clearCTS() {_USART2_(USART_SR) &= ~USART_SR_CTS;}
	uint16_t checkError() {return (_USART2_(USART_SR) & 0x001F);}
	uint16_t checkIdle() {return (_USART2_(USART_SR) & 0x0010);}
	uint16_t readDR() {return _USART2_(USART_DR);}

	void sendStreamDMA(uint8_t* dat, uint16_t size);
	void getStreamDMA(uint8_t* dat, uint16_t size);
	void startTX(uint8_t* dat, uint16_t size, uint16_t pri = 0x1000);
	void stopTX();
	void startRX(uint8_t* dat, uint16_t size, uint16_t pri = 0x1000);
	void stopRX();


private:

};


class usart3 : public usart
{
public:
	void init(uint32_t baud, uint_fast8_t remap = 0);
	void initTX(uint32_t baud, uint_fast8_t remap = 0);
	void initRX(uint32_t baud, uint_fast8_t remap = 0);
	void sendByte(uint8_t dat);
	uint8_t getByte();
	void dump() {while(_USART3_(USART_SR) & USART_SR_RXNE) usart3::readDR();}

	void RXenable() {_USART3_(USART_CR1) |= USART_CR1_RE;}
	void RXdisable() {_USART3_(USART_CR1) &= ~USART_CR1_RE;}
	void TXenable() {_USART3_(USART_CR1) |= USART_CR1_TE;}
	void TXdisable() {_USART3_(USART_CR1) &= ~USART_CR1_TE;}
	void CLKenable(uint8_t cpol = 0, uint8_t cpha = 0, uint8_t lbcl = 0)
		{_USART3_(USART_CR2) |= USART_CR2_CLKEN | (cpha << 9) | (cpol << 10) | (lbcl << 8);}
	void CLKdisable() {_USART3_(USART_CR2) &= ~(USART_CR2_CLKEN | 0x0700);}
	void RTSenable() {_USART3_(USART_CR3) |= USART_CR3_RTSE;}
	void RTSdisable() {_USART3_(USART_CR3) &= ~USART_CR3_RTSE;}
	void CTSenable() {_USART3_(USART_CR3) |= USART_CR3_CTSE;}
	void CTSdisable() {_USART3_(USART_CR3) &= ~USART_CR3_CTSE;}
	void HDenable() {_USART3_(USART_CR3) |= USART_CR3_HDSEL;}
	void HDdisable() {_USART3_(USART_CR3) &= ~USART_CR3_HDSEL;}
	void DMARXenable() {_USART3_(USART_CR3) |= USART_CR3_DMAR;}
	void DMARXdisable() {_USART3_(USART_CR3) &= ~USART_CR3_DMAR;}
	void DMATXenable() {_USART3_(USART_CR3) |= USART_CR3_DMAT;}
	void DMATXdisable() {_USART3_(USART_CR3) &= ~USART_CR3_DMAT;}
	void sendBreak() {_USART3_(USART_CR1) |= USART_CR1_SBK;}

	void wordLength(uint8_t M) {BB_USART3_CR1_M = M&0x01;}
	void stopBits(uint8_t stp) {_USART3_(USART_CR2) &= ~USART_CR2_STOP; _USART3_(USART_CR2) |= stp << 12;}
	void parityEnable(uint8_t ps) {_USART3_(USART_CR1) |= USART_CR1_PCE | (ps<<9);}
	void parityDisable() {_USART3_(USART_CR1) &= ~(USART_CR1_PCE | USART_CR1_PS);}

	void IRQenable(uint16_t irqs);
	void IRQdisable() {IRQ_32TO63_CER |= IRQ_BITMASK_USART3;}

	void clearCTS() {_USART3_(USART_SR) &= ~USART_SR_CTS;}
	uint16_t checkError() {return (_USART3_(USART_SR) & 0x001F);}
	uint16_t checkIdle() {return (_USART3_(USART_SR) & 0x0010);}
	uint16_t readDR() {return _USART3_(USART_DR);}

	void sendStreamDMA(uint8_t* dat, uint16_t size);
	void getStreamDMA(uint8_t* dat, uint16_t size);
	void startTX(uint8_t* dat, uint16_t size, uint16_t pri = 0x1000);
	void stopTX();
	void startRX(uint8_t* dat, uint16_t size, uint16_t pri = 0x1000);
	void stopRX();


private:

};

char hexChar(uint8_t val);

/*
inline void usart1_send(uint8_t a)
{
	while(!(_USART1_(USART_SR) & USART_SR_TC));
	_USART1_(USART_DR) = a;
}

inline void usart1_init(uint32_t brate)
{
	//enable GPIOA | USART1 |alt func
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
	_USART1_(USART_BRR) = APB2SPEED/brate; //evil way to calculate it; freq/baudrate
	//configure pins; TX(PA9) alt push-pull output; RX(PA10) input
	pinA9_Output_AFPP_50(); //these are in gpio_func header
	pinA10_Input();
	//enable USART
	_USART1_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART1_(USART_CR1) |= USART_CR1_TE | USART_CR1_RE;
}
*/

#endif /* STM32F103_USART_H_ */
