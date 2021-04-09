#include "mbed.h"
#include "pinout.h"
#include "sw_tick_serial.h"
#include "to_7seg.h"

// seven segment display anodes
// when in a int8_t, they are 0b-GFEDCBA
BusOut      g_seven_seg(SGA_PIN, SGB_PIN, SGC_PIN, SGD_PIN,
                        SGE_PIN, SGF_PIN, SGG_PIN);

// display cathodes
DigitalOut  g_dsr(DSR_PIN);
DigitalOut  g_dsl(DSL_PIN);

// leds
// when in a int8_t, they are LMR
BusOut      g_leds(LDR_PIN, LDM_PIN, LDL_PIN);

int main (void) {
  int8_t      c;            // esta es la variable de cuenta

  // [1] primer bloque de c�digo que puede rellenar ++++++++++++++++++++
  c = 99;
  g_seven_seg = to_7seg(c);
  sw_tick_serial_init();
  int8_t cnt_switch;
  g_dsr = 1;
  g_dsl = 0;
  // [1] fin del primer bloque de c�digo -------------------------------

  for (;;) {

    // [2] segundo bloque de c�digo que puede rellenar +++++++++++++++++
    if(gb_swl_evnt){
      gb_swl_evnt = false;
      cnt_switch++;
      c = (c==0) ? 99 : --c;
      g_seven_seg = to_7seg(c);
    }
    
    if(gb_tick_1s_evnt){
      gb_tick_1s_evnt = false;
      if(0 == g_leds){
        g_leds = 1;
      }
      else{
        g_leds = 0;
      }
    }
    if(gb_tick_1ms_evnt){
      gb_tick_1ms_evnt = false;
      g_seven_seg = 0;
      g_dsr = !g_dsr;
      g_dsl = !g_dsl;
      g_seven_seg = (g_dsl ? to_7seg(c / 10) : to_7seg(c % 10));
    }
    // [2] fin del segundo bloque de c�digo ----------------------------

  } // for (;;)
} // main()
