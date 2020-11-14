clear; % clear all stored variables

% frequency (f) data (MHz)
x_data = [9.00, 9.60, 10.20, 10.80, 11.40, ...
    12.00, 12.60, 13.20, 13.80, 14.40, ...
    15.00, 15.60, 16.20, 16.80, 17.40, 18.00];

% reactance (X) data (Ohm)
y0_data = [229.49, 190.98, 154.00, 117.74, ...
    81.36, 43.84, 3.90, -40.33, -91.81, ...
    -155.33, -237.61, -330.25, -231.01, ...
    229.80, 247.89, 152.36];

% input resistance (R) data (Ohm)
y1_data = [6.58, 8.05, 9.90, 12.25, 15.34, ...
    19.55, 25.54, 34.62, 49.54, 76.91, ...
    135.30, 284.09, 618.48, 547.86, 252.51, ...
    136.87];

% sampling range and frequency
xq = 9:0.0001:18;

% cubic spline interpolation graph for f vs. X
figure
f_vs_X_interp = interp1(x_data, y0_data, xq, 'spline');
plot(x_data, y0_data, 'o', xq, f_vs_X_interp);
xlim([9 18]);
xlabel('f (MHz)');
ylabel('X (Ohm)');
title('f vs. X (MATLAB Cubic Spline Interpolation)');
line(xlim(), [0,0], 'LineWidth', 1, 'Color', 'k'); % draw horizontal line at y = 0
line([12.66 12.66], ylim(), 'LineStyle', '--', 'LineWidth', 1, 'Color', 'k'); % draw vertical lines at roots of f
line([16.49 16.49], ylim(), 'LineStyle', '--', 'LineWidth', 1, 'Color', 'k');
legend('Given data', 'Interpolated data')
grid on
grid minor

% cubic spline interpolation graph for f vs. R
figure
f_vs_R_interp = interp1(x_data, y1_data, xq, 'spline');
plot(x_data, y1_data, 'o', xq, f_vs_R_interp);
xlim([9 18]);
xlabel('f (MHz)');
ylabel('R (Ohm)');
title('f vs. R (MATLAB Cubic Spline Interpolation)');
line(xlim(), [0,0], 'LineWidth', 1, 'Color', 'k'); % draw horizontal line at y = 0
line([12.66 12.66], ylim(), 'LineStyle', '--', 'LineWidth', 1, 'Color', 'k'); % draw vertical lines at roots of f
line([16.49 16.49], ylim(), 'LineStyle', '--', 'LineWidth', 1, 'Color', 'k');
legend('Given data', 'Interpolated data')
grid on
grid minor