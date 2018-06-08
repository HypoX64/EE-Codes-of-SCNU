function [y,n] = sigscale(x,n,m)%y(n)=x(mn)  横坐标缩小n倍  使用条件：m>0
n1=n/m;
n2=find(n1==fix(n1));
n3=n1(n2);%找到变换后的n
x3=x(n2);%找到变换后的x
y=x3;n=n3;