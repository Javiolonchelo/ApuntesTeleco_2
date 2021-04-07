% Autor: Javier Rodrigo López
% Laboratorio de Señales y Sistemas - Práctica 2
% Fecha de finalización: 16/03/2021
%
% Para visualizar esta práctica, se ha implementado la función 'pause',
% por lo que durante la ejecución cada gráfica se generará al pulsar la
% tecla Enter. La última vez que sea pulsada, cerrará todas las ventanas.

%% Preámbulo
% Comandos útiles
clear all
clc
close all

% Definición de señales impulso y escalón
d = @(t) t == 0;
u = @(t) t >= 0;

% Constantes
A1 = 2;
A2 = -2;
A3 = 3;
A4 = -1/2;
N1 = 6;
N2 = 4;
N3 = 3;
N4 = 2;
N5 = 20;
N6 = 12;
W1 = 1/3;
W2 = 3 * pi / 8;

%% Ejercicio 1
% Suficientes muestras para representar todas las señales.
n = -10:10;

% Definición de las señales con las que trabajaremos.
x1 = @(n) A1 * (u(n + N1) - u(n - N1));
x2 = @(n) A2 .* u(n + N2) .* u(-n + N2);
x3 = @(n) A3 * (u(n + N1) - u(n - N2)) .* exp(1i * W1 .* n);

figure
stem(n, x1(n)), title('1 - Señal x_1[n]'), xlabel('n')
pause
figure
stem(n, x2(n)), title('1 - Señal x_2[n]'), xlabel('n')
pause
figure
subplot(2, 1, 1)
stem(n, real(x3(n))), title('1 - Señal x_3[n]'), ylabel('Parte real')
subplot(2, 1, 2)
stem(n, imag(x3(n))), ylabel('Parte imaginaria'), xlabel('n')
pause

% Cálculo de las convoluciones.
[y1, n1] = convolucion(x1(n), x1(n + N3), n);
[y2, n2] = convolucion(x1(n), x2(n), n);
[y3, n3] = convolucion(x1(n), y2, n);
[y4, n4] = convolucion(real(x3(n)), imag(x3(n - N4)), n);

% Recorte de las señales, para mejor representación.
y1 = y1(1, 1:find(y1, 1, 'last'));
n1 = n1(1:length(y1));

y2 = y2(1, 1:find(y2, 1, 'last'));
n2 = n2(1:length(y2));

y3 = y3(1, 1:find(y3, 1, 'last'));
n3 = n3(1:length(y3));

y4 = y4(1, 1:find(y4, 1, 'last'));
n4 = n4(1:length(y4));

% Ajuste de los límites para que las señales se ajusten al ancho de la
% gráfica.
figure
stem(n1, y1), title('1.1 - Señal y_1[n]'), xlabel('n'), axis tight
pause
figure
stem(n2, y2), title('1.2 - Señal y_2[n]'), xlabel('n'), axis tight
pause
figure
stem(n3, y3), title('1.3 - Señal y_3[n]'), xlabel('n'), axis tight
pause
figure
stem(n4, y4), title('1.4 - Señal y_4[n]'), xlabel('n'), axis tight
pause

%% Ejercicio 2
n = 0:N5;
imp = d(n);

% Apartado 2.1
a1 = [1 0 0 0];
b1 = [A1 0 0 A3];

h1 = filter(b1, a1, imp);

figure
stem(n, h1), title('2.1 - Señal h1[n]'), xlabel('n')
pause

% Resultado: Este sistema es estable, pues su respuesta al impulso es una
% combinación de dos deltas. La suma absoluta de todos sus valores es un
% valor finito.

% Apartado 2.2
a2 = [1 1 0 0];
b2 = [1 A1 A2 A3];

h2 = filter(b2, a2, imp);

figure
stem(n, h2), title('2.2 - Señal h2[n]'), xlabel('n')
pause

% Resultado: Este sistema no es estable. Si realizamos la suma absoluta de
% todos sus valores, esta tiende a infinito.

