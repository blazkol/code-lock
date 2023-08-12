# Code-Lock
Simple bare-metal project

# Overview
My “Code lock” project was made using an Arduino Uno with an ATmega328 microprocessor fully bare-metal and it works in the following way:
We can enter a four-digit cipher with the use of a numerical keypad. After each digit has been entered, yellow LEDs will light up one after the other. After entering all four digits, the green diode will light up if the given cipher is correct or the red diode if it is incorrect. After that we can start the sequence all over again by pressing one of the keys. The correct cipher is software predefined.

# Detailed code description
The readKeypad() function is responsible for handling the numerical keypad. It first sets high state on all pins connected to the keyboard rows except one. Then a character is returned depending on which of the pins connected to the keyboard columns the low state was detected on.

The enterCipher() function checks the keyboard state - if no key is pressed, it resets the timer and sets the “pressed” variable to false. If the key is pressed for some time and the state of “pressed” is false, the character is entered in the appropriate place in the cipher, the variable “pressed” is set to true and the variable “i”, which points to the appropriate place in the cipher, is incremented.

The enlightenLEDs() function lights up the yellow LEDs, depending on the value of the variable “i” and green/yellow LED depending on whether the given cipher was correct.

Timer2 interrupt is triggered every 10 milliseconds. The “timer” variable (used for debouncing in the enterCipher() function) is then incremented.

# Hardware
- Arduino UNO
- 4x3 Keypad
- 1x green LED
- 1x red LED
- 4x yellow LED
- 6x 330 ohm resistor
