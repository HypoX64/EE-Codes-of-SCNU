-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 13.0.0 Build 156 04/24/2013 SJ Full Version"

-- DATE "05/16/2017 21:13:23"

-- 
-- Device: Altera EP2C5T144C8 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEII;
LIBRARY IEEE;
USE CYCLONEII.CYCLONEII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	test IS
    PORT (
	sysclk : IN std_logic;
	seg7data : OUT std_logic_vector(7 DOWNTO 0);
	seg7com : OUT std_logic_vector(3 DOWNTO 0);
	clkout : OUT std_logic
	);
END test;

-- Design Ports Information
-- seg7data[0]	=>  Location: PIN_53,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[1]	=>  Location: PIN_55,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[2]	=>  Location: PIN_57,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[3]	=>  Location: PIN_58,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[4]	=>  Location: PIN_59,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[5]	=>  Location: PIN_60,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[6]	=>  Location: PIN_63,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7data[7]	=>  Location: PIN_64,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7com[0]	=>  Location: PIN_65,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7com[1]	=>  Location: PIN_67,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7com[2]	=>  Location: PIN_69,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- seg7com[3]	=>  Location: PIN_70,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- clkout	=>  Location: PIN_40,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- sysclk	=>  Location: PIN_17,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default


ARCHITECTURE structure OF test IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_sysclk : std_logic;
SIGNAL ww_seg7data : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_seg7com : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_clkout : std_logic;
SIGNAL \div|Q_min~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_s~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \sysclk~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Add1~4_combout\ : std_logic;
SIGNAL \div|Add1~6_combout\ : std_logic;
SIGNAL \div|Add1~10_combout\ : std_logic;
SIGNAL \div|Add1~14_combout\ : std_logic;
SIGNAL \div|Add1~32_combout\ : std_logic;
SIGNAL \div|Add1~42_combout\ : std_logic;
SIGNAL \div|Add1~51\ : std_logic;
SIGNAL \div|Add1~52_combout\ : std_logic;
SIGNAL \div|Add2~0_combout\ : std_logic;
SIGNAL \div|Add2~1\ : std_logic;
SIGNAL \div|Add2~2_combout\ : std_logic;
SIGNAL \div|Add2~3\ : std_logic;
SIGNAL \div|Add2~4_combout\ : std_logic;
SIGNAL \div|Add2~5\ : std_logic;
SIGNAL \div|Add2~6_combout\ : std_logic;
SIGNAL \div|Add2~7\ : std_logic;
SIGNAL \div|Add2~8_combout\ : std_logic;
SIGNAL \div|Add2~9\ : std_logic;
SIGNAL \div|Add2~10_combout\ : std_logic;
SIGNAL \div|Add2~11\ : std_logic;
SIGNAL \div|Add2~12_combout\ : std_logic;
SIGNAL \div|Q_min~regout\ : std_logic;
SIGNAL \div|Equal1~0_combout\ : std_logic;
SIGNAL \div|Equal2~0_combout\ : std_logic;
SIGNAL \div|Equal2~1_combout\ : std_logic;
SIGNAL \div|Q_min~0_combout\ : std_logic;
SIGNAL \div|data_s~6_combout\ : std_logic;
SIGNAL \div|data_min~0_combout\ : std_logic;
SIGNAL \div|data_min~1_combout\ : std_logic;
SIGNAL \div|data_min~2_combout\ : std_logic;
SIGNAL \div|data_min~3_combout\ : std_logic;
SIGNAL \div|data_min~4_combout\ : std_logic;
SIGNAL \div|Q_min~clkctrl_outclk\ : std_logic;
SIGNAL \div|Q_s~clkctrl_outclk\ : std_logic;
SIGNAL \data_min[0]~0_combout\ : std_logic;
SIGNAL \Add0~0_combout\ : std_logic;
SIGNAL \Add0~1\ : std_logic;
SIGNAL \Add0~2_combout\ : std_logic;
SIGNAL \dis|Mux6~0_combout\ : std_logic;
SIGNAL \dis|Mux5~0_combout\ : std_logic;
SIGNAL \dis|Mux4~0_combout\ : std_logic;
SIGNAL \dis|Mux3~0_combout\ : std_logic;
SIGNAL \dis|Mux2~0_combout\ : std_logic;
SIGNAL \dis|Mux1~0_combout\ : std_logic;
SIGNAL \dis|Mux0~0_combout\ : std_logic;
SIGNAL \sysclk~combout\ : std_logic;
SIGNAL \sysclk~clkctrl_outclk\ : std_logic;
SIGNAL \div|Add1~39\ : std_logic;
SIGNAL \div|Add1~40_combout\ : std_logic;
SIGNAL \div|Add1~41\ : std_logic;
SIGNAL \div|Add1~43\ : std_logic;
SIGNAL \div|Add1~44_combout\ : std_logic;
SIGNAL \div|Add1~45\ : std_logic;
SIGNAL \div|Add1~47\ : std_logic;
SIGNAL \div|Add1~48_combout\ : std_logic;
SIGNAL \div|Add1~49\ : std_logic;
SIGNAL \div|Add1~50_combout\ : std_logic;
SIGNAL \div|Add1~46_combout\ : std_logic;
SIGNAL \div|Equal1~6_combout\ : std_logic;
SIGNAL \div|Equal1~7_combout\ : std_logic;
SIGNAL \div|Add1~30_combout\ : std_logic;
SIGNAL \div|data_s~5_combout\ : std_logic;
SIGNAL \div|Add1~0_combout\ : std_logic;
SIGNAL \div|data_s~0_combout\ : std_logic;
SIGNAL \div|Add1~1\ : std_logic;
SIGNAL \div|Add1~2_combout\ : std_logic;
SIGNAL \div|Add1~3\ : std_logic;
SIGNAL \div|Add1~5\ : std_logic;
SIGNAL \div|Add1~7\ : std_logic;
SIGNAL \div|Add1~8_combout\ : std_logic;
SIGNAL \div|data_s~1_combout\ : std_logic;
SIGNAL \div|Add1~9\ : std_logic;
SIGNAL \div|Add1~11\ : std_logic;
SIGNAL \div|Add1~12_combout\ : std_logic;
SIGNAL \div|Add1~13\ : std_logic;
SIGNAL \div|Add1~15\ : std_logic;
SIGNAL \div|Add1~16_combout\ : std_logic;
SIGNAL \div|Add1~17\ : std_logic;
SIGNAL \div|Add1~19\ : std_logic;
SIGNAL \div|Add1~20_combout\ : std_logic;
SIGNAL \div|Add1~21\ : std_logic;
SIGNAL \div|Add1~22_combout\ : std_logic;
SIGNAL \div|Add1~23\ : std_logic;
SIGNAL \div|Add1~24_combout\ : std_logic;
SIGNAL \div|data_s~3_combout\ : std_logic;
SIGNAL \div|Add1~25\ : std_logic;
SIGNAL \div|Add1~26_combout\ : std_logic;
SIGNAL \div|Equal1~3_combout\ : std_logic;
SIGNAL \div|Add1~18_combout\ : std_logic;
SIGNAL \div|Equal1~2_combout\ : std_logic;
SIGNAL \div|data_s~2_combout\ : std_logic;
SIGNAL \div|Equal1~1_combout\ : std_logic;
SIGNAL \div|Equal1~4_combout\ : std_logic;
SIGNAL \div|Add1~27\ : std_logic;
SIGNAL \div|Add1~28_combout\ : std_logic;
SIGNAL \div|data_s~4_combout\ : std_logic;
SIGNAL \div|Add1~29\ : std_logic;
SIGNAL \div|Add1~31\ : std_logic;
SIGNAL \div|Add1~33\ : std_logic;
SIGNAL \div|Add1~34_combout\ : std_logic;
SIGNAL \div|data_s~7_combout\ : std_logic;
SIGNAL \div|Add1~35\ : std_logic;
SIGNAL \div|Add1~37\ : std_logic;
SIGNAL \div|Add1~38_combout\ : std_logic;
SIGNAL \div|Add1~36_combout\ : std_logic;
SIGNAL \div|Equal1~5_combout\ : std_logic;
SIGNAL \div|Q_s~0_combout\ : std_logic;
SIGNAL \div|Q_s~regout\ : std_logic;
SIGNAL data_min : std_logic_vector(6 DOWNTO 0);
SIGNAL \div|data_s\ : std_logic_vector(26 DOWNTO 0);
SIGNAL \div|data_min\ : std_logic_vector(6 DOWNTO 0);

