function [y,n] = sigshift(x,m,n0) %��x(n0)����ƽ��m����λ�õ�y(n)
    % ʵ�� y(n) = x(n-n0)
    % [y,n] = sigshift(x,m,n0)
n = m+n0; y = x;
