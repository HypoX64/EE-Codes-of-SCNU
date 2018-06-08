 function  [k,xk]=fft_Hypo(fs,N,data) %FFT函数，已去直流分量
 data=data-mean(data);
 data_fft=fft(data,N);%fft变换
 k=((1:N/2)-1)*fs/N;
 xk=abs(data_fft(1:N/2));