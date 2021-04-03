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
  
  g_dsl = 1; // Inicialización de los transistores. Como trabajamos con
  g_dsr = 0; // multiplexación, siempre serán valores opuestos.
  
  c = 0;
  g_seven_seg = to_7seg(c); // Inicialización del display.
  
  int8_t con = 0;
  int8_t cnt_sw = 0; // Situado aquí por restricciones en el enunciado.
                     // Si fuera global, debería situarse anterior a la
                     // línea 19.

  // [1] fin del primer bloque de código -------------------------------

  for (;;) {

    // [2] segundo bloque de código que puede rellenar +++++++++++++++++

    if(gb_tick_100ms_evnt) // Cuenta 100 ms un total de 12 veces
    {
      gb_tick_100ms_evnt = false;
      con++;
    }
    
    if(12 == con) // Se cumple cada 1.2 segundos
    {
      c = ((c > 98) ? 0 : ++c);
      con = 0;  // Se resetea nuestro temporizador.
    }
    
    if(gb_swr_evnt)
    {
      gb_swr_evnt = false;
      cnt_sw++;
      
      g_leds = ((cnt_sw % 2) ? 2 : 0); // Se conmuta el led central.
    }
    
    if(gb_tick_1ms_evnt) // Multiplexación
    {
      gb_tick_1ms_evnt = false;
      
      g_seven_seg = 0; // Se apaga el display para evitar sombras.
      
      g_dsl = !g_dsl; // Se conmuta el estado de cada transistor.
      g_dsr = !g_dsr;
      
      g_seven_seg = (g_dsl) ? to_7seg(c / 10) : to_7seg(c % 10);
      // Al dividir la cuenta 'c' entre 10, el cociente indica el valor
      // de las decenas, mientras que el resto indica el valor de las
      // unidades.
    }
    
    if(gb_tick_10s_evnt) // Suma cada 10 segundos
    {
      gb_tick_10s_evnt = false;
      
      printf("%d -- %d\n", cnt_sw, c);
      
      c = (((c + cnt_sw) > 99) ? (c % cnt_sw) : (c + cnt_sw));
    }
    
    __WFI();

    // [2] fin del segundo bloque de código ----------------------------

  } // for (;;)
} // main()
