#include "mbed.h"
#include "pinout.h"
#include "to_7seg.h"

static DigitalOut led_der(LDR_PIN);

Ticker tick_2Hz;
Timeout to_CT;

bool b_tick_2Hz;
bool b_to_CT;

void tick_2Hz_isr(void) { b_tick_2Hz = true; }
void to_CT_isr(void) { b_to_CT = true; }

int main(void)
{
  uint8_t cnt_led = 0;
  led_der = 0;
  b_tick_2Hz = false;
  b_to_CT = false;
  tick_2Hz.attach_us(tick_2Hz_isr, 500000); //500ms
  for (;;) {
    if (b_tick_2Hz) {
      b_tick_2Hz = false;
      cnt_led++;
      led_der = 1;
      to_CT.attach_us(to_CT_isr, 400000); //400ms
    }
    if (b_to_CT) {
      b_to_CT = false;
      led_der = 0;
    }
    __disable_irq();
    if (!b_tick_2Hz && !b_to_CT) {
      __WFI();
    }
    __enable_irq();
  } // for (;;)
} // main()
