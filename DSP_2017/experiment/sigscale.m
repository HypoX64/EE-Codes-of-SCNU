function [y,n] = sigscale(x,n,m)%y(n)=x(mn)  ��������Сn��  ʹ��������m>0
n1=n/m;
n2=find(n1==fix(n1));
n3=n1(n2);%�ҵ��任���n
x3=x(n2);%�ҵ��任���x
y=x3;n=n3;