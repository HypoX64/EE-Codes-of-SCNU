--@By Hypo 20170520
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY test IS
	PORT(
	   key1,key2,key3,key4,key5,key6: IN STD_LOGIC;--按键输入
	   sysclk: IN STD_LOGIC;--时钟输入
		led_c_r,led_c_y,led_c_g,led_p_r,led_p_g: OUT STD_LOGIC;--led输出
		seg7data:	OUT STD_LOGIC_VECTOR(7 DOWNTO 0);--数码管位选
		seg7com: OUT STD_LOGIC_VECTOR(3 DOWNTO 0)	--数码管段选
		);
END test;

ARCHITECTURE example OF test IS

	
	COMPONENT seg7led IS  ----------------------数码管
		PORT (
			int_in: 		IN INTEGER  RANGE 0 TO 16;
			data_out:	OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
		);
	END COMPONENT seg7led;
	
	
	COMPONENT clkdiv IS---------------------------------分频器
       PORT( clk_in:IN STD_LOGIC;     --时钟信号输入
				 clk_out_ms:OUT STD_LOGIC;  --毫秒信号输出
             clk_out_s:OUT STD_LOGIC;  --秒信号输出 
				 clk_out_min:OUT STD_LOGIC;  --分钟信号输出
             clk_out_h:OUT STD_LOGIC;  --时钟信号输出 
				 clk_out_50ms : OUT STD_LOGIC
            );  
	END COMPONENT clkdiv;

	------------------------------------------------数码管扫描
	SIGNAL tmp_seg7data :integer range 0 to 16;
	SIGNAL data_count_seg:integer range 0 to 10;
	
	------------------------------------分频器输出
	SIGNAL tmp_sig_s,tmp_sig_ms,tmp_sig_min,tmp_sig_h,tmp_sig_50ms :STD_LOGIC;--分频器输出时钟信号
	
	--------------------------------------------------24小时时钟
	SIGNAL data_min_low:integer range 0 to 20;
	SIGNAL data_min_high:integer range 0 to 10;
	SIGNAL data_min:integer range 0 to 100;
	SIGNAL data_h_low:integer range 0 to 20;
	SIGNAL data_h_high:integer range 0 to 10;
	SIGNAL data_h:integer range 0 to 100;
	
	------------------------------------------------数码管显示模式切换
	SIGNAL data_mode: integer range 0 to 10:=0;
	SIGNAL data_count_key:integer range 0 to 100;
	
	----------------------------------------------交通灯主控程序
	SIGNAL led_p :integer range 0 to 3;--车道灯
	SIGNAL led_c :integer range 0 to 3:=1;--人行道灯
	SIGNAL key_flag :integer range 0 to 1:=0;
	SIGNAL data_time_count:integer range 0 to 1000;--时间计数
	SIGNAL data_mode_led: integer range 0 to 10:=0;--红绿灯剩余时间显示
	
	-----------------------------------------------------------夜间模式初始化设置
	SIGNAL data_time_nightin: integer range 0 to 100:=22;
	SIGNAL data_time_nightout: integer range 0 to 100:=8;
	SIGNAL night :STD_LOGIC:='0';
	
	-----------------------------------------------------------红绿灯时间设置
	SIGNAL data_time_cp : integer range 0 to 100:=30;--车通行30秒
	SIGNAL data_time_pp : integer range 0 to 100:=15;--人通行15秒
	
BEGIN
	
	div: clkdiv PORT MAP (    ------------分频器
				clk_in 	=> sysclk,
				clk_out_s => tmp_sig_s,
				clk_out_ms => tmp_sig_ms,
				clk_out_min => tmp_sig_min,
				clk_out_h => tmp_sig_h,
				clk_out_50ms => tmp_sig_50ms);
			
	dis: seg7led PORT MAP (   ---------------数码管
				int_in 	=> tmp_seg7data,
				data_out => seg7data
			);
	


---------------------------------------------------------------------------------------------------------

	process(sysclk,key5)     ------按键5消抖+数码管模式选择（s6）
	variable COUNT1 :integer range 0 to 1000000; 
	begin 
	if key5='0' then 
		if RISING_EDGE(sysclk) then
			if COUNT1<1000000 then 
			COUNT1:=COUNT1+1; 
			else COUNT1:=COUNT1;
			end if; 
			if COUNT1=999999 then 
			data_mode <= data_mode+1;
			else data_mode <= data_mode; 
			end if; 
		end if; 
	else COUNT1:=0;
	END if; 
	if(data_mode = 4)then
	data_mode <= 0;
	end if;
	end process ;
	
