LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY test IS
	PORT(
	   sysclk: IN STD_LOGIC;
		seg7data:	OUT STD_LOGIC_VECTOR(7 downto 0);
		seg7com: OUT STD_LOGIC_VECTOR(3 downto 0);
		clkout: OUT STD_LOGIC
		);
END test;

ARCHITECTURE example OF test IS

	
	COMPONENT seg7led IS
		PORT (
			bcd_in: 		IN STD_LOGIC_VECTOR(3 downto 0);
			data_out:	OUT STD_LOGIC_VECTOR(7 downto 0)
		);
	END COMPONENT seg7led;
	
	COMPONENT clkdiv IS
       PORT( clk_in:IN STD_LOGIC;     --时钟信号输入
				 clk_out_ms:OUT STD_LOGIC;  --时钟信号输出
             clk_out_s:OUT STD_LOGIC;  --时钟信号输出 
				 clk_out_min:OUT STD_LOGIC;  --时钟信号输出
             clk_out_h:OUT STD_LOGIC   --时钟信号输出 
            );  
	END COMPONENT clkdiv;
	
	SIGNAL tmp_seg7data :STD_LOGIC_VECTOR(3 DOWNTO 0);
	SIGNAL tmp_sig_s :STD_LOGIC;
	SIGNAL tmp_sig_ms :STD_LOGIC;
	SIGNAL tmp_sig_min :STD_LOGIC;
	SIGNAL tmp_sig_h :STD_LOGIC;
	
	SIGNAL data_min_low:integer range 0 to 10;
	SIGNAL data_min_high:integer range 0 to 10;
	SIGNAL data_min:integer range 0 to 100;
	SIGNAL data_h_low:integer range 0 to 10;
	SIGNAL data_h_high:integer range 0 to 10;
	SIGNAL data_h:integer range 0 to 100;
	
BEGIN
	
	clkout <= tmp_sig_s;
	
	div: clkdiv PORT MAP (
				clk_in 	=> sysclk,
				clk_out_s => tmp_sig_s,
				clk_out_ms => tmp_sig_ms,
				clk_out_min => tmp_sig_min,
				clk_out_h => tmp_sig_h);
			
	dis: seg7led PORT MAP (
				bcd_in 	=> tmp_seg7data,
				data_out => seg7data
			);
			
	process(tmp_sig_min,sysclk)  --分钟计数
   begin
   if rising_edge(tmp_sig_min) then
	data_min<=data_min+1;
   end if;
	end process;
	
	process(data_min,sysclk)  
   begin
   case data_min is
		when 0=>tmp_seg7data<="0000";
		when 1=>tmp_seg7data<="0001";
		when 2=>tmp_seg7data<="0010";
		when 3=>tmp_seg7data<="0011";
		when 4=>tmp_seg7data<="0100";
		when 5=>tmp_seg7data<="0101";
		when 6=>tmp_seg7data<="0110";
		when others=>tmp_seg7data<="XXXX";
	end case;
	end process;
			
END example;
