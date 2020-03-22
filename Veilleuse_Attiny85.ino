#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define INTERRUPT_PIN0 PCINT4
#define LED_0 PB2
#define LED_1 PB3
#define BUTTON PB4
#define debounce 20
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)

//----------------------- graphique et page
volatile byte page = 1;
volatile byte sleeping = 0;
const unsigned long Alarm = 30000; // alarm time - 15 minutes
unsigned long StartTime = 0;        // start time

//================================================
void setup()
//================================================
{

  DDRB |= (1 << LED_0) | (1 << LED_1);// configured in output
  PORTB |= (1 << LED_0) | (1 << LED_1);

  DDRB &= ~(1 << BUTTON);//configured in input
  PORTB |= (1 << BUTTON);// pullup

  ADCSRB &= ~(1 << ACME); // select AIN1 as neative ref
  DIDR0 |= (1 << AIN1D) | (1 << AIN0D);

  adc_disable();// for low power reduction
  initInterupt();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

}

//================================================
void initInterupt()
//================================================
{
  cli();
  GIMSK |= (1 << PCIE);
  PCMSK |= (1 << INTERRUPT_PIN0);
  sei();
}

//================================================
void enterSleep()
//================================================
{
  sleeping = 1;
  sleep_enable();
  sleep_cpu();
}

//================================================
ISR(PCINT0_vect)
//================================================
{
  byte buttonNow = PINB & (1 << BUTTON);// 1 si relache et 0 si appuie

  cli();
  _delay_ms(debounce);// for debounce

  if (sleeping == 0) {// not cause by wake up
    if (!(PINB & (1 << BUTTON))) { // 1 si relache et 0 si appuie
      page = (page == 0) ? 1 : 0;
    }
  }
  sei();
  (!buttonNow) ? PORTB |= (1 << LED_0) : PORTB &= ~ (1 << LED_0);
}


//================================================
void loop()
//================================================
{

  //  if ((millis() - StartTime) > Alarm) {
  //enterSleep();
  sleeping = 0;
  StartTime = millis();
  if ((ACSR & (1 << ACO)) == 0) {
    PORTB |= (1 << LED_1);
  }
  else {
    PORTB &= ~ (1 << LED_1);
  }
  //}
}



