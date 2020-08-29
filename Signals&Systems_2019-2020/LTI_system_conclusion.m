a=10^3;
w=2*10^9;
w0=w^0.5;
b=(w-(a^2))^0.5;
o=atan(b/a);
t=[0:0.001:0.008];
h=(w/b)*exp(-a.*t).*sin(b.*t);
g=1-((w0/b)*exp(-a.*t).*sin(b.*t+o));
subplot(1, 2, 1);
hold on, box on;
plot(t, h);
title('³å¼¤ÏìÓ¦h(t)');

subplot(1, 2, 2);
hold on, box on;
plot(t, g);
title('½×Ô¾ÏìÓ¦g(t)');