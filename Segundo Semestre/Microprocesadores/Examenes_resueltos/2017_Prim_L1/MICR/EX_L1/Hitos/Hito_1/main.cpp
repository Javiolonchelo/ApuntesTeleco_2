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
  // int8_t      c;            // esta es la variable de cuenta
  // int16_t     cnt_led = 0;  // y esta el contador del LED

  // [1] primer bloque de código que puede rellenar ++++++++++++++++++++
  
  bool estado = false; // Apagado es 'false', encendido es 'true'

  uint64_t cnt_on = 0;
  // No podemos acceder a esta variable con el debugger. Creo que esto se debe a
  // que antes se definía el tipo da las variables de la siguiente forma:
  // unsigned long int cnt_on = 0;
  
  g_dsl = 0;
  g_dsr = 1;
  
  g_leds = 0;
  
  sw_tick_serial_init();
  
  // [1] fin del primer bloque de código -------------------------------

  for (;;) {

    // [2] segundo bloque de código que puede rellenar +++++++++++++++++
    
    if(gb_swr_evnt) // Conmutar de 'On' a 'OF'
    {
      gb_swr_evnt = false;
      
      estado = !estado;
      
      if(estado)
      {
        cnt_on++;
        g_leds = 1;
      }
      else
      {
        g_leds = 0;
      }
    }
    
    if(gb_tick_1ms_evnt) // Multiplexación
    {
      gb_tick_1ms_evnt = false;
      
      g_seven_seg = 0; // Evita las sombras
      
      g_dsl = !g_dsl; // Conmuta los transistores
      g_dsr = !g_dsr;
      
      if(estado)
      {
        g_seven_seg = ((g_dsl) ? to_7seg(0) : to_7seg(13));
      }
      
      else
      {
         g_seven_seg = ((g_dsl) ? to_7seg(0) : to_7seg(15));
      }
    }
    
    // [2] fin del segundo bloque de código ----------------------------

  } // for (;;)
} // main()