BEGIN

ww_sysclk <= sysclk;
seg7data <= ww_seg7data;
seg7com <= ww_seg7com;
clkout <= ww_clkout;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\div|Q_min~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_min~regout\);

\div|Q_s~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_s~regout\);

\sysclk~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \sysclk~combout\);

-- Location: LCCOMB_X2_Y2_N10
\div|Add1~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~4_combout\ = (\div|data_s\(2) & (\div|Add1~3\ $ (GND))) # (!\div|data_s\(2) & (!\div|Add1~3\ & VCC))
-- \div|Add1~5\ = CARRY((\div|data_s\(2) & !\div|Add1~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(2),
	datad => VCC,
	cin => \div|Add1~3\,
	combout => \div|Add1~4_combout\,
	cout => \div|Add1~5\);

-- Location: LCCOMB_X2_Y2_N12
\div|Add1~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~6_combout\ = (\div|data_s\(3) & (!\div|Add1~5\)) # (!\div|data_s\(3) & ((\div|Add1~5\) # (GND)))
-- \div|Add1~7\ = CARRY((!\div|Add1~5\) # (!\div|data_s\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(3),
	datad => VCC,
	cin => \div|Add1~5\,
	combout => \div|Add1~6_combout\,
	cout => \div|Add1~7\);

-- Location: LCCOMB_X2_Y2_N16
\div|Add1~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~10_combout\ = (\div|data_s\(5) & (!\div|Add1~9\)) # (!\div|data_s\(5) & ((\div|Add1~9\) # (GND)))
-- \div|Add1~11\ = CARRY((!\div|Add1~9\) # (!\div|data_s\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(5),
	datad => VCC,
	cin => \div|Add1~9\,
	combout => \div|Add1~10_combout\,
	cout => \div|Add1~11\);

-- Location: LCCOMB_X2_Y2_N20
\div|Add1~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~14_combout\ = (\div|data_s\(7) & (!\div|Add1~13\)) # (!\div|data_s\(7) & ((\div|Add1~13\) # (GND)))
-- \div|Add1~15\ = CARRY((!\div|Add1~13\) # (!\div|data_s\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(7),
	datad => VCC,
	cin => \div|Add1~13\,
	combout => \div|Add1~14_combout\,
	cout => \div|Add1~15\);

-- Location: LCCOMB_X2_Y1_N6
\div|Add1~32\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~32_combout\ = (\div|data_s\(16) & (\div|Add1~31\ $ (GND))) # (!\div|data_s\(16) & (!\div|Add1~31\ & VCC))
-- \div|Add1~33\ = CARRY((\div|data_s\(16) & !\div|Add1~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(16),
	datad => VCC,
	cin => \div|Add1~31\,
	combout => \div|Add1~32_combout\,
	cout => \div|Add1~33\);

-- Location: LCCOMB_X2_Y1_N16
\div|Add1~42\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~42_combout\ = (\div|data_s\(21) & (!\div|Add1~41\)) # (!\div|data_s\(21) & ((\div|Add1~41\) # (GND)))
-- \div|Add1~43\ = CARRY((!\div|Add1~41\) # (!\div|data_s\(21)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(21),
	datad => VCC,
	cin => \div|Add1~41\,
	combout => \div|Add1~42_combout\,
	cout => \div|Add1~43\);

-- Location: LCCOMB_X2_Y1_N24
\div|Add1~50\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~50_combout\ = (\div|data_s\(25) & (!\div|Add1~49\)) # (!\div|data_s\(25) & ((\div|Add1~49\) # (GND)))
-- \div|Add1~51\ = CARRY((!\div|Add1~49\) # (!\div|data_s\(25)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(25),
	datad => VCC,
	cin => \div|Add1~49\,
	combout => \div|Add1~50_combout\,
	cout => \div|Add1~51\);

-- Location: LCCOMB_X2_Y1_N26
\div|Add1~52\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~52_combout\ = \div|Add1~51\ $ (!\div|data_s\(26))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \div|data_s\(26),
	cin => \div|Add1~51\,
	combout => \div|Add1~52_combout\);

-- Location: LCCOMB_X1_Y6_N6
\div|Add2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~0_combout\ = \div|data_min\(0) $ (VCC)
-- \div|Add2~1\ = CARRY(\div|data_min\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(0),
	datad => VCC,
	combout => \div|Add2~0_combout\,
	cout => \div|Add2~1\);

-- Location: LCCOMB_X1_Y6_N8
\div|Add2~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~2_combout\ = (\div|data_min\(1) & (!\div|Add2~1\)) # (!\div|data_min\(1) & ((\div|Add2~1\) # (GND)))
-- \div|Add2~3\ = CARRY((!\div|Add2~1\) # (!\div|data_min\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(1),
	datad => VCC,
	cin => \div|Add2~1\,
	combout => \div|Add2~2_combout\,
	cout => \div|Add2~3\);

-- Location: LCCOMB_X1_Y6_N10
\div|Add2~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~4_combout\ = (\div|data_min\(2) & (\div|Add2~3\ $ (GND))) # (!\div|data_min\(2) & (!\div|Add2~3\ & VCC))
-- \div|Add2~5\ = CARRY((\div|data_min\(2) & !\div|Add2~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(2),
	datad => VCC,
	cin => \div|Add2~3\,
	combout => \div|Add2~4_combout\,
	cout => \div|Add2~5\);

-- Location: LCCOMB_X1_Y6_N12
\div|Add2~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~6_combout\ = (\div|data_min\(3) & (!\div|Add2~5\)) # (!\div|data_min\(3) & ((\div|Add2~5\) # (GND)))
-- \div|Add2~7\ = CARRY((!\div|Add2~5\) # (!\div|data_min\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(3),
	datad => VCC,
	cin => \div|Add2~5\,
	combout => \div|Add2~6_combout\,
	cout => \div|Add2~7\);

-- Location: LCCOMB_X1_Y6_N14
\div|Add2~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~8_combout\ = (\div|data_min\(4) & (\div|Add2~7\ $ (GND))) # (!\div|data_min\(4) & (!\div|Add2~7\ & VCC))
-- \div|Add2~9\ = CARRY((\div|data_min\(4) & !\div|Add2~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(4),
	datad => VCC,
	cin => \div|Add2~7\,
	combout => \div|Add2~8_combout\,
	cout => \div|Add2~9\);

-- Location: LCCOMB_X1_Y6_N16
\div|Add2~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~10_combout\ = (\div|data_min\(5) & (!\div|Add2~9\)) # (!\div|data_min\(5) & ((\div|Add2~9\) # (GND)))
-- \div|Add2~11\ = CARRY((!\div|Add2~9\) # (!\div|data_min\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(5),
	datad => VCC,
	cin => \div|Add2~9\,
	combout => \div|Add2~10_combout\,
	cout => \div|Add2~11\);

-- Location: LCCOMB_X1_Y6_N18
\div|Add2~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~12_combout\ = \div|Add2~11\ $ (!\div|data_min\(6))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \div|data_min\(6),
	cin => \div|Add2~11\,
	combout => \div|Add2~12_combout\);

-- Location: LCFF_X1_Y6_N21
\div|Q_min\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|Q_min~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_min~regout\);

-- Location: LCFF_X2_Y2_N11
\div|data_s[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(2));

-- Location: LCFF_X2_Y2_N13
\div|data_s[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(3));

-- Location: LCCOMB_X1_Y2_N16
\div|Equal1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~0_combout\ = (!\div|data_s\(0) & (!\div|data_s\(2) & (!\div|data_s\(1) & !\div|data_s\(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(0),
	datab => \div|data_s\(2),
	datac => \div|data_s\(1),
	datad => \div|data_s\(3),
	combout => \div|Equal1~0_combout\);

-- Location: LCFF_X2_Y2_N17
\div|data_s[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(5));

-- Location: LCFF_X1_Y1_N15
\div|data_s[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(16));

-- Location: LCFF_X2_Y1_N17
\div|data_s[21]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~42_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(21));

-- Location: LCFF_X2_Y1_N27
\div|data_s[26]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~52_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(26));

-- Location: LCFF_X1_Y6_N29
\div|data_min[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(4));

-- Location: LCFF_X1_Y6_N23
\div|data_min[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(3));

-- Location: LCFF_X1_Y6_N19
\div|data_min[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|Add2~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(6));

-- Location: LCFF_X1_Y6_N17
\div|data_min[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|Add2~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(5));

-- Location: LCCOMB_X1_Y6_N24
\div|Equal2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~0_combout\ = (\div|data_min\(3) & (\div|data_min\(4) & (!\div|data_min\(5) & !\div|data_min\(6))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(3),
	datab => \div|data_min\(4),
	datac => \div|data_min\(5),
	datad => \div|data_min\(6),
	combout => \div|Equal2~0_combout\);

-- Location: LCFF_X1_Y6_N3
\div|data_min[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(2));

-- Location: LCFF_X1_Y6_N27
\div|data_min[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(1));

-- Location: LCFF_X1_Y6_N5
\div|data_min[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(0));

-- Location: LCCOMB_X1_Y6_N30
\div|Equal2~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~1_combout\ = (\div|data_min\(1) & (!\div|data_min\(0) & \div|data_min\(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(1),
	datac => \div|data_min\(0),
	datad => \div|data_min\(2),
	combout => \div|Equal2~1_combout\);

-- Location: LCCOMB_X1_Y6_N20
\div|Q_min~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_min~0_combout\ = \div|Q_min~regout\ $ (((\div|Equal2~0_combout\ & \div|Equal2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~0_combout\,
	datac => \div|Q_min~regout\,
	datad => \div|Equal2~1_combout\,
	combout => \div|Q_min~0_combout\);

-- Location: LCCOMB_X1_Y1_N14
\div|data_s~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~6_combout\ = (\div|Add1~32_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~5_combout\)) # (!\div|Equal1~7_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~7_combout\,
	datab => \div|Equal1~5_combout\,
	datac => \div|Equal1~4_combout\,
	datad => \div|Add1~32_combout\,
	combout => \div|data_s~6_combout\);

-- Location: LCCOMB_X1_Y6_N28
\div|data_min~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~0_combout\ = (\div|Add2~8_combout\ & ((!\div|Equal2~1_combout\) # (!\div|Equal2~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~0_combout\,
	datac => \div|Add2~8_combout\,
	datad => \div|Equal2~1_combout\,
	combout => \div|data_min~0_combout\);

-- Location: LCCOMB_X1_Y6_N22
\div|data_min~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~1_combout\ = (\div|Add2~6_combout\ & ((!\div|Equal2~0_combout\) # (!\div|Equal2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal2~1_combout\,
	datac => \div|Equal2~0_combout\,
	datad => \div|Add2~6_combout\,
	combout => \div|data_min~1_combout\);

-- Location: LCCOMB_X1_Y6_N2
\div|data_min~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~2_combout\ = (\div|Add2~4_combout\ & ((!\div|Equal2~0_combout\) # (!\div|Equal2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal2~1_combout\,
	datac => \div|Equal2~0_combout\,
	datad => \div|Add2~4_combout\,
	combout => \div|data_min~2_combout\);

-- Location: LCCOMB_X1_Y6_N26
\div|data_min~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~3_combout\ = (\div|Add2~2_combout\ & ((!\div|Equal2~1_combout\) # (!\div|Equal2~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~0_combout\,
	datac => \div|Add2~2_combout\,
	datad => \div|Equal2~1_combout\,
	combout => \div|data_min~3_combout\);

-- Location: LCCOMB_X1_Y6_N4
\div|data_min~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~4_combout\ = (\div|Add2~0_combout\ & ((!\div|Equal2~0_combout\) # (!\div|Equal2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal2~1_combout\,
	datac => \div|Equal2~0_combout\,
	datad => \div|Add2~0_combout\,
	combout => \div|data_min~4_combout\);

-- Location: CLKCTRL_G0
\div|Q_min~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \div|Q_min~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \div|Q_min~clkctrl_outclk\);

-- Location: CLKCTRL_G1
\div|Q_s~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \div|Q_s~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \div|Q_s~clkctrl_outclk\);

-- Location: LCCOMB_X15_Y1_N4
\data_min[0]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min[0]~0_combout\ = !data_min(0)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_min(0),
	combout => \data_min[0]~0_combout\);

-- Location: LCFF_X15_Y1_N5
\data_min[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min[0]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min(0));

-- Location: LCCOMB_X15_Y1_N6
\Add0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~0_combout\ = (data_min(1) & (data_min(0) $ (VCC))) # (!data_min(1) & (data_min(0) & VCC))
-- \Add0~1\ = CARRY((data_min(1) & data_min(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110011010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min(1),
	datab => data_min(0),
	datad => VCC,
	combout => \Add0~0_combout\,
	cout => \Add0~1\);

-- Location: LCFF_X15_Y1_N11
\data_min[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	sdata => \Add0~0_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min(1));

-- Location: LCCOMB_X15_Y1_N8
\Add0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~2_combout\ = data_min(2) $ (\Add0~1\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_min(2),
	cin => \Add0~1\,
	combout => \Add0~2_combout\);

-- Location: LCFF_X15_Y1_N9
\data_min[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min(2));

-- Location: LCCOMB_X14_Y1_N8
\dis|Mux6~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux6~0_combout\ = (!data_min(1) & (data_min(0) $ (data_min(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001001000010010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min(0),
	datab => data_min(1),
	datac => data_min(2),
	combout => \dis|Mux6~0_combout\);

-- Location: LCCOMB_X14_Y1_N10
\dis|Mux5~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux5~0_combout\ = (\Add0~0_combout\ & data_min(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Add0~0_combout\,
	datac => data_min(2),
	combout => \dis|Mux5~0_combout\);

-- Location: LCCOMB_X14_Y1_N20
\dis|Mux4~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux4~0_combout\ = (!data_min(0) & (!data_min(2) & data_min(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min(0),
	datac => data_min(2),
	datad => data_min(1),
	combout => \dis|Mux4~0_combout\);

-- Location: LCCOMB_X14_Y1_N6
\dis|Mux3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux3~0_combout\ = (data_min(2) & (((!\Add0~0_combout\)))) # (!data_min(2) & (data_min(0) & ((!data_min(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000000111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min(0),
	datab => \Add0~0_combout\,
	datac => data_min(2),
	datad => data_min(1),
	combout => \dis|Mux3~0_combout\);

-- Location: LCCOMB_X15_Y1_N10
\dis|Mux2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux2~0_combout\ = (data_min(0)) # ((data_min(2) & !data_min(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min(2),
	datac => data_min(1),
	datad => data_min(0),
	combout => \dis|Mux2~0_combout\);

-- Location: LCCOMB_X15_Y1_N28
\dis|Mux1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux1~0_combout\ = (data_min(2) & (data_min(0) & data_min(1))) # (!data_min(2) & ((data_min(0)) # (data_min(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111001100110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min(2),
	datac => data_min(0),
	datad => data_min(1),
	combout => \dis|Mux1~0_combout\);

-- Location: LCCOMB_X15_Y1_N18
\dis|Mux0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux0~0_combout\ = (data_min(2) & (data_min(0) & data_min(1))) # (!data_min(2) & ((!data_min(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000000110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min(2),
	datac => data_min(0),
	datad => data_min(1),
	combout => \dis|Mux0~0_combout\);

-- Location: PIN_17,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\sysclk~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_sysclk,
	combout => \sysclk~combout\);

-- Location: CLKCTRL_G2
\sysclk~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \sysclk~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \sysclk~clkctrl_outclk\);

-- Location: LCCOMB_X2_Y1_N12
\div|Add1~38\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~38_combout\ = (\div|data_s\(19) & (!\div|Add1~37\)) # (!\div|data_s\(19) & ((\div|Add1~37\) # (GND)))
-- \div|Add1~39\ = CARRY((!\div|Add1~37\) # (!\div|data_s\(19)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(19),
	datad => VCC,
	cin => \div|Add1~37\,
	combout => \div|Add1~38_combout\,
	cout => \div|Add1~39\);

-- Location: LCCOMB_X2_Y1_N14
\div|Add1~40\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~40_combout\ = (\div|data_s\(20) & (\div|Add1~39\ $ (GND))) # (!\div|data_s\(20) & (!\div|Add1~39\ & VCC))
-- \div|Add1~41\ = CARRY((\div|data_s\(20) & !\div|Add1~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(20),
	datad => VCC,
	cin => \div|Add1~39\,
	combout => \div|Add1~40_combout\,
	cout => \div|Add1~41\);

-- Location: LCFF_X2_Y1_N15
\div|data_s[20]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~40_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(20));

-- Location: LCCOMB_X2_Y1_N18
\div|Add1~44\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~44_combout\ = (\div|data_s\(22) & (\div|Add1~43\ $ (GND))) # (!\div|data_s\(22) & (!\div|Add1~43\ & VCC))
-- \div|Add1~45\ = CARRY((\div|data_s\(22) & !\div|Add1~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(22),
	datad => VCC,
	cin => \div|Add1~43\,
	combout => \div|Add1~44_combout\,
	cout => \div|Add1~45\);

-- Location: LCFF_X2_Y1_N19
\div|data_s[22]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~44_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(22));

-- Location: LCCOMB_X2_Y1_N20
\div|Add1~46\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~46_combout\ = (\div|data_s\(23) & (!\div|Add1~45\)) # (!\div|data_s\(23) & ((\div|Add1~45\) # (GND)))
-- \div|Add1~47\ = CARRY((!\div|Add1~45\) # (!\div|data_s\(23)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(23),
	datad => VCC,
	cin => \div|Add1~45\,
	combout => \div|Add1~46_combout\,
	cout => \div|Add1~47\);

-- Location: LCCOMB_X2_Y1_N22
\div|Add1~48\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~48_combout\ = (\div|data_s\(24) & (\div|Add1~47\ $ (GND))) # (!\div|data_s\(24) & (!\div|Add1~47\ & VCC))
-- \div|Add1~49\ = CARRY((\div|data_s\(24) & !\div|Add1~47\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(24),
	datad => VCC,
	cin => \div|Add1~47\,
	combout => \div|Add1~48_combout\,
	cout => \div|Add1~49\);

-- Location: LCFF_X2_Y1_N23
\div|data_s[24]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~48_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(24));

-- Location: LCFF_X2_Y1_N25
\div|data_s[25]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~50_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(25));

-- Location: LCFF_X2_Y1_N21
\div|data_s[23]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~46_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(23));

-- Location: LCCOMB_X1_Y1_N24
\div|Equal1~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~6_combout\ = (!\div|data_s\(21) & (!\div|data_s\(23) & (!\div|data_s\(20) & !\div|data_s\(22))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(21),
	datab => \div|data_s\(23),
	datac => \div|data_s\(20),
	datad => \div|data_s\(22),
	combout => \div|Equal1~6_combout\);

-- Location: LCCOMB_X1_Y1_N16
\div|Equal1~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~7_combout\ = (!\div|data_s\(26) & (!\div|data_s\(25) & (\div|Equal1~6_combout\ & !\div|data_s\(24))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(26),
	datab => \div|data_s\(25),
	datac => \div|Equal1~6_combout\,
	datad => \div|data_s\(24),
	combout => \div|Equal1~7_combout\);

-- Location: LCCOMB_X2_Y1_N4
\div|Add1~30\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~30_combout\ = (\div|data_s\(15) & (!\div|Add1~29\)) # (!\div|data_s\(15) & ((\div|Add1~29\) # (GND)))
-- \div|Add1~31\ = CARRY((!\div|Add1~29\) # (!\div|data_s\(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(15),
	datad => VCC,
	cin => \div|Add1~29\,
	combout => \div|Add1~30_combout\,
	cout => \div|Add1~31\);

-- Location: LCCOMB_X1_Y1_N30
\div|data_s~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~5_combout\ = (\div|Add1~30_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~5_combout\)) # (!\div|Equal1~7_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~7_combout\,
	datab => \div|Equal1~5_combout\,
	datac => \div|Equal1~4_combout\,
	datad => \div|Add1~30_combout\,
	combout => \div|data_s~5_combout\);

-- Location: LCFF_X1_Y1_N31
\div|data_s[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(15));

-- Location: LCCOMB_X2_Y2_N6
\div|Add1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~0_combout\ = \div|data_s\(0) $ (VCC)
-- \div|Add1~1\ = CARRY(\div|data_s\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(0),
	datad => VCC,
	combout => \div|Add1~0_combout\,
	cout => \div|Add1~1\);

-- Location: LCCOMB_X2_Y2_N4
\div|data_s~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~0_combout\ = (\div|Add1~0_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~7_combout\)) # (!\div|Equal1~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~5_combout\,
	datab => \div|Add1~0_combout\,
	datac => \div|Equal1~7_combout\,
	datad => \div|Equal1~4_combout\,
	combout => \div|data_s~0_combout\);

-- Location: LCFF_X2_Y2_N5
\div|data_s[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(0));

-- Location: LCCOMB_X2_Y2_N8
\div|Add1~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~2_combout\ = (\div|data_s\(1) & (!\div|Add1~1\)) # (!\div|data_s\(1) & ((\div|Add1~1\) # (GND)))
-- \div|Add1~3\ = CARRY((!\div|Add1~1\) # (!\div|data_s\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(1),
	datad => VCC,
	cin => \div|Add1~1\,
	combout => \div|Add1~2_combout\,
	cout => \div|Add1~3\);

-- Location: LCFF_X2_Y2_N9
\div|data_s[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(1));

-- Location: LCCOMB_X2_Y2_N14
\div|Add1~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~8_combout\ = (\div|data_s\(4) & (\div|Add1~7\ $ (GND))) # (!\div|data_s\(4) & (!\div|Add1~7\ & VCC))
-- \div|Add1~9\ = CARRY((\div|data_s\(4) & !\div|Add1~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(4),
	datad => VCC,
	cin => \div|Add1~7\,
	combout => \div|Add1~8_combout\,
	cout => \div|Add1~9\);

-- Location: LCCOMB_X2_Y2_N2
\div|data_s~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~1_combout\ = (\div|Add1~8_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~7_combout\)) # (!\div|Equal1~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~5_combout\,
	datab => \div|Add1~8_combout\,
	datac => \div|Equal1~7_combout\,
	datad => \div|Equal1~4_combout\,
	combout => \div|data_s~1_combout\);

-- Location: LCFF_X2_Y2_N3
\div|data_s[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(4));

-- Location: LCCOMB_X2_Y2_N18
\div|Add1~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~12_combout\ = (\div|data_s\(6) & (\div|Add1~11\ $ (GND))) # (!\div|data_s\(6) & (!\div|Add1~11\ & VCC))
-- \div|Add1~13\ = CARRY((\div|data_s\(6) & !\div|Add1~11\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(6),
	datad => VCC,
	cin => \div|Add1~11\,
	combout => \div|Add1~12_combout\,
	cout => \div|Add1~13\);

-- Location: LCFF_X2_Y2_N19
\div|data_s[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(6));

-- Location: LCCOMB_X2_Y2_N22
\div|Add1~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~16_combout\ = (\div|data_s\(8) & (\div|Add1~15\ $ (GND))) # (!\div|data_s\(8) & (!\div|Add1~15\ & VCC))
-- \div|Add1~17\ = CARRY((\div|data_s\(8) & !\div|Add1~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(8),
	datad => VCC,
	cin => \div|Add1~15\,
	combout => \div|Add1~16_combout\,
	cout => \div|Add1~17\);

-- Location: LCFF_X2_Y2_N23
\div|data_s[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~16_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(8));

-- Location: LCCOMB_X2_Y2_N24
\div|Add1~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~18_combout\ = (\div|data_s\(9) & (!\div|Add1~17\)) # (!\div|data_s\(9) & ((\div|Add1~17\) # (GND)))
-- \div|Add1~19\ = CARRY((!\div|Add1~17\) # (!\div|data_s\(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(9),
	datad => VCC,
	cin => \div|Add1~17\,
	combout => \div|Add1~18_combout\,
	cout => \div|Add1~19\);

-- Location: LCCOMB_X2_Y2_N26
\div|Add1~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~20_combout\ = (\div|data_s\(10) & (\div|Add1~19\ $ (GND))) # (!\div|data_s\(10) & (!\div|Add1~19\ & VCC))
-- \div|Add1~21\ = CARRY((\div|data_s\(10) & !\div|Add1~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(10),
	datad => VCC,
	cin => \div|Add1~19\,
	combout => \div|Add1~20_combout\,
	cout => \div|Add1~21\);

-- Location: LCFF_X2_Y2_N27
\div|data_s[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(10));

-- Location: LCCOMB_X2_Y2_N28
\div|Add1~22\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~22_combout\ = (\div|data_s\(11) & (!\div|Add1~21\)) # (!\div|data_s\(11) & ((\div|Add1~21\) # (GND)))
-- \div|Add1~23\ = CARRY((!\div|Add1~21\) # (!\div|data_s\(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(11),
	datad => VCC,
	cin => \div|Add1~21\,
	combout => \div|Add1~22_combout\,
	cout => \div|Add1~23\);

-- Location: LCFF_X2_Y2_N29
\div|data_s[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~22_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(11));

-- Location: LCCOMB_X2_Y2_N30
\div|Add1~24\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~24_combout\ = (\div|data_s\(12) & (\div|Add1~23\ $ (GND))) # (!\div|data_s\(12) & (!\div|Add1~23\ & VCC))
-- \div|Add1~25\ = CARRY((\div|data_s\(12) & !\div|Add1~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(12),
	datad => VCC,
	cin => \div|Add1~23\,
	combout => \div|Add1~24_combout\,
	cout => \div|Add1~25\);

-- Location: LCCOMB_X1_Y1_N12
\div|data_s~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~3_combout\ = (\div|Add1~24_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~5_combout\)) # (!\div|Equal1~7_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~7_combout\,
	datab => \div|Equal1~5_combout\,
	datac => \div|Equal1~4_combout\,
	datad => \div|Add1~24_combout\,
	combout => \div|data_s~3_combout\);

-- Location: LCFF_X1_Y1_N13
\div|data_s[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(12));

-- Location: LCCOMB_X2_Y1_N0
\div|Add1~26\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~26_combout\ = (\div|data_s\(13) & (!\div|Add1~25\)) # (!\div|data_s\(13) & ((\div|Add1~25\) # (GND)))
-- \div|Add1~27\ = CARRY((!\div|Add1~25\) # (!\div|data_s\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(13),
	datad => VCC,
	cin => \div|Add1~25\,
	combout => \div|Add1~26_combout\,
	cout => \div|Add1~27\);

-- Location: LCFF_X2_Y1_N1
\div|data_s[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~26_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(13));

-- Location: LCCOMB_X1_Y1_N26
\div|Equal1~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~3_combout\ = (\div|data_s\(12) & (\div|data_s\(15) & (!\div|data_s\(13) & \div|data_s\(14))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000100000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(12),
	datab => \div|data_s\(15),
	datac => \div|data_s\(13),
	datad => \div|data_s\(14),
	combout => \div|Equal1~3_combout\);

-- Location: LCFF_X2_Y2_N25
\div|data_s[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(9));

-- Location: LCCOMB_X1_Y2_N20
\div|Equal1~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~2_combout\ = (!\div|data_s\(10) & (!\div|data_s\(9) & (!\div|data_s\(8) & !\div|data_s\(11))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(10),
	datab => \div|data_s\(9),
	datac => \div|data_s\(8),
	datad => \div|data_s\(11),
	combout => \div|Equal1~2_combout\);

-- Location: LCCOMB_X1_Y2_N30
\div|data_s~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~2_combout\ = (\div|Add1~14_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~7_combout\)) # (!\div|Equal1~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010101010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Add1~14_combout\,
	datab => \div|Equal1~5_combout\,
	datac => \div|Equal1~7_combout\,
	datad => \div|Equal1~4_combout\,
	combout => \div|data_s~2_combout\);

-- Location: LCFF_X1_Y2_N31
\div|data_s[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(7));

-- Location: LCCOMB_X2_Y2_N0
\div|Equal1~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~1_combout\ = (!\div|data_s\(5) & (!\div|data_s\(6) & (\div|data_s\(7) & \div|data_s\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(5),
	datab => \div|data_s\(6),
	datac => \div|data_s\(7),
	datad => \div|data_s\(4),
	combout => \div|Equal1~1_combout\);

-- Location: LCCOMB_X1_Y1_N20
\div|Equal1~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~4_combout\ = (\div|Equal1~0_combout\ & (\div|Equal1~3_combout\ & (\div|Equal1~2_combout\ & \div|Equal1~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~0_combout\,
	datab => \div|Equal1~3_combout\,
	datac => \div|Equal1~2_combout\,
	datad => \div|Equal1~1_combout\,
	combout => \div|Equal1~4_combout\);

-- Location: LCCOMB_X2_Y1_N2
\div|Add1~28\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~28_combout\ = (\div|data_s\(14) & (\div|Add1~27\ $ (GND))) # (!\div|data_s\(14) & (!\div|Add1~27\ & VCC))
-- \div|Add1~29\ = CARRY((\div|data_s\(14) & !\div|Add1~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(14),
	datad => VCC,
	cin => \div|Add1~27\,
	combout => \div|Add1~28_combout\,
	cout => \div|Add1~29\);

-- Location: LCCOMB_X2_Y1_N28
\div|data_s~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~4_combout\ = (\div|Add1~28_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~7_combout\)) # (!\div|Equal1~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~5_combout\,
	datab => \div|Equal1~7_combout\,
	datac => \div|Equal1~4_combout\,
	datad => \div|Add1~28_combout\,
	combout => \div|data_s~4_combout\);

-- Location: LCFF_X2_Y1_N29
\div|data_s[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(14));

-- Location: LCCOMB_X2_Y1_N8
\div|Add1~34\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~34_combout\ = (\div|data_s\(17) & (!\div|Add1~33\)) # (!\div|data_s\(17) & ((\div|Add1~33\) # (GND)))
-- \div|Add1~35\ = CARRY((!\div|Add1~33\) # (!\div|data_s\(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(17),
	datad => VCC,
	cin => \div|Add1~33\,
	combout => \div|Add1~34_combout\,
	cout => \div|Add1~35\);

-- Location: LCCOMB_X2_Y1_N30
\div|data_s~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~7_combout\ = (\div|Add1~34_combout\ & (((!\div|Equal1~4_combout\) # (!\div|Equal1~7_combout\)) # (!\div|Equal1~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~5_combout\,
	datab => \div|Equal1~7_combout\,
	datac => \div|Add1~34_combout\,
	datad => \div|Equal1~4_combout\,
	combout => \div|data_s~7_combout\);

-- Location: LCFF_X2_Y1_N31
\div|data_s[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~7_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(17));

-- Location: LCCOMB_X2_Y1_N10
\div|Add1~36\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add1~36_combout\ = (\div|data_s\(18) & (\div|Add1~35\ $ (GND))) # (!\div|data_s\(18) & (!\div|Add1~35\ & VCC))
-- \div|Add1~37\ = CARRY((\div|data_s\(18) & !\div|Add1~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(18),
	datad => VCC,
	cin => \div|Add1~35\,
	combout => \div|Add1~36_combout\,
	cout => \div|Add1~37\);

-- Location: LCFF_X2_Y1_N13
\div|data_s[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~38_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(19));

-- Location: LCFF_X2_Y1_N11
\div|data_s[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add1~36_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(18));

-- Location: LCCOMB_X1_Y1_N0
\div|Equal1~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal1~5_combout\ = (\div|data_s\(16) & (!\div|data_s\(19) & (!\div|data_s\(18) & \div|data_s\(17))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(16),
	datab => \div|data_s\(19),
	datac => \div|data_s\(18),
	datad => \div|data_s\(17),
	combout => \div|Equal1~5_combout\);

-- Location: LCCOMB_X1_Y1_N22
\div|Q_s~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_s~0_combout\ = \div|Q_s~regout\ $ (((\div|Equal1~4_combout\ & (\div|Equal1~5_combout\ & \div|Equal1~7_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal1~4_combout\,
	datab => \div|Equal1~5_combout\,
	datac => \div|Q_s~regout\,
	datad => \div|Equal1~7_combout\,
	combout => \div|Q_s~0_combout\);

-- Location: LCFF_X1_Y1_N23
\div|Q_s\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Q_s~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_s~regout\);

-- Location: PIN_53,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[0]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux6~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(0));

-- Location: PIN_55,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[1]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux5~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(1));

-- Location: PIN_57,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[2]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux4~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(2));

-- Location: PIN_58,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[3]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux3~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(3));

-- Location: PIN_59,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[4]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux2~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(4));

-- Location: PIN_60,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[5]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(5));

-- Location: PIN_63,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[6]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \dis|Mux0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(6));

-- Location: PIN_64,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7data[7]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7data(7));

-- Location: PIN_65,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7com[0]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7com(0));

-- Location: PIN_67,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7com[1]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7com(1));

-- Location: PIN_69,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7com[2]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7com(2));

-- Location: PIN_70,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\seg7com[3]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => GND,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7com(3));

-- Location: PIN_40,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\clkout~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \div|Q_s~regout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_clkout);
END structure;


