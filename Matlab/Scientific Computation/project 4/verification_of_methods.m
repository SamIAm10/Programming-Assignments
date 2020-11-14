clear;

% define diff eq and constants to use later
syms f(y, x);
f(y, x) = x + y; % diff eq function
y0 = 1; % initial condition
a = 0; % lower limit
b = 3; % upper limit
N = 20; % number of iterations
h = (b - a)/N; % step size

% arrays for storing solutions from various methods
w_euler = zeros(1, N+1);
w_RK4 = zeros(1, N+1);
w_mod_euler = zeros(1, N+1);

% exact solutions
w_exact = zeros(1, N+1);
syms y(x);
ode = diff(y, x) == f(y, x);
exact_solns(x) = dsolve(ode, y(0) == y0);
for n = 1:N+1
    w_exact(n) = exact_solns(a+(n-1)*h);
end

% Euler solutions
w_euler(1) = y0;
for n = 2:N+1
    wn = w_euler(n-1);
    tn = a+(n-1)*h;
    w_euler(n) = wn + h*f(wn, tn);
end

% Runge-Kutta 4th order solutions
w_RK4(1) = y0;
for n = 2:N+1
    wn = w_RK4(n-1);
    tn = a+(n-1)*h;
    k1 = h*f(wn, tn);
    k2 = h*f(wn + k1/2, tn + h/2);
    k3 = h*f(wn + k2/2, tn + h/2);
    k4 = h*f(wn + k3, tn + h);
    w_RK4(n) = wn + 1/6*(k1+2*k2+2*k3+k4);
end

% modified Euler solutions
w_mod_euler(1) = y0;
for n = 2:N+1
    wn = w_mod_euler(n-1);
    tn = a+(n-1)*h;
    w_mod_euler(n) = wn + h/2*(f(wn, tn) + f(wn + h*f(wn, tn), tn + h));
end

% RMS error
euler_RMS = sqrt(mean((w_euler - w_exact).^2));
RK4_RMS = sqrt(mean((w_RK4 - w_exact).^2));
mod_euler_RMS = sqrt(mean((w_mod_euler - w_exact).^2));

% plots
x_range = a:h:b;

% plot solutions
figure
hold on
plot(x_range, w_exact)
plot(x_range, w_euler)
plot(x_range, w_RK4)
plot(x_range, w_mod_euler)
title('Solutions from various methods')
xlabel('x values')
ylabel('y values')
legend('Exact', 'Euler', 'RK4', 'Modified Euler')
grid on
grid minor
hold off

% plot percent error
figure
hold on
plot(x_range, abs(w_euler - w_exact)./w_exact*100)
plot(x_range, abs(w_RK4 - w_exact)./w_exact*100)
plot(x_range, abs(w_mod_euler - w_exact)./w_exact*100)
title('Percent error for various methods')
xlabel('x values')
ylabel('% error')
legend('Euler', 'RK4', 'Modified Euler')
grid on
grid minor
hold off