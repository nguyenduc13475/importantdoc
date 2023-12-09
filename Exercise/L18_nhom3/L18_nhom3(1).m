syms t;

disp("Enter the parametric equations: ");
r = sym([input("x: ") input("y: ")]);

t_start = input("Starting time: ");
t_end = input("End time: ");
t0 = input("Calculate the magnitude of acceleration at t = ");

fig = figure(1);

subplot(1, 1, 1);
title("Motion Trajectory");
xlabel("x (m)");
ylabel("y (m)");
[left, right, bottom, top] = autofit(r(1), r(2), t_start, t_end);
xlim([left, right]);
ylim([bottom, top]);
hold on;
grid on;

fplot(r(1), r(2), [t_start t_end]);

a = diff(r,t,2);
a_length = subs(norm(a), t0);
disp("The magnitude of acceleration at t = " + string(t0) + "s (SI unit) is " + string(double(a_length)) + " m/s2");

function [left, right, bottom, top] = autofit(x, y, t_start, t_end)
    resolution = (t_end - t_start) / 10;
    timestamps = t_start:resolution:t_end;
    x_coords = subs(x, timestamps);
    y_coords = subs(y, timestamps);
    x_left = double(min(x_coords));
    x_right = double(max(x_coords));
    x_range = x_right - x_left;
    y_bottom = double(min(y_coords));
    y_top = double(max(y_coords));
    y_range = y_top - y_bottom;
    if x_range > y_range
        left = x_left - 5;
        right = x_right + 5;
        width = right - left;
        y_mid = (y_top + y_bottom) / 2;
        bottom = y_mid - width / 2;
        top = y_mid + width / 2;
    else
        bottom = y_bottom - 5;
        top = y_top + 5;
        height = top - bottom;
        x_mid = (x_left + x_right) / 2;
        left = x_mid - height / 2;
        right = x_mid + height / 2;
    end
end
