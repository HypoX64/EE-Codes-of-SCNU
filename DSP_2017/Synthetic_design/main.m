 function  homework(fs, N) %fs=1000;N=200       homework(1000,400) 
 
n=0:N-1;
t=n/fs;
figure(1);
base1=0.5*square(2*pi*10*t)+0.3;subplot(3,4,1);plot(t,base1);title('����1(10HZ����)')
carrier1=sin(2*pi*100*t);subplot(3,4,2);plot(t,carrier1);title('�ز�1(100HZ���Ҳ�)')
mix1=base1.*carrier1;subplot(3,4,3);plot(t,mix1);title('����1���ƽ��')

%base2=sawtooth(2*pi*10*t,0.5)+1;subplot(3,4,5);plot(t,base2);title('����10HZ���ǲ�')
base2=0.5*square(2*pi*10*t)+0.3;subplot(3,4,5);plot(t,base2);title('����2��10HZ������')
carrier2=sin(2*pi*300*t);subplot(3,4,6);plot(t,carrier2);title('�ز�2��300HZ���Ҳ���')
mix2=base2.*carrier2;subplot(3,4,7);plot(t,mix2);title('����2���ƽ��')

mix3=mix1+mix2;subplot(3,4,8);plot(t,mix3);title('�����źŵ��ӽ��')

bandpass1=filter(filter_IIR_Butter(fs,4,50,150),mix3);subplot(3,4,9);plot(t,bandpass1);title('50~150HZ��ͨ�˲�');%IIR��ʽ��ͨ�˲�
%bandpass1=filter(filter_FIR_ButterBPF(fs,10,50,150,200),mix3);subplot(3,4,9);plot(t,bandpass1);title('50~150HZ��ͨ�˲�');%FIR��ʽ��ͨ�˲�
demod1=bandpass1.*carrier1;%��ɽ��
final1=filter(filter_butterLPF(fs,12,100),demod1);subplot(3,4,10);plot(t,final1);title('100HZ��ͨ&����ź�1�����ս����');

bandpass2=filter(filter_IIR_Butter(fs,4,250,350),mix3);subplot(3,4,11);plot(t,bandpass2);title('250~350HZ��ͨ�˲�');%IIR��ʽ��ͨ�˲�
%bandpass2=filter(filter_FIR_ButterBPF(fs,150,220,380,450),mix3);subplot(3,4,11);plot(t,bandpass2);title('220~380HZ��ͨ�˲�');%FIR��ʽ��ͨ�˲�
demod2=bandpass2.*carrier2;%��ɽ��
final2=filter(filter_butterLPF(fs,12,100),demod2);subplot(3,4,12);plot(t,final2);title('100HZ��ͨ&����ź�2�����ս����');

figure(2);
[k,xk]=fft_Hypo(fs,N,base1);subplot(2,2,1);stem(k,xk);title('����1Ƶ��ͼ(10HZ����)');
[k,xk]=fft_Hypo(fs,N,final1);subplot(2,2,2);stem(k,xk);title('����ź�1Ƶ��ͼ(10HZ����)');
[k,xk]=fft_Hypo(fs,N,base2);subplot(2,2,3);stem(k,xk);title('����2Ƶ��ͼ(10HZ����)');
[k,xk]=fft_Hypo(fs,N,final2);subplot(2,2,4);stem(k,xk);title('����2Ƶ��ͼ(10HZ����)');
figure(3);
[k,xk]=fft_Hypo(fs,N,mix1);subplot(2,3,1);stem(k,xk);title('����1���ƽ��Ƶ��ͼ');
[k,xk]=fft_Hypo(fs,N,mix2);subplot(2,3,2);stem(k,xk);title('����2���ƽ��Ƶ��ͼ');
[k,xk]=fft_Hypo(fs,N,mix3);subplot(2,3,3);stem(k,xk);title('���ӽ��Ƶ��ͼ');
[k,xk]=fft_Hypo(fs,N,bandpass1);subplot(2,3,4);stem(k,xk);title('50~150HZ��ͨ�˲�Ƶ��ͼ');
[k,xk]=fft_Hypo(fs,N,bandpass2);subplot(2,3,5);stem(k,xk);title('220~380HZ��ͨ�˲�Ƶ��ͼ');
[k,xk]=fft_Hypo(fs,N,base1);subplot(2,3,6);stem(k,xk);title('����');
figure(4);
[k,xk]=fft_Hypo(fs,N,demod1);subplot(1,2,1);stem(k,xk);title('�ź�1����ɽ���󣬵�ͨǰ');
[k,xk]=fft_Hypo(fs,N,demod2);subplot(1,2,2);stem(k,xk);title('�ź�2����ɽ���󣬵�ͨǰ');
%figure(5);
%[k,xk]=fft_Hypo(fs,N,carrier1);stem(k,xk);title('����');
%fvtool(filter_FIR_ButterBPF(fs,50,80,120,150));
%fvtool(filter_FIR_ButterBPF(fs,250,280,320,350));
%fvtool(filter_butterLPF(fs,10,100));
