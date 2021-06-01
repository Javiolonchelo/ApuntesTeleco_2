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

static uint8_t cnt_on = 0;

int main (void) {
  // int8_t      c;            // esta es la variable de cuenta
  int16_t     cnt_led = 0;  // y esta el contador del LED

  // [1] primer bloque de código que puede rellenar ++++++++++++++++++++
  
  bool estado_disp = false; // Encendido es 'true', apagado es 'false'
  
  g_dsr = 0;
  g_dsl = 1;
  
  sw_tick_serial_init();
  
  // [1] fin del primer bloque de código -------------------------------

  for (;;) {

    // [2] segundo bloque de código que puede rellenar +++++++++++++++++
    
    if(gb_swl_evnt)
    {
      gb_swl_evnt = false;
      estado_disp = !estado_disp; // Conmuta de 'On' a 'OF' y viceverssa
      
      if(estado_disp && (cnt_on < 99))
      {
        cnt_on++;
      }
    }
    
    if(estado_disp)
    {
      if(gb_tick_100ms_evnt)
      {
        gb_tick_100ms_evnt = false;
        if(90 == cnt_on)
        {
          cnt_led = ((4 == cnt_led) ? 5 : 4);
        }
        
        else
        {
          cnt_led = ((0 == cnt_led) ? 1 : 0);
        }
      }
    }
    
    else
    {
      cnt_led = 0;
    }
    
    g_leds = cnt_led;
    
    if(gb_tick_1ms_evnt) // Multiplexación de 1 kHz
    {
      gb_tick_1ms_evnt = false;
      
      g_seven_seg = 0; // Evita las sombras
      
      g_dsl = !g_dsl;
      g_dsr = !g_dsr;
      
      if(g_dsl) // Asignación del display izquierdo
      {
        g_seven_seg = ((estado_disp) ? to_7seg(cnt_on / 10) : to_7seg(0));
      }
      
      else // Asignación del display derecho
      {
        g_seven_seg = ((estado_disp) ? to_7seg(cnt_on % 10) : to_7seg(15));
      }
    }
    
    if(gb_swm_evnt)
    {
      gb_swm_evnt = false;
      if(cnt_on < 99) { cnt_on++; }
    }
    
    if(gb_swr_evnt)
    {
      gb_swr_evnt = false;
      if(cnt_on > 0) { cnt_on--; }
    }
    
    // [2] fin del segundo bloque de código ----------------------------

  } // for (;;)
} // main()
