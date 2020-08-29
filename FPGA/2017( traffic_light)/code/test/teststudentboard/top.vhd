LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY top IS
	PORT(
		key1,key2,key3,key4,key5: IN STD_LOGIC;
		seg7data:	OUT STD_LOGIC_VECTOR(7 downto 0);
		seg7com: OUT STD_LOGIC_VECTOR(3 downto 0)
		);
END top;

ARCHITECTURE example OF top IS

	component encoder8_3 is 
		port (
			input: IN STD_LOGIC_VECTOR(7 downto 0);
			code:	OUT STD_LOGIC_VECTOR(2 downto 0)
		);
	end component;
	
	
	COMPONENT seg7led IS
		PORT (
			bcd_in: 		IN STD_LOGIC_VECTOR(3 downto 0);
			data_out:	OUT STD_LOGIC_VECTOR(7 downto 0)
		);
	END COMPONENT seg7led;
	
	SIGNAL keysignal :STD_LOGIC_VECTOR(7 DOWNTO 0);
	SIGNAL codesignal :STD_LOGIC_VECTOR(2 DOWNTO 0);
	
BEGIN

   keysignal(0) <= '1'; 
	keysignal(1) <= key5; --S6
	keysignal(2) <= key4; --S5
	keysignal(3) <= key3; --S4
	keysignal(4) <= key2; --S3	
	keysignal(5) <= key1; --S2
	keysignal(6) <= '1';
	keysignal(7) <= '1'; 
	
	seg7com <= "0111";
	
	enc: encoder8_3 PORT MAP (
				input => keysignal,
				code 	=> codesignal
			);
	
			
	dis: seg7led PORT MAP (
				bcd_in 	=> '0' & codesignal,
				data_out => seg7data
			);
			
END example;
