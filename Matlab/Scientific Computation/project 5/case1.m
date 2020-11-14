clear;

N = 10; % number of nodes (must be >= 2)
Is = 2; % current source

% resistor values
Rs = zeros(1, N-1);
Rg = zeros(1, N-1);

Rs(1) = 400;
Rg(1) = 50;
for m = 2:N-1
    Rs(m) = Rs(m-1)/4;
    Rg(m) = Rg(m-1)/2;
end

% conductance values
Gs = 1./Rs;
Gg = 1./Rg;

% building the matrices
A = zeros(N, N);
b = zeros(N, 1);

A(1, 1) = Gs(1);
A(1, 2) = -Gs(1);
b(1) = Is;

for n = 2:N-1
    A(n, n-1) = Gs(n-1);
    A(n, n) = -(Gs(n-1) + Gs(n) + Gg(n-1));
    A(n, n+1) = Gs(n);
end

A(N, N-1) = Gs(N-1);
A(N, N) = -(Gs(N-1) + Gg(N-1));

% exact solution
x_exact = A\b;

% Jacobi solution
D = zeros(N, N); % diagonal matrix
D1 = diag(A);
for n = 1:N
    D(n, n) = D1(n);
end

R = A - D; % remainder matrix

inv_D = inv(D); % inverse of diagonal

% assert spectral radius of iteration matrix is < 1
assert(max(abs(eig(inv_D*R))) < 1);

x_old = ones(N, 1);
x_new = x_old;
for n = 1:500
    x_new = inv_D*(b - R*x_old);
    x_old = x_new;
end

figure
plot(abs(x_exact - x_new))
xlabel('N')
ylabel('Absolute error')
title('Absolute error for case 1')
set(gca, 'XTick', 1:N)
grid on
grid minor