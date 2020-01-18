n=1;
f1=100; f2=300;
fs=1000;%采样频率?
t=0:1/fs:n;
fre=10;
y1=square(2*fre*pi*t)/2;
y2=square(2*fre*pi*t)/2;
dt=1/fs;%定义时间步长?
n1=length(t);%样点个数?
f_end=1/dt;%频率轴的显示范围?
f=(0:n1-1)*f_end/n1-f_end/2;%频率自变量?
Xf1=dt*fftshift(fft(y1));%频谱?
Xf2=dt*fftshift(fft(y2));
figure(1);
subplot(211);plot(t,y1);xlabel('t');title('基带信号时域图');
subplot(212);plot(f,abs(Xf1));xlabel('f');title('基带信号频谱');

z1=1*sin(2*pi*f1*t);
z2=1*sin(2*pi*f2*t);
figure(2);
subplot(221);plot(t,z1);xlabel('t');title('100Hz正弦波时域图');
subplot(222);plot(f,abs(dt*fftshift(fft(z1))));xlabel('f');title('100Hz正弦波幅度频谱');
subplot(223);plot(t,z2);xlabel('t');title('300Hz正弦波时域图');
subplot(224);plot(f,abs(dt*fftshift(fft(z2))));xlabel('f');title('300Hz正弦波幅度频谱');

yy1=y1.*z1;%信号相乘?
yy2=y2.*z2;
yy3=yy1+yy2;

Xf3=dt*fftshift(fft(yy1));
figure(3);
subplot(411);plot(t,yy1);xlabel('t');title('调制信号1时域');
subplot(412);plot(f,abs(Xf3));xlabel('f');title('调制信号1频谱');

Xf4=dt*fftshift(fft(yy2));
figure(3);
subplot(413);plot(t,yy2);xlabel('t');title('调制信号2时域');
subplot(414);plot(f,abs(Xf4));xlabel('f');title('调制信号2频谱');

Xf5=dt*fftshift(fft(yy3));
figure(4);
subplot(211);plot(t,yy3);xlabel('t');title('调制信号1+2时域');
subplot(212);plot(f,abs(Xf5));xlabel('f');title('调制信号1+2频谱');

fp1=50;fp2=150;%FIR滤波器100Hz?
fs1=0;fs2=200;
As=15;
Ws1=(fp1+fs1)/fs; Ws2=(fp2+fs2)/fs;
w=(fp1-fs1)/fs;
M=ceil((As-7.95)/(14.36*w));
H=hamming(M+1);
b=fir1(M,[Ws1,Ws2],H);
% figure(5);
% freqz(b,1,fs,fs);title('FIR滤波器50-150Hz');

t=0:1/fs:n;
yyy1=filter(b,2,yy3);%信号1+2经过滤波器1?
% zz1=filter(b,2,z1);%100Hz正弦波经过滤波器1
Xf10=dt*fftshift(fft(yyy1)); Xf11=dt*fftshift(fft(zz1));
figure(7);
subplot(411);plot(t,yyy1);xlabel('t');title('信号1+2经滤波器1后时域图');
subplot(412);plot(f,abs(Xf10));xlabel('f');title('信号1+2经滤波器1后频谱');
% figure(8);
% subplot(212);plot(f,abs(zz1));xlabel('f');title('100Hz正弦波滤波器1后频谱');
% subplot(212);plot(f,abs(zz1));xlabel('f');title('100Hz正弦波滤波器1后频谱');

fp1=250;fp2=350;%FIR滤波器300Hz?
fs1=200;fs2=400;
As=15;
Ws1=(fp1+fs1)/fs; Ws2=(fp2+fs2)/fs;
w=(fp1-fs1)/fs;
M=ceil((As-7.95)/(14.36*w));
H2=hamming(M+1);
b=fir1(M,[Ws1,Ws2],H2);
% figure(9);
% freqz(b,1,fs,fs);title('FIR滤波器250-350Hz');

t=0:1/fs:n;
yyy2=filter(b,2,yy3);
% zz2=filter(b,2,z2);
Xf12=dt*fftshift(fft(yyy2));
Xf13=dt*fftshift(fft(zz2));
figure(7);
subplot(413);plot(t,yyy2);xlabel('t');title('信号1+2经滤波器2后时域图');
subplot(414);plot(f,abs(Xf12));xlabel('f');title('信号1+2经滤波器2后频谱');
% figure(11);
% subplot(211);plot(t,zz2);xlabel('t');title('300Hz正弦波滤波器2后时域图');
% subplot(212);plot(f,abs(zz2));xlabel('f');title('300Hz正弦波滤波器2后频谱');

k1=yyy1.*z1;%解调?
k2=yyy2.*z2;
% figure(12);
% subplot(211);plot(t,k1);xlabel('t');title('解调信号1时域图');
% subplot(212);plot(f,abs(dt*fftshift(fft(k1))));xlabel('f');title('解调信号1频谱');
% figure(13);
% subplot(211);plot(t,k2);xlabel('t');title('解调信号2时域图');
% subplot(212);plot(f,abs(dt*fftshift(fft(k2))));xlabel('f');title('解调信号2频谱');

N=8;%8阶巴特沃斯低通滤波器上限频率100Hz?
Wn=100/(fs/2);
[b,a]=butter(N,Wn,'low');

kk1=filter(b,a,k1);
kk2=filter(b,a,k2);
% figure(14);
[H,W]=freqz(b,a);%返回频率响应
% subplot(211);plot(W*fs/(2*pi),abs(H));xlabel('频率Hz');ylabel('幅值');
% grid on;
% subplot(212);plot(W*fs/(2*pi),20*log10(abs(H)));xlabel('频率Hz');ylabel('幅值dB');
% grid on;

Xf6=dt*fftshift(fft(kk1));
Xf7=dt*fftshift(fft(kk2));
figure(15);
subplot(211);plot(t,kk1);xlabel('t');title('解调信号1经滤波时域');
subplot(212);plot(f,abs(Xf6));xlabel('f');title('解调信号1经滤波频谱');
figure(16);
subplot(211);plot(t,kk2);xlabel('t');title('解调信号2经滤波时域');
subplot(212);plot(f,abs(Xf7));xlabel('f');title('解调信号2经滤波频谱');