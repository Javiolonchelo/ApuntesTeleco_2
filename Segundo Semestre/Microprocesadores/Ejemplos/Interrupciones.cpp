#include <stdint.h>

uint32_t volatile *const p_periph_status = (uint32_t *)0x4008E000U;
uint32_t volatile *const p_periph_tx_data = (uint32_t *)0x4008E004U;
uint32_t volatile *const p_periph_rx_data = (uint32_t *)0x4008E008U;
uint8_t my_data;

// El modificador 'volatile' indica que se puede modificar el valor de las variables por dispositivos externos al procesador.

// MÁSCARAS (datos que se esperan recibir)
#define PERIPH_RX_AVAIL (0X0000001U)
#define PERIPH_TX_RDY (0X0000008U)

bool volatile b_tx_rdy;
bool volatile b_rx_data;

int main(void)
{
    for (;;)
    {
        if (b_tx_rdy)
        {
            b_tx_rdy = false;
            *p_periph_tx_data = my_data;
        }

        if (b_rx_data)
        {
            b_rx_data = false;
            my_data = *p_periph_tx_data;
        }
    }
}

// FUNCIONES
void periph_tx(void)
{
    b_tx_rdy = true;
}

void periph_tx(void)
{
    b_rx_data = true;
}