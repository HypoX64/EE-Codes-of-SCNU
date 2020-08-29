n=1;
f1=100; f2=300;
fs=1000;%����Ƶ��?
t=0:1/fs:n;
fre=10;
y1=square(2*fre*pi*t)/2;
y2=square(2*fre*pi*t)/2;
dt=1/fs;%����ʱ�䲽��?
n1=length(t);%�������?
f_end=1/dt;%Ƶ�������ʾ��Χ?
f=(0:n1-1)*f_end/n1-f_end/2;%Ƶ���Ա���?
Xf1=dt*fftshift(fft(y1));%Ƶ��?
Xf2=dt*fftshift(fft(y2));
figure(1);
subplot(211);plot(t,y1);xlabel('t');title('�����ź�ʱ��ͼ');
subplot(212);plot(f,abs(Xf1));xlabel('f');title('�����ź�Ƶ��');

z1=1*sin(2*pi*f1*t);
z2=1*sin(2*pi*f2*t);
figure(2);
subplot(221);plot(t,z1);xlabel('t');title('100Hz���Ҳ�ʱ��ͼ');
subplot(222);plot(f,abs(dt*fftshift(fft(z1))));xlabel('f');title('100Hz���Ҳ�����Ƶ��');
subplot(223);plot(t,z2);xlabel('t');title('300Hz���Ҳ�ʱ��ͼ');
subplot(224);plot(f,abs(dt*fftshift(fft(z2))));xlabel('f');title('300Hz���Ҳ�����Ƶ��');

yy1=y1.*z1;%�ź����?
yy2=y2.*z2;
yy3=yy1+yy2;

Xf3=dt*fftshift(fft(yy1));
figure(3);
subplot(411);plot(t,yy1);xlabel('t');title('�����ź�1ʱ��');
subplot(412);plot(f,abs(Xf3));xlabel('f');title('�����ź�1Ƶ��');

Xf4=dt*fftshift(fft(yy2));
figure(3);
subplot(413);plot(t,yy2);xlabel('t');title('�����ź�2ʱ��');
subplot(414);plot(f,abs(Xf4));xlabel('f');title('�����ź�2Ƶ��');

Xf5=dt*fftshift(fft(yy3));
figure(4);
subplot(211);plot(t,yy3);xlabel('t');title('�����ź�1+2ʱ��');
subplot(212);plot(f,abs(Xf5));xlabel('f');title('�����ź�1+2Ƶ��');

fp1=50;fp2=150;%FIR�˲���100Hz?
fs1=0;fs2=200;
As=15;
Ws1=(fp1+fs1)/fs; Ws2=(fp2+fs2)/fs;
w=(fp1-fs1)/fs;
M=ceil((As-7.95)/(14.36*w));
H=hamming(M+1);
b=fir1(M,[Ws1,Ws2],H);
% figure(5);
% freqz(b,1,fs,fs);title('FIR�˲���50-150Hz');

t=0:1/fs:n;
yyy1=filter(b,2,yy3);%�ź�1+2�����˲���1?
% zz1=filter(b,2,z1);%100Hz���Ҳ������˲���1
Xf10=dt*fftshift(fft(yyy1)); Xf11=dt*fftshift(fft(zz1));
figure(7);
subplot(411);plot(t,yyy1);xlabel('t');title('�ź�1+2���˲���1��ʱ��ͼ');
subplot(412);plot(f,abs(Xf10));xlabel('f');title('�ź�1+2���˲���1��Ƶ��');
% figure(8);
% subplot(212);plot(f,abs(zz1));xlabel('f');title('100Hz���Ҳ��˲���1��Ƶ��');
% subplot(212);plot(f,abs(zz1));xlabel('f');title('100Hz���Ҳ��˲���1��Ƶ��');

fp1=250;fp2=350;%FIR�˲���300Hz?
fs1=200;fs2=400;
As=15;
Ws1=(fp1+fs1)/fs; Ws2=(fp2+fs2)/fs;
w=(fp1-fs1)/fs;
M=ceil((As-7.95)/(14.36*w));
H2=hamming(M+1);
b=fir1(M,[Ws1,Ws2],H2);
% figure(9);
% freqz(b,1,fs,fs);title('FIR�˲���250-350Hz');

t=0:1/fs:n;
yyy2=filter(b,2,yy3);
% zz2=filter(b,2,z2);
Xf12=dt*fftshift(fft(yyy2));
Xf13=dt*fftshift(fft(zz2));
figure(7);
subplot(413);plot(t,yyy2);xlabel('t');title('�ź�1+2���˲���2��ʱ��ͼ');
subplot(414);plot(f,abs(Xf12));xlabel('f');title('�ź�1+2���˲���2��Ƶ��');
% figure(11);
% subplot(211);plot(t,zz2);xlabel('t');title('300Hz���Ҳ��˲���2��ʱ��ͼ');
% subplot(212);plot(f,abs(zz2));xlabel('f');title('300Hz���Ҳ��˲���2��Ƶ��');

k1=yyy1.*z1;%���?
k2=yyy2.*z2;
% figure(12);
% subplot(211);plot(t,k1);xlabel('t');title('����ź�1ʱ��ͼ');
% subplot(212);plot(f,abs(dt*fftshift(fft(k1))));xlabel('f');title('����ź�1Ƶ��');
% figure(13);
% subplot(211);plot(t,k2);xlabel('t');title('����ź�2ʱ��ͼ');
% subplot(212);plot(f,abs(dt*fftshift(fft(k2))));xlabel('f');title('����ź�2Ƶ��');

N=8;%8�װ�����˹��ͨ�˲�������Ƶ��100Hz?
Wn=100/(fs/2);
[b,a]=butter(N,Wn,'low');

kk1=filter(b,a,k1);
kk2=filter(b,a,k2);
% figure(14);
[H,W]=freqz(b,a);%����Ƶ����Ӧ
% subplot(211);plot(W*fs/(2*pi),abs(H));xlabel('Ƶ��Hz');ylabel('��ֵ');
% grid on;
% subplot(212);plot(W*fs/(2*pi),20*log10(abs(H)));xlabel('Ƶ��Hz');ylabel('��ֵdB');
% grid on;

Xf6=dt*fftshift(fft(kk1));
Xf7=dt*fftshift(fft(kk2));
figure(15);
subplot(211);plot(t,kk1);xlabel('t');title('����ź�1���˲�ʱ��');
subplot(212);plot(f,abs(Xf6));xlabel('f');title('����ź�1���˲�Ƶ��');
figure(16);
subplot(211);plot(t,kk2);xlabel('t');title('����ź�2���˲�ʱ��');
subplot(212);plot(f,abs(Xf7));xlabel('f');title('����ź�2���˲�Ƶ��');