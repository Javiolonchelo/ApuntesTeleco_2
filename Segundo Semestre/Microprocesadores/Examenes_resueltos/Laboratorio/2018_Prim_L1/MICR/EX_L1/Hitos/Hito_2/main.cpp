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
  int16_t     cnt_led = 0;  // y esta el contador del LED
  
  // [1] primer bloque de código que puede rellenar ++++++++++++++++++++
  
  sw_tick_serial_init();
  g_dsr = 1;
  g_dsl = 0;
  c = 98;
  //g_seven_seg = to_7seg(c);   
  //creo que esta línea apagaría el display pero cada 1 ms se ejecuta
  //la multiplexación de displays así que es inútil
  uint8_t cnt_switch = 0;
  
  // [1] fin del primer bloque de código -------------------------------

  for (;;) {

    // [2] segundo bloque de código que puede rellenar +++++++++++++++++
    if (gb_tick_1ms_evnt)
    {
      gb_tick_1ms_evnt = false;
      g_dsl = !g_dsl;
      g_dsr = !g_dsr;
      g_seven_seg = 16; 
      //apagamos display para evitar sombras
      //display se apaga con número mayor que 6
      g_seven_seg = ((g_dsl) ? (to_7seg(c / 10)) : (to_7seg(c % 10)));
    }
    
    if (gb_swl_evnt)
    {
      gb_swl_evnt = false;
      cnt_switch++;
      c = ((c == 0) ? 98 : (c-2));
      g_seven_seg = to_7seg(c);
    }
    
    if (gb_tick_1s_evnt)
    {
      gb_tick_1s_evnt = false;
      g_leds = ((g_leds == 4) ? 0 : 4);
    }
    
    // [2] fin del segundo bloque de código ----------------------------

  } // for (;;)
} // main()
