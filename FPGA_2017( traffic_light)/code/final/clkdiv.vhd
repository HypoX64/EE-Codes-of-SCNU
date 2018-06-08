library ieee;
USE ieee.std_logic_1164.all;
ENTITY clkdiv IS
       PORT( clk_in:IN STD_LOGIC;     --时钟信号输入
				 clk_out_ms:OUT STD_LOGIC;  --时钟信号输出
             clk_out_s:OUT STD_LOGIC;   --时钟信号输出 
				 clk_out_min:OUT STD_LOGIC;
				 clk_out_h:OUT STD_LOGIC;
				 clk_out_50ms : OUT STD_LOGIC
				 );  
end clkdiv;

architecture div of clkdiv is

SIGNAL data_ms:integer range 0 to 1000000;
SIGNAL data_s:integer range 0 to 100000000;
SIGNAL data_min:integer range 0 to 100;
SIGNAL data_h:integer range 0 to 100;
SIGNAL data_50ms:integer range 0 to 10000000;
SIGNAL Q_ms,Q_s,Q_min,Q_h,Q_50ms:std_logic;

begin

process(clk_in)  --1ms 系统时钟输入
begin
   if rising_edge(clk_in) then--当检测到时钟信号为上升沿时
		if(data_ms=25000) then --由计数器实现分频的功能， 
		                     --由50M/（25000*2）得到信号翻转周期。
									--修改data_ms的判断值就可以实现不同的分频比
      data_ms<=0;
      Q_ms<=not Q_ms;     --对暂存状态量进行翻转
		else
      data_ms<=data_ms+1;
		end if;
   end if;
clk_out_ms<=Q_ms;        --将暂存量进行输出
end process;


process(clk_in)  --50ms  当前输出为实际时间（最终没有用到）
  begin
   if rising_edge(clk_in) then
    if(data_50ms=1250000) then --此句为你想要的分频比，in/out=data*2+1 ; data=(in/out  -1)/2
       data_50ms<=0;
      Q_50ms<=not Q_50ms;
    else
       data_50ms<=data_50ms+1;
    end if;
   end if;
clk_out_50ms<=Q_50ms;
end process;


process(clk_in)  --1s 已缩短10倍
  begin
   if rising_edge(clk_in) then
	if(data_s=2500000) then --data_s=25000000正常  data_s=2500000时1s已经缩短10倍--data_s=250000时1s已经缩短100倍
       data_s<=0;
      Q_s<=not Q_s;
    else
       data_s<=data_s+1;
    end if;
   end if;
clk_out_s<=Q_s;
end process;

process(Q_ms)  --1min 已缩短1000倍
  begin
   if rising_edge(Q_ms) then
    if(data_min=30) then 
       data_min<=0;
      Q_min<=not Q_min;
    else
       data_min<=data_min+1;
    end if;
   end if;
clk_out_min<=Q_min;
end process;


process(Q_min)  --1h 已经缩短1000倍（最终没有用到）
  begin
   if rising_edge(Q_min) then
    if(data_h=30) then 
       data_h<=0;
      Q_h<=not Q_h;
    else
       data_h<=data_h+1;
    end if;
   end if;
clk_out_h<=Q_h;
end process;

end div;