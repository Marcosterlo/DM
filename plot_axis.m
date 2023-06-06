clc; close all; clear all;

cd /home/marco/Desktop/'Working directory'/DM/;
data = readmatrix("log.txt");

t = data(:,1);
value = data(:,3);
hold on;
plot(t,value);
plot([0 4], [0.5, 0.5], 'r');
axis([0 4, 0, 1]);
hold off;
