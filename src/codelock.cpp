#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

char cipher[] = {'3', '5', '9', '3'};     //predefined cipher
char input_num[] = {'-', '-', '-', '-'};  //entered cipher
long int timer = 0;                       //variable incremented after each Timer2 interrupt
bool pressed;                             //variable that changes state after pressing / unpressing a key
int i = 0;

void setup() {                            
  DDRB = 0b00001111;      //PORTB 0-3 connected to rows of keypad and declared as output
  PORTB = 0b00000000;     
  DDRD = 0b00000000;      //PORTD 4-7 connected to columns of keypad and declared as input with pull-ups
  PORTD = 0b00000000;
  DDRC = 0b00111111;      //PORTC 0-5 connected to LEDs and declared as output
  PORTC = 0b00000000;

  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 0x9C;
  TCCR2A = 1 << WGM21;
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  sei();

}

char readKeypad() {
  PORTB = 0b00000111;
  if ((PIND & 0b00010000) == 0) { return 'A'; }
  else if ((PIND & 0b10000000) == 0) { return '1'; }
  else if ((PIND & 0b01000000) == 0) { return '2'; }
  else if ((PIND & 0b00100000) == 0) { return '3'; }

  PORTB = 0b00001011;
  if ((PIND & 0b00010000) == 0) { return 'B'; }
  else if ((PIND & 0b10000000) == 0) { return '4'; }
  else if ((PIND & 0b01000000) == 0) { return '5'; }
  else if ((PIND & 0b00100000) == 0) { return '6'; }

  PORTB = 0b00001101;
  if ((PIND & 0b00010000) == 0) { return 'C'; }
  else if ((PIND & 0b10000000) == 0) { return '7'; }
  else if ((PIND & 0b01000000) == 0) { return '8'; }
  else if ((PIND & 0b00100000) == 0) { return '9'; }

  PORTB = 0b00001110;
  if ((PIND & 0b00010000) == 0) { return 'D'; }
  else if ((PIND & 0b10000000) == 0) { return '*'; }
  else if ((PIND & 0b01000000) == 0) { return '0'; }
  else if ((PIND & 0b00100000) == 0) { return '#'; }

  return '-';
}

void enterCipher() {
  if(readKeypad() == '-'){
    timer = 0;
    pressed = false;
  }
  if (timer > 10 && pressed == false){
    input_num[i] = readKeypad();
    pressed = true;
    i++;
  }
}

void enlightenLEDs() {
  if(i == 1){
    PORTC = 0b00000100;
  }
  else if (i == 2){
    PORTC = 0b00001100;
  }
  else if (i == 3){
    PORTC = 0b00011100;
  }
  else if (i == 4){
    if(cipher[0] == input_num[0] &&
       cipher[1] == input_num[1] &&
       cipher[2] == input_num[2] &&
       cipher[3] == input_num[3]){
         PORTC = 0b00111101;
       }
    else{
      PORTC = 0b00111110;
    }
    i = 0;
  }
}

ISR(TIMER2_COMPA_vect){
  timer++;
}

void loop() {
  enterCipher();
  enlightenLEDs();
}