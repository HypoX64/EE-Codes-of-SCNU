function [y,n] = sigfold(x,n)
    % ʵ�� y(n) = x(-n)
    % [y,n] = sigfold(x,n)
    y = fliplr(x); n = -fliplr(n); 
