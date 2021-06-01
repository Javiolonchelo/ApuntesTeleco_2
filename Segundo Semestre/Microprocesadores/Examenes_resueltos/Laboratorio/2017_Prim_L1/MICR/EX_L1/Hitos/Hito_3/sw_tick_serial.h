// DTE-ETSIST-UPM

// Microprocesadores 19/20

// auxiliary functions and objects

#ifndef SW_TICK_SERIAL_H
# define SW_TICK_SERIAL_H
# include "mbed.h"

// These flags turn true after a keypress upon the
// corresponding switch. Must be turned false by user
// All switches must be active low. External pull-ups are not needed
extern bool volatile  gb_swl_evnt;
extern bool volatile  gb_swm_evnt;
extern bool volatile  gb_swr_evnt;

// These flags turn true periodically with the indicated period
// Must be turned false by user
extern bool volatile  gb_tick_1ms_evnt;
extern bool volatile  gb_tick_10ms_evnt;
extern bool volatile  gb_tick_100ms_evnt;
extern bool volatile  gb_tick_1s_evnt;
extern bool volatile  gb_tick_10s_evnt;

// To use printf as g_pc.printf(). 115200-8N1
extern Serial         g_pc;

// to be called from main() a single time in order to initialize
// all previous machinery
void sw_tick_serial_init(void);

#endif // SW_TICK_SERIAL_H