-----------------------------------------------------------------------------------------------------------
	
	process(sysclk)  --------按键1 2 3 4消抖+改变设定时间(s2 s3 s4 s5)
	variable COUNT1 :integer range 0 to 1000000; 
	begin
	if key1='0' or key2='0' or key3='0' or key4='0' then 
		if rising_edge(sysclk) then
			if COUNT1<1000000 then 
			COUNT1:=COUNT1+1; 
			else COUNT1:=COUNT1;
			end if; 
			if COUNT1=999999 then 
			   if(key1='0')then
					if(data_mode = 2)then
					data_time_cp <= data_time_cp+1;
					elsif(data_mode =3)then
					data_time_nightout <= data_time_nightout+1;
					end if;
				end if;
			   if(key2='0')then
					if(data_mode = 2)then
					data_time_cp <= data_time_cp-1;
					elsif(data_mode =3)then
					data_time_nightout <= data_time_nightout-1;
					end if;
				end if;	
				if(key3='0')then
					if(data_mode = 2)then
					data_time_pp <= data_time_pp+1;
					elsif(data_mode =3)then
					data_time_nightin <= data_time_nightin+1;
					end if;
				end if;
				 if(key4='0')then
					if(data_mode = 2)then
					data_time_pp <= data_time_pp-1;
					elsif(data_mode =3)then
					data_time_nightin <= data_time_nightin-1;
					end if;
				end if;		
			end if; 
		end if; 
	else COUNT1:=0;
	end if; 	
	end process;
	
----------------------------------------------------------------------------------------------------------

	process(sysclk)                     ---红绿灯点亮定义
	begin
	if(led_c = 0)then
	led_c_r <= '1';
	led_c_g <='0';
	led_c_y <='0';
	elsif(led_c = 1)then
	led_c_r <='0';
	led_c_g <='1';
	led_c_y <='0';
	else
	led_c_r <='0';
	led_c_g <='0';
	led_c_y <='1';
	end if;
	if(led_p = 0)then
	led_p_r <= '1';
	led_p_g <= '0';
	else
	led_p_r <= '0';
	led_p_g <= '1';
	end if;	
	end process;

-------------------------------------------------------------------------------------------------------------

	process(sysclk)                     ---红绿灯主控程序
	begin
	if rising_edge(tmp_sig_s)then
	data_time_count<=data_time_count+1;
		if(night='1')then-----------黑夜模式
			if(key_flag=1)then
				if(data_time_count=data_time_cp)then
				led_p <=0;   --进入黄灯
				led_c <=2;
				data_mode_led <=3;
				end if;
				if(data_time_count=(data_time_cp+3))then
				led_p <=1;   --行人通行
				led_c <=0;
				data_mode_led <=2;
				end if;
				if(data_time_count=(data_time_cp+3+data_time_pp))then
				led_p <=0;   --车通行
				led_c <=1;
				key_flag <=0;
				data_time_count <=0;
				data_mode_led <= 0;
				end if;	
			else 
			led_p <=0;
			led_c <=1;	
			data_mode_led <= 0;
			end if;	
		end if;
		
		if(night='0')then-------------白天模式
			if(data_time_count =data_time_cp)then
			led_p <=0;    --进入黄灯
			led_c <=2;
			data_mode_led <=3;
			end if;
			if(data_time_count = (data_time_cp+3))then
			led_p <=1;   --行人通行
			led_c <=0;
			data_mode_led <=2;
			end if;
			if(data_time_count >=(data_time_cp+3+data_time_pp) )then
			led_p <=0;   --车通行
			led_c <=1;
			data_time_count <=0;	
			data_mode_led <=1;	
			end if;			
		end if;		
	end if;
	
	if(key6='0' and key_flag = 0)then
	data_time_count <= 0;
	data_mode_led <=1;
	end if;
	
	if(key6='0')then
	key_flag <=1;
	end if;
	
	end process;
	
--------------------------------------------------------------------------------------------------------------	

   process(tmp_sig_ms,data_count_seg)  ---数码管扫描计时
	begin
	if rising_edge(tmp_sig_ms) then
	data_count_seg <= data_count_seg+1;
		if(data_count_seg = 4) then
		data_count_seg <= 0;
		end if;
	end if;
	end process;
	
