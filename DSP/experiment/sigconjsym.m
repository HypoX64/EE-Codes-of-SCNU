function [y,n] = sigconjsym(x,n,type)%type=0求共轭对称分量，type=1求共轭反对称分量
if(type==0)   %Xf=0.5*(X(n) + X*(-n))
    [x1,n1]=sigfold(conj(x),n);
    [y,n]=sigadd(x,n,x1,n1);
    y=y/2;
end 
if(type==1)   %Xf=0.5*(X(n) - X*(-n))
    [x1,n1]=sigfold(conj(x),n);
    [y,n]=sigadd(x,n,-x1,n1);
    y=y/2;
end 