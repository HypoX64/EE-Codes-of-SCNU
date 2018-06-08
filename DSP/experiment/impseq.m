 function [x,n] = impseq(n0,n1,n2)
 %产生x(n)=ε(n-n0) 时域范围n1 n2
    % 产生 x(n) = delta(n-n0); n1 <= n,n0 <= n2
    % [x,n] = impseq(n0,n1,n2)
    if ((n0 < n1) | (n0 > n2) | (n1 > n2))
        error('参数必须满足 n1 <= n0 <= n4')
    end
    n = [n1:n2];
    %x = [zeros(1,(n0-n1)), 1, zeros(1,(n2-n0))];
x = [(n-n0) == 0]; 
