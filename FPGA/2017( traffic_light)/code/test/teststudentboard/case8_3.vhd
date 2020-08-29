LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY case8_3 IS
	PORT(
		input: IN STD_LOGIC_VECTOR(7 downto 0);
		code:	OUT STD_LOGIC_VECTOR(2 downto 0)
		);
END case8_3;

ARCHITECTURE example OF case8_3 IS
BEGIN
	PROCESS(input)
	BEGIN
		case input is
			when "11111110" => code <= "111";
			when "11111101" => code <= "110";
			when "11111011" => code <= "101";
			when "11110111" => code <= "100";
			when "11101111" => code <= "011";
			when "11011111" => code <= "010";
			when "10111111" => code <= "001";
			when "01111111" => code <= "000";
			when others => code <= "000";
		end case;
	END PROCESS;
END example;
