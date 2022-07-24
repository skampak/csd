a=[1 -1.25*(exp(j*pi/4))];
b=[1 -1.25*(exp(-j*pi/4))];

c=[1 -0.97*(exp(j*3*pi/4))];
d=[1 1 -0.97*(exp(-j*3*pi/4))];

num=conv(a,b);
denom=conv(c,d);
pezw2(num,denom);

