function [y,n] = sigmult(x1,n1,x2,n2)
    % ʵ�� y(n) = x1(n)*x2(n)
    % [y,n] = sigmult(x1,n1,x2,n2)
    % y = ��n�����ϵĳ˻�����,n ���� n1 �� n2
    % x1 = �� n1�ϵĵ�һ����
    % x2 = �� n2�ϵĵڶ�����(n2���� n1����)
n = min(min(n1),min(n2)):max(max(n1),max(n2)); % y(n)�ĳ���
    y1 = zeros(1,length(n)); y2 = y1;                %��ʼ��
    y1(find((n>=min(n1))&(n<=max(n1))==1))=x1;     % ����y�ĳ��ȵ� x1 
    y2(find((n>=min(n2))&(n<=max(n2))==1))=x2;     % ����y�ĳ��ȵ� x2 
    y = y1 .* y2;                                  % ������� 
