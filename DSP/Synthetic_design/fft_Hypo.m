 function  [k,xk]=fft_Hypo(fs,N,data) %FFT��������ȥֱ������
 data=data-mean(data);
 data_fft=fft(data,N);%fft�任
 k=((1:N/2)-1)*fs/N;
 xk=abs(data_fft(1:N/2));