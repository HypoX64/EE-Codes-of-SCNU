 function [X,magX,angX] = sigFourierTran(x,n,dot)
    % 计算离散序列的付立叶变换
    % [X,magX,angX] = FourierTran(x,n)
    % 或[X,magX,angX] = FourierTran(x,n,dot)
    if nargin< 3   % nargin是输入变量的个数
        dot=600;
    end
    k=-dot:dot;
    w=(pi/dot)*k; 
    X=x*(exp(-j).^(n'*w));%做傅里叶变换
    magX=abs(X);
    angX=angle(X);
    subplot(211);
    plot(w/pi,magX);
    xlabel('频率(单位{\pi})');ylabel('|X(e^{ j\omega})|');
    title('幅频特性');
    subplot(212);
    plot(w/pi,angX/pi);
    xlabel('频率(单位{\pi})');ylabel('弧度/{\pi}');
    title('相频特性'); 
