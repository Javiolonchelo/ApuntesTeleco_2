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

  sw_tick_serial_init(); // SIEMPRE AL USAR LA LIBRERÍA 'sw_tick_serial'
  
  c = 4;
  g_seven_seg = to_7seg(c); // Con esto mostraremos un 4 cuando comience
  
  g_dsl = 1; // Se escoge el display de la izquierda y se apaga el otro
  g_dsr = 0;

  // [1] fin del primer bloque de código -------------------------------

  for (;;) { 

    // [2] segundo bloque de código que puede rellenar +++++++++++++++++

    if(gb_swm_evnt)
    {
      gb_swm_evnt = false;
      c = ((c < 1) ? 8 : (c - 2));
      g_seven_seg = to_7seg(c);
    }
    
    if(gb_tick_1s_evnt)
    {
      gb_tick_1s_evnt = false;
      
      if(0 == g_leds)
      {
        g_leds = 2;
        cnt_led++;
      }
      
      else
      {
        g_leds = 0;
      }
    }
    
    __WFI(); // No te olvides de activar la espera a interrupciones

    // [2] fin del segundo bloque de código ----------------------------

  } // for (;;)
} // main()
