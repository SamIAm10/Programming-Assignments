clear; % clear all stored variables

% parameters for Bessel functions
a = 0.075;
b = 0.325;

% cutoff equation in f(x) = 0 form
syms x;
f = besselj(0, x*a)*bessely(0, x*b) - besselj(0, x*b)*bessely(0, x*a);
f_deriv = diff(f); % derivative of f(x)

n_max = 40;
tol = 0.0001;

first_initial_guess = zeros(100, 1);
second_initial_guess = zeros(100, 1);
number_of_iterations = zeros(100, 1);
solution = zeros(100, 1);
fail_or_success = strings([100, 1]);

% main algorithm loop
for i = 1:100
    a = i;
    b = i + 20;
    for n = 1:n_max
        f_a = vpa(subs(f, x, a));
        f_b = vpa(subs(f, x, b));
        slope = (f_b - f_a)/(b - a);
        c = a - f_a/slope;
        f_c = vpa(subs(f, x, c));
        abs_error = abs(f_c);
        if f_a*f_c > 0
            a = c;
        else
            b = c;
        end
        if abs_error < tol
            break
        end
    end
    first_initial_guess(i) = i;
    second_initial_guess(i) = i + 20;
    number_of_iterations(i) = n;
    solution(i) = c;
    if n >= n_max || c <= 0
        fail_or_success(i) = "F";
    else
        fail_or_success(i) = "S";
    end
end

data = table(first_initial_guess, second_initial_guess, number_of_iterations, solution, fail_or_success);
writetable(data, 'regula_falsi_data.xlsx')
