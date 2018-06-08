function [x,n] = stepseq(n0,n1,n2)
    % 产生 x(n) = u(n-n0);
    %n1 <= n0 <= n2
    % [x,n] = stepseq(n0,n1,n2)
    if ((n0 < n1) | (n0 > n2) | (n1 > n2))
        error('参数必须满足 n1 <= n0 <= n2')
    end
    n = [n1:n2];
    %x = [zeros(1,(n0-n1)), ones(1,(n2-n0+1))];
x = [(n-n0) >= 0]; 
