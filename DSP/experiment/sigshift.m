function [y,n] = sigshift(x,m,n0) %将x(n0)向右平移m个单位得到y(n)
    % 实现 y(n) = x(n-n0)
    % [y,n] = sigshift(x,m,n0)
n = m+n0; y = x;
