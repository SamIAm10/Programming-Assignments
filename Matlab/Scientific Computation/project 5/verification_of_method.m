clear;

N = 4; % size of matrices/vectors

% generate random matrices/vectors until the spectral radius is < 1
while true
    try
        A = rand(N, N);
        b = rand(N, 1);

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
        break
        
    catch
        continue
    end
end

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
title('Absolute error for method verification, N = 4')
set(gca, 'XTick', 1:N)
grid on
grid minor