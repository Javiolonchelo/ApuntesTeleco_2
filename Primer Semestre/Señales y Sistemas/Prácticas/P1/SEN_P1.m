% Autor: Javier Rodrigo L�pez
% Laboratorio de Se�ales y Sistemas - Pr�ctica 1
% Fecha de finalizaci�n: 02/03/2021
%
% Para visualizar esta pr�ctica, se ha implementado la funci�n 'pause', por
% lo que durante la ejecuci�n cada gr�fica se generar� al pulsar la tecla
% Enter. La �ltima vez que sea pulsada, cerrar� todas las ventanas.

%% Pre�mbulo
% Comandos �tiles
clear all
clc
close all

% Definici�n de se�ales impulso y escal�n
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
stem(n, x1(n)), title('Se�al x_1[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
stem(n, x2(n)), title('Se�al x_2[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
subplot(2, 1, 1)
stem(n, real(x3(n))), title('Se�al x_3[n]'), xlabel('n'), ylabel('Parte real');
subplot(2, 1, 2)
stem(n, imag(x3(n))), xlabel('n'), ylabel('Parte imaginaria');
pause

figure
subplot(2, 1, 1)
stem(n, abs(x3(n))), title('Se�al x_3[n]'), xlabel('n'), ylabel('M�dulo');
subplot(2, 1, 2)
stem(n, angle(x3(n))), xlabel('n'), ylabel('Fase');
pause
%% Ejercicio 2
t = T2:step:T3;

x1c = exp(-s0 .* t) .* (u(t + t2) - u(t - t2)); % La c indica que es continua.

figure
subplot(2, 1, 1)
plot(t, real(x1c)), title('Se�al x_1(t)'), xlabel('t'), ylabel('Parte real');
subplot(2, 1, 2)
plot(t, imag(x1c)), xlabel('t'), ylabel('Parte imaginaria');
pause

t = -T1:step:T1;

x2c = (t0 <= t & t < X0) * 4 .* cos(X0 * t / 4) + (X0 <= t & t < X1 - X0) .* t.^2 + (X1 - X0 <= t & t <= t1) .* (-t + X0);

figure
plot(t, x2c), title('Se�al x_2(t)'), xlabel('t'), ylabel('Amplitud');
pause

%% Ejercicio 3
% La variable 'n' ya fue definido en el primer ejercicio.

x7 = alfa1 * x1(n) + alfa2 * x2(n);
x8 = x1(n) .* x2(n);
x9 = conj(x3(n));

figure
stem(n, x7), title('Se�al x_7[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
stem(n, x8), title('Se�al x_8[n]'), xlabel('n'), ylabel('Amplitud');
pause

figure
subplot(2, 1, 1)
stem(n, real(x9)), title('Se�al x_9[n]'), xlabel('n'), ylabel('Parte real');
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
