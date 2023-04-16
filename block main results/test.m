clearvars; clc;

tab = readtable("data.csv");
t = tab.t;
x = tab.x;
y = tab.y;
z = tab.z;

figure
hold on
grid on
view(20, 30)
axis([-200 200 -200 200 -200 200])

for i=1:size(t,1)
    plot3(x(i), y(i), z(i), '.b')
    drawnow
end


