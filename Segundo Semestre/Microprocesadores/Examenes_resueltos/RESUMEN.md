# Resumen para el primer examen de laboratorio

## Introducción

Mientras resolvíamos exámenes, hemos notado ciertos patrones a la hora de resolverlos.

He aquí un listado de dichos patrones y algún que otro truco para que puedas repasarlos antes de ir al examen.

> _**Nota:** El símbolo_ `[...]` _indica que puede haber más código, pero es irrelevante para cada anotación._

## Tabla de contenidos

- [Introducción](#introducci-n)
- [Tabla de contenidos](#tabla-de-contenidos)
- [Patrones frecuentes y trucos](#patrones-frecuentes-y-trucos)
  - [Activar la librería `sw_tick_serial`](#activar-la-librer-a--sw-tick-serial-)
  - [Eliminar el flag](#eliminar-el-flag)
  - [Evitar sombras](#evitar-sombras)
  - [Uso de contadores](#uso-de-contadores)
  - [Evitar el modo reposo](#evitar-el-modo-reposo)

## Patrones frecuentes y trucos

### Activar la librería `sw_tick_serial`

```c++
int main(void)
{
    [...]

    sw_tick_serial_init();

    [...]
}
```

Es importantísimo poner esa línea de código en el `main`, al comienzo del programa, para que pueda funcionar correctamente la librería `sw_tick_serial`.

### Eliminar el flag

```c++
if(event)
{
    event = false; // Elimina el flag

    [...]
}
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

    [...] // Resto de operaciones
}
```

La frecuencia puede ser diferente, es de ejemplo. Esta es suficiente para no detectarlo a simple vista.

### Uso de contadores

```c++
int8_t contador; // Un contador que cuenta de 0 a 99

[...]

decenas  = contador / 10;
unidades = contador % 10;
```

Si nuestro contador tiene dos dígitos (por ejemplo, `contador = 95`), cuando dividimos entre 10 y cogemos el cociente (operador `/`, el de toda la vida) el resultado es truncado. Por eso en lugar de darnos 9'5 obtenemos simplemente un 9. En otras palabras, obtenemos el valor de las decenas (**display izquierdo**).

Por otra parte, si cogemos el resto de la división (con el operador `%`) obtenemos un 5, que es el valor de las unidades (**display derecho**).

Se puede implementar este concepto en los ejercicios del examen.

### Evitar el modo reposo

Nosotros no manejaremos las interrupciones directamente, para eso usamos la librería `sw_tick_serial`. Por eso mismo debemos **evitar utilizar** `__WFI();`.
