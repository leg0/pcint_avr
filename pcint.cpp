#include "pcint.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern "C" {
    void __attribute__((weak)) PC_0(bool value) { }
    void __attribute__((weak)) PC_1(bool value) { }
    void __attribute__((weak)) PC_2(bool value) { }
    void __attribute__((weak)) PC_3(bool value) { }
    void __attribute__((weak)) PC_4(bool value) { }
    void __attribute__((weak)) PC_5(bool value) { }
    void __attribute__((weak)) PC_6(bool value) { }
    void __attribute__((weak)) PC_7(bool value) { }
    void __attribute__((weak)) PC_8(bool value) { }
    void __attribute__((weak)) PC_9(bool value) { }
    void __attribute__((weak)) PC_10(bool value) { }
    void __attribute__((weak)) PC_11(bool value) { }
    void __attribute__((weak)) PC_12(bool value) { }
    void __attribute__((weak)) PC_13(bool value) { }
    void __attribute__((weak)) PC_14(bool value) { }
    void __attribute__((weak)) PC_16(bool value) { }
    void __attribute__((weak)) PC_17(bool value) { }
    void __attribute__((weak)) PC_18(bool value) { }
    void __attribute__((weak)) PC_19(bool value) { }
    void __attribute__((weak)) PC_20(bool value) { }
    void __attribute__((weak)) PC_21(bool value) { }
    void __attribute__((weak)) PC_22(bool value) { }
    void __attribute__((weak)) PC_23(bool value) { }
}

using cb = void(*)(bool value);
using cb_const = cb const;

template <uint8_t N>
static void pcint_x
    ( cb_const (&callbacks)[N]
    , uint8_t const volatile& in
    , uint8_t const volatile& pcmsk
    , uint8_t volatile& prev
    )
{
    uint8_t const newBits = in;
    uint8_t const changed_bits = (prev ^ newBits) & pcmsk;
    prev = newBits;
    for (uint8_t i = 0; i < N; ++i)
    {
        if (changed_bits & (1<<i))
            callbacks[i]((newBits & (1<<i)) != 0);
    }
}

ISR(PCINT0_vect)
{
    constexpr cb p[] = { &PC_0, &PC_1, &PC_2, &PC_3, &PC_4, &PC_5, &PC_6, &PC_7 };
    pcint_x(p, PINB, PCMSK0, GPIOR0);
}

ISR(PCINT1_vect)
{
    constexpr cb p[] = { &PC_8, &PC_9, &PC_10, &PC_11, &PC_12, &PC_13, &PC_14 }; // there is no 15.
    pcint_x(p, PINC, PCMSK1, GPIOR1);
}

ISR(PCINT2_vect)
{
    constexpr cb p[] = { &PC_16, &PC_17, &PC_18, &PC_19, &PC_20, &PC_21, &PC_22, &PC_23 };
    pcint_x(p, PIND, PCMSK2, GPIOR2);
}

static uint8_t enable_count0 = 0;
static uint8_t enable_count1 = 0;
static uint8_t enable_count2 = 0;

extern "C" void pcint_enable(uint8_t arduinoPin)
{
	if (arduinoPin < 8)
	{
		PCMSK2 |= 1 << arduinoPin;
		PCICR  |= 1 << PCIE2;
		GPIOR2 = (GPIOR2 & ~(1<<arduinoPin))
			   | (PIND   &  (1<<arduinoPin));
		++enable_count2;
	}
	else if (8 <= arduinoPin && arduinoPin < 14)
	{
		auto const pin = arduinoPin - 8;
		PCMSK0 |= 1 << pin;
		PCICR  |= 1 << PCIE0;
		GPIOR0 = (GPIOR0 & ~(1<<pin))
			   | (PINB   &  (1<<pin));
		++enable_count0;
	}
	else if (14 <= arduinoPin)
	{
		auto const pin = arduinoPin-14;
		PCMSK1 |= 1 << pin;
		PCICR  |= 1 << PCIE1;
		GPIOR1 = (GPIOR1 & ~(1<<pin))
			   | (PINC   &  (1<<pin));
		++enable_count1;
	}

}

extern "C" void pcint_disable(uint8_t arduinoPin)
{
	if (arduinoPin < 8)
	{
		PCMSK2 &= ~(1 << arduinoPin);
		if (--enable_count2 == 0)
			PCICR &= ~(1 << PCIE2);
	}
	else if (arduinoPin < 16)
	{
		PCMSK0 &= ~(1 << (arduinoPin % 8));
		if (++enable_count0 == 0)
			PCICR &= ~(1 << PCIE0);
	}
	else if (arduinoPin < 24)
	{
		PCMSK1 &= ~(1 << (arduinoPin % 8));
		if (--enable_count1 == 0)
			PCICR &= ~(1 << PCIE1);
	}
}
