% trapezoid
N = 100;
S2_2 = 0;
for n = 1:0.1:N
    x0 = n; % lower bound
    x1 = n + 0.1; % upper bound
    y0 = sin(x0)/sqrt(x0);
    y1 = sin(x1)/sqrt(x1);
    h = x1 - x0;
    S2_2 = S2_2 + (h/2)*(y0 + y1);
end

% ruffa
N = 15; % number of iterations
RR = 0; % solution to summations
x0 = 1; % lower bound
x1 = 100; % upper bound
for n = 1:N
    for m = 1:2^(n-1)
        a_R = ((2*m-1)*x1+(2^n-2*m+1)*x0)/(2^n);
        RR = RR + sin(a_R)/sqrt(a_R);
    end
end
S3_1 = (x1-x0)/(2^N)*RR;