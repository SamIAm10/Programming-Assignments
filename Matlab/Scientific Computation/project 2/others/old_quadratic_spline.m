clear; % clear all stored variables

% frequency (f) data (MHz)
global x;
x = [9.00, 9.60, 10.20, 10.80, 11.40, ...
    12.00, 12.60, 13.20, 13.80, 14.40, 15.00, ...
    15.60, 16.20, 16.80, 17.40, 18.00];

% reactance (X) data (Ohm)
global y;
y = [229.49, 190.98, 154.00, 117.74, ...
    81.36, 43.84, 3.90, -40.33, -91.81, ...
    -155.33, -237.61, -330.25, -231.01, ...
    229.80, 247.89, 152.36];

h = [];
i = 1;
for n = 12:0.01:18
    h(i) = qquadspline(n);
    i = i + 1;
end
plot(12:0.01:18, h)
hold on
plot(x, y, 'o')
hold off

function b = bb(k)
    global x;
    global y;
    if k == 1
        b = (y(2) - y(1))/(x(2) - x(1));
    else
        b = 2*(y(k) - y(k-1))/(x(k) - x(k-1)) - bb(k - 1);
    end
end

function c = cc(k)
    global x;
    c = (bb(k + 1) - bb(k))/(2*(x(k+1) - x(k)));
end

function spline = sspline(u, k)
    global x;
    global y;
    spline = y(k) + bb(k)*(u - x(k)) + cc(k)*(u - x(k))^2;
end

function quadspline = qquadspline(u)
    global x;
    if u <= x(7)
        quadspline = sspline(u, 1);
    elseif u <= x(8)
        quadspline = sspline(u, 2);
    elseif u <= x(9)
        quadspline = sspline(u, 3);
    elseif u <= x(10)
        quadspline = sspline(u, 4);
    elseif u <= x(11)
        quadspline = sspline(u, 5);
    elseif u <= x(12)
        quadspline = sspline(u, 6);
    elseif u <= x(13)
        quadspline = sspline(u, 7);
    elseif u <= x(14) 
        quadspline = sspline(u, 8);
    else
        quadspline = sspline(u, 9);
    end
end