a2=[1 -1.25*(exp(j*pi/4))];
b2=[1 -1.25*(exp(-j*pi/4))];

c2=[1 -0.97*(exp(j*3*pi/4))];
d2=[1 1 -0.97*(exp(-j*3*pi/4))];

num2=conv(a,b);
denom2=conv(c,d);
pezw2(num2,denom2);