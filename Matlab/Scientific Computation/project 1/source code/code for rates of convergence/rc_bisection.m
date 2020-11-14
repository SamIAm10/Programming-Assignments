clear; % clear all stored variables

% parameters for Bessel functions
a = 0.075;
b = 0.325;

% cutoff equation in f(x) = 0 form
syms x;
f = besselj(0, x*a)*bessely(0, x*b) - besselj(0, x*b)*bessely(0, x*a);

% take inputs from command line
n_max = input('Enter the maximum number of iterations:');
tol = input('Enter the tolerance for the solution:');
a = input('Enter the left limit:');
b = input('Enter the right limit:');

% if no inputs provided, use these default values
if isempty(n_max)
    n_max = 40;
end
if isempty(tol)
    tol = 0.0001;
end
if isempty(a)
    a = 5;
end
if isempty(b)
    b = 100;
end

% check for guarantee of a solution
f_a = vpa(subs(f, x, a));
f_b = vpa(subs(f, x, b));

if (f_a*f_b > 0)
    fprintf('\nERROR: no guarantee there is a zero in the interval given.\n');
end

fprintf('\n\n    Step #      a          b          c        Delta (abs(f(c)))\n ----------------------------------------------------------\n');

% main algorithm loop
for n = 1:n_max
    f_a = vpa(subs(f, x, a));
    f_b = vpa(subs(f, x, b));
    c = (a + b)/2;
    x_2 = c;
    f_c = vpa(subs(f, x, c));
    abs_error = abs(f_c);
    fprintf('   %3d      %8.5f      %8.5f     %8.5f      %8.5f\n', n, a, b, c, abs_error);
    if f_a*f_c > 0
        x_1 = a;
        a = c;
    else
        x_1 = b;
        b = c;
    end
    delta(n, 1) = n;
    delta(n, 2) = abs(x_2 - x_1);
    if abs_error < tol
        break
    end
end

% print results
if n >= n_max
    fprintf('\nERROR: method failed to converge after %d iterations.\n', n);
    fprintf('Final solution: %8.5f\n', c);
elseif c <= 0
    fprintf('\nERROR: the solution %8.5f is not greater than 0.\n', c);
    fprintf('Number of iterations: %d\n', n);
else
    fprintf('\nSolution found at %8.5f after %d iterations.\n', c, n);
end

figure
plot(delta(1:n, 2))
title('Bisection')
xlabel('Iteration')
ylabel('Step-to-step error')
set(gca, 'YScale', 'log')