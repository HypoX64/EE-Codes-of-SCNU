function [y,n] = sigmult(x1,n1,x2,n2)
    % 实现 y(n) = x1(n)*x2(n)
    % [y,n] = sigmult(x1,n1,x2,n2)
    % y = 在n区间上的乘积序列,n 包含 n1 和 n2
    % x1 = 在 n1上的第一序列
    % x2 = 在 n2上的第二序列(n2可与 n1不等)
n = min(min(n1),min(n2)):max(max(n1),max(n2)); % y(n)的长度
    y1 = zeros(1,length(n)); y2 = y1;                %初始化
    y1(find((n>=min(n1))&(n<=max(n1))==1))=x1;     % 具有y的长度的 x1 
    y2(find((n>=min(n2))&(n<=max(n2))==1))=x2;     % 具有y的长度的 x2 
    y = y1 .* y2;                                  % 序列相乘 
