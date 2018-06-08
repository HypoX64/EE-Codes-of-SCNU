 function [X,magX,angX] = sigFourierTran(x,n,dot)
    % ������ɢ���еĸ���Ҷ�任
    % [X,magX,angX] = FourierTran(x,n)
    % ��[X,magX,angX] = FourierTran(x,n,dot)
    if nargin< 3   % nargin����������ĸ���
        dot=600;
    end
    k=-dot:dot;
    w=(pi/dot)*k; 
    X=x*(exp(-j).^(n'*w));%������Ҷ�任
    magX=abs(X);
    angX=angle(X);
    subplot(211);
    plot(w/pi,magX);
    xlabel('Ƶ��(��λ{\pi})');ylabel('|X(e^{ j\omega})|');
    title('��Ƶ����');
    subplot(212);
    plot(w/pi,angX/pi);
    xlabel('Ƶ��(��λ{\pi})');ylabel('����/{\pi}');
    title('��Ƶ����'); 
