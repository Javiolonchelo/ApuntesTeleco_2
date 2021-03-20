% Autor: Javier Rodrigo López
% Laboratorio de Señales y Sistemas - Práctica 1
% Fecha de finalización: 02/03/2021
%
% Para visualizar esta práctica, se ha implementado la función 'pause', por
% lo que durante la ejecución cada gráfica se generará al pulsar la tecla
% Enter. La última vez que sea pulsada, cerrará todas las ventanas.

%% Preámbulo
% Comandos útiles
clear all
clc
close all

% Definición de señales impulso y escalón
d = @(t) t == 0;
u = @(t) t >= 0;

% Constantes
n1 = 10;
N1 = 15;
n2 = 8;
n3 = 11;
z0 = (5/4) * exp(1i * pi / 6);
n4 = 4;
n5 = 8;
X0 = -2;
X1 = 4;
t0 = -4;
t1 = 8;
T1 = 10;
s0 = 2 + 8 * pi * 1i;
t2 = 4;
T2 = -6;
T3 = 8;
alfa1 = 1/2;
alfa2 = 5;
step = 1E-3;

%% Ejercicio 1
n = -N1:N1;

x1 = @(n) n.^2 .* (u(n) - u(n - n1));
x2 = @(n) cos(pi * n / 2) .* (u(n + n3) - u(n - n2));
x3 = @(n) z0.^n .* (u(n + n4) .* u(-n + n5));

figure
stem(n, x1(n)), title('Señal x_1[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
stem(n, x2(n)), title('Señal x_2[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
subplot(2, 1, 1)
stem(n, real(x3(n))), title('Señal x_3[n]'), xlabel('n'), ylabel('Parte real');
subplot(2, 1, 2)
stem(n, imag(x3(n))), xlabel('n'), ylabel('Parte imaginaria');
pause

figure
subplot(2, 1, 1)
stem(n, abs(x3(n))), title('Señal x_3[n]'), xlabel('n'), ylabel('Módulo');
subplot(2, 1, 2)
stem(n, angle(x3(n))), xlabel('n'), ylabel('Fase');
pause
%% Ejercicio 2
t = T2:step:T3;

x1c = exp(-s0 .* t) .* (u(t + t2) - u(t - t2)); % La c indica que es continua.

figure
subplot(2, 1, 1)
plot(t, real(x1c)), title('Señal x_1(t)'), xlabel('t'), ylabel('Parte real');
subplot(2, 1, 2)
plot(t, imag(x1c)), xlabel('t'), ylabel('Parte imaginaria');
pause

t = -T1:step:T1;

x2c = (t0 <= t & t < X0) * 4 .* cos(X0 * t / 4) + (X0 <= t & t < X1 - X0) .* t.^2 + (X1 - X0 <= t & t <= t1) .* (-t + X0);

figure
plot(t, x2c), title('Señal x_2(t)'), xlabel('t'), ylabel('Amplitud');
pause

%% Ejercicio 3
% La variable 'n' ya fue definido en el primer ejercicio.

x7 = alfa1 * x1(n) + alfa2 * x2(n);
x8 = x1(n) .* x2(n);
x9 = conj(x3(n));

figure
stem(n, x7), title('Señal x_7[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
stem(n, x8), title('Señal x_8[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
subplot(2, 1, 1)
stem(n, real(x9)), title('Señal x_9[n]'), xlabel('n'), ylabel('Parte real');
subplot(2, 1, 2)
stem(n, imag(x9)), xlabel('n'), ylabel('Parte imaginaria');
pause

%% Ejercicio 4

x1p = (x1(n) + x1(-n)) / 2;
x1i = (x1(n) - x1(-n)) / 2;

figure
subplot(2, 1, 1)
stem(n, x1p), title('Parte par de x_1[n]'), xlabel('n'), ylabel('Amplitud');
subplot(2, 1, 2)
stem(n, x1i), title('Parte impar de x_1[n]'), xlabel('n'), ylabel('Amplitud');
pause

close all
