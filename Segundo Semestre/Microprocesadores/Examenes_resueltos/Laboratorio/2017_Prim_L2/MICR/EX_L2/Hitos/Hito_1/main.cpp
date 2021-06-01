#include "mbed.h"
#include "pinout.h"
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

// Sensor de ultrasonidos
DigitalOut trig(TRG_PIN);
InterruptIn echo(ECH_PIN);
static bool volatile echo_rise_event;
static bool volatile echo_fall_event;

// Temporizadores
static Ticker tick_measure;
static Ticker tick_mux;
static Timer timer_echo;
static Timeout timeout_trig;

static bool volatile tick_measure_event;
static bool volatile tick_mux_event;
static bool volatile timer_echo_event;
static bool volatile timeout_trig_event;

// ISR
void tick_measure_isr (void) { tick_measure_event = true; }
void tick_mux_isr (void) { tick_mux_event = true; }
void timer_echo_isr (void) { timer_echo_event = true; }
void timeout_trig_isr (void) { timeout_trig_event = true; }

void echo_rise_isr (void) { echo_rise_event = true; }
void echo_fall_isr (void) { echo_fall_event = true; }


int main (void) {

  // [1] primer bloque de código que puede rellenar ++++++++++++++++++++

  // echo.mode(PullIp);
  echo.rise(echo_rise_isr);
  echo.fall(echo_fall_isr);
  
  uint16_t cnt_near = 0;
  uint32_t distancia;
  tick_measure.attach_us(tick_measure_isr, 2000000);
  tick_mux.attach_us(tick_mux_isr, 4000);
  g_dsl = 0;
  g_dsr = 1;

  // [1] fin del primer bloque de código -------------------------------

  for (;;) {

    // [2] segundo bloque de código que puede rellenar +++++++++++++++++
    
    if(tick_mux_event)
    {
      tick_mux_event = false;
      
      g_dsl = !g_dsl;
      g_dsr = !g_dsr;
      
      g_seven_seg = 0; // Evitamos sombras
      
      if(g_dsl)
      {
        g_seven_seg = (distancia > 9 ? to_7seg(12) : to_7seg(distancia));
      }
      else
      {
        g_seven_seg = to_7seg(11);
      }
    }
    
    if(tick_measure_event)
    {
      tick_measure_event = false;
      trig = 1;
      timeout_trig.attach_us(timeout_trig_isr, 10);
    }
    
    if(timeout_trig_event)
    {
      timeout_trig_event = false;
      trig = 0;
    }
    
    if(echo_rise_event)
    {
      echo_rise_event = false;
      timer_echo.reset();
      timer_echo.start();
    }
    
    if(echo_fall_event)
    {
      echo_fall_event = false;
      timer_echo.stop();
      distancia = timer_echo.read_us() / (58 * 2.54);
      if(distancia < 4) { cnt_near++; }
    }
    
    __disable_irq();
    if(!tick_mux_event && !tick_measure_event && !timeout_trig_event && !echo_rise_event && !echo_fall_event)
    {
      __WFI();
    }
    __enable_irq();

    // [2] fin del segundo bloque de código ----------------------------

  } // for (;;)
} // main()
