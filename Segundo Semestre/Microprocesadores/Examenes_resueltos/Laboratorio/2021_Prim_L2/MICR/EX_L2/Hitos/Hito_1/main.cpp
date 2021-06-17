#include "mbed.h"
#include "pinout.h"
#include "to_7seg.h"

// seven segment display anodes
// when in a int8_t, they are 0b-GFEDCBA
static BusOut         g_seven_seg(SGA_PIN, SGB_PIN, SGC_PIN, SGD_PIN,
  SGE_PIN, SGF_PIN, SGG_PIN);

// display cathodes
static DigitalOut     g_dsl(DSL_PIN);
static PwmOut         g_dsr(DSR_PIN);

// LDR
static AnalogIn       g_lit(LIT_PIN);

// LED
static DigitalOut     g_ldr(LDR_PIN);

// hc-sr04 stuff
static DigitalOut     g_trg(TRG_PIN);
static InterruptIn    g_ech(ECH_PIN);
//hasta aqui te lo dan todo
//TO-DO

static Ticker tick_mux;                                             //para la multiplexación utilizamos un ticker para que cada cierta frecuencia haga la multiplexacion
static Ticker tick_trg;                                             //ticker creado para el trigger, para tomar la medida cada cierto tiempo
static Timeout to_trg;                                              //timeout para desactivar trigger en el caso de que termine este tiempo
static Timer timer_echo;                                            //timer para tomar la medida final segun el tiempo medido

bool b_tick_mux;                                                    //bool para multiplexacion

bool b_timer_echo_rise;                                             //bool para flanco de subida de echo
bool b_timer_echo_fall;                                             //bool para flanco de bajada de echo
bool b_to_trg;                                                      //bool para el timeout de trigger
bool b_tick_trg;                                                    //bool para el ticker de trigger

static void tick_mux_isr(void) { b_tick_mux = true; }                  //isr para la multiplexacion

static void timer_echo_fall_isr(void) { b_timer_echo_fall = true; }    //isr para flanco de bajada de echo
static void timer_echo_rise_isr(void) { b_timer_echo_rise = true; }    //isr para flanco de subida de echo
static void tick_trg_isr(void) { b_tick_trg = true; }                  //isr para ticker de trigger
static void to_trg_isr(void) { b_to_trg = true; }                      //isr para timeout de trigger

int main(void)
{
  //TO-DO
  bool estado = false;                                              //variable booleana usada para la multiplexacion
  int distancia;                                                    //almacena el valor medido por el ultrasonidos en decimetros(quizá se pueda resolver sin necesitarla)
  int16_t cnt_near = 0;                                             //variable para contar si la distancia es menor de 4dm, de tipo NO GLOBAL
  g_trg = 1;                                                        //señal de trigger empieza en 1 para activar el ultrasonidos
  g_ldr = 0;                                                        //leds apagados todo el tiempo
  g_dsl = 0;                                                        //display izquierdo empieza apagado antes de multiplexacion
  g_dsr.period_us(100);                                             //ponemos periodo a 100 para ajustar pulsewidth después
  g_dsr.pulsewidth_us(100);                                         //pulsewidth en 100 para que esté encendido
  g_seven_seg = to_7seg(11);                                        //muestra - si está encendido el display derecho
  g_ech.rise(timer_echo_rise_isr);                                  //activa isr si detecta flanco de subida de echo
  g_ech.fall(timer_echo_fall_isr);                                  //activa isr si detecta flanco de bajada de echo
  tick_mux.attach_us(tick_mux_isr, 1000);                           //1kHz = 1ms
  tick_trg.attach_us(tick_trg_isr, 2000000);                        //cada 2s activa isr que pone trigger a 1

  for (;;)
  {
    // TO-DO
    if (b_tick_trg)
    {                                                 //entra cada 2s 
      b_tick_trg = false;                                           //eliminamos el flag
      g_trg = 1;                                                    //activamos trigger a 1
      to_trg.attach_us(to_trg_isr, 10000);                          //10us, lo pone en datasheet
    }
    if (b_to_trg)
    {                                                   //entra si pasa el to_trg_isr
      b_to_trg = false;                                             //eliminamos el flag
      g_trg = 0;                                                    //ponemos trigger a 0
    }
    if (b_timer_echo_rise)
    {                                          //si se produce flanco de subida de echo
      b_timer_echo_rise = false;                                    //eliminamos el flag
      timer_echo.reset();                                           //reseteamos el timer
      timer_echo.start();                                           //iniciamos el timer
    }
    if (b_timer_echo_fall)
    {                                          //si se produce flanco de bajada, ha terminado de medir
      b_timer_echo_fall = false;                                    //eliminamos el flag
      g_trg = 0;                                                    //ponemos trigger a 0, se activa a 1 a los 2s
      timer_echo.stop();                                            //detenemos el timer
      distancia = timer_echo.read_us() / 580;                         //obtenemos la distancia medida, y dividimos entre 58 para cm, entre 580 para dm
      if (distancia < 4)                                             //si distancia menor de 4dm
        cnt_near++;                                                 //sumamos 1 a la variable que nos dicen
      if (distancia > 9)
      {                                            //si distancia mayor de 9dm
        distancia = 10;                                             //distancia igual a 10 para que represente A
        g_seven_seg = ((g_dsl) ? to_7seg(distancia) : to_7seg(11)); //representa A si esta encendido display izquierdo, - si esta encendido el display derecho
      }
      else
        g_seven_seg = ((g_dsl) ? to_7seg(distancia) : to_7seg(11)); //representa la distancia si esta encendido el display izquierdo, - si esta encendido el display derecho
    }
    if (b_tick_mux)
    {                                                 //multiplexacion, entra cada 1ms
      b_tick_mux = false;                                           //eliminamos el flag
      estado = !estado;                                             //variable para la multiplexacion
      if (estado)
      {
        g_dsl = 1;
        g_seven_seg = to_7seg(distancia);
        g_dsr.pulsewidth_us(0);
      }
      else
      {
        g_dsl = 0;
        g_seven_seg = to_7seg(11);
        g_dsr.pulsewidth_us(100);
      }
    }
    __disable_irq();
    if (!b_tick_mux && !b_tick_trg && !b_timer_echo_fall && !b_timer_echo_rise && !b_to_trg)
    {
      __WFI();                                                      //dormimos el microprocesador cuando no haga nada
    }
    __enable_irq();
  }
}