-----------------------------------------------------------------------------------------------------------------	

	process(sysclk)	--数码管扫描各模式显示样式	
	begin
	if(data_mode = 0)then------------------------------------------模式0，时钟显示
		if(data_count_seg = 0)then
		seg7com <="0111";
		tmp_seg7data <= data_min_low;
		elsif (data_count_seg = 1)then
		seg7com <="1011";
		tmp_seg7data <= data_min_high;
		elsif (data_count_seg = 2)then
		seg7com <="1101";
		tmp_seg7data <= data_h_low;
		else
		seg7com <="1110";
		tmp_seg7data <= data_h_high;
		end if;
	elsif(data_mode = 1)then----------------------------------------模式1，红绿灯剩余时间显示
		if(data_mode_led = 0)then--------夜间模式一直车走
			if(data_count_seg = 0)then
			seg7com <="0111";
			tmp_seg7data <= 16;        
			elsif (data_count_seg = 1)then
			seg7com <="1011";
			tmp_seg7data <= 16;
			elsif (data_count_seg = 2)then
			seg7com <="1101";
			tmp_seg7data <= 16;        
			else
			seg7com <="1110";
			tmp_seg7data <= 16;   
			end if;
		elsif(data_mode_led = 1)then----车通行剩余时间
			if(data_count_seg = 0)then
			seg7com <="0111";
			tmp_seg7data <= (data_time_cp - data_time_count)rem 10;        
			elsif (data_count_seg = 1)then
			seg7com <="1011";
			tmp_seg7data <= (data_time_cp - data_time_count)/ 10;
			elsif (data_count_seg = 2)then
			seg7com <="1101";
			tmp_seg7data <= 16;        
			else
			seg7com <="1110";
			tmp_seg7data <= 16;   
			end if;
		elsif(data_mode_led = 2)then----人通行剩余时间
			if(data_count_seg = 0)then
			seg7com <="0111";
			tmp_seg7data <= ((data_time_cp+3+data_time_pp) - data_time_count)rem 10;        
			elsif (data_count_seg = 1)then
			seg7com <="1011";
			tmp_seg7data <= ((data_time_cp+3+data_time_pp) - data_time_count)/ 10;
			elsif (data_count_seg = 2)then
			seg7com <="1101";
			tmp_seg7data <= 16;        
			else
			seg7com <="1110";
			tmp_seg7data <= 16;
			end if;
		else                        ----黄灯
			if(data_count_seg = 0)then
			seg7com <="0111";
			tmp_seg7data <= 0;        
			elsif (data_count_seg = 1)then
			seg7com <="1011";
			tmp_seg7data <= 0;
			elsif (data_count_seg = 2)then
			seg7com <="1101";
			tmp_seg7data <= 16;        
			else
			seg7com <="1110";
			tmp_seg7data <= 16;		
			end if;
		end if;
	elsif(data_mode = 2)then-------------------------------------模式2，红绿灯时间显示
		if(data_count_seg = 0)then
		seg7com <="0111";
		tmp_seg7data <= data_time_pp rem 10;        
		elsif (data_count_seg = 1)then
		seg7com <="1011";
		tmp_seg7data <= data_time_pp / 10;    
		elsif (data_count_seg = 2)then
		seg7com <="1101";
		tmp_seg7data <= data_time_cp rem 10;        
		else
		seg7com <="1110";
		tmp_seg7data <= data_time_cp /10;   
	   end if;
	else
		if(data_count_seg = 0)then----------------------------------------模式3，白天黑夜显示
		seg7com <="0111";
		tmp_seg7data <= data_time_nightin rem 10;  
		elsif (data_count_seg = 1)then
		seg7com <="1011";
		tmp_seg7data <= data_time_nightin / 10; 
		elsif (data_count_seg = 2)then
		seg7com <="1101";
		tmp_seg7data <= data_time_nightout rem 10;  
		else
		seg7com <="1110";
		tmp_seg7data <= data_time_nightout / 10; 
		end if;
	end if;
	end process;
	
	
------------------------------------------------------------------------------------------------------------------
	
	process(sysclk)  --24小时时钟计数
   begin
   if rising_edge(tmp_sig_min) then
	data_min_low<=data_min_low+1;
		if(data_min_low = 9)then
		data_min_low <=0;
		data_min_high<=data_min_high+1;
			if(data_min_high = 5)then
			data_min_low <=0;
			data_min_high <=0;
			data_h_low <= data_h_low+1;
			data_h <= data_h+1;
				if(data_h_low = 9 )then
				data_min_low <=0;
				data_min_high <=0;
				data_h_low <=0;
				data_h_high <=data_h_high+1;
				end if;
			end if;
	   end if;
   end if;
	if(data_h = 24)then
	data_min_low <=0;
	data_min_high <=0;
	data_h_low <=0;
	data_h_high <=0;
	data_h <= 0;
	end if;
	if(data_h >= data_time_nightin or data_h <data_time_nightout)then 
	night <='1';
	else
	night <='0';
	end if;
	end process;
	
--------------------------------------------------------------------------------------------------------------	
			
END example;
