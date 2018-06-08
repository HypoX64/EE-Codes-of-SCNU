LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY seg7led IS
	PORT(
		int_in: 		IN INTEGER  RANGE 0 TO 15 ;
		data_out:	OUT STD_LOGIC_VECTOR(7 downto 0)
		);
END seg7led;

ARCHITECTURE example OF seg7led IS
BEGIN

	process(int_in)
	begin
			case int_in is
				when 0 => data_out <= "11000000"; -- 0
				when 1 => data_out <= "11111001"; -- 1
				when 2 => data_out <= "10100100"; -- 2
				when 3 => data_out <= "10110000"; -- 3
				when 4 => data_out <= "10011001"; -- 4
				when 5 => data_out <= "10010010"; -- 5
				when 6 => data_out <= "10000010"; -- 6
				when 7 => data_out <= "11111000"; -- 7
				when 8 => data_out <= "10000000"; -- 8
				when 9 => data_out <= "10010000"; -- 9
				when 10 => data_out <= "10001000"; -- A
				when 11 => data_out <= "10000011"; -- b
				when 12 => data_out <= "10100111"; -- c
				when 13 => data_out <= "10100001"; -- d
				when 14 => data_out <= "10000110"; -- E
				when 15 => data_out <= "10001110"; -- F
				when others => NULL;
			end case;
	end process;

END example;
------------------------------------------------------------------------------------
-- DESCRIPTION   :   BIN to seven segments converter
--                   segment encoding
--                        a(0)
--                      +---+ 
--                 f(5) |   | b(1)
--                      +---+  <- g(6)
--                 e(4) |   | c(2)
--                      +---+
--                        d(3)
--                  Outputs (data_out) active         : low
------------------------------------------------------------------------------------

