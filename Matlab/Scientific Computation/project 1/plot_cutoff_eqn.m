% parameters for Bessel functions
a = 0.075;
b = 0.325;

% cutoff equation in f(x) = 0 form
syms x;
f = besselj(0, x*a)*bessely(0, x*b) - besselj(0, x*b)*bessely(0, x*a);

% plot
figure
fplot(f, [0, 110])
title('Cutoff Equation Plot')
xlabel('k')
ylabel('f(k)')
grid on
grid minor