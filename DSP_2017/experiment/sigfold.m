function [y,n] = sigfold(x,n)
    % й╣ож y(n) = x(-n)
    % [y,n] = sigfold(x,n)
    y = fliplr(x); n = -fliplr(n); 
