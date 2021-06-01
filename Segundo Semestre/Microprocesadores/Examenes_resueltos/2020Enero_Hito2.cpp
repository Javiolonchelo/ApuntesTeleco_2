#include "mbed.h"
#include "pinout.h"
#include "to_7seg.h"

static DigitalOut led_der(LDR_PIN);
static BusOut segs(SGA_PIN, SGB_PIN, SGC_PIN, SGD_PIN, SGE_PIN, SGF_PIN, SGG_PIN);
static DigitalOut dsl(DSL_PIN);
static DigitalOut dsr(DSR_PIN);

Ticker tick_display;
Ticker tick_2Hz;
Timeout to_CT;
Timeout to_bounds;

bool b_tick_display;
bool b_tick_2Hz;
bool b_to_CT;

void tick_2Hz_isr(void) { b_tick_2Hz = true; }
void to_CT_isr(void) { b_to_CT = true; }
void tick_display_isr(void) { b_tick_display = true; }

int main(void)
{
  bool mux = false;
  uint8_t cnt_led = 0;
  led_der = 0;
  b_tick_2Hz = false;
  b_to_CT = false;
  tick_2Hz.attach_us(tick_2Hz_isr, 500000); //500ms
  tick_display.attach_us(tick_display_isr, 4000); //4ms
  for (;;) {
    if (b_tick_2Hz) {
      b_tick_2Hz = false;
      cnt_led = (cnt_led == 99) ? 0 : ++cnt_led;
      led_der = 1;
      to_CT.attach_us(to_CT_isr, 400000); //400ms
    }
    if (b_to_CT) {
      b_to_CT = false;
      led_der = 0;
    }
    if (b_tick_display) {
      b_tick_display = false;
      mux = !mux;
      if (mux) {
        dsl = 0;
        segs = to_7seg(cnt_led % 10);
        dsr = 1;
      }
      else {
        dsl = 1;
        segs = to_7seg(cnt_led / 10);
        dsr = 0;
      }
    }
    __disable_irq();
    if (!b_tick_2Hz && !b_to_CT && !b_tick_display) {
      __WFI();
    }
    __enable_irq();
  } // for (;;)
} // main()
