# Resumen de Microprocesadores

## Índice

- [Archivos útiles](#archivos-útiles)
- [Teoría](#teoría)
  - [_Endianness_](#endianness)
  - [Bits de estado](#bits-de-estado)
  - [Stack](#stack)
  - [Instrucciones de salto](#instrucciones-de-salto)
- [Laboratorio](#laboratorio)

## Archivos útiles

- [Set de instrucciones](Instructions_Cortex-M0.pdf) para el procesador Cortex-M0.

## Teoría

### _Endianness_

Se refiere al orden en el que se almacenan en memoria los diferentes bytes de cada dato. Puede ser **_little endian_** o **_big endian_**.

> Tenemos los siguientes datos en memoria:
>
> | Valor de `y`  | `0`  | `1`  | `2`  | `3`  | `4`  | `5`  | `6`  | `7`  | `8`  | `9`  | `A`  | `B`  | `C`  | `D`  | `E`  | `F`  |
> | :------------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
> | `0x1000 000y` | `0E` | `3E` | `2D` | `40` | `BF` | `C0` | `C1` | `00` | `01` | `FF` | `7E` | `7F` | `80` | `81` | `0D` | `A6` |
>
> Se nos pide obtener la palabra de tamaño 32 bits (4 bytes) ubicada en la dirección de memoria `0x1000 0004`.
>
> - Si el procesador es _little endian_ (como el Cortex-M0), el dato obtenido será `0x00C1 C0BF`.
> - Si es _big endian_, el dato obtenido será `0xBFC0 C100`.

### Bits de estado

Al realizar operaciones con la ALU (_Arithmetic Logic Unit_), es posible que necesitemos cierta información para comprender los resultados. En concreto, nos interesa comprobar si se ha producido **acarreo**, overflow, Es importante entender la importancia de los mismos a la hora de tomar decisiones condicionales.

| Bit de estado | Significado                     | Descripción                                                                    |
| :-----------: | ------------------------------- | ------------------------------------------------------------------------------ |
|      `N`      | _**N**egative result from ALU_  | Si en la operación anterior el resultado es negativo, `N` cambia su valor a 1. |
|      `Z`      | _**Z**ero result from ALU_      | Si en la operación anterior el resultado es 0, `Z` cambia su valor a 1.        |
|      `C`      | _ALU operation **C**arried out_ | Si en la operación anterior se produce un acarreo, `C` cambia su valor a 1.    |
|      `V`      | _ALU operation o**V**erflowed_  | Si en la operación anterior se produce _overflow_, `V` cambia su valor a 1.    |

### Instrucciones de salto

Son aquellas que empiezan por `B`. Suelen corresponder a bucles `while`, `do while`, `for`... o condiciones `if`, `else`, `else if`... Cuando se cumple la condición necesaria, se produce el salto. De lo contrario, continúa con la siguiente línea del programa.

### Stack

Es importante saber cómo funciona la pila o **stack** de un procesador para desarrollar correctamente los programas.

![Imagen ](https://azeria-labs.com/wp-content/uploads/2017/04/stacks.gif.pagespeed.ce.tFWFJqf3Ga.gif)

### Ejemplos

- BEQ

```Assembly
        LDR     R0, =0x00000000
loop
        ADDS    R0, #1
        CMP     R0, #6
        BEQ     loop    ; Sale de este bucle cuando el contenido de R0 es 6,
                        ; porque CMP cambia el bit de estado Z a 1
        END
```

- BHS / BHI / BLS / BLO

```Assembly
; Junio 2017 - Ejercicio 1

```

## Laboratorio
