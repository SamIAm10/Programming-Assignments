clear;

% constants
c = 300000000;
r = 10000;

% syms a;
% f = 100e3;
% k = (2*pi*f)/c;
% func = (a*besselj(0, a*r))/sqrt(a^2 - k^2);
% sommerfeld_id = int(func, 0, 0.01);

% solution lists
exact_solns = zeros(1, 45);
matlab_integral_solns = zeros(1, 45);
trapezoid_solns = zeros(1, 45);
ruffa_solns = zeros(1, 45);

i = 1;
for f = 10e3:2e3:100e3
    k = (2*pi*f)/c;
    
%     % exact solutions
%     S0 = exp(-1j*k*r)/r;
%     exact_solns(i) = S0;
%     
%     % matlab integral solutions
%     F1 = @(a) (a.*besselj(0, a.*r))/sqrt(k^2 - a.^2);
%     I1 = -1j*integral(F1, 0, k, 'ArrayValued', true);
%     F2 = @(a) (a.*besselj(0, a.*r))/sqrt(a.^2 - k^2);
%     I2 = integral(F2, k, 200*k, 'ArrayValued', true);
%     S1 = I1 + I2;
%     matlab_integral_solns(i) = S1;
    
    % trapezoid solutions
    syms a;
    func1 = (a*besselj(0, a*r))/sqrt(k^2 - a^2);
    func2 = (a*besselj(0, a*r))/sqrt(a^2 - k^2);
    
    x0 = 0; % lower bound
    x1 = k; % upper bound
    h = x1 - x0;
    deriv1 = diff(diff(func1));
    S2_1 = (h/2)*(subs(func1, a, x0) + subs(func1, a, x1));% - ((h^3)/12)*subs(deriv1, a, (x1+x0)/2);
    
    N = 100;
    S2_2 = 0;
    for n = 1:10:N
        x0 = n*k; % lower bound
        x1 = n*k + 10*k; % upper bound
        h = x1 - x0;
        deriv2 = diff(diff(func2));
        S2_2 = S2_2 + (h/2)*(subs(func2, a, x0) + subs(func2, a, x1));% - ((h^3)/12)*subs(deriv2, a, (x1+x0)/2);
    end
        
    S2 = -1j*S2_1 + S2_2;
    trapezoid_solns(i) = S2;

%     syms a;
%     func1 = (a*besselj(0, a*r))/sqrt(k^2 - a^2);
%     func2 = (a*besselj(0, a*r))/sqrt(a^2 - k^2);
%     
%     x0 = 0; % lower bound
%     x1 = k; % upper bound
%     h = x1 - x0;
%     deriv1 = diff(diff(func1));
%     S2_1 = (h/2)*(subs(func1, a, x0) + subs(func1, a, x1)) - ((h^3)/12)*subs(deriv1, a, (x1+x0)/2);
%     
%     x0 = k; % lower bound
%     x1 = x0 + k; % upper bound
%     x2 = x1 + k;
%     x3 = x2 + k;
%     h = (x3 - x0)/50000000000;
%     deriv2 = diff(diff(diff(diff(func2))));
%     S2_2 = (3*h/8)*(subs(func2, a, x0) + 3*subs(func2, a, x1) + 3*subs(func2, a, x2) + subs(func2, a, x3)) - ((3*h^5)/80)*subs(deriv2, a, (x1+x0)/2);
%         
%     S2 = -1j*S2_1 + S2_2;
%     trapezoid_solns(i) = S2;
    
%     % ruffa solutions
%     N = 15; % number of iterations
%     RR = 0; % solution to summations
%     x0 = 0; % lower bound
%     x1 = k; % upper bound
%     for n = 1:N
%         for m = 1:2^(n-1)
%             a_R = ((2*m-1)*x1+(2^n-2*m+1)*x0)/(2^n);
%             %RR = RR + (-1)^(m+1)*2^(-n)*((0+m*(k-0)/(2^n))*besselj(0, (0+m*(k-0)/(2^n))*r))/sqrt(k^2 - (0+m*(k-0)/(2^n))^2);
%             RR = RR + (a_R*besselj(0, a_R*r))/sqrt(k^2 - a_R^2);
%         end
%     end
%     S3_1 = (x1-x0)/(2^N)*RR;
%     
%     N = 15; % number of iterations
%     RR = 0; % solution to summations
%     x0 = k; % lower bound
%     x1 = 100*k; % upper bound
%     for n = 1:N
%         for m = 1:2^(n-1)
%             a_R = ((2*m-1)*x1+(2^n-2*m+1)*x0)/(2^n);
%             %RR = RR + (-1)^(m+1)*2^(-n)*((k+m*(b-k)/(2^n))*besselj(0, (k+m*(b-k)/(2^n))*r))/sqrt(k^2 - (k+m*(b-k)/(2^n))^2);
%             RR = RR + (a_R*besselj(0, a_R*r))/sqrt(a_R^2 - k^2);
%         end
%     end
%     S3_2 = (x1-x0)/(2^N)*RR;
%     
%     S3 = -1j*S3_1 + S3_2;
%     ruffa_solns(i) = S3;

    i = i + 1;
end

plot(matlab_integral_solns)
hold on
plot(exact_solns)
%plot(trapezoid_solns)
plot(ruffa_solns)
hold off