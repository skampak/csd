load Lab4.mat

plot(fr1);
hold on;
fr2=filter(-B,1,fr1);

plot(fr2);
hold on;
fr31=filter(-B,1,fr1);
fr32=fliplr(fr1);
fr33=filter(-B,1,fr32);
fr34=fliplr(fr33);
fr3=(1/2)*(fr31+fr34);


plot(fr3);
hold on;

fr41=filter(-B,1,fr1);
fr42=fliplr(fr41);
fr43=filter(-B,1,fr42);
fr44=fliplr(fr43);


plot(fr44);
hold on;