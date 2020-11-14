clear;

% constants
c = 300000000;
r = 1000;

% solution lists
needed_size = (2000-500)/10 + 1;
exact_solns = zeros(1, needed_size);
trapezoid_solns = zeros(1, needed_size);
ruffa_solns = zeros(1, needed_size);

i = 1;
for f = 500e3:10e3:2000e3
    k = (2*pi*f)/c;
    
    % exact solutions
    S0 = exp(-1j*k*r)/r;
    exact_solns(i) = S0;
    
    % trapezoid solutions 
    N = 0.8;
    S2_1 = 0;
    for n = 0:0.1:N
        x0 = n*k; % lower bound
        x1 = n*k + 0.1*k; % upper bound
        y0 = (x0*besselj(0, x0*r))/sqrt(k^2 - x0^2);
        y1 = (x1*besselj(0, x1*r))/sqrt(k^2 - x1^2);
        h = x1 - x0;
        S2_1 = S2_1 + (h/2)*(y0 + y1);
    end
    
    N = 100;
    S2_2 = 0;
    for n = 1.1:0.1:N
        x0 = n*k; % lower bound
        x1 = n*k + 0.1*k; % upper bound
        y0 = (x0*besselj(0, x0*r))/sqrt(x0^2 - k^2);
        y1 = (x1*besselj(0, x1*r))/sqrt(x1^2 - k^2);
        h = x1 - x0;
        S2_2 = S2_2 + (h/2)*(y0 + y1);
    end
        
    S2 = -1j*S2_1 + S2_2;
    trapezoid_solns(i) = S2;
    
    % ruffa solutions
    N = 15; % number of iterations
    RR = 0; % solution to summations
    x0 = 0; % lower bound
    x1 = k; % upper bound
    for n = 1:N
        for m = 1:2^(n-1)
            a_R = ((2*m-1)*x1+(2^n-2*m+1)*x0)/(2^n);
            RR = RR + (a_R*besselj(0, a_R*r))/sqrt(k^2 - a_R^2);
        end
    end
    S3_1 = (x1-x0)/(2^N)*RR;
    
    N = 15; % number of iterations
    RR = 0; % solution to summations
    x0 = k; % lower bound
    x1 = 100*k; % upper bound
    for n = 1:N
        for m = 1:2^(n-1)
            a_R = ((2*m-1)*x1+(2^n-2*m+1)*x0)/(2^n);
            RR = RR + (a_R*besselj(0, a_R*r))/sqrt(a_R^2 - k^2);
        end
    end
    S3_2 = (x1-x0)/(2^N)*RR;
    
    S3 = -1j*S3_1 + S3_2;
    ruffa_solns(i) = S3;

    % increment index
    i = i + 1;
end

figure
hold on
plot(exact_solns, '--x', 'MarkerSize', 10)
plot(trapezoid_solns, '--x', 'MarkerSize', 10)
plot(ruffa_solns, '--x', 'MarkerSize', 10)
xlabel('Real')
ylabel('Imaginary')
title('All solutions for f = [500kHz, 2000kHz] and r = 1000m')
legend('Exact solutions', 'Trapezoid solutions', 'Ruffa solutions')
hold off

figure
hold on
plot(500e3:10e3:2000e3, abs(trapezoid_solns-exact_solns), '--x', 'MarkerSize', 10)
plot(500e3:10e3:2000e3, abs(ruffa_solns-exact_solns), '--x', 'MarkerSize', 10)
xlabel('f (kHz)')
ylabel('Absolute error')
title('Absolute error analysis for f = [500kHz, 2000kHz] and r = 1000m')
legend('Trapezoid error', 'Ruffa error')
hold off