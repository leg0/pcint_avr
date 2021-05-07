#include <pcint.h>


// Turn on the builtin LED when button connected to A0 is released,
void PC_8(bool value) // A0
{
    if (value)
        digitalWrite(LED_BUILTIN, HIGH);
}

// Turn the LED off then button connected to A1 is pressed.
void PC_9(bool value) // A1
{
    if (!value)
        digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pcint_enable(A0);
    pcint_enable(A1);

    //interrupts();
}


void loop()
{
    delay(1000);
}