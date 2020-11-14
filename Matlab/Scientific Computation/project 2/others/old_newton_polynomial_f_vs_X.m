clear; % clear all stored variables

% frequency (f) data (MHz)
x_data = [9.00, 9.60, 10.20, 10.80, 11.40, ...
    12.00, 12.60, 13.20, 13.80, 14.40, 15.00, ...
    15.60, 16.20, 16.80, 17.40, 18.00];

% reactance (X) data (Ohm)
y_data = [229.49, 190.98, 154.00, 117.74, ...
    81.36, 43.84, 3.90, -40.33, -91.81, ...
    -155.33, -237.61, -330.25, -231.01, ...
    229.80, 247.89, 152.36];

% define the divided differences (from 6th to 15th data point, for a total of 10 data points)
f0 = y_data(6);
f1 = y_data(7);
f2 = y_data(8);
f3 = y_data(9);
f4 = y_data(10);
f5 = y_data(11);
f6 = y_data(12);
f7 = y_data(13);
f8 = y_data(14);
f9 = y_data(15);

x0 = x_data(6);
x1 = x_data(7);
x2 = x_data(8);
x3 = x_data(9);
x4 = x_data(10);
x5 = x_data(11);
x6 = x_data(12);
x7 = x_data(13);
x8 = x_data(14);
x9 = x_data(15);

% first order divided differences
f01 = (f1 - f0)/(x1 - x0);
f12 = (f2 - f1)/(x2 - x1);
f23 = (f3 - f2)/(x3 - x2);
f34 = (f4 - f3)/(x4 - x3);
f45 = (f5 - f4)/(x5 - x4);
f56 = (f6 - f5)/(x6 - x5);
f67 = (f7 - f6)/(x7 - x6);
f78 = (f8 - f7)/(x8 - x7);
f89 = (f9 - f8)/(x9 - x8);

% second order
f012 = (f12 - f01)/(x2 - x0);
f123 = (f23 - f12)/(x3 - x1);
f234 = (f34 - f23)/(x4 - x2);
f345 = (f45 - f34)/(x5 - x3);
f456 = (f56 - f45)/(x6 - x4);
f567 = (f67 - f56)/(x7 - x5);
f678 = (f78 - f67)/(x8 - x6);
f789 = (f89 - f78)/(x9 - x7);

% third
f0123 = (f123 - f012)/(x3 - x0);
f1234 = (f234 - f123)/(x4 - x1);
f2345 = (f345 - f234)/(x5 - x2);
f3456 = (f456 - f345)/(x6 - x3);
f4567 = (f567 - f456)/(x7 - x4);
f5678 = (f678 - f567)/(x8 - x5);
f6789 = (f789 - f678)/(x9 - x6);

% fourth
f01234 = (f1234 - f0123)/(x4 - x0);
f12345 = (f2345 - f1234)/(x5 - x1);
f23456 = (f3456 - f2345)/(x6 - x2);
f34567 = (f4567 - f3456)/(x7 - x3);
f45678 = (f5678 - f4567)/(x8 - x4);
f56789 = (f6789 - f5678)/(x9 - x5);

% fifth
f012345 = (f12345 - f01234)/(x5 - x0);
f123456 = (f23456 - f12345)/(x6 - x1);
f234567 = (f34567 - f23456)/(x7 - x2);
f345678 = (f45678 - f34567)/(x8 - x3);
f456789 = (f56789 - f45678)/(x9 - x4);

% sixth
f0123456 = (f123456 - f012345)/(x6 - x0);
f1234567 = (f234567 - f123456)/(x7 - x1);
f2345678 = (f345678 - f234567)/(x8 - x2);
f3456789 = (f456789 - f345678)/(x9 - x3);

% seventh
f01234567 = (f1234567 - f0123456)/(x7 - x0);
f12345678 = (f2345678 - f1234567)/(x8 - x1);
f23456789 = (f3456789 - f2345678)/(x9 - x2);

% eighth
f012345678 = (f12345678 - f01234567)/(x8 - x0);
f123456789 = (f23456789 - f12345678)/(x9 - x1);

% ninth
f0123456789 = (f123456789 - f012345678)/(x9 - x0);

% resulting polynomial
syms x;
p = f0 ...
    + f01*(x - x0) ...
    + f012*(x - x0)*(x - x1) ...
    + f0123*(x - x0)*(x - x1)*(x - x2) ...
    + f01234*(x - x0)*(x - x1)*(x - x2)*(x - x3) ...
    + f012345*(x - x0)*(x - x1)*(x - x2)*(x - x3)*(x - x4) ...
    + f0123456*(x - x0)*(x - x1)*(x - x2)*(x - x3)*(x - x4)*(x - x5) ...
    + f01234567*(x - x0)*(x - x1)*(x - x2)*(x - x3)*(x - x4)*(x - x5)*(x - x6) ...
    + f012345678*(x - x0)*(x - x1)*(x - x2)*(x - x3)*(x - x4)*(x - x5)*(x - x6)*(x - x7) ...
    + f0123456789*(x - x0)*(x - x1)*(x - x2)*(x - x3)*(x - x4)*(x - x5)*(x - x6)*(x - x7)*(x - x8);

% plot
figure
plot(x_data, y_data, 'o');
hold on
fplot(p, [12 17.4]);
xlim([12 17.4]);
title('f vs. X (Newton Polynomial)');
xlabel('f (MHz)');
ylabel('X (Ohm)');
line(xlim(), [0,0], 'LineWidth', 1, 'Color', 'k'); % draw horizontal line at y = 0
line([12.63 12.63], ylim(), 'LineStyle', '--', 'LineWidth', 1, 'Color', 'k'); % draw vertical lines at roots of f
line([16.54 16.54], ylim(), 'LineStyle', '--', 'LineWidth', 1, 'Color', 'k');
grid on
grid minor
hold off