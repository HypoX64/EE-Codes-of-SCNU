LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY Encoder8_3 IS
	PORT(
		input: IN STD_LOGIC_VECTOR(7 downto 0);
		code:	OUT STD_LOGIC_VECTOR(2 downto 0)
		);
END Encoder8_3;

ARCHITECTURE example OF Encoder8_3 IS
BEGIN
	PROCESS(input)
	BEGIN
		if input(0) = '0' then		
			code <= "111";
		elsif input(1) = '0' then		
			code <= "110";
		elsif input(2) = '0' then		
			code <= "101";
		elsif input(3) = '0' then	
			code <= "100";
		elsif input(4) = '0' then	
			code <= "011";	
		elsif input(5) = '0' then	
			code <= "010";
		elsif input(6) = '0' then	
			code <= "001";	
		else
			code <= "000";
		end if;
	END PROCESS;
END example;