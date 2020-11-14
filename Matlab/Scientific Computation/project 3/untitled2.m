syms a;
func1 = sqrt(a);
func2 = sqrt(a);

x0 = 0; % lower bound
x1 = 1; % upper bound
h = x1 - x0;
deriv1 = diff(diff(func1));
S2_1 = (h/2)*(subs(func1, a, x0) + subs(func1, a, x1));% - ((h^3)/12)*subs(deriv1, a, (x1+x0)/2);

S2_2 = 0;
for n = 1:2:50
    x0 = n; % lower bound
    x1 = n + 2; % upper bound
    h = x1 - x0;
    deriv2 = diff(diff(func2));
    S2_2 = S2_2 + (h/2)*(sqrt(x0) + sqrt(x1));% - ((h^3)/12)*subs(deriv2, a, (x1+x0)/2);
end

S2 = S2_1 + S2_2;