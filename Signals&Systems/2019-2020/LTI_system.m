a=[1, 2*10^3, 2*10^9];  %微分方程左侧系数
b=[2*10^9];  %微分方程右侧系数
sys=tf(b, a);  %建立系统描述
t=[0:0.00001:0.008];  %定义仿真时间
%e1=1.*dirac(t-0);
e1=(t==0).*1;
f1=lsim(sys, e1, t);  %用e1激励sys, 输出为f1
e2=1.*heaviside(t);
f2=lsim(sys, e2, t);  %用e2激励sys, 输出为f2
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