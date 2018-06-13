%阶跃响应
xlabel('t--sec'), ylabel('c(t)');
num=[1 0 0];
den=[1 4.443e+06 9.87e+12];
t=0:1e-7:1e-5;
c=step(num,den,t);
plot(t,c); grid;
xlabel('t--sec'), ylabel('c(t)');

%冲激响应
xlabel('t--sec'), ylabel('c(t)');
num=[1 0 0];
den=[1 4.443e+06 9.87e+12];
t=0:1e-7:1e-5;
c=-impulse(num,den,t);
plot(t,c); grid;
xlabel('t--sec'), ylabel('c(t)');

%幅频特性
bode(tf([1 0 0],[1 4.7e+6 1e+13]))
