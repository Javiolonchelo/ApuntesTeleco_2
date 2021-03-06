#include "mbed.h"
#include "pinout.h"
#include "sw_tick_serial.h"
#include "to_7seg.h"

// seven segment display anodes
// when in a int8_t, they are 0b-GFEDCBA
BusOut g_seven_seg(SGA_PIN, SGB_PIN, SGC_PIN, SGD_PIN,
                   SGE_PIN, SGF_PIN, SGG_PIN);

// display cathodes
DigitalOut g_dsr(DSR_PIN);
DigitalOut g_dsl(DSL_PIN);

// leds
// when in a int8_t, they are LMR
BusOut g_leds(LDR_PIN, LDM_PIN, LDL_PIN);

int main(void)
{
  int8_t c;            // esta es la variable de cuenta
  int16_t cnt_led = 0; // y esta el contador del LED

  // [1] primer bloque de c�digo que puede rellenar ++++++++++++++++++++

  sw_tick_serial_init(); // SIEMPRE AL USAR LA LIBRER�A 'sw_tick_serial'

  c = 96;
  g_seven_seg = to_7seg(c); // Con esto mostraremos un 4 cuando comience

  g_dsl = 1; // Se escoge el display de la izquierda y se apaga el otro
  g_dsr = 0;

  // [1] fin del primer bloque de c�digo -------------------------------

  for (;;)
  {

    // [2] segundo bloque de c�digo que puede rellenar +++++++++++++++++

    if (gb_swm_evnt)
    {
      gb_swm_evnt = false;

      c = ((c < 1) ? 98 : (c - 2));
    }

    if (gb_tick_1s_evnt)
    {
      gb_tick_1s_evnt = false;

      if (0 == g_leds)
      {
        g_leds = 2;
        cnt_led++;
      }

      else
      {
        g_leds = 0;
      }
    }

    if (gb_tick_1ms_evnt) // Multiplexaci�n
    {
      gb_tick_1ms_evnt = false;

      g_seven_seg = 0; // Para evitar sombras

      g_dsl = !g_dsl; // Se conmuta el estado de los transistores
      g_dsr = !g_dsr;

      g_seven_seg = (g_dsl ? to_7seg(c / 10) : to_7seg(c % 10));
    }

    if (gb_tick_10s_evnt)
    {
      gb_tick_10s_evnt = false;

      c = ((c > 95) ? ((c + 4) % 100) : (c + 4));
      printf("10 s MAS (%d)\n", c);
    }

    // [2] fin del segundo bloque de c�digo ----------------------------

  } // for (;;)
} // main()
