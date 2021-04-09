t = 0:0.001:3; 
figure
plot(t,exp(-2*t).*cos(6*pi*t),t,exp(-2*t),t,-exp(-2*t),'g')
legend({' A_oe^{-δt}cos(ωt+φ)',' A_oe^{-δt}','-A_oe^{-δt}'}, 'FontSize',12)