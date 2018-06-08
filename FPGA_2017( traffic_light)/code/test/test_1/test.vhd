LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY test IS
	PORT(
	   key1,key2,key3,key4,key5: IN STD_LOGIC;
	   sysclk: IN STD_LOGIC;
		seg7data:	OUT STD_LOGIC_VECTOR(7 downto 0);
		seg7com: OUT STD_LOGIC_VECTOR(3 downto 0)	
		);
END test;

ARCHITECTURE example OF test IS

	
	COMPONENT seg7led IS  -----
		PORT (
			int_in: 		IN INTEGER  RANGE 0 TO 15;
			data_out:	OUT STD_LOGIC_VECTOR(7 downto 0)
		);
	END COMPONENT seg7led;
	
	
	COMPONENT clkdiv IS
       PORT( clk_in:IN STD_LOGIC;     --时钟信号输入
				 clk_out_ms:OUT STD_LOGIC;  --毫秒信号输出
             clk_out_s:OUT STD_LOGIC;  --秒信号输出 
				 clk_out_min:OUT STD_LOGIC;  --分钟信号输出
             clk_out_h:OUT STD_LOGIC;  --时钟信号输出 
				 clk_out_50ms : OUT STD_LOGIC
            );  
	END COMPONENT clkdiv;
	
	
	SIGNAL tmp_seg7data :integer range 0 to 15;
	SIGNAL tmp_sig_s :STD_LOGIC;
	SIGNAL tmp_sig_ms :STD_LOGIC;
	SIGNAL tmp_sig_min :STD_LOGIC;
	SIGNAL tmp_sig_h :STD_LOGIC;
	SIGNAL tmp_sig_50ms :STD_LOGIC;
	SIGNAL night :STD_LOGIC;
   SIGNAL key_signal :STD_LOGIC_VECTOR(7 DOWNTO 0);
	
	SIGNAL data_min_low:integer range 0 to 20;
	SIGNAL data_min_high:integer range 0 to 10;
	SIGNAL data_min:integer range 0 to 100;
	SIGNAL data_h_low:integer range 0 to 20;
	SIGNAL data_h_high:integer range 0 to 10;
	SIGNAL data_h:integer range 0 to 100;
	SIGNAL data_count_seg:integer range 0 to 10;
   
	SIGNAL data_mode: integer range 0 to 10;
	SIGNAL data_count_key:integer range 0 to 100;
	
	
	SIGNAL data_time_nightin_high: integer range 0 to 100:=2;
	SIGNAL data_time_nightin_low: integer range 0 to 100:=2;
	
BEGIN
	
	
	
	div: clkdiv PORT MAP (  ------------分频器
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
	
--------------------------------------------------------------------------------------------------------------	

------------------------------------------------------------------------------
PROCESS(sysclk,key1) ------按键1消抖（s2）
	VARIABLE COUNT1 :INTEGER RANGE 0 TO 1000000; 
	BEGIN 
	IF key1='0' THEN 
		IF RISING_EDGE(sysclk) THEN
			IF COUNT1<1000000 THEN 
			COUNT1:=COUNT1+1; 
	 	ELSE COUNT1:=COUNT1;
		END IF; 
	IF COUNT1=999999 THEN 
		key_signal(2)<='1'; 
		ELSE key_signal(2)<='0'; 
		END IF; 
		END IF; 
	ELSE COUNT1:=0;
	END IF; 
	END PROCESS ;
------------------------------------------------------------------------------
	PROCESS(sysclk,key2) ------按键5消抖(s3)
	VARIABLE COUNT1 :INTEGER RANGE 0 TO 1000000; 
	BEGIN 
	IF key2='0' THEN 
		IF RISING_EDGE(sysclk) THEN
			IF COUNT1<1000000 THEN 
			COUNT1:=COUNT1+1; 
			ELSE COUNT1:=COUNT1;
			END IF; 
		IF COUNT1=999999 THEN 
		key_signal(3)<='1'; 
		ELSE key_signal(3)<='0'; 
		END IF; 
		END IF; 
	ELSE COUNT1:=0;
	END IF; 
	END PROCESS ;



------------------------------------------------------------------------

   process(sysclk) ---模式选择
	begin
   if(key_signal(2)='1')then
	data_mode <= data_mode+1;
	end if;
	if(data_mode = 3)then
	data_mode <= 0;
	end if;
	end process;


-----------------------------------------------------------------------
	--process(sysclk,data_time_nightin_low) ---调整设定的时间
	--begin
	--if(key_signal(3) = '1')then
	--data_time_nightin_low <= data_time_nightin_low+1;
	--end if;
	--end process;



-------------------------------------------------------------------------	
 

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
	
	
	process(data_min_low,data_min_high,data_h_low,data_h_high,tmp_seg7data,data_count_seg)	--数码管扫描显示	
	begin
	if(data_mode = 0)then
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
	elsif(data_mode = 1)then
		if(data_count_seg = 0)then
		seg7com <="0111";
		tmp_seg7data <= 5;
		elsif (data_count_seg = 1)then
		seg7com <="1011";
		tmp_seg7data <= 1;
		elsif (data_count_seg = 2)then
		seg7com <="1101";
		tmp_seg7data <= 5;
		else
		seg7com <="1110";
		tmp_seg7data <= 4;
	   end if;
	else
		if(data_count_seg = 0)then
		seg7com <="0111";
		tmp_seg7data <= 8;
		elsif (data_count_seg = 1)then
		seg7com <="1011";
		tmp_seg7data <= 0;
		elsif (data_count_seg = 2)then
		seg7com <="1101";
		tmp_seg7data <= data_time_nightin_low;
		else
		seg7com <="1110";
		tmp_seg7data <= data_time_nightin_high;
		end if;
	end if;
	end process;
	
	
------------------------------------------------------------------------------------------------------------------	
	process(sysclk,tmp_sig_50ms,data_min_low,data_min_high,data_h_low,data_h_high)  --24小时时钟计数
   begin
   if rising_edge(tmp_sig_min) then-----------------
	data_min_low<=data_min_low+1;
		if(data_min_low = 9)then-------------------
		data_min_low <=0;
		data_min_high<=data_min_high+1;
			if(data_min_high = 5)then---------------------
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
	--if(key_signal(2)='1')then
	--data_h_low <= data_h_low+1;
	--end if;
	end process;
	
--------------------------------------------------------------------------------------------------------------	
			
END example;
