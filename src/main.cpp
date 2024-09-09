#include <Arduino.h>
//Modificato.
volatile const uint8_t
    pinTick = 10,
    pinLED = LED_BUILTIN;

void setup()
{
  pinMode(pinTick, OUTPUT); // connected to OC1B; pulses at 1pps
  pinMode(pinLED, OUTPUT);  // toggled in OC1A interrupt at 1-sec intervals
  // timer 1 setup
  //   WGM15, prescaler /256
  //   connect OC1B to pinTick
  //   enable the OC1A interrupt
  
  // TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  // TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS12);

  // TIMSK1 = _BV(OCIE1A);

  // with a /256 prescaler, timer 1 ticks at 62.5kHz
  // 1-second is thus 62500 ticks or 0xF424
  // OCR1A = 0xF424;
  // defines width of 1pps on pinTick
  //   width == N * 16uS
  //       in this example, should be ~160uS
  // OCR1B = 0x0064;
  TCCR1A = 0b00000000;
  TCCR1B = 0b00000101;
  TIMSK1 = 0b00000001;
  OCR1A = 0xF424;
  TCNT1 = 0b00000000;
} // setup

void loop()
{
  // run normal program here
  //...

} // loop

ISR(TIMER1_COMPA_vect)
{
  static bool flag = false;
  // on each interrupt, toggle the state of the on-board LED
  flag ^= true;
  digitalWrite(pinLED, flag);
  // can do other stuff in here, within limits
} // ISR

void PrimaModifica(){
  
}