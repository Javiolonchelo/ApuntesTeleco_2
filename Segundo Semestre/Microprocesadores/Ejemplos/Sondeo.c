#include <stdint.h>

uint32_t volatile *const p_periph_status = (uint32_t *)0x4008E000U;
uint32_t volatile *const p_periph_tx_data = (uint8_t *)0x4008E004U;
uint32_t volatile *const p_periph_rx_data = (uint8_t *)0x4008E008U;

// El modificador 'volatile' indica que se puede modificar el valor de las variables por dispositivos externos al procesador.

// MÁSCARAS (datos que se esperan recibir)
#define PERIPH_RX_AVAIL (0X0000001U)
#define PERIPH_TX_RDY (0X0000008U)

bool = b_tx_rdy;
bool = b_rx_data;

int main(void)
{
    uint8_t my_data;
    for (;;)
    {
        while (!(*p_periph_status & PERIPH_RX_AVAIL))
        {
        }
        my_data = *p_periph_rx_data;

        while (!(*p_periph_status & PERIPH_TX_RDY))
        {
        }
        *p_periph_rx_data = my_data;
    }
}

// FUNCIONES
void periph_tx