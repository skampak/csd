x1 = cos(pi/4*(0:100)).*hanning(101)';
x2 = cos(2*pi/4*(0:100)).*hanning(101)';
x = [x1 x2 zeros(1,200)];

plot(x);