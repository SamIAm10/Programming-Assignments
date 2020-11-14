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
x_0 = input('Enter the initial approximation:');

% if no inputs provided, use these default values
if isempty(n_max)
    n_max = 40;
end
if isempty(tol)
    tol = 0.0001;
end
if isempty(x_0)
    x_0 = 5;
end

fprintf('\n\n    Step #      x_0          x_1        Delta (abs(f(x_1)))\n ----------------------------------------------------------\n');

% main algorithm loop
for n = 1:n_max
    f_0 = vpa(subs(f, x, x_0));
    f_h = vpa(subs(f, x, x_0 + f_0));
    slope = (f_h - f_0)/f_0;
    x_1 = x_0 - f_0/slope;
    f_1 = vpa(subs(f, x, x_1));
    abs_error = abs(f_1);
    fprintf('   %3d      %8.5f      %8.5f     %8.5f\n', n, x_0, x_1, abs_error);
    if abs_error < tol
        break
    end
    x_0 = x_1;
end

% print results
if n >= n_max
    fprintf('\nERROR: method failed to converge after %d iterations.\n', n);
    fprintf('Final solution: %8.5f\n', x_1);
elseif x_1 <= 0
    fprintf('\nERROR: the solution %8.5f is not greater than 0.\n', x_1);
    fprintf('Number of iterations: %d\n', n);
else
    fprintf('\nSolution found at %8.5f after %d iterations.\n', x_1, n);
end