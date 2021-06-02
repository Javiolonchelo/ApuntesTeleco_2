# Resumen para el primer examen de laboratorio

## Introducción

Mientras resolvíamos exámenes, hemos notado ciertos patrones a la hora de resolverlos.

He aquí un listado de dichos patrones y algún que otro truco para que puedas repasarlos antes de ir al examen.

> _**Nota:** El símbolo_ `[...]` _indica que puede haber más código, pero es irrelevante para cada anotación._

## Tabla de contenidos

- [Introducción](#introducci-n)
- [Tabla de contenidos](#tabla-de-contenidos)
- [Patrones frecuentes y trucos](#patrones-frecuentes-y-trucos)
  - [Entender los tipos de datos](#entender-los-tipos-de-datos)
  - [Activar la librería `sw_tick_serial`](#activar-la-librería-sw_tick_serial)
  - [Eliminar el flag](#eliminar-el-flag)
  - [Evitar sombras](#evitar-sombras)
  - [Uso de contadores](#uso-de-contadores)
  - [Dormir al procesador](#dormir-al-procesador)
    - [Para el examen L1](#para-el-examen-l1)
    - [Para el examen L2](#para-el-examen-l2)

## Patrones frecuentes y trucos

### Entender los tipos de datos

#### Números

Las variables de tipo `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `int64_t`, `uint64_t` representan **números enteros** de 8, 16, 32 y 64 bits, respectivamente. La `u` indica que el número es sin signo, mientras que aquellos tipos que no la llevan representan números con signo.

Las variables de tipo `float` y `double` representan **números decimales** (en coma flotante). Hay que evitarlos a toda cosa, porque ocupan demasiada memoria y nuestra licencia de Keil no nos permite hacerlo.

Los **estados de un autómata** se suelen especificar como:

```cpp
typedef enum {IDLE, MEASURE, WAIT, ON} estado_t;
static estado_t estado;
```

#### Booleanos

### Activar la librería `sw_tick_serial`

```c++
int main(void)
{
    // [...]

    sw_tick_serial_init();

    // [...]
}
```

Es importantísimo poner esa línea de código en el `main`, al comienzo del programa, para que pueda funcionar correctamente la librería `sw_tick_serial`.

### Eliminar el flag

```c++
if(event)
{
    event = false; // Elimina el flag

    // [...]
} // if end
```

Tras detectar una interrupción de un pulsador o de un temporizador, lo primero que debemos hacer es **eliminar el flag**.

### Evitar sombras

Si los segmentos del display han sido definidos como:

```c++
static BusOut g_seven_seg(SGA_PIN, SGB_PIN, [...]);
```

Entonces en el código deberemos implementarlo de la siguiente forma para evitar posibles sombras:

```c++
if(gb_tick_1ms_event) // Multiplexación de 1 kHz
{
    gb_tick_1ms_event = false;

    g_seven_seg = 0; // Apaga todos los segmentos del display

    // [...]
}
```

La frecuencia puede ser diferente, es de ejemplo. Esta es suficiente para no detectarlo a simple vista.

### Uso de contadores

```c++
uint8_t contador; // Un contador que cuenta de 0 a 99

// [...]

decenas  = contador / 10;
unidades = contador % 10;
```

Si nuestro contador tiene dos dígitos (por ejemplo, `contador = 95`), cuando dividimos entre 10 y cogemos el cociente (operador `/`, el de toda la vida) el resultado es truncado. Por eso en lugar de darnos 9'5 obtenemos simplemente un 9. En otras palabras, obtenemos el valor de las decenas (**display izquierdo**).

Por otra parte, si cogemos el resto de la división (con el operador `%`) obtenemos un 5, que es el valor de las unidades (**display derecho**).

Se puede implementar este concepto en los ejercicios del examen.

### Dormir al procesador

#### Para el examen L1

Nosotros no manejaremos las interrupciones directamente, para eso usamos la librería `sw_tick_serial`. Por eso mismo debemos **evitar utilizar** `__WFI();`.

#### Para el examen L2

Si tenemos `n` flags en uso, la forma de poner de dormir al procesador es la siguiente:

```cpp
void main(void) {

    // [...]

    for(;;){

        //[...]

        __disable_irq(); // Deshabilita las interrupciones
        if(!flag_1 && !flag_2 && [...] && !flag_n)
        {
            __WFI(); // Duerme al procesador
        }
        __enable_irq(); // Habilita las interrupciones

    } // for end
} // main end
```
