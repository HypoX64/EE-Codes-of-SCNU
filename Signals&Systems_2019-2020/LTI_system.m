a=[1, 2*10^3, 2*10^9];  %΢�ַ������ϵ��
b=[2*10^9];  %΢�ַ����Ҳ�ϵ��
sys=tf(b, a);  %����ϵͳ����
t=[0:0.00001:0.008];  %�������ʱ��
%e1=1.*dirac(t-0);
e1=(t==0).*1;
f1=lsim(sys, e1, t);  %��e1����sys, ���Ϊf1
e2=1.*heaviside(t);
f2=lsim(sys, e2, t);  %��e2����sys, ���Ϊf2
figure;
subplot(1, 2, 1);
hold on, box on;
%set(gca, 'YScale', 'log');
set(gca, 'FontSize', 16);
plot(t, e1, 'k-', t, e2, 'k-.');
legend('e_1', 'e_2');
xlabel('time/s');
ylabel('input');

subplot(1, 2, 2);
hold on, box on;
%set(gca, 'YScale', 'log');
set(gca, 'FontSize', 16);
plot(t, f1, 'k-', t, f2, 'k-.');
legend('f_1', 'f_2');
xlabel('time/s');
ylabel('output');