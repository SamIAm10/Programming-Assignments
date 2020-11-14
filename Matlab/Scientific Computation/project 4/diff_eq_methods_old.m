clear;

% variables to use later
syms y x;
f = x*y^2*exp(-x^4);
y0 = 2;
a = 0;
b = 2.5;
N = 50;
h = (b - a)/N;

% arrays for storing solutions from various methods
w_exact = zeros(1, N+1);
w_euler = zeros(1, N+1);
w_RK4 = zeros(1, N+1);
w_midpoint = zeros(1, N+1);
w_mod_euler = zeros(1, N+1);

% Euler solutions
w_euler(1) = y0;
for n = 2:N+1
    wn = w_euler(n-1);
    tn = a+(n-1)*h;
    w_euler(n) = wn + h*subs(f, [y, x], [wn, tn]);
end

% Runge-Kutta 4th order solutions
w_RK4(1) = y0;
for n = 2:N+1
    wn = w_RK4(n-1);
    tn = a+(n-1)*h;
    k1 = h*subs(f, [y, x], [wn, tn]);
    k2 = h*subs(f, [y, x], [wn + k1/2, tn + h/2]);
    k3 = h*subs(f, [y, x], [wn + k2/2, tn + h/2]);
    k4 = h*subs(f, [y, x], [wn + k3, tn + h]);
    w_RK4(n) = wn + 1/6*(k1+2*k2+2*k3+k4);
end

% midpoint solutions
w_midpoint(1) = y0;
for n = 2:N+1
    wn = w_midpoint(n-1);
    tn = a+(n-1)*h;
    w_midpoint(n) = wn + h*subs(f, [y, x], [wn + h*subs(f, [y, x], [wn, tn]), tn + h/2]);
end

% modified Euler solutions
w_mod_euler(1) = y0;
for n = 2:N+1
    wn = w_mod_euler(n-1);
    tn = a+(n-1)*h;
    w_mod_euler(n) = wn + h/2*(subs(f, [y, x], [wn tn]) + subs(f, [y, x], [wn + h*subs(f, [y, x], [wn tn]), tn + h]));
end

% exact solutions
syms y(x);
ode = diff(y, x) == x*y^2*exp(-x^4);
exact_solns(x) = dsolve(ode, y(0) == 2);
for n = 1:N+1
    w_exact(n) = exact_solns(a+(n-1)*h);
end

% plot solutions
figure
plot(0:0.05:2.5, w_exact)
hold on
plot(0:0.05:2.5, w_euler)
plot(0:0.05:2.5, w_RK4)
%plot(0:0.05:2.5, w_midpoint)
plot(0:0.05:2.5, w_mod_euler)
legend()
grid on
grid minor
hold off

% plot percent error
figure
plot(0:0.05:2.5, abs(w_euler - w_exact)./abs(w_exact)*100)
hold on
plot(0:0.05:2.5, abs(w_RK4 - w_exact)./abs(w_exact)*100)
plot(0:0.05:2.5, abs(w_mod_euler - w_exact)./abs(w_exact)*100)
legend()
grid on
grid minor
hold off