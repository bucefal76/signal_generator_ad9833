#ifndef X9C103S_HPP
#define X9C103S_HPP

#include "X9C103S.h"

/*
    This class exist only to fix the problem with wrong initialization of the X9C103S chip.
    What is missing in the original X9C103S code is to synchronize chips state with the firmware at start.
*/

class X9C103S_ : public X9C103S
{
public:
    X9C103S_(int inc_pin, int ud_pin, int cs_pin)
        : X9C103S(inc_pin, ud_pin, cs_pin), _inc_pin(inc_pin), _ud_pin(ud_pin), _cs_pin(cs_pin)
    {
    }

    void initializePot()
    {
        pinMode(_inc_pin, OUTPUT);
        pinMode(_ud_pin, OUTPUT);
        pinMode(_cs_pin, OUTPUT);

        digitalWrite(_cs_pin, HIGH); // Ensure initial state is HIGH
        digitalWrite(_ud_pin, LOW);  // Set direction to decrement
        digitalWrite(_cs_pin, LOW);  // Enable the potentiometer

        // Now dial down the potentiometer, it may not be down
        // when we start firmware without power cycle the device.

        for (uint8_t i = 0; i < 101; i++)
        {
            digitalWrite(_inc_pin, LOW);
            delay(1);
            digitalWrite(_inc_pin, HIGH);
            delay(1);
        }

        digitalWrite(_cs_pin, HIGH); // Disable the potentiometer

        /// Now initialize the base class, a library.
        X9C103S::initializePot();
    }

private:
    int _inc_pin;
    int _ud_pin;
    int _cs_pin;
};

#endif