%% Ejercicio 3
x4 = A1 * (u(n) - u(n - N1));
x5 = A3 * exp(1i * W1 * n) .* u(n);

% Apartado 3.1
[y41, ~] = convolucion(x4, h1, n);
y41 = y41(1, 1:length(n));
y41f = filter(b1, a1, x4);

figure
subplot(2, 1, 1)
stem(n, y41), title('3.1 - Señal y_4_1[n] - convolucion()')
subplot(2, 1, 2)
stem(n, y41f), title('3.1 - Señal y_4_1[n] - filter()'), xlabel('n')
pause

[y42, ~] = convolucion(x4, h2, n);
y42 = y42(1, 1:length(n));
y42f = filter(b2, a2, x4);

figure
subplot(2, 1, 1)
stem(n, y42), title('3.1 - Señal y_4_2[n] - convolucion()')
subplot(2, 1, 2)
stem(n, y42f), title('3.1 - Señal y_4_2[n] - filter()'), xlabel('n')
pause

% Apartado 3.2
[y51, ~] = convolucion(x5, h1, n);
y51 = y51(1, 1:length(n));
y51f = filter(b1, a1, x5);

figure
subplot(2, 2, 1)
stem(n, real(y51)), title('3.2 - Señal y_5_1[n] - convolucion()'), ylabel('Parte real')
subplot(2, 2, 3)
stem(n, imag(y51)), xlabel('n'), ylabel('Parte imaginaria')
subplot(2, 2, 2)
stem(n, real(y51f)), title('3.2 - Señal y_5_1[n] - filter()'), ylabel('Parte real')
subplot(2, 2, 4)
stem(n, imag(y51f)), xlabel('n'), ylabel('Parte imaginaria')
pause

[y52, ~] = convolucion(x5, h2, n);
y52 = y52(1, 1:length(n));
y52f = filter(b2, a2, x5);

figure
subplot(2, 2, 1)
stem(n, real(y52)), title('3.2 - Señal y_5_2[n] - convolucion()'), ylabel('Parte real')
subplot(2, 2, 3)
stem(n, imag(y52)), xlabel('n'), ylabel('Parte imaginaria')
subplot(2, 2, 2)
stem(n, real(y52f)), title('3.2 - Señal y_5_2[n] - filter()'), ylabel('Parte real')
subplot(2, 2, 4)
stem(n, imag(y52f)), xlabel('n'), ylabel('Parte imaginaria')
pause

% Resultados: Ambas gráficas son iguales, independientemente de la función
% utilizada. Podemos suponer que los resultados son correctos.

%% Ejercicio 4
n = 0:15;
x = A1 * cos(W2 * n) .* (u(n) - u(n - N6));
imp = d(n);

% Cálculo de las señales solicitadas.
a = [1 0 A4];
b = [0 0 A1];
s = filter(b, a, x);

h = d(n) + A1 * d(n - N4) + A2 * d(n - N2) +A3 * d(n - N1);
[v, ~] = convolucion(h, s, n);
v = v(1, 1:length(n));

y = v + s .* cos(pi * n / 2);

figure
stem(n, s), title('4 - Señal s[n]'), xlabel('n')
pause
figure
stem(n, v), title('4 - Señal v[n]'), xlabel('n')
pause
figure
stem(n, y), title('4 - Señal y[n]'), xlabel('n')
pause

close all

%% Funciones

% Realiza la convolución mediante la función 'conv()'.
function [y, eje] = convolucion(x, h, eje)
    % Cálculo de los instantes iniciales.
    xi = find(x, 1) + eje(1, 1) - 1;
    hi = find(h, 1) + eje(1, 1) - 1;
    yi = xi + hi;

    % Hacemos que los vectores empiecen desde el primer valor no nulo.
    x = x(1, find(x, 1):end);
    h = h(1, find(h, 1):end);

    % Calculamos el resultado y su eje de tiempos.
    y = conv(x, h);
    eje = (1:length(y)) + yi - 1;
end
