LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY seg7led IS
	PORT(
		bcd_in: 		IN STD_LOGIC_VECTOR(3 downto 0);
		data_out:	OUT STD_LOGIC_VECTOR(7 downto 0)
		);
END seg7led;

ARCHITECTURE example OF seg7led IS
BEGIN

	process(bcd_in)
	begin
			case bcd_in is
				when "0000" => data_out <= "11000000"; -- 0
				when "0001" => data_out <= "11111001"; -- 1
				when "0010" => data_out <= "10100100"; -- 2
				when "0011" => data_out <= "10110000"; -- 3
				when "0100" => data_out <= "10011001"; -- 4
				when "0101" => data_out <= "10010010"; -- 5
				when "0110" => data_out <= "10000010"; -- 6
				when "0111" => data_out <= "11111000"; -- 7
				when "1000" => data_out <= "10000000"; -- 8
				when "1001" => data_out <= "10010000"; -- 9
				when "1010" => data_out <= "10001000"; -- A
				when "1011" => data_out <= "10000011"; -- b
				when "1100" => data_out <= "10100111"; -- c
				when "1101" => data_out <= "10100001"; -- d
				when "1110" => data_out <= "10000110"; -- E
				when "1111" => data_out <= "10001110"; -- F
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

