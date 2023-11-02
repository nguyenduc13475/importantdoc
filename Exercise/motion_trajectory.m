close all;

syms t;
disp("Enter the parametric equation: ");
r = sym([input("x: ") input("y: ")]);
v = diff(r, t, 1);
a = diff(v, t, 1);
v_length = norm(v);
a_length = norm(a);
a_t = v / max(v_length, 1e-5) * diff(v_length, t, 1);
a_n = a - a_t;

t_start = input("Starting time: ");
t_end = input("End time: ");
t = input("Calculate the magnitude of acceleration at t = ");

fig = figure(1);
fig.Position = [200, 200, 1200, 500];

subplot(1, 2, 1);
title("Motion Trajectory");
xlabel("x (m)");
ylabel("y (m)");
[left, right, bottom, top] = autofit(r(1), r(2), t_start, t_end);
xlim([left, right]);
ylim([bottom, top]);
hold on;
grid on;
fplot(r(1), r(2), [t_start t_end]);

root = scatter(0, 0, "filled");
vector_v = quiver(0, 0, 0, 0, 0, "linewidth", 1, "MaxHeadSize", 10, "color", [0 0 1]);
vector_at = quiver(0, 0, 0, 0, 0, "linewidth", 2, "MaxHeadSize", 10, "color", [0 1 0]);
vector_an = quiver(0, 0, 0, 0, 0, "linewidth", 2, "MaxHeadSize", 10, "color", [1 0 0]);
vector_notes = text([0 0 0], [0 0 0], ["v" sprintf("a_t") sprintf("a_n")]);

subplot(1, 2, 2);
title("Acceleration Magnitude Over Time");
xlabel("Time (s)");
ylabel(sprintf("Acceleration Magnitude (m/s^2)"));
[left, right, bottom, top] = autofit(t, a_length, t_start, t_end);
xlim([left, right]);
ylim([bottom, top]);
hold on;
grid on;
fplot(a_length, [t_start t_end]);

magnitude = subs(a_length, t);
plot([t t], [0 magnitude], "-.");
text(t - 0.1, magnitude + 0.4, string(double(magnitude)));

projection_line = plot([0 0], [0 0], "--");
projection_note = text(0, 0, "");

while ishandle(fig)
    for step = t_start:0.1:t_end
        if ~ishandle(fig)
            break;
        end
        location = double(subs(r, step));
        velocity = double(subs(v, step));
        acceleration = double(subs(a_length, step));
        tangential = double(subs(a_t, step));
        normal = double(subs(a_n, step));
        [root.XData, vector_v.XData, vector_at.XData, vector_an.XData] = deal(location(1));
        [root.YData, vector_v.YData, vector_at.YData, vector_an.YData] = deal(location(2));
        vector_v.UData = velocity(1);
        vector_v.VData = velocity(2);
        vector_at.UData = tangential(1);
        vector_at.VData = tangential(2);
        vector_an.UData = normal(1);
        vector_an.VData = normal(2);

        vector_notes(1).Position = location + velocity * (1 + 0.4 / norm(velocity));
        vector_notes(2).Position = location + tangential * (1 + 0.4 / norm(tangential));
        vector_notes(3).Position = location + normal * (1 + 0.4 / norm(normal));

        projection_line.XData = [step step];
        projection_line.YData = [0 acceleration];
        projection_note.Position = [step - 0.1, acceleration + 0.4];
        set(projection_note, "String", string(double(acceleration)))
        
        pause(0.02);
    end
end

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
