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
END clkdiv;

architecture div of clkdiv is

SIGNAL data_ms:integer range 0 to 1000000;
SIGNAL data_s:integer range 0 to 100000000;
SIGNAL data_min:integer range 0 to 100;
SIGNAL data_h:integer range 0 to 100;
SIGNAL data_50ms:integer range 0 to 10000000;
SIGNAL Q_ms:std_logic;
SIGNAL Q_s:std_logic;
SIGNAL Q_min:std_logic;
SIGNAL Q_h:std_logic;
SIGNAL Q_50ms:std_logic;

BEGIN

PROCESS(clk_in)  --1ms
  BEGIN
   if rising_edge(clk_in) then
    if(data_ms=25000) then --此句为你想要的分频比，in/out=data*2+1 ; data=(in/out  -1)/2
       data_ms<=0;
      Q_ms<=NOT Q_ms;
    else
       data_ms<=data_ms+1;
    end if;
   end if;
clk_out_ms<=Q_ms;
END PROCESS;


PROCESS(clk_in)  --50ms
  BEGIN
   if rising_edge(clk_in) then
    if(data_50ms=1250000) then --此句为你想要的分频比，in/out=data*2+1 ; data=(in/out  -1)/2
       data_50ms<=0;
      Q_50ms<=NOT Q_50ms;
    else
       data_50ms<=data_50ms+1;
    end if;
   end if;
clk_out_50ms<=Q_50ms;
END PROCESS;


PROCESS(clk_in)  --1s
  BEGIN
   if rising_edge(clk_in) then
	if(data_s=2500000) then --data_s=25000000正常  data_s=2500000时1s已经缩短10倍--data_s=250000时1s已经缩短100倍
       data_s<=0;
      Q_s<=NOT Q_s;
    else
       data_s<=data_s+1;
    end if;
   end if;
clk_out_s<=Q_s;
END PROCESS;

PROCESS(Q_s)  --1min
  BEGIN
   if rising_edge(Q_s) then
    if(data_min=30) then --此句为你想要的分频比，in/out=data*2+1 ; data=(in/out  -1)/2
       data_min<=0;
      Q_min<=NOT Q_min;
    else
       data_min<=data_min+1;
    end if;
   end if;
clk_out_min<=Q_min;
END PROCESS;

PROCESS(Q_min)  --1h
  BEGIN
   if rising_edge(Q_min) then
    if(data_h=30) then --此句为你想要的分频比，in/out=data*2+1 ; data=(in/out  -1)/2
       data_h<=0;
      Q_h<=NOT Q_h;
    else
       data_h<=data_h+1;
    end if;
   end if;
clk_out_h<=Q_h;
END PROCESS;




END div;