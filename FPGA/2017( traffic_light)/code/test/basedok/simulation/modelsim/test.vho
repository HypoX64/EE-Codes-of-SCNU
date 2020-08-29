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

-- DATE "05/20/2017 10:49:50"

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
	key1 : IN std_logic;
	key2 : IN std_logic;
	key3 : IN std_logic;
	key4 : IN std_logic;
	key5 : IN std_logic;
	sysclk : IN std_logic;
	seg7data : OUT std_logic_vector(7 DOWNTO 0);
	seg7com : OUT std_logic_vector(3 DOWNTO 0)
	);
END test;

-- Design Ports Information
-- key3	=>  Location: PIN_90,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key4	=>  Location: PIN_91,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key5	=>  Location: PIN_72,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
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
-- sysclk	=>  Location: PIN_17,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key2	=>  Location: PIN_89,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key1	=>  Location: PIN_88,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default


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
SIGNAL ww_key1 : std_logic;
SIGNAL ww_key2 : std_logic;
SIGNAL ww_key3 : std_logic;
SIGNAL ww_key4 : std_logic;
SIGNAL ww_key5 : std_logic;
SIGNAL ww_sysclk : std_logic;
SIGNAL ww_seg7data : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_seg7com : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_s~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_ms~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_min~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \sysclk~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \key2~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \key1~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \key_signal[2]~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \Add3~0_combout\ : std_logic;
SIGNAL \Add3~1\ : std_logic;
SIGNAL \Add3~2_combout\ : std_logic;
SIGNAL \Add3~3\ : std_logic;
SIGNAL \Add3~4_combout\ : std_logic;
SIGNAL \Add3~5\ : std_logic;
SIGNAL \Add3~6_combout\ : std_logic;
SIGNAL \Add3~7\ : std_logic;
SIGNAL \Add3~8_combout\ : std_logic;
SIGNAL \Add3~9\ : std_logic;
SIGNAL \Add3~10_combout\ : std_logic;
SIGNAL \Add3~11\ : std_logic;
SIGNAL \Add3~12_combout\ : std_logic;
SIGNAL \Add3~13\ : std_logic;
SIGNAL \Add3~14_combout\ : std_logic;
SIGNAL \Add3~15\ : std_logic;
SIGNAL \Add3~16_combout\ : std_logic;
SIGNAL \Add3~17\ : std_logic;
SIGNAL \Add3~18_combout\ : std_logic;
SIGNAL \Add3~19\ : std_logic;
SIGNAL \Add3~20_combout\ : std_logic;
SIGNAL \Add7~2_combout\ : std_logic;
SIGNAL \Add5~7\ : std_logic;
SIGNAL \data_h[5]~15\ : std_logic;
SIGNAL \data_h[6]~16_combout\ : std_logic;
SIGNAL \Add5~8_combout\ : std_logic;
SIGNAL \data_time_count[1]~9_combout\ : std_logic;
SIGNAL \data_time_count[1]~10\ : std_logic;
SIGNAL \data_time_count[2]~11_combout\ : std_logic;
SIGNAL \data_time_count[2]~12\ : std_logic;
SIGNAL \data_time_count[3]~13_combout\ : std_logic;
SIGNAL \data_time_count[3]~14\ : std_logic;
SIGNAL \data_time_count[4]~15_combout\ : std_logic;
SIGNAL \data_time_count[4]~16\ : std_logic;
SIGNAL \data_time_count[5]~17_combout\ : std_logic;
SIGNAL \data_time_count[5]~18\ : std_logic;
SIGNAL \data_time_count[6]~19_combout\ : std_logic;
SIGNAL \data_time_count[6]~20\ : std_logic;
SIGNAL \data_time_count[7]~21_combout\ : std_logic;
SIGNAL \data_time_count[7]~22\ : std_logic;
SIGNAL \data_time_count[8]~23_combout\ : std_logic;
SIGNAL \data_time_count[8]~24\ : std_logic;
SIGNAL \data_time_count[9]~25_combout\ : std_logic;
SIGNAL \Add0~8_combout\ : std_logic;
SIGNAL \Add0~12_combout\ : std_logic;
SIGNAL \Add0~18_combout\ : std_logic;
SIGNAL \Add0~20_combout\ : std_logic;
SIGNAL \Add0~30_combout\ : std_logic;
SIGNAL \div|Add3~0_combout\ : std_logic;
SIGNAL \div|Add3~1\ : std_logic;
SIGNAL \div|Add3~2_combout\ : std_logic;
SIGNAL \div|Add3~3\ : std_logic;
SIGNAL \div|Add3~4_combout\ : std_logic;
SIGNAL \div|Add3~5\ : std_logic;
SIGNAL \div|Add3~6_combout\ : std_logic;
SIGNAL \div|Add3~7\ : std_logic;
SIGNAL \div|Add3~8_combout\ : std_logic;
SIGNAL \div|Add3~9\ : std_logic;
SIGNAL \div|Add3~10_combout\ : std_logic;
SIGNAL \div|Add3~11\ : std_logic;
SIGNAL \div|Add3~12_combout\ : std_logic;
SIGNAL \div|Add0~0_combout\ : std_logic;
SIGNAL \div|Add0~1\ : std_logic;
SIGNAL \div|Add0~2_combout\ : std_logic;
SIGNAL \div|Add0~3\ : std_logic;
SIGNAL \div|Add0~4_combout\ : std_logic;
SIGNAL \div|Add0~5\ : std_logic;
SIGNAL \div|Add0~6_combout\ : std_logic;
SIGNAL \div|Add0~7\ : std_logic;
SIGNAL \div|Add0~8_combout\ : std_logic;
SIGNAL \div|Add0~9\ : std_logic;
SIGNAL \div|Add0~10_combout\ : std_logic;
SIGNAL \div|Add0~11\ : std_logic;
SIGNAL \div|Add0~12_combout\ : std_logic;
SIGNAL \div|Add0~13\ : std_logic;
SIGNAL \div|Add0~14_combout\ : std_logic;
SIGNAL \div|Add0~15\ : std_logic;
SIGNAL \div|Add0~16_combout\ : std_logic;
SIGNAL \div|Add0~17\ : std_logic;
SIGNAL \div|Add0~18_combout\ : std_logic;
SIGNAL \div|Add0~19\ : std_logic;
SIGNAL \div|Add0~20_combout\ : std_logic;
SIGNAL \div|Add0~21\ : std_logic;
SIGNAL \div|Add0~22_combout\ : std_logic;
SIGNAL \div|Add0~23\ : std_logic;
SIGNAL \div|Add0~24_combout\ : std_logic;
SIGNAL \div|Add0~25\ : std_logic;
SIGNAL \div|Add0~26_combout\ : std_logic;
SIGNAL \div|Add0~27\ : std_logic;
SIGNAL \div|Add0~28_combout\ : std_logic;
SIGNAL \div|Add0~29\ : std_logic;
SIGNAL \div|Add0~30_combout\ : std_logic;
SIGNAL \div|Add0~31\ : std_logic;
SIGNAL \div|Add0~32_combout\ : std_logic;
SIGNAL \div|Add0~33\ : std_logic;
SIGNAL \div|Add0~34_combout\ : std_logic;
SIGNAL \div|Add0~35\ : std_logic;
SIGNAL \div|Add0~36_combout\ : std_logic;
SIGNAL \div|Add0~37\ : std_logic;
SIGNAL \div|Add0~38_combout\ : std_logic;
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
SIGNAL \div|Add2~13\ : std_logic;
SIGNAL \div|Add2~14_combout\ : std_logic;
SIGNAL \div|Add2~15\ : std_logic;
SIGNAL \div|Add2~16_combout\ : std_logic;
SIGNAL \div|Add2~17\ : std_logic;
SIGNAL \div|Add2~18_combout\ : std_logic;
SIGNAL \div|Add2~19\ : std_logic;
SIGNAL \div|Add2~20_combout\ : std_logic;
SIGNAL \div|Add2~21\ : std_logic;
SIGNAL \div|Add2~22_combout\ : std_logic;
SIGNAL \div|Add2~23\ : std_logic;
SIGNAL \div|Add2~24_combout\ : std_logic;
SIGNAL \div|Add2~25\ : std_logic;
SIGNAL \div|Add2~26_combout\ : std_logic;
SIGNAL \div|Add2~27\ : std_logic;
SIGNAL \div|Add2~28_combout\ : std_logic;
SIGNAL \div|Add2~29\ : std_logic;
SIGNAL \div|Add2~30_combout\ : std_logic;
SIGNAL \div|Add2~31\ : std_logic;
SIGNAL \div|Add2~32_combout\ : std_logic;
SIGNAL \div|Add2~33\ : std_logic;
SIGNAL \div|Add2~34_combout\ : std_logic;
SIGNAL \div|Add2~35\ : std_logic;
SIGNAL \div|Add2~36_combout\ : std_logic;
SIGNAL \div|Add2~37\ : std_logic;
SIGNAL \div|Add2~38_combout\ : std_logic;
SIGNAL \div|Add2~39\ : std_logic;
SIGNAL \div|Add2~40_combout\ : std_logic;
SIGNAL \div|Add2~41\ : std_logic;
SIGNAL \div|Add2~42_combout\ : std_logic;
SIGNAL \div|Add2~43\ : std_logic;
SIGNAL \div|Add2~44_combout\ : std_logic;
SIGNAL \div|Add2~45\ : std_logic;
SIGNAL \div|Add2~46_combout\ : std_logic;
SIGNAL \div|Add2~47\ : std_logic;
SIGNAL \div|Add2~48_combout\ : std_logic;
SIGNAL \div|Add2~49\ : std_logic;
SIGNAL \div|Add2~50_combout\ : std_logic;
SIGNAL \div|Add2~51\ : std_logic;
SIGNAL \div|Add2~52_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~0_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~1_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~3_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~6_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~12_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~17_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~21_combout\ : std_logic;
SIGNAL \div|Q_min~regout\ : std_logic;
SIGNAL \div|Q_ms~regout\ : std_logic;
SIGNAL \Equal2~0_combout\ : std_logic;
SIGNAL \Equal2~1_combout\ : std_logic;
SIGNAL \Equal3~0_combout\ : std_logic;
SIGNAL \Equal3~1_combout\ : std_logic;
SIGNAL \Equal3~2_combout\ : std_logic;
SIGNAL \div|Q_s~regout\ : std_logic;
SIGNAL \Equal4~0_combout\ : std_logic;
SIGNAL \Equal4~1_combout\ : std_logic;
SIGNAL \Equal2~2_combout\ : std_logic;
SIGNAL \Equal2~3_combout\ : std_logic;
SIGNAL \key_flag~regout\ : std_logic;
SIGNAL \led_c[1]~0_combout\ : std_logic;
SIGNAL \led_c[0]~1_combout\ : std_logic;
SIGNAL \led_c[0]~2_combout\ : std_logic;
SIGNAL \data_h_low~0_combout\ : std_logic;
SIGNAL \data_h_high[1]~3_combout\ : std_logic;
SIGNAL \led_c~3_combout\ : std_logic;
SIGNAL \div|Equal3~0_combout\ : std_logic;
SIGNAL \div|Equal3~1_combout\ : std_logic;
SIGNAL \div|Q_min~0_combout\ : std_logic;
SIGNAL \div|Equal0~0_combout\ : std_logic;
SIGNAL \div|Equal0~1_combout\ : std_logic;
SIGNAL \div|Equal0~2_combout\ : std_logic;
SIGNAL \div|Equal0~3_combout\ : std_logic;
SIGNAL \div|Equal0~4_combout\ : std_logic;
SIGNAL \div|Equal0~5_combout\ : std_logic;
SIGNAL \div|Equal0~6_combout\ : std_logic;
SIGNAL \div|Q_ms~0_combout\ : std_logic;
SIGNAL \div|Equal2~0_combout\ : std_logic;
SIGNAL \div|Equal2~1_combout\ : std_logic;
SIGNAL \div|Equal2~2_combout\ : std_logic;
SIGNAL \div|Equal2~3_combout\ : std_logic;
SIGNAL \div|Equal2~4_combout\ : std_logic;
SIGNAL \div|Equal2~5_combout\ : std_logic;
SIGNAL \div|Equal2~6_combout\ : std_logic;
SIGNAL \div|Equal2~7_combout\ : std_logic;
SIGNAL \div|Equal2~8_combout\ : std_logic;
SIGNAL \div|Q_s~0_combout\ : std_logic;
SIGNAL \Equal5~0_combout\ : std_logic;
SIGNAL \Equal5~1_combout\ : std_logic;
SIGNAL \key_flag~0_combout\ : std_logic;
SIGNAL \Add0~59_combout\ : std_logic;
SIGNAL \Equal0~4_combout\ : std_logic;
SIGNAL \div|data_min~0_combout\ : std_logic;
SIGNAL \div|data_min~1_combout\ : std_logic;
SIGNAL \div|data_min~2_combout\ : std_logic;
SIGNAL \div|data_min~3_combout\ : std_logic;
SIGNAL \div|data_min~4_combout\ : std_logic;
SIGNAL \div|data_ms~0_combout\ : std_logic;
SIGNAL \div|data_ms~1_combout\ : std_logic;
SIGNAL \div|data_ms~2_combout\ : std_logic;
SIGNAL \div|data_ms~3_combout\ : std_logic;
SIGNAL \div|data_ms~4_combout\ : std_logic;
SIGNAL \div|data_ms~5_combout\ : std_logic;
SIGNAL \div|data_ms~6_combout\ : std_logic;
SIGNAL \div|data_s~0_combout\ : std_logic;
SIGNAL \div|data_s~1_combout\ : std_logic;
SIGNAL \div|data_s~2_combout\ : std_logic;
SIGNAL \div|data_s~3_combout\ : std_logic;
SIGNAL \div|data_s~4_combout\ : std_logic;
SIGNAL \div|data_s~5_combout\ : std_logic;
SIGNAL \div|data_s~6_combout\ : std_logic;
SIGNAL \div|data_s~7_combout\ : std_logic;
SIGNAL \div|data_s~8_combout\ : std_logic;
SIGNAL \data_time_count[0]~27_combout\ : std_logic;
SIGNAL \sysclk~combout\ : std_logic;
SIGNAL \key2~combout\ : std_logic;
SIGNAL \div|Q_s~clkctrl_outclk\ : std_logic;
SIGNAL \div|Q_ms~clkctrl_outclk\ : std_logic;
SIGNAL \div|Q_min~clkctrl_outclk\ : std_logic;
SIGNAL \sysclk~clkctrl_outclk\ : std_logic;
SIGNAL \key2~clkctrl_outclk\ : std_logic;
SIGNAL \Add0~41\ : std_logic;
SIGNAL \Add0~42_combout\ : std_logic;
SIGNAL \Add0~65_combout\ : std_logic;
SIGNAL \key1~combout\ : std_logic;
SIGNAL \key1~clkctrl_outclk\ : std_logic;
SIGNAL \LessThan0~0_combout\ : std_logic;
SIGNAL \Add0~49_combout\ : std_logic;
SIGNAL \Add0~52_combout\ : std_logic;
SIGNAL \Add0~9\ : std_logic;
SIGNAL \Add0~10_combout\ : std_logic;
SIGNAL \Add0~51_combout\ : std_logic;
SIGNAL \Add0~11\ : std_logic;
SIGNAL \Add0~13\ : std_logic;
SIGNAL \Add0~14_combout\ : std_logic;
SIGNAL \Add0~53_combout\ : std_logic;
SIGNAL \Add0~15\ : std_logic;
SIGNAL \Add0~16_combout\ : std_logic;
SIGNAL \Add0~48_combout\ : std_logic;
SIGNAL \Add0~17\ : std_logic;
SIGNAL \Add0~19\ : std_logic;
SIGNAL \Add0~21\ : std_logic;
SIGNAL \Add0~22_combout\ : std_logic;
SIGNAL \Add0~55_combout\ : std_logic;
SIGNAL \Add0~23\ : std_logic;
SIGNAL \Add0~24_combout\ : std_logic;
SIGNAL \Add0~57_combout\ : std_logic;
SIGNAL \COUNT1[8]~feeder_combout\ : std_logic;
SIGNAL \Add0~25\ : std_logic;
SIGNAL \Add0~26_combout\ : std_logic;
SIGNAL \Add0~56_combout\ : std_logic;
SIGNAL \Add0~27\ : std_logic;
SIGNAL \Add0~28_combout\ : std_logic;
SIGNAL \Add0~58_combout\ : std_logic;
SIGNAL \Add0~29\ : std_logic;
SIGNAL \Add0~31\ : std_logic;
SIGNAL \Add0~32_combout\ : std_logic;
SIGNAL \Add0~61_combout\ : std_logic;
SIGNAL \Add0~33\ : std_logic;
SIGNAL \Add0~35\ : std_logic;
SIGNAL \Add0~37\ : std_logic;
SIGNAL \Add0~38_combout\ : std_logic;
SIGNAL \Add0~63_combout\ : std_logic;
SIGNAL \Add0~39\ : std_logic;
SIGNAL \Add0~40_combout\ : std_logic;
SIGNAL \Add0~64_combout\ : std_logic;
SIGNAL \Add0~43\ : std_logic;
SIGNAL \Add0~44_combout\ : std_logic;
SIGNAL \Add0~66_combout\ : std_logic;
SIGNAL \Add0~36_combout\ : std_logic;
SIGNAL \Add0~60_combout\ : std_logic;
SIGNAL \LessThan0~1_combout\ : std_logic;
SIGNAL \Add0~34_combout\ : std_logic;
SIGNAL \Add0~62_combout\ : std_logic;
SIGNAL \COUNT1[13]~feeder_combout\ : std_logic;
SIGNAL \LessThan0~3_combout\ : std_logic;
SIGNAL \Add0~54_combout\ : std_logic;
SIGNAL \LessThan0~2_combout\ : std_logic;
SIGNAL \LessThan0~4_combout\ : std_logic;
SIGNAL \COUNT1[19]~feeder_combout\ : std_logic;
SIGNAL \Add0~45\ : std_logic;
SIGNAL \Add0~46_combout\ : std_logic;
SIGNAL \Add0~67_combout\ : std_logic;
SIGNAL \Equal0~0_combout\ : std_logic;
SIGNAL \Equal0~5_combout\ : std_logic;
SIGNAL \Equal0~2_combout\ : std_logic;
SIGNAL \Add0~50_combout\ : std_logic;
SIGNAL \Equal0~1_combout\ : std_logic;
SIGNAL \Equal0~3_combout\ : std_logic;
SIGNAL \Equal0~6_combout\ : std_logic;
SIGNAL \key_signal[2]~clkctrl_outclk\ : std_logic;
SIGNAL \Add1~1_combout\ : std_logic;
SIGNAL \Equal1~0_combout\ : std_logic;
SIGNAL \data_mode[0]~0_combout\ : std_logic;
SIGNAL \Add1~0_combout\ : std_logic;
SIGNAL \Add1~2_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~10_combout\ : std_logic;
SIGNAL \Equal7~0_combout\ : std_logic;
SIGNAL \data_min_high[0]~4_combout\ : std_logic;
SIGNAL \Add7~0_combout\ : std_logic;
SIGNAL \Add5~0_combout\ : std_logic;
SIGNAL \Add5~1\ : std_logic;
SIGNAL \Add5~2_combout\ : std_logic;
SIGNAL \data_min_low~0_combout\ : std_logic;
SIGNAL \Add5~3\ : std_logic;
SIGNAL \Add5~5\ : std_logic;
SIGNAL \Add5~6_combout\ : std_logic;
SIGNAL \data_min_low~1_combout\ : std_logic;
SIGNAL \Add5~4_combout\ : std_logic;
SIGNAL \Equal12~0_combout\ : std_logic;
SIGNAL \data_min_high[3]~2_combout\ : std_logic;
SIGNAL \data_min_high[3]~3_combout\ : std_logic;
SIGNAL \data_min_high~1_combout\ : std_logic;
SIGNAL \Equal12~1_combout\ : std_logic;
SIGNAL \data_min_high~0_combout\ : std_logic;
SIGNAL \Equal13~0_combout\ : std_logic;
SIGNAL \data_h_high[0]~2_combout\ : std_logic;
SIGNAL \data_h[1]~7\ : std_logic;
SIGNAL \data_h[2]~9\ : std_logic;
SIGNAL \data_h[3]~11\ : std_logic;
SIGNAL \data_h[4]~13\ : std_logic;
SIGNAL \data_h[5]~14_combout\ : std_logic;
SIGNAL \data_h[4]~12_combout\ : std_logic;
SIGNAL \data_h[1]~6_combout\ : std_logic;
SIGNAL \data_h[2]~8_combout\ : std_logic;
SIGNAL \data_h[3]~10_combout\ : std_logic;
SIGNAL \Equal15~0_combout\ : std_logic;
SIGNAL \Equal15~1_combout\ : std_logic;
SIGNAL \data_count_seg~2_combout\ : std_logic;
SIGNAL \data_count_seg[3]~3_combout\ : std_logic;
SIGNAL \data_count_seg~1_combout\ : std_logic;
SIGNAL \Equal10~0_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~7_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~8_combout\ : std_logic;
SIGNAL \tmp_seg7data~9_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~11_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~18_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~16_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~19_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~13_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~5_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~14_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~4_combout\ : std_logic;
SIGNAL \data_count_seg[1]~0_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~2_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~15_combout\ : std_logic;
SIGNAL \Add7~1\ : std_logic;
SIGNAL \Add7~3\ : std_logic;
SIGNAL \Add7~4_combout\ : std_logic;
SIGNAL \Add7~5\ : std_logic;
SIGNAL \Add7~6_combout\ : std_logic;
SIGNAL \data_h_low~1_combout\ : std_logic;
SIGNAL \Add7~7\ : std_logic;
SIGNAL \Add7~8_combout\ : std_logic;
SIGNAL \Equal14~0_combout\ : std_logic;
SIGNAL \data_h_high[0]~7_combout\ : std_logic;
SIGNAL \Equal14~1_combout\ : std_logic;
SIGNAL \data_h_high[2]~4_combout\ : std_logic;
SIGNAL \data_h_high[2]~5_combout\ : std_logic;
SIGNAL \data_h_high[3]~6_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~20_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~22_combout\ : std_logic;
SIGNAL \dis|Mux6~0_combout\ : std_logic;
SIGNAL \dis|Mux5~0_combout\ : std_logic;
SIGNAL \dis|Mux4~0_combout\ : std_logic;
SIGNAL \dis|Mux3~0_combout\ : std_logic;
SIGNAL \dis|Mux2~0_combout\ : std_logic;
SIGNAL \dis|Mux1~0_combout\ : std_logic;
SIGNAL \dis|Mux0~0_combout\ : std_logic;
SIGNAL \seg7com~0_combout\ : std_logic;
SIGNAL \Equal9~0_combout\ : std_logic;
SIGNAL data_time_tmp : std_logic_vector(9 DOWNTO 0);
SIGNAL data_time_count : std_logic_vector(9 DOWNTO 0);
SIGNAL data_mode : std_logic_vector(3 DOWNTO 0);
SIGNAL data_min_low : std_logic_vector(4 DOWNTO 0);
SIGNAL data_min_high : std_logic_vector(3 DOWNTO 0);
SIGNAL data_h_low : std_logic_vector(4 DOWNTO 0);
SIGNAL data_h_high : std_logic_vector(3 DOWNTO 0);
SIGNAL data_h : std_logic_vector(6 DOWNTO 0);
SIGNAL data_count_seg : std_logic_vector(3 DOWNTO 0);
SIGNAL COUNT1 : std_logic_vector(19 DOWNTO 0);
SIGNAL \div|data_s\ : std_logic_vector(26 DOWNTO 0);
SIGNAL \div|data_ms\ : std_logic_vector(19 DOWNTO 0);
SIGNAL \div|data_min\ : std_logic_vector(6 DOWNTO 0);
SIGNAL led_p : std_logic_vector(1 DOWNTO 0);
SIGNAL led_c : std_logic_vector(1 DOWNTO 0);
SIGNAL key_signal : std_logic_vector(7 DOWNTO 0);
SIGNAL \ALT_INV_key2~clkctrl_outclk\ : std_logic;
SIGNAL \dis|ALT_INV_Mux0~0_combout\ : std_logic;
SIGNAL \ALT_INV_Equal9~0_combout\ : std_logic;
SIGNAL \ALT_INV_key1~combout\ : std_logic;

BEGIN

ww_key1 <= key1;
ww_key2 <= key2;
ww_key3 <= key3;
ww_key4 <= key4;
ww_key5 <= key5;
ww_sysclk <= sysclk;
seg7data <= ww_seg7data;
seg7com <= ww_seg7com;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\div|Q_s~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_s~regout\);

\div|Q_ms~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_ms~regout\);

\div|Q_min~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_min~regout\);

\sysclk~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \sysclk~combout\);

\key2~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \key2~combout\);

\key1~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \key1~combout\);

\key_signal[2]~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & key_signal(2));
\ALT_INV_key2~clkctrl_outclk\ <= NOT \key2~clkctrl_outclk\;
\dis|ALT_INV_Mux0~0_combout\ <= NOT \dis|Mux0~0_combout\;
\ALT_INV_Equal9~0_combout\ <= NOT \Equal9~0_combout\;
\ALT_INV_key1~combout\ <= NOT \key1~combout\;

-- Location: LCFF_X25_Y6_N29
\data_h[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[6]~16_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(6));

-- Location: LCFF_X17_Y8_N27
\data_time_count[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[9]~25_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(9));

-- Location: LCFF_X17_Y8_N25
\data_time_count[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[8]~23_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(8));

-- Location: LCFF_X17_Y8_N23
\data_time_count[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[7]~21_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(7));

-- Location: LCFF_X17_Y8_N21
\data_time_count[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[6]~19_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(6));

-- Location: LCFF_X17_Y8_N19
\data_time_count[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[5]~17_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(5));

-- Location: LCFF_X18_Y8_N1
\data_time_count[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	sdata => \data_time_count[4]~15_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(4));

-- Location: LCFF_X17_Y8_N15
\data_time_count[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[3]~13_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(3));

-- Location: LCFF_X17_Y8_N13
\data_time_count[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[2]~11_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(2));

-- Location: LCFF_X18_Y8_N31
\data_time_count[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	sdata => \data_time_count[1]~9_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(1));

-- Location: LCCOMB_X18_Y8_N4
\Add3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~0_combout\ = (data_time_tmp(0) & (data_time_count(0) $ (VCC))) # (!data_time_tmp(0) & ((data_time_count(0)) # (GND)))
-- \Add3~1\ = CARRY((data_time_count(0)) # (!data_time_tmp(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110011011011101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(0),
	datab => data_time_count(0),
	datad => VCC,
	combout => \Add3~0_combout\,
	cout => \Add3~1\);

-- Location: LCCOMB_X18_Y8_N6
\Add3~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~2_combout\ = (data_time_tmp(1) & ((data_time_count(1) & (!\Add3~1\)) # (!data_time_count(1) & ((\Add3~1\) # (GND))))) # (!data_time_tmp(1) & ((data_time_count(1) & (\Add3~1\ & VCC)) # (!data_time_count(1) & (!\Add3~1\))))
-- \Add3~3\ = CARRY((data_time_tmp(1) & ((!\Add3~1\) # (!data_time_count(1)))) # (!data_time_tmp(1) & (!data_time_count(1) & !\Add3~1\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100100101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(1),
	datab => data_time_count(1),
	datad => VCC,
	cin => \Add3~1\,
	combout => \Add3~2_combout\,
	cout => \Add3~3\);

-- Location: LCCOMB_X18_Y8_N8
\Add3~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~4_combout\ = ((data_time_count(2) $ (data_time_tmp(2) $ (\Add3~3\)))) # (GND)
-- \Add3~5\ = CARRY((data_time_count(2) & ((!\Add3~3\) # (!data_time_tmp(2)))) # (!data_time_count(2) & (!data_time_tmp(2) & !\Add3~3\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011000101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(2),
	datab => data_time_tmp(2),
	datad => VCC,
	cin => \Add3~3\,
	combout => \Add3~4_combout\,
	cout => \Add3~5\);

-- Location: LCCOMB_X18_Y8_N10
\Add3~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~6_combout\ = (data_time_count(3) & ((data_time_tmp(3) & (!\Add3~5\)) # (!data_time_tmp(3) & (\Add3~5\ & VCC)))) # (!data_time_count(3) & ((data_time_tmp(3) & ((\Add3~5\) # (GND))) # (!data_time_tmp(3) & (!\Add3~5\))))
-- \Add3~7\ = CARRY((data_time_count(3) & (data_time_tmp(3) & !\Add3~5\)) # (!data_time_count(3) & ((data_time_tmp(3)) # (!\Add3~5\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100101001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(3),
	datab => data_time_tmp(3),
	datad => VCC,
	cin => \Add3~5\,
	combout => \Add3~6_combout\,
	cout => \Add3~7\);

-- Location: LCCOMB_X18_Y8_N12
\Add3~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~8_combout\ = ((data_time_tmp(4) $ (data_time_count(4) $ (\Add3~7\)))) # (GND)
-- \Add3~9\ = CARRY((data_time_tmp(4) & (data_time_count(4) & !\Add3~7\)) # (!data_time_tmp(4) & ((data_time_count(4)) # (!\Add3~7\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011001001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(4),
	datab => data_time_count(4),
	datad => VCC,
	cin => \Add3~7\,
	combout => \Add3~8_combout\,
	cout => \Add3~9\);

-- Location: LCCOMB_X18_Y8_N14
\Add3~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~10_combout\ = (data_time_count(5) & ((data_time_tmp(5) & (!\Add3~9\)) # (!data_time_tmp(5) & (\Add3~9\ & VCC)))) # (!data_time_count(5) & ((data_time_tmp(5) & ((\Add3~9\) # (GND))) # (!data_time_tmp(5) & (!\Add3~9\))))
-- \Add3~11\ = CARRY((data_time_count(5) & (data_time_tmp(5) & !\Add3~9\)) # (!data_time_count(5) & ((data_time_tmp(5)) # (!\Add3~9\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100101001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(5),
	datab => data_time_tmp(5),
	datad => VCC,
	cin => \Add3~9\,
	combout => \Add3~10_combout\,
	cout => \Add3~11\);

-- Location: LCCOMB_X18_Y8_N16
\Add3~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~12_combout\ = ((data_time_tmp(6) $ (data_time_count(6) $ (\Add3~11\)))) # (GND)
-- \Add3~13\ = CARRY((data_time_tmp(6) & (data_time_count(6) & !\Add3~11\)) # (!data_time_tmp(6) & ((data_time_count(6)) # (!\Add3~11\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011001001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(6),
	datab => data_time_count(6),
	datad => VCC,
	cin => \Add3~11\,
	combout => \Add3~12_combout\,
	cout => \Add3~13\);

-- Location: LCCOMB_X18_Y8_N18
\Add3~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~14_combout\ = (data_time_tmp(7) & ((data_time_count(7) & (!\Add3~13\)) # (!data_time_count(7) & ((\Add3~13\) # (GND))))) # (!data_time_tmp(7) & ((data_time_count(7) & (\Add3~13\ & VCC)) # (!data_time_count(7) & (!\Add3~13\))))
-- \Add3~15\ = CARRY((data_time_tmp(7) & ((!\Add3~13\) # (!data_time_count(7)))) # (!data_time_tmp(7) & (!data_time_count(7) & !\Add3~13\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100100101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(7),
	datab => data_time_count(7),
	datad => VCC,
	cin => \Add3~13\,
	combout => \Add3~14_combout\,
	cout => \Add3~15\);

-- Location: LCCOMB_X18_Y8_N20
\Add3~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~16_combout\ = ((data_time_tmp(8) $ (data_time_count(8) $ (\Add3~15\)))) # (GND)
-- \Add3~17\ = CARRY((data_time_tmp(8) & (data_time_count(8) & !\Add3~15\)) # (!data_time_tmp(8) & ((data_time_count(8)) # (!\Add3~15\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011001001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(8),
	datab => data_time_count(8),
	datad => VCC,
	cin => \Add3~15\,
	combout => \Add3~16_combout\,
	cout => \Add3~17\);

-- Location: LCCOMB_X18_Y8_N22
\Add3~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~18_combout\ = (data_time_tmp(9) & ((data_time_count(9) & (!\Add3~17\)) # (!data_time_count(9) & ((\Add3~17\) # (GND))))) # (!data_time_tmp(9) & ((data_time_count(9) & (\Add3~17\ & VCC)) # (!data_time_count(9) & (!\Add3~17\))))
-- \Add3~19\ = CARRY((data_time_tmp(9) & ((!\Add3~17\) # (!data_time_count(9)))) # (!data_time_tmp(9) & (!data_time_count(9) & !\Add3~17\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100100101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(9),
	datab => data_time_count(9),
	datad => VCC,
	cin => \Add3~17\,
	combout => \Add3~18_combout\,
	cout => \Add3~19\);

-- Location: LCCOMB_X18_Y8_N24
\Add3~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add3~20_combout\ = !\Add3~19\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	cin => \Add3~19\,
	combout => \Add3~20_combout\);

-- Location: LCCOMB_X25_Y6_N2
\Add7~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add7~2_combout\ = (data_h_low(1) & (!\Add7~1\)) # (!data_h_low(1) & ((\Add7~1\) # (GND)))
-- \Add7~3\ = CARRY((!\Add7~1\) # (!data_h_low(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(1),
	datad => VCC,
	cin => \Add7~1\,
	combout => \Add7~2_combout\,
	cout => \Add7~3\);

-- Location: LCCOMB_X26_Y6_N22
\Add5~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add5~6_combout\ = (data_min_low(3) & (!\Add5~5\)) # (!data_min_low(3) & ((\Add5~5\) # (GND)))
-- \Add5~7\ = CARRY((!\Add5~5\) # (!data_min_low(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(3),
	datad => VCC,
	cin => \Add5~5\,
	combout => \Add5~6_combout\,
	cout => \Add5~7\);

-- Location: LCCOMB_X25_Y6_N26
\data_h[5]~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[5]~14_combout\ = (data_h(5) & (\data_h[4]~13\ $ (GND))) # (!data_h(5) & (!\data_h[4]~13\ & VCC))
-- \data_h[5]~15\ = CARRY((data_h(5) & !\data_h[4]~13\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_h(5),
	datad => VCC,
	cin => \data_h[4]~13\,
	combout => \data_h[5]~14_combout\,
	cout => \data_h[5]~15\);

-- Location: LCCOMB_X25_Y6_N28
\data_h[6]~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[6]~16_combout\ = \data_h[5]~15\ $ (data_h(6))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => data_h(6),
	cin => \data_h[5]~15\,
	combout => \data_h[6]~16_combout\);

-- Location: LCCOMB_X26_Y6_N24
\Add5~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add5~8_combout\ = \Add5~7\ $ (!data_min_low(4))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => data_min_low(4),
	cin => \Add5~7\,
	combout => \Add5~8_combout\);

-- Location: LCCOMB_X17_Y8_N10
\data_time_count[1]~9\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[1]~9_combout\ = (data_time_count(1) & (data_time_count(0) $ (VCC))) # (!data_time_count(1) & (data_time_count(0) & VCC))
-- \data_time_count[1]~10\ = CARRY((data_time_count(1) & data_time_count(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110011010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(1),
	datab => data_time_count(0),
	datad => VCC,
	combout => \data_time_count[1]~9_combout\,
	cout => \data_time_count[1]~10\);

-- Location: LCCOMB_X17_Y8_N12
\data_time_count[2]~11\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[2]~11_combout\ = (data_time_count(2) & (!\data_time_count[1]~10\)) # (!data_time_count(2) & ((\data_time_count[1]~10\) # (GND)))
-- \data_time_count[2]~12\ = CARRY((!\data_time_count[1]~10\) # (!data_time_count(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(2),
	datad => VCC,
	cin => \data_time_count[1]~10\,
	combout => \data_time_count[2]~11_combout\,
	cout => \data_time_count[2]~12\);

-- Location: LCCOMB_X17_Y8_N14
\data_time_count[3]~13\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[3]~13_combout\ = (data_time_count(3) & (\data_time_count[2]~12\ $ (GND))) # (!data_time_count(3) & (!\data_time_count[2]~12\ & VCC))
-- \data_time_count[3]~14\ = CARRY((data_time_count(3) & !\data_time_count[2]~12\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(3),
	datad => VCC,
	cin => \data_time_count[2]~12\,
	combout => \data_time_count[3]~13_combout\,
	cout => \data_time_count[3]~14\);

-- Location: LCCOMB_X17_Y8_N16
\data_time_count[4]~15\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[4]~15_combout\ = (data_time_count(4) & (!\data_time_count[3]~14\)) # (!data_time_count(4) & ((\data_time_count[3]~14\) # (GND)))
-- \data_time_count[4]~16\ = CARRY((!\data_time_count[3]~14\) # (!data_time_count(4)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(4),
	datad => VCC,
	cin => \data_time_count[3]~14\,
	combout => \data_time_count[4]~15_combout\,
	cout => \data_time_count[4]~16\);

-- Location: LCCOMB_X17_Y8_N18
\data_time_count[5]~17\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[5]~17_combout\ = (data_time_count(5) & (\data_time_count[4]~16\ $ (GND))) # (!data_time_count(5) & (!\data_time_count[4]~16\ & VCC))
-- \data_time_count[5]~18\ = CARRY((data_time_count(5) & !\data_time_count[4]~16\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(5),
	datad => VCC,
	cin => \data_time_count[4]~16\,
	combout => \data_time_count[5]~17_combout\,
	cout => \data_time_count[5]~18\);

-- Location: LCCOMB_X17_Y8_N20
\data_time_count[6]~19\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[6]~19_combout\ = (data_time_count(6) & (!\data_time_count[5]~18\)) # (!data_time_count(6) & ((\data_time_count[5]~18\) # (GND)))
-- \data_time_count[6]~20\ = CARRY((!\data_time_count[5]~18\) # (!data_time_count(6)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(6),
	datad => VCC,
	cin => \data_time_count[5]~18\,
	combout => \data_time_count[6]~19_combout\,
	cout => \data_time_count[6]~20\);

-- Location: LCCOMB_X17_Y8_N22
\data_time_count[7]~21\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[7]~21_combout\ = (data_time_count(7) & (\data_time_count[6]~20\ $ (GND))) # (!data_time_count(7) & (!\data_time_count[6]~20\ & VCC))
-- \data_time_count[7]~22\ = CARRY((data_time_count(7) & !\data_time_count[6]~20\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(7),
	datad => VCC,
	cin => \data_time_count[6]~20\,
	combout => \data_time_count[7]~21_combout\,
	cout => \data_time_count[7]~22\);

-- Location: LCCOMB_X17_Y8_N24
\data_time_count[8]~23\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[8]~23_combout\ = (data_time_count(8) & (!\data_time_count[7]~22\)) # (!data_time_count(8) & ((\data_time_count[7]~22\) # (GND)))
-- \data_time_count[8]~24\ = CARRY((!\data_time_count[7]~22\) # (!data_time_count(8)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(8),
	datad => VCC,
	cin => \data_time_count[7]~22\,
	combout => \data_time_count[8]~23_combout\,
	cout => \data_time_count[8]~24\);

-- Location: LCCOMB_X17_Y8_N26
\data_time_count[9]~25\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[9]~25_combout\ = \data_time_count[8]~24\ $ (!data_time_count(9))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => data_time_count(9),
	cin => \data_time_count[8]~24\,
	combout => \data_time_count[9]~25_combout\);

-- Location: LCCOMB_X9_Y10_N12
\Add0~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~8_combout\ = COUNT1(0) $ (VCC)
-- \Add0~9\ = CARRY(COUNT1(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(0),
	datad => VCC,
	combout => \Add0~8_combout\,
	cout => \Add0~9\);

-- Location: LCCOMB_X9_Y10_N16
\Add0~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~12_combout\ = (COUNT1(2) & (\Add0~11\ $ (GND))) # (!COUNT1(2) & (!\Add0~11\ & VCC))
-- \Add0~13\ = CARRY((COUNT1(2) & !\Add0~11\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(2),
	datad => VCC,
	cin => \Add0~11\,
	combout => \Add0~12_combout\,
	cout => \Add0~13\);

-- Location: LCCOMB_X9_Y10_N22
\Add0~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~18_combout\ = (COUNT1(5) & (!\Add0~17\)) # (!COUNT1(5) & ((\Add0~17\) # (GND)))
-- \Add0~19\ = CARRY((!\Add0~17\) # (!COUNT1(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(5),
	datad => VCC,
	cin => \Add0~17\,
	combout => \Add0~18_combout\,
	cout => \Add0~19\);

-- Location: LCCOMB_X9_Y10_N24
\Add0~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~20_combout\ = (COUNT1(6) & (\Add0~19\ $ (GND))) # (!COUNT1(6) & (!\Add0~19\ & VCC))
-- \Add0~21\ = CARRY((COUNT1(6) & !\Add0~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(6),
	datad => VCC,
	cin => \Add0~19\,
	combout => \Add0~20_combout\,
	cout => \Add0~21\);

-- Location: LCCOMB_X9_Y9_N2
\Add0~30\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~30_combout\ = (COUNT1(11) & (!\Add0~29\)) # (!COUNT1(11) & ((\Add0~29\) # (GND)))
-- \Add0~31\ = CARRY((!\Add0~29\) # (!COUNT1(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(11),
	datad => VCC,
	cin => \Add0~29\,
	combout => \Add0~30_combout\,
	cout => \Add0~31\);

-- Location: LCCOMB_X27_Y7_N4
\div|Add3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~0_combout\ = \div|data_min\(0) $ (VCC)
-- \div|Add3~1\ = CARRY(\div|data_min\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(0),
	datad => VCC,
	combout => \div|Add3~0_combout\,
	cout => \div|Add3~1\);

-- Location: LCCOMB_X27_Y7_N6
\div|Add3~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~2_combout\ = (\div|data_min\(1) & (!\div|Add3~1\)) # (!\div|data_min\(1) & ((\div|Add3~1\) # (GND)))
-- \div|Add3~3\ = CARRY((!\div|Add3~1\) # (!\div|data_min\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(1),
	datad => VCC,
	cin => \div|Add3~1\,
	combout => \div|Add3~2_combout\,
	cout => \div|Add3~3\);

-- Location: LCCOMB_X27_Y7_N8
\div|Add3~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~4_combout\ = (\div|data_min\(2) & (\div|Add3~3\ $ (GND))) # (!\div|data_min\(2) & (!\div|Add3~3\ & VCC))
-- \div|Add3~5\ = CARRY((\div|data_min\(2) & !\div|Add3~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(2),
	datad => VCC,
	cin => \div|Add3~3\,
	combout => \div|Add3~4_combout\,
	cout => \div|Add3~5\);

-- Location: LCCOMB_X27_Y7_N10
\div|Add3~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~6_combout\ = (\div|data_min\(3) & (!\div|Add3~5\)) # (!\div|data_min\(3) & ((\div|Add3~5\) # (GND)))
-- \div|Add3~7\ = CARRY((!\div|Add3~5\) # (!\div|data_min\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(3),
	datad => VCC,
	cin => \div|Add3~5\,
	combout => \div|Add3~6_combout\,
	cout => \div|Add3~7\);

-- Location: LCCOMB_X27_Y7_N12
\div|Add3~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~8_combout\ = (\div|data_min\(4) & (\div|Add3~7\ $ (GND))) # (!\div|data_min\(4) & (!\div|Add3~7\ & VCC))
-- \div|Add3~9\ = CARRY((\div|data_min\(4) & !\div|Add3~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(4),
	datad => VCC,
	cin => \div|Add3~7\,
	combout => \div|Add3~8_combout\,
	cout => \div|Add3~9\);

-- Location: LCCOMB_X27_Y7_N14
\div|Add3~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~10_combout\ = (\div|data_min\(5) & (!\div|Add3~9\)) # (!\div|data_min\(5) & ((\div|Add3~9\) # (GND)))
-- \div|Add3~11\ = CARRY((!\div|Add3~9\) # (!\div|data_min\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(5),
	datad => VCC,
	cin => \div|Add3~9\,
	combout => \div|Add3~10_combout\,
	cout => \div|Add3~11\);

-- Location: LCCOMB_X27_Y7_N16
\div|Add3~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~12_combout\ = \div|Add3~11\ $ (!\div|data_min\(6))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \div|data_min\(6),
	cin => \div|Add3~11\,
	combout => \div|Add3~12_combout\);

-- Location: LCCOMB_X2_Y4_N12
\div|Add0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~0_combout\ = \div|data_ms\(0) $ (VCC)
-- \div|Add0~1\ = CARRY(\div|data_ms\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(0),
	datad => VCC,
	combout => \div|Add0~0_combout\,
	cout => \div|Add0~1\);

-- Location: LCCOMB_X2_Y4_N14
\div|Add0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~2_combout\ = (\div|data_ms\(1) & (!\div|Add0~1\)) # (!\div|data_ms\(1) & ((\div|Add0~1\) # (GND)))
-- \div|Add0~3\ = CARRY((!\div|Add0~1\) # (!\div|data_ms\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(1),
	datad => VCC,
	cin => \div|Add0~1\,
	combout => \div|Add0~2_combout\,
	cout => \div|Add0~3\);

-- Location: LCCOMB_X2_Y4_N16
\div|Add0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~4_combout\ = (\div|data_ms\(2) & (\div|Add0~3\ $ (GND))) # (!\div|data_ms\(2) & (!\div|Add0~3\ & VCC))
-- \div|Add0~5\ = CARRY((\div|data_ms\(2) & !\div|Add0~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(2),
	datad => VCC,
	cin => \div|Add0~3\,
	combout => \div|Add0~4_combout\,
	cout => \div|Add0~5\);

-- Location: LCCOMB_X2_Y4_N18
\div|Add0~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~6_combout\ = (\div|data_ms\(3) & (!\div|Add0~5\)) # (!\div|data_ms\(3) & ((\div|Add0~5\) # (GND)))
-- \div|Add0~7\ = CARRY((!\div|Add0~5\) # (!\div|data_ms\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(3),
	datad => VCC,
	cin => \div|Add0~5\,
	combout => \div|Add0~6_combout\,
	cout => \div|Add0~7\);

-- Location: LCCOMB_X2_Y4_N20
\div|Add0~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~8_combout\ = (\div|data_ms\(4) & (\div|Add0~7\ $ (GND))) # (!\div|data_ms\(4) & (!\div|Add0~7\ & VCC))
-- \div|Add0~9\ = CARRY((\div|data_ms\(4) & !\div|Add0~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(4),
	datad => VCC,
	cin => \div|Add0~7\,
	combout => \div|Add0~8_combout\,
	cout => \div|Add0~9\);

-- Location: LCCOMB_X2_Y4_N22
\div|Add0~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~10_combout\ = (\div|data_ms\(5) & (!\div|Add0~9\)) # (!\div|data_ms\(5) & ((\div|Add0~9\) # (GND)))
-- \div|Add0~11\ = CARRY((!\div|Add0~9\) # (!\div|data_ms\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(5),
	datad => VCC,
	cin => \div|Add0~9\,
	combout => \div|Add0~10_combout\,
	cout => \div|Add0~11\);

-- Location: LCCOMB_X2_Y4_N24
\div|Add0~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~12_combout\ = (\div|data_ms\(6) & (\div|Add0~11\ $ (GND))) # (!\div|data_ms\(6) & (!\div|Add0~11\ & VCC))
-- \div|Add0~13\ = CARRY((\div|data_ms\(6) & !\div|Add0~11\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(6),
	datad => VCC,
	cin => \div|Add0~11\,
	combout => \div|Add0~12_combout\,
	cout => \div|Add0~13\);

-- Location: LCCOMB_X2_Y4_N26
\div|Add0~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~14_combout\ = (\div|data_ms\(7) & (!\div|Add0~13\)) # (!\div|data_ms\(7) & ((\div|Add0~13\) # (GND)))
-- \div|Add0~15\ = CARRY((!\div|Add0~13\) # (!\div|data_ms\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(7),
	datad => VCC,
	cin => \div|Add0~13\,
	combout => \div|Add0~14_combout\,
	cout => \div|Add0~15\);

-- Location: LCCOMB_X2_Y4_N28
\div|Add0~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~16_combout\ = (\div|data_ms\(8) & (\div|Add0~15\ $ (GND))) # (!\div|data_ms\(8) & (!\div|Add0~15\ & VCC))
-- \div|Add0~17\ = CARRY((\div|data_ms\(8) & !\div|Add0~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(8),
	datad => VCC,
	cin => \div|Add0~15\,
	combout => \div|Add0~16_combout\,
	cout => \div|Add0~17\);

-- Location: LCCOMB_X2_Y4_N30
\div|Add0~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~18_combout\ = (\div|data_ms\(9) & (!\div|Add0~17\)) # (!\div|data_ms\(9) & ((\div|Add0~17\) # (GND)))
-- \div|Add0~19\ = CARRY((!\div|Add0~17\) # (!\div|data_ms\(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(9),
	datad => VCC,
	cin => \div|Add0~17\,
	combout => \div|Add0~18_combout\,
	cout => \div|Add0~19\);

-- Location: LCCOMB_X2_Y3_N0
\div|Add0~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~20_combout\ = (\div|data_ms\(10) & (\div|Add0~19\ $ (GND))) # (!\div|data_ms\(10) & (!\div|Add0~19\ & VCC))
-- \div|Add0~21\ = CARRY((\div|data_ms\(10) & !\div|Add0~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(10),
	datad => VCC,
	cin => \div|Add0~19\,
	combout => \div|Add0~20_combout\,
	cout => \div|Add0~21\);

-- Location: LCCOMB_X2_Y3_N2
\div|Add0~22\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~22_combout\ = (\div|data_ms\(11) & (!\div|Add0~21\)) # (!\div|data_ms\(11) & ((\div|Add0~21\) # (GND)))
-- \div|Add0~23\ = CARRY((!\div|Add0~21\) # (!\div|data_ms\(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(11),
	datad => VCC,
	cin => \div|Add0~21\,
	combout => \div|Add0~22_combout\,
	cout => \div|Add0~23\);

-- Location: LCCOMB_X2_Y3_N4
\div|Add0~24\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~24_combout\ = (\div|data_ms\(12) & (\div|Add0~23\ $ (GND))) # (!\div|data_ms\(12) & (!\div|Add0~23\ & VCC))
-- \div|Add0~25\ = CARRY((\div|data_ms\(12) & !\div|Add0~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(12),
	datad => VCC,
	cin => \div|Add0~23\,
	combout => \div|Add0~24_combout\,
	cout => \div|Add0~25\);

-- Location: LCCOMB_X2_Y3_N6
\div|Add0~26\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~26_combout\ = (\div|data_ms\(13) & (!\div|Add0~25\)) # (!\div|data_ms\(13) & ((\div|Add0~25\) # (GND)))
-- \div|Add0~27\ = CARRY((!\div|Add0~25\) # (!\div|data_ms\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(13),
	datad => VCC,
	cin => \div|Add0~25\,
	combout => \div|Add0~26_combout\,
	cout => \div|Add0~27\);

-- Location: LCCOMB_X2_Y3_N8
\div|Add0~28\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~28_combout\ = (\div|data_ms\(14) & (\div|Add0~27\ $ (GND))) # (!\div|data_ms\(14) & (!\div|Add0~27\ & VCC))
-- \div|Add0~29\ = CARRY((\div|data_ms\(14) & !\div|Add0~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(14),
	datad => VCC,
	cin => \div|Add0~27\,
	combout => \div|Add0~28_combout\,
	cout => \div|Add0~29\);

-- Location: LCCOMB_X2_Y3_N10
\div|Add0~30\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~30_combout\ = (\div|data_ms\(15) & (!\div|Add0~29\)) # (!\div|data_ms\(15) & ((\div|Add0~29\) # (GND)))
-- \div|Add0~31\ = CARRY((!\div|Add0~29\) # (!\div|data_ms\(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(15),
	datad => VCC,
	cin => \div|Add0~29\,
	combout => \div|Add0~30_combout\,
	cout => \div|Add0~31\);

-- Location: LCCOMB_X2_Y3_N12
\div|Add0~32\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~32_combout\ = (\div|data_ms\(16) & (\div|Add0~31\ $ (GND))) # (!\div|data_ms\(16) & (!\div|Add0~31\ & VCC))
-- \div|Add0~33\ = CARRY((\div|data_ms\(16) & !\div|Add0~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(16),
	datad => VCC,
	cin => \div|Add0~31\,
	combout => \div|Add0~32_combout\,
	cout => \div|Add0~33\);

-- Location: LCCOMB_X2_Y3_N14
\div|Add0~34\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~34_combout\ = (\div|data_ms\(17) & (!\div|Add0~33\)) # (!\div|data_ms\(17) & ((\div|Add0~33\) # (GND)))
-- \div|Add0~35\ = CARRY((!\div|Add0~33\) # (!\div|data_ms\(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(17),
	datad => VCC,
	cin => \div|Add0~33\,
	combout => \div|Add0~34_combout\,
	cout => \div|Add0~35\);

-- Location: LCCOMB_X2_Y3_N16
\div|Add0~36\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~36_combout\ = (\div|data_ms\(18) & (\div|Add0~35\ $ (GND))) # (!\div|data_ms\(18) & (!\div|Add0~35\ & VCC))
-- \div|Add0~37\ = CARRY((\div|data_ms\(18) & !\div|Add0~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(18),
	datad => VCC,
	cin => \div|Add0~35\,
	combout => \div|Add0~36_combout\,
	cout => \div|Add0~37\);

-- Location: LCCOMB_X2_Y3_N18
\div|Add0~38\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~38_combout\ = \div|Add0~37\ $ (\div|data_ms\(19))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \div|data_ms\(19),
	cin => \div|Add0~37\,
	combout => \div|Add0~38_combout\);

-- Location: LCCOMB_X2_Y6_N6
\div|Add2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~0_combout\ = \div|data_s\(0) $ (VCC)
-- \div|Add2~1\ = CARRY(\div|data_s\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(0),
	datad => VCC,
	combout => \div|Add2~0_combout\,
	cout => \div|Add2~1\);

-- Location: LCCOMB_X2_Y6_N8
\div|Add2~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~2_combout\ = (\div|data_s\(1) & (!\div|Add2~1\)) # (!\div|data_s\(1) & ((\div|Add2~1\) # (GND)))
-- \div|Add2~3\ = CARRY((!\div|Add2~1\) # (!\div|data_s\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(1),
	datad => VCC,
	cin => \div|Add2~1\,
	combout => \div|Add2~2_combout\,
	cout => \div|Add2~3\);

-- Location: LCCOMB_X2_Y6_N10
\div|Add2~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~4_combout\ = (\div|data_s\(2) & (\div|Add2~3\ $ (GND))) # (!\div|data_s\(2) & (!\div|Add2~3\ & VCC))
-- \div|Add2~5\ = CARRY((\div|data_s\(2) & !\div|Add2~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(2),
	datad => VCC,
	cin => \div|Add2~3\,
	combout => \div|Add2~4_combout\,
	cout => \div|Add2~5\);

-- Location: LCCOMB_X2_Y6_N12
\div|Add2~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~6_combout\ = (\div|data_s\(3) & (!\div|Add2~5\)) # (!\div|data_s\(3) & ((\div|Add2~5\) # (GND)))
-- \div|Add2~7\ = CARRY((!\div|Add2~5\) # (!\div|data_s\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(3),
	datad => VCC,
	cin => \div|Add2~5\,
	combout => \div|Add2~6_combout\,
	cout => \div|Add2~7\);

-- Location: LCCOMB_X2_Y6_N14
\div|Add2~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~8_combout\ = (\div|data_s\(4) & (\div|Add2~7\ $ (GND))) # (!\div|data_s\(4) & (!\div|Add2~7\ & VCC))
-- \div|Add2~9\ = CARRY((\div|data_s\(4) & !\div|Add2~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(4),
	datad => VCC,
	cin => \div|Add2~7\,
	combout => \div|Add2~8_combout\,
	cout => \div|Add2~9\);

-- Location: LCCOMB_X2_Y6_N16
\div|Add2~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~10_combout\ = (\div|data_s\(5) & (!\div|Add2~9\)) # (!\div|data_s\(5) & ((\div|Add2~9\) # (GND)))
-- \div|Add2~11\ = CARRY((!\div|Add2~9\) # (!\div|data_s\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(5),
	datad => VCC,
	cin => \div|Add2~9\,
	combout => \div|Add2~10_combout\,
	cout => \div|Add2~11\);

-- Location: LCCOMB_X2_Y6_N18
\div|Add2~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~12_combout\ = (\div|data_s\(6) & (\div|Add2~11\ $ (GND))) # (!\div|data_s\(6) & (!\div|Add2~11\ & VCC))
-- \div|Add2~13\ = CARRY((\div|data_s\(6) & !\div|Add2~11\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(6),
	datad => VCC,
	cin => \div|Add2~11\,
	combout => \div|Add2~12_combout\,
	cout => \div|Add2~13\);

-- Location: LCCOMB_X2_Y6_N20
\div|Add2~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~14_combout\ = (\div|data_s\(7) & (!\div|Add2~13\)) # (!\div|data_s\(7) & ((\div|Add2~13\) # (GND)))
-- \div|Add2~15\ = CARRY((!\div|Add2~13\) # (!\div|data_s\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(7),
	datad => VCC,
	cin => \div|Add2~13\,
	combout => \div|Add2~14_combout\,
	cout => \div|Add2~15\);

-- Location: LCCOMB_X2_Y6_N22
\div|Add2~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~16_combout\ = (\div|data_s\(8) & (\div|Add2~15\ $ (GND))) # (!\div|data_s\(8) & (!\div|Add2~15\ & VCC))
-- \div|Add2~17\ = CARRY((\div|data_s\(8) & !\div|Add2~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(8),
	datad => VCC,
	cin => \div|Add2~15\,
	combout => \div|Add2~16_combout\,
	cout => \div|Add2~17\);

-- Location: LCCOMB_X2_Y6_N24
\div|Add2~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~18_combout\ = (\div|data_s\(9) & (!\div|Add2~17\)) # (!\div|data_s\(9) & ((\div|Add2~17\) # (GND)))
-- \div|Add2~19\ = CARRY((!\div|Add2~17\) # (!\div|data_s\(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(9),
	datad => VCC,
	cin => \div|Add2~17\,
	combout => \div|Add2~18_combout\,
	cout => \div|Add2~19\);

-- Location: LCCOMB_X2_Y6_N26
\div|Add2~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~20_combout\ = (\div|data_s\(10) & (\div|Add2~19\ $ (GND))) # (!\div|data_s\(10) & (!\div|Add2~19\ & VCC))
-- \div|Add2~21\ = CARRY((\div|data_s\(10) & !\div|Add2~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(10),
	datad => VCC,
	cin => \div|Add2~19\,
	combout => \div|Add2~20_combout\,
	cout => \div|Add2~21\);

-- Location: LCCOMB_X2_Y6_N28
\div|Add2~22\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~22_combout\ = (\div|data_s\(11) & (!\div|Add2~21\)) # (!\div|data_s\(11) & ((\div|Add2~21\) # (GND)))
-- \div|Add2~23\ = CARRY((!\div|Add2~21\) # (!\div|data_s\(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(11),
	datad => VCC,
	cin => \div|Add2~21\,
	combout => \div|Add2~22_combout\,
	cout => \div|Add2~23\);

-- Location: LCCOMB_X2_Y6_N30
\div|Add2~24\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~24_combout\ = (\div|data_s\(12) & (\div|Add2~23\ $ (GND))) # (!\div|data_s\(12) & (!\div|Add2~23\ & VCC))
-- \div|Add2~25\ = CARRY((\div|data_s\(12) & !\div|Add2~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(12),
	datad => VCC,
	cin => \div|Add2~23\,
	combout => \div|Add2~24_combout\,
	cout => \div|Add2~25\);

-- Location: LCCOMB_X2_Y5_N0
\div|Add2~26\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~26_combout\ = (\div|data_s\(13) & (!\div|Add2~25\)) # (!\div|data_s\(13) & ((\div|Add2~25\) # (GND)))
-- \div|Add2~27\ = CARRY((!\div|Add2~25\) # (!\div|data_s\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(13),
	datad => VCC,
	cin => \div|Add2~25\,
	combout => \div|Add2~26_combout\,
	cout => \div|Add2~27\);

-- Location: LCCOMB_X2_Y5_N2
\div|Add2~28\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~28_combout\ = (\div|data_s\(14) & (\div|Add2~27\ $ (GND))) # (!\div|data_s\(14) & (!\div|Add2~27\ & VCC))
-- \div|Add2~29\ = CARRY((\div|data_s\(14) & !\div|Add2~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(14),
	datad => VCC,
	cin => \div|Add2~27\,
	combout => \div|Add2~28_combout\,
	cout => \div|Add2~29\);

-- Location: LCCOMB_X2_Y5_N4
\div|Add2~30\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~30_combout\ = (\div|data_s\(15) & (!\div|Add2~29\)) # (!\div|data_s\(15) & ((\div|Add2~29\) # (GND)))
-- \div|Add2~31\ = CARRY((!\div|Add2~29\) # (!\div|data_s\(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(15),
	datad => VCC,
	cin => \div|Add2~29\,
	combout => \div|Add2~30_combout\,
	cout => \div|Add2~31\);

-- Location: LCCOMB_X2_Y5_N6
\div|Add2~32\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~32_combout\ = (\div|data_s\(16) & (\div|Add2~31\ $ (GND))) # (!\div|data_s\(16) & (!\div|Add2~31\ & VCC))
-- \div|Add2~33\ = CARRY((\div|data_s\(16) & !\div|Add2~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(16),
	datad => VCC,
	cin => \div|Add2~31\,
	combout => \div|Add2~32_combout\,
	cout => \div|Add2~33\);

-- Location: LCCOMB_X2_Y5_N8
\div|Add2~34\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~34_combout\ = (\div|data_s\(17) & (!\div|Add2~33\)) # (!\div|data_s\(17) & ((\div|Add2~33\) # (GND)))
-- \div|Add2~35\ = CARRY((!\div|Add2~33\) # (!\div|data_s\(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(17),
	datad => VCC,
	cin => \div|Add2~33\,
	combout => \div|Add2~34_combout\,
	cout => \div|Add2~35\);

-- Location: LCCOMB_X2_Y5_N10
\div|Add2~36\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~36_combout\ = (\div|data_s\(18) & (\div|Add2~35\ $ (GND))) # (!\div|data_s\(18) & (!\div|Add2~35\ & VCC))
-- \div|Add2~37\ = CARRY((\div|data_s\(18) & !\div|Add2~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(18),
	datad => VCC,
	cin => \div|Add2~35\,
	combout => \div|Add2~36_combout\,
	cout => \div|Add2~37\);

-- Location: LCCOMB_X2_Y5_N12
\div|Add2~38\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~38_combout\ = (\div|data_s\(19) & (!\div|Add2~37\)) # (!\div|data_s\(19) & ((\div|Add2~37\) # (GND)))
-- \div|Add2~39\ = CARRY((!\div|Add2~37\) # (!\div|data_s\(19)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(19),
	datad => VCC,
	cin => \div|Add2~37\,
	combout => \div|Add2~38_combout\,
	cout => \div|Add2~39\);

-- Location: LCCOMB_X2_Y5_N14
\div|Add2~40\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~40_combout\ = (\div|data_s\(20) & (\div|Add2~39\ $ (GND))) # (!\div|data_s\(20) & (!\div|Add2~39\ & VCC))
-- \div|Add2~41\ = CARRY((\div|data_s\(20) & !\div|Add2~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(20),
	datad => VCC,
	cin => \div|Add2~39\,
	combout => \div|Add2~40_combout\,
	cout => \div|Add2~41\);

-- Location: LCCOMB_X2_Y5_N16
\div|Add2~42\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~42_combout\ = (\div|data_s\(21) & (!\div|Add2~41\)) # (!\div|data_s\(21) & ((\div|Add2~41\) # (GND)))
-- \div|Add2~43\ = CARRY((!\div|Add2~41\) # (!\div|data_s\(21)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(21),
	datad => VCC,
	cin => \div|Add2~41\,
	combout => \div|Add2~42_combout\,
	cout => \div|Add2~43\);

-- Location: LCCOMB_X2_Y5_N18
\div|Add2~44\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~44_combout\ = (\div|data_s\(22) & (\div|Add2~43\ $ (GND))) # (!\div|data_s\(22) & (!\div|Add2~43\ & VCC))
-- \div|Add2~45\ = CARRY((\div|data_s\(22) & !\div|Add2~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(22),
	datad => VCC,
	cin => \div|Add2~43\,
	combout => \div|Add2~44_combout\,
	cout => \div|Add2~45\);

-- Location: LCCOMB_X2_Y5_N20
\div|Add2~46\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~46_combout\ = (\div|data_s\(23) & (!\div|Add2~45\)) # (!\div|data_s\(23) & ((\div|Add2~45\) # (GND)))
-- \div|Add2~47\ = CARRY((!\div|Add2~45\) # (!\div|data_s\(23)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(23),
	datad => VCC,
	cin => \div|Add2~45\,
	combout => \div|Add2~46_combout\,
	cout => \div|Add2~47\);

-- Location: LCCOMB_X2_Y5_N22
\div|Add2~48\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~48_combout\ = (\div|data_s\(24) & (\div|Add2~47\ $ (GND))) # (!\div|data_s\(24) & (!\div|Add2~47\ & VCC))
-- \div|Add2~49\ = CARRY((\div|data_s\(24) & !\div|Add2~47\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(24),
	datad => VCC,
	cin => \div|Add2~47\,
	combout => \div|Add2~48_combout\,
	cout => \div|Add2~49\);

-- Location: LCCOMB_X2_Y5_N24
\div|Add2~50\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~50_combout\ = (\div|data_s\(25) & (!\div|Add2~49\)) # (!\div|data_s\(25) & ((\div|Add2~49\) # (GND)))
-- \div|Add2~51\ = CARRY((!\div|Add2~49\) # (!\div|data_s\(25)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(25),
	datad => VCC,
	cin => \div|Add2~49\,
	combout => \div|Add2~50_combout\,
	cout => \div|Add2~51\);

-- Location: LCCOMB_X2_Y5_N26
\div|Add2~52\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~52_combout\ = \div|Add2~51\ $ (!\div|data_s\(26))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \div|data_s\(26),
	cin => \div|Add2~51\,
	combout => \div|Add2~52_combout\);

-- Location: LCCOMB_X22_Y6_N16
\tmp_seg7data[0]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~0_combout\ = (data_count_seg(1) & (!data_count_seg(0) & (!data_count_seg(3) & !data_count_seg(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(0),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \tmp_seg7data[0]~0_combout\);

-- Location: LCCOMB_X24_Y6_N28
\tmp_seg7data[0]~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~1_combout\ = (\tmp_seg7data[0]~0_combout\ & (data_h_low(0))) # (!\tmp_seg7data[0]~0_combout\ & ((data_h_high(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111010110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~0_combout\,
	datac => data_h_low(0),
	datad => data_h_high(0),
	combout => \tmp_seg7data[0]~1_combout\);

-- Location: LCFF_X19_Y8_N17
\led_p[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \Equal3~2_combout\,
	ena => \led_c[1]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => led_p(0));

-- Location: LCFF_X19_Y8_N19
\led_c[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \led_c[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => led_c(0));

-- Location: LCCOMB_X20_Y6_N0
\tmp_seg7data[0]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~3_combout\ = (\tmp_seg7data[0]~2_combout\ & (((led_p(0) & \tmp_seg7data[0]~0_combout\)) # (!led_c(0)))) # (!\tmp_seg7data[0]~2_combout\ & (led_p(0) & ((\tmp_seg7data[0]~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~2_combout\,
	datab => led_p(0),
	datac => led_c(0),
	datad => \tmp_seg7data[0]~0_combout\,
	combout => \tmp_seg7data[0]~3_combout\);

-- Location: LCCOMB_X20_Y6_N6
\tmp_seg7data[0]~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~6_combout\ = (\tmp_seg7data[0]~1_combout\ & ((\tmp_seg7data[3]~5_combout\) # ((\tmp_seg7data[0]~3_combout\ & \tmp_seg7data[0]~4_combout\)))) # (!\tmp_seg7data[0]~1_combout\ & (\tmp_seg7data[0]~3_combout\ & (\tmp_seg7data[0]~4_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110101011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~1_combout\,
	datab => \tmp_seg7data[0]~3_combout\,
	datac => \tmp_seg7data[0]~4_combout\,
	datad => \tmp_seg7data[3]~5_combout\,
	combout => \tmp_seg7data[0]~6_combout\);

-- Location: LCFF_X25_Y6_N17
\data_h_low[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_low~0_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(1));

-- Location: LCFF_X25_Y6_N11
\data_h_high[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[1]~3_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(1));

-- Location: LCCOMB_X24_Y6_N16
\tmp_seg7data[1]~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~12_combout\ = (\tmp_seg7data[0]~0_combout\ & (data_h_low(1))) # (!\tmp_seg7data[0]~0_combout\ & ((data_h_high(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111010110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~0_combout\,
	datac => data_h_low(1),
	datad => data_h_high(1),
	combout => \tmp_seg7data[1]~12_combout\);

-- Location: LCFF_X19_Y8_N13
\led_c[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \led_c~3_combout\,
	ena => \led_c[1]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => led_c(1));

-- Location: LCCOMB_X24_Y6_N20
\tmp_seg7data[2]~17\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~17_combout\ = (\tmp_seg7data[3]~5_combout\ & ((\tmp_seg7data[0]~0_combout\ & (data_h_low(2))) # (!\tmp_seg7data[0]~0_combout\ & ((data_h_high(2))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(2),
	datab => data_h_high(2),
	datac => \tmp_seg7data[0]~0_combout\,
	datad => \tmp_seg7data[3]~5_combout\,
	combout => \tmp_seg7data[2]~17_combout\);

-- Location: LCCOMB_X24_Y6_N24
\tmp_seg7data[3]~21\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~21_combout\ = (\Equal9~0_combout\ & (((data_min_low(3))))) # (!\Equal9~0_combout\ & (data_min_high(3) & ((!\Equal10~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000011100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => data_min_high(3),
	datac => data_min_low(3),
	datad => \Equal10~0_combout\,
	combout => \tmp_seg7data[3]~21_combout\);

-- Location: LCFF_X27_Y7_N31
\div|Q_min\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|Q_min~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_min~regout\);

-- Location: LCFF_X26_Y6_N25
\data_min_low[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add5~8_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(4));

-- Location: LCFF_X1_Y3_N25
\div|Q_ms\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Q_ms~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_ms~regout\);

-- Location: LCFF_X18_Y8_N27
\data_time_count[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	sdata => \data_time_count[0]~27_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(0));

-- Location: LCCOMB_X18_Y8_N28
\Equal2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal2~0_combout\ = (!\Add3~16_combout\ & (!\Add3~14_combout\ & (\Add3~20_combout\ & !\Add3~18_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~16_combout\,
	datab => \Add3~14_combout\,
	datac => \Add3~20_combout\,
	datad => \Add3~18_combout\,
	combout => \Equal2~0_combout\);

-- Location: LCCOMB_X19_Y8_N30
\Equal2~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal2~1_combout\ = (\Add3~2_combout\ & !\Add3~12_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \Add3~2_combout\,
	datad => \Add3~12_combout\,
	combout => \Equal2~1_combout\);

-- Location: LCCOMB_X19_Y8_N20
\Equal3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal3~0_combout\ = (!\Add3~4_combout\ & (!\Add3~6_combout\ & \Add3~10_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~4_combout\,
	datac => \Add3~6_combout\,
	datad => \Add3~10_combout\,
	combout => \Equal3~0_combout\);

-- Location: LCCOMB_X19_Y8_N26
\Equal3~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal3~1_combout\ = (\Add3~0_combout\ & !\Add3~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \Add3~0_combout\,
	datad => \Add3~8_combout\,
	combout => \Equal3~1_combout\);

-- Location: LCCOMB_X19_Y8_N16
\Equal3~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal3~2_combout\ = (\Equal3~1_combout\ & (\Equal2~1_combout\ & (\Equal3~0_combout\ & \Equal2~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal3~1_combout\,
	datab => \Equal2~1_combout\,
	datac => \Equal3~0_combout\,
	datad => \Equal2~0_combout\,
	combout => \Equal3~2_combout\);

-- Location: LCFF_X1_Y6_N11
\div|Q_s\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Q_s~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_s~regout\);

-- Location: LCCOMB_X19_Y8_N28
\Equal4~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal4~0_combout\ = (!\Add3~0_combout\ & \Add3~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \Add3~0_combout\,
	datad => \Add3~8_combout\,
	combout => \Equal4~0_combout\);

-- Location: LCCOMB_X19_Y8_N14
\Equal4~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal4~1_combout\ = (\Equal2~1_combout\ & (\Equal4~0_combout\ & (\Equal3~0_combout\ & \Equal2~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal2~1_combout\,
	datab => \Equal4~0_combout\,
	datac => \Equal3~0_combout\,
	datad => \Equal2~0_combout\,
	combout => \Equal4~1_combout\);

-- Location: LCCOMB_X18_Y8_N2
\Equal2~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal2~2_combout\ = (!\Add3~0_combout\ & (\Add3~4_combout\ & (!\Add3~10_combout\ & \Add3~8_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~0_combout\,
	datab => \Add3~4_combout\,
	datac => \Add3~10_combout\,
	datad => \Add3~8_combout\,
	combout => \Equal2~2_combout\);

-- Location: LCCOMB_X19_Y8_N0
\Equal2~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal2~3_combout\ = (\Equal2~2_combout\ & (\Equal2~1_combout\ & (\Add3~6_combout\ & \Equal2~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal2~2_combout\,
	datab => \Equal2~1_combout\,
	datac => \Add3~6_combout\,
	datad => \Equal2~0_combout\,
	combout => \Equal2~3_combout\);

-- Location: LCFF_X19_Y8_N7
key_flag : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \key_flag~0_combout\,
	aclr => \ALT_INV_key2~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \key_flag~regout\);

-- Location: LCCOMB_X19_Y8_N4
\led_c[1]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c[1]~0_combout\ = (!\key_flag~regout\ & ((\Equal4~1_combout\) # ((\Equal3~2_combout\) # (\Equal2~3_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010101010100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key_flag~regout\,
	datab => \Equal4~1_combout\,
	datac => \Equal3~2_combout\,
	datad => \Equal2~3_combout\,
	combout => \led_c[1]~0_combout\);

-- Location: LCCOMB_X19_Y8_N10
\led_c[0]~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c[0]~1_combout\ = (!\key_flag~regout\ & ((\Equal4~1_combout\) # ((!\Equal3~2_combout\ & \Equal2~3_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100010101000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key_flag~regout\,
	datab => \Equal4~1_combout\,
	datac => \Equal3~2_combout\,
	datad => \Equal2~3_combout\,
	combout => \led_c[0]~1_combout\);

-- Location: LCCOMB_X19_Y8_N18
\led_c[0]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c[0]~2_combout\ = (!\led_c[0]~1_combout\ & ((led_c(0)) # ((\Equal3~2_combout\ & !\key_flag~regout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal3~2_combout\,
	datab => \key_flag~regout\,
	datac => led_c(0),
	datad => \led_c[0]~1_combout\,
	combout => \led_c[0]~2_combout\);

-- Location: LCCOMB_X25_Y6_N16
\data_h_low~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_low~0_combout\ = (\Add7~2_combout\ & ((!\Equal14~0_combout\) # (!data_h_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(0),
	datac => \Equal14~0_combout\,
	datad => \Add7~2_combout\,
	combout => \data_h_low~0_combout\);

-- Location: LCCOMB_X25_Y6_N10
\data_h_high[1]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[1]~3_combout\ = data_h_high(1) $ (((\Equal14~1_combout\ & (data_h_high(0) & \data_h_high[0]~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal14~1_combout\,
	datab => data_h_high(0),
	datac => data_h_high(1),
	datad => \data_h_high[0]~2_combout\,
	combout => \data_h_high[1]~3_combout\);

-- Location: LCCOMB_X19_Y8_N12
\led_c~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~3_combout\ = (!\Equal3~2_combout\ & !\Equal4~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010100000101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal3~2_combout\,
	datac => \Equal4~1_combout\,
	combout => \led_c~3_combout\);

-- Location: LCFF_X27_Y7_N27
\div|data_min[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(4));

-- Location: LCFF_X27_Y7_N19
\div|data_min[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(3));

-- Location: LCFF_X27_Y7_N17
\div|data_min[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|Add3~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(6));

-- Location: LCFF_X27_Y7_N15
\div|data_min[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|Add3~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(5));

-- Location: LCCOMB_X27_Y7_N2
\div|Equal3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal3~0_combout\ = (!\div|data_min\(6) & (\div|data_min\(3) & (!\div|data_min\(5) & \div|data_min\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(6),
	datab => \div|data_min\(3),
	datac => \div|data_min\(5),
	datad => \div|data_min\(4),
	combout => \div|Equal3~0_combout\);

-- Location: LCFF_X27_Y7_N21
\div|data_min[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(2));

-- Location: LCFF_X27_Y7_N25
\div|data_min[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(1));

-- Location: LCFF_X27_Y7_N29
\div|data_min[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \div|data_min~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(0));

-- Location: LCCOMB_X27_Y7_N22
\div|Equal3~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal3~1_combout\ = (\div|data_min\(2) & (!\div|data_min\(0) & (\div|data_min\(1) & \div|Equal3~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(2),
	datab => \div|data_min\(0),
	datac => \div|data_min\(1),
	datad => \div|Equal3~0_combout\,
	combout => \div|Equal3~1_combout\);

-- Location: LCCOMB_X27_Y7_N30
\div|Q_min~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_min~0_combout\ = \div|Q_min~regout\ $ (\div|Equal3~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Q_min~regout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|Q_min~0_combout\);

-- Location: LCFF_X2_Y3_N13
\div|data_ms[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~32_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(16));

-- Location: LCFF_X2_Y3_N15
\div|data_ms[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~34_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(17));

-- Location: LCFF_X2_Y3_N17
\div|data_ms[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~36_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(18));

-- Location: LCFF_X2_Y3_N19
\div|data_ms[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~38_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(19));

-- Location: LCCOMB_X2_Y3_N20
\div|Equal0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~0_combout\ = (!\div|data_ms\(18) & (!\div|data_ms\(19) & (!\div|data_ms\(17) & !\div|data_ms\(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(18),
	datab => \div|data_ms\(19),
	datac => \div|data_ms\(17),
	datad => \div|data_ms\(16),
	combout => \div|Equal0~0_combout\);

-- Location: LCFF_X1_Y3_N23
\div|data_ms[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(3));

-- Location: LCFF_X1_Y3_N3
\div|data_ms[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(0));

-- Location: LCFF_X2_Y4_N15
\div|data_ms[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(1));

-- Location: LCFF_X2_Y4_N17
\div|data_ms[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(2));

-- Location: LCCOMB_X1_Y3_N30
\div|Equal0~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~1_combout\ = (!\div|data_ms\(0) & (\div|data_ms\(3) & (!\div|data_ms\(2) & !\div|data_ms\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(0),
	datab => \div|data_ms\(3),
	datac => \div|data_ms\(2),
	datad => \div|data_ms\(1),
	combout => \div|Equal0~1_combout\);

-- Location: LCFF_X1_Y3_N29
\div|data_ms[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(5));

-- Location: LCFF_X1_Y3_N11
\div|data_ms[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(7));

-- Location: LCFF_X2_Y4_N21
\div|data_ms[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(4));

-- Location: LCFF_X2_Y4_N25
\div|data_ms[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(6));

-- Location: LCCOMB_X1_Y3_N20
\div|Equal0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~2_combout\ = (\div|data_ms\(7) & (\div|data_ms\(5) & (!\div|data_ms\(6) & !\div|data_ms\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(7),
	datab => \div|data_ms\(5),
	datac => \div|data_ms\(6),
	datad => \div|data_ms\(4),
	combout => \div|Equal0~2_combout\);

-- Location: LCFF_X2_Y4_N9
\div|data_ms[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(8));

-- Location: LCFF_X2_Y3_N1
\div|data_ms[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(10));

-- Location: LCFF_X2_Y3_N3
\div|data_ms[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~22_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(11));

-- Location: LCCOMB_X2_Y3_N26
\div|Equal0~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~3_combout\ = (!\div|data_ms\(11) & !\div|data_ms\(10))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(11),
	datad => \div|data_ms\(10),
	combout => \div|Equal0~3_combout\);

-- Location: LCFF_X2_Y3_N29
\div|data_ms[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(13));

-- Location: LCFF_X1_Y3_N13
\div|data_ms[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(14));

-- Location: LCFF_X2_Y3_N5
\div|data_ms[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~24_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(12));

-- Location: LCFF_X2_Y3_N11
\div|data_ms[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~30_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(15));

-- Location: LCCOMB_X1_Y3_N14
\div|Equal0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~4_combout\ = (\div|data_ms\(14) & (!\div|data_ms\(12) & (!\div|data_ms\(15) & \div|data_ms\(13))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(14),
	datab => \div|data_ms\(12),
	datac => \div|data_ms\(15),
	datad => \div|data_ms\(13),
	combout => \div|Equal0~4_combout\);

-- Location: LCFF_X2_Y4_N31
\div|data_ms[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(9));

-- Location: LCCOMB_X1_Y3_N8
\div|Equal0~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~5_combout\ = (\div|Equal0~3_combout\ & (\div|data_ms\(8) & (\div|Equal0~4_combout\ & !\div|data_ms\(9))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~3_combout\,
	datab => \div|data_ms\(8),
	datac => \div|Equal0~4_combout\,
	datad => \div|data_ms\(9),
	combout => \div|Equal0~5_combout\);

-- Location: LCCOMB_X1_Y3_N16
\div|Equal0~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~6_combout\ = (\div|Equal0~2_combout\ & (\div|Equal0~0_combout\ & (\div|Equal0~5_combout\ & \div|Equal0~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~2_combout\,
	datab => \div|Equal0~0_combout\,
	datac => \div|Equal0~5_combout\,
	datad => \div|Equal0~1_combout\,
	combout => \div|Equal0~6_combout\);

-- Location: LCCOMB_X1_Y3_N24
\div|Q_ms~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_ms~0_combout\ = \div|Equal0~6_combout\ $ (\div|Q_ms~regout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~6_combout\,
	datac => \div|Q_ms~regout\,
	combout => \div|Q_ms~0_combout\);

-- Location: LCFF_X2_Y6_N5
\div|data_s[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(5));

-- Location: LCFF_X2_Y6_N15
\div|data_s[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(4));

-- Location: LCFF_X2_Y6_N13
\div|data_s[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(3));

-- Location: LCFF_X2_Y6_N11
\div|data_s[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(2));

-- Location: LCCOMB_X1_Y6_N24
\div|Equal2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~0_combout\ = (!\div|data_s\(3) & (!\div|data_s\(4) & (!\div|data_s\(2) & \div|data_s\(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(3),
	datab => \div|data_s\(4),
	datac => \div|data_s\(2),
	datad => \div|data_s\(5),
	combout => \div|Equal2~0_combout\);

-- Location: LCFF_X2_Y6_N3
\div|data_s[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(7));

-- Location: LCFF_X2_Y6_N9
\div|data_s[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(1));

-- Location: LCFF_X2_Y6_N1
\div|data_s[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(0));

-- Location: LCFF_X2_Y6_N19
\div|data_s[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(6));

-- Location: LCCOMB_X1_Y6_N20
\div|Equal2~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~1_combout\ = (\div|data_s\(7) & (!\div|data_s\(0) & (!\div|data_s\(1) & !\div|data_s\(6))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(7),
	datab => \div|data_s\(0),
	datac => \div|data_s\(1),
	datad => \div|data_s\(6),
	combout => \div|Equal2~1_combout\);

-- Location: LCFF_X1_Y6_N31
\div|data_s[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(8));

-- Location: LCFF_X1_Y6_N15
\div|data_s[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(10));

-- Location: LCFF_X2_Y6_N25
\div|data_s[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(9));

-- Location: LCFF_X2_Y6_N29
\div|data_s[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~22_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(11));

-- Location: LCCOMB_X1_Y6_N26
\div|Equal2~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~2_combout\ = (!\div|data_s\(11) & (\div|data_s\(8) & (\div|data_s\(10) & !\div|data_s\(9))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(11),
	datab => \div|data_s\(8),
	datac => \div|data_s\(10),
	datad => \div|data_s\(9),
	combout => \div|Equal2~2_combout\);

-- Location: LCFF_X1_Y6_N9
\div|data_s[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(13));

-- Location: LCFF_X2_Y6_N31
\div|data_s[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~24_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(12));

-- Location: LCFF_X2_Y5_N3
\div|data_s[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~28_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(14));

-- Location: LCFF_X2_Y5_N5
\div|data_s[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~30_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(15));

-- Location: LCCOMB_X1_Y6_N22
\div|Equal2~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~3_combout\ = (\div|data_s\(13) & (!\div|data_s\(12) & (!\div|data_s\(15) & !\div|data_s\(14))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(13),
	datab => \div|data_s\(12),
	datac => \div|data_s\(15),
	datad => \div|data_s\(14),
	combout => \div|Equal2~3_combout\);

-- Location: LCCOMB_X1_Y6_N28
\div|Equal2~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~4_combout\ = (\div|Equal2~1_combout\ & (\div|Equal2~3_combout\ & (\div|Equal2~0_combout\ & \div|Equal2~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~1_combout\,
	datab => \div|Equal2~3_combout\,
	datac => \div|Equal2~0_combout\,
	datad => \div|Equal2~2_combout\,
	combout => \div|Equal2~4_combout\);

-- Location: LCFF_X2_Y5_N29
\div|data_s[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(17));

-- Location: LCFF_X2_Y5_N31
\div|data_s[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~7_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(18));

-- Location: LCFF_X2_Y5_N7
\div|data_s[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~32_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(16));

-- Location: LCFF_X2_Y5_N13
\div|data_s[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~38_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(19));

-- Location: LCCOMB_X1_Y5_N0
\div|Equal2~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~5_combout\ = (!\div|data_s\(16) & (\div|data_s\(18) & (!\div|data_s\(19) & \div|data_s\(17))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(16),
	datab => \div|data_s\(18),
	datac => \div|data_s\(19),
	datad => \div|data_s\(17),
	combout => \div|Equal2~5_combout\);

-- Location: LCFF_X1_Y6_N19
\div|data_s[21]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(21));

-- Location: LCFF_X2_Y5_N15
\div|data_s[20]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~40_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(20));

-- Location: LCFF_X2_Y5_N19
\div|data_s[22]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~44_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(22));

-- Location: LCFF_X2_Y5_N21
\div|data_s[23]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~46_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(23));

-- Location: LCCOMB_X1_Y6_N12
\div|Equal2~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~6_combout\ = (!\div|data_s\(23) & (\div|data_s\(21) & (!\div|data_s\(22) & !\div|data_s\(20))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(23),
	datab => \div|data_s\(21),
	datac => \div|data_s\(22),
	datad => \div|data_s\(20),
	combout => \div|Equal2~6_combout\);

-- Location: LCFF_X2_Y5_N23
\div|data_s[24]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~48_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(24));

-- Location: LCFF_X2_Y5_N25
\div|data_s[25]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~50_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(25));

-- Location: LCFF_X2_Y5_N27
\div|data_s[26]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~52_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(26));

-- Location: LCCOMB_X1_Y5_N10
\div|Equal2~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~7_combout\ = (!\div|data_s\(25) & (!\div|data_s\(26) & !\div|data_s\(24)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(25),
	datac => \div|data_s\(26),
	datad => \div|data_s\(24),
	combout => \div|Equal2~7_combout\);

-- Location: LCCOMB_X1_Y6_N16
\div|Equal2~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~8_combout\ = (\div|Equal2~6_combout\ & (\div|Equal2~5_combout\ & (\div|Equal2~7_combout\ & \div|Equal2~4_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~6_combout\,
	datab => \div|Equal2~5_combout\,
	datac => \div|Equal2~7_combout\,
	datad => \div|Equal2~4_combout\,
	combout => \div|Equal2~8_combout\);

-- Location: LCCOMB_X1_Y6_N10
\div|Q_s~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_s~0_combout\ = \div|Equal2~8_combout\ $ (\div|Q_s~regout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~8_combout\,
	datac => \div|Q_s~regout\,
	combout => \div|Q_s~0_combout\);

-- Location: LCCOMB_X19_Y8_N24
\Equal5~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal5~0_combout\ = (\Add3~10_combout\) # ((\Add3~2_combout\) # ((\Add3~0_combout\) # (!\Add3~8_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111011111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~10_combout\,
	datab => \Add3~2_combout\,
	datac => \Add3~0_combout\,
	datad => \Add3~8_combout\,
	combout => \Equal5~0_combout\);

-- Location: LCCOMB_X19_Y8_N22
\Equal5~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal5~1_combout\ = (\Add3~6_combout\) # ((\Add3~4_combout\) # (!\Add3~12_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111110111011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add3~6_combout\,
	datab => \Add3~12_combout\,
	datad => \Add3~4_combout\,
	combout => \Equal5~1_combout\);

-- Location: LCCOMB_X19_Y8_N6
\key_flag~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \key_flag~0_combout\ = (\key_flag~regout\) # ((!\Equal5~0_combout\ & (!\Equal5~1_combout\ & \Equal2~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal5~0_combout\,
	datab => \Equal5~1_combout\,
	datac => \key_flag~regout\,
	datad => \Equal2~0_combout\,
	combout => \key_flag~0_combout\);

-- Location: LCFF_X9_Y9_N21
\COUNT1[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~59_combout\,
	aclr => \key1~clkctrl_outclk\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(11));

-- Location: LCCOMB_X9_Y9_N24
\Add0~59\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~59_combout\ = (\LessThan0~4_combout\ & (((\Add0~30_combout\)))) # (!\LessThan0~4_combout\ & ((\LessThan0~0_combout\ & ((\Add0~30_combout\))) # (!\LessThan0~0_combout\ & (COUNT1(11)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(11),
	datab => \Add0~30_combout\,
	datac => \LessThan0~4_combout\,
	datad => \LessThan0~0_combout\,
	combout => \Add0~59_combout\);

-- Location: LCCOMB_X8_Y10_N30
\Equal0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~4_combout\ = (!\Add0~58_combout\ & (\Add0~56_combout\ & (!\Add0~59_combout\ & !\Add0~57_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~58_combout\,
	datab => \Add0~56_combout\,
	datac => \Add0~59_combout\,
	datad => \Add0~57_combout\,
	combout => \Equal0~4_combout\);

-- Location: LCCOMB_X27_Y7_N26
\div|data_min~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~0_combout\ = (!\div|Equal3~1_combout\ & \div|Add3~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal3~1_combout\,
	datad => \div|Add3~8_combout\,
	combout => \div|data_min~0_combout\);

-- Location: LCCOMB_X27_Y7_N18
\div|data_min~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~1_combout\ = (\div|Add3~6_combout\ & !\div|Equal3~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Add3~6_combout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|data_min~1_combout\);

-- Location: LCCOMB_X27_Y7_N20
\div|data_min~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~2_combout\ = (\div|Add3~4_combout\ & !\div|Equal3~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Add3~4_combout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|data_min~2_combout\);

-- Location: LCCOMB_X27_Y7_N24
\div|data_min~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~3_combout\ = (\div|Add3~2_combout\ & !\div|Equal3~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Add3~2_combout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|data_min~3_combout\);

-- Location: LCCOMB_X27_Y7_N28
\div|data_min~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~4_combout\ = (\div|Add3~0_combout\ & !\div|Equal3~1_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Add3~0_combout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|data_min~4_combout\);

-- Location: LCCOMB_X1_Y3_N22
\div|data_ms~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~0_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~6_combout\,
	datac => \div|Add0~6_combout\,
	combout => \div|data_ms~0_combout\);

-- Location: LCCOMB_X1_Y3_N2
\div|data_ms~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~1_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~6_combout\,
	datac => \div|Add0~0_combout\,
	combout => \div|data_ms~1_combout\);

-- Location: LCCOMB_X1_Y3_N28
\div|data_ms~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~2_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~10_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal0~6_combout\,
	datad => \div|Add0~10_combout\,
	combout => \div|data_ms~2_combout\);

-- Location: LCCOMB_X1_Y3_N10
\div|data_ms~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~3_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~14_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~6_combout\,
	datac => \div|Add0~14_combout\,
	combout => \div|data_ms~3_combout\);

-- Location: LCCOMB_X2_Y4_N8
\div|data_ms~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~4_combout\ = (\div|Add0~16_combout\ & !\div|Equal0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110000001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Add0~16_combout\,
	datac => \div|Equal0~6_combout\,
	combout => \div|data_ms~4_combout\);

-- Location: LCCOMB_X2_Y3_N28
\div|data_ms~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~5_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~26_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal0~6_combout\,
	datad => \div|Add0~26_combout\,
	combout => \div|data_ms~5_combout\);

-- Location: LCCOMB_X1_Y3_N12
\div|data_ms~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~6_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~28_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~6_combout\,
	datac => \div|Add0~28_combout\,
	combout => \div|data_ms~6_combout\);

-- Location: LCCOMB_X2_Y6_N4
\div|data_s~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~0_combout\ = (\div|Add2~10_combout\ & !\div|Equal2~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Add2~10_combout\,
	datad => \div|Equal2~8_combout\,
	combout => \div|data_s~0_combout\);

-- Location: LCCOMB_X2_Y6_N2
\div|data_s~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~1_combout\ = (\div|Add2~14_combout\ & !\div|Equal2~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Add2~14_combout\,
	datad => \div|Equal2~8_combout\,
	combout => \div|data_s~1_combout\);

-- Location: LCCOMB_X2_Y6_N0
\div|data_s~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~2_combout\ = (\div|Add2~0_combout\ & !\div|Equal2~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Add2~0_combout\,
	datad => \div|Equal2~8_combout\,
	combout => \div|data_s~2_combout\);

-- Location: LCCOMB_X1_Y6_N30
\div|data_s~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~3_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~16_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal2~8_combout\,
	datad => \div|Add2~16_combout\,
	combout => \div|data_s~3_combout\);

-- Location: LCCOMB_X1_Y6_N14
\div|data_s~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~4_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~20_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~8_combout\,
	datac => \div|Add2~20_combout\,
	combout => \div|data_s~4_combout\);

-- Location: LCCOMB_X1_Y6_N8
\div|data_s~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~5_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~26_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal2~8_combout\,
	datad => \div|Add2~26_combout\,
	combout => \div|data_s~5_combout\);

-- Location: LCCOMB_X2_Y5_N28
\div|data_s~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~6_combout\ = (\div|Add2~34_combout\ & !\div|Equal2~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Add2~34_combout\,
	datad => \div|Equal2~8_combout\,
	combout => \div|data_s~6_combout\);

-- Location: LCCOMB_X2_Y5_N30
\div|data_s~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~7_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~36_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal2~8_combout\,
	datad => \div|Add2~36_combout\,
	combout => \div|data_s~7_combout\);

-- Location: LCCOMB_X1_Y6_N18
\div|data_s~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~8_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~42_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal2~8_combout\,
	datad => \div|Add2~42_combout\,
	combout => \div|data_s~8_combout\);

-- Location: LCCOMB_X19_Y8_N8
\data_time_count[0]~27\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[0]~27_combout\ = !data_time_count(0)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => data_time_count(0),
	combout => \data_time_count[0]~27_combout\);

-- Location: LCCOMB_X17_Y8_N4
\data_time_tmp[9]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(9) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(9))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(9))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_time_tmp(9),
	datac => \key2~clkctrl_outclk\,
	datad => data_time_count(9),
	combout => data_time_tmp(9));

-- Location: LCCOMB_X17_Y8_N2
\data_time_tmp[8]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(8) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(8))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(8))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_time_tmp(8),
	datac => data_time_count(8),
	datad => \key2~clkctrl_outclk\,
	combout => data_time_tmp(8));

-- Location: LCCOMB_X17_Y8_N8
\data_time_tmp[7]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(7) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(7))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(7))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_time_tmp(7),
	datac => \key2~clkctrl_outclk\,
	datad => data_time_count(7),
	combout => data_time_tmp(7));

-- Location: LCCOMB_X17_Y8_N30
\data_time_tmp[6]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(6) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(6))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(6))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_time_tmp(6),
	datac => data_time_count(6),
	datad => \key2~clkctrl_outclk\,
	combout => data_time_tmp(6));

-- Location: LCCOMB_X17_Y8_N0
\data_time_tmp[5]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(5) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(5))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_time_tmp(5),
	datac => \key2~clkctrl_outclk\,
	datad => data_time_count(5),
	combout => data_time_tmp(5));

-- Location: LCCOMB_X18_Y8_N26
\data_time_tmp[4]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(4) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(4))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101110001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(4),
	datab => \key2~clkctrl_outclk\,
	datad => data_time_count(4),
	combout => data_time_tmp(4));

-- Location: LCCOMB_X17_Y8_N28
\data_time_tmp[3]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(3) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(3))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_time_tmp(3),
	datac => data_time_count(3),
	datad => \key2~clkctrl_outclk\,
	combout => data_time_tmp(3));

-- Location: LCCOMB_X17_Y8_N6
\data_time_tmp[2]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(2) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(2))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010111110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(2),
	datac => \key2~clkctrl_outclk\,
	datad => data_time_count(2),
	combout => data_time_tmp(2));

-- Location: LCCOMB_X18_Y8_N0
\data_time_tmp[1]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(1) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(1))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101110001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(1),
	datab => \key2~clkctrl_outclk\,
	datad => data_time_count(1),
	combout => data_time_tmp(1));

-- Location: LCCOMB_X18_Y8_N30
\data_time_tmp[0]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_time_tmp(0) = (GLOBAL(\key2~clkctrl_outclk\) & (data_time_tmp(0))) # (!GLOBAL(\key2~clkctrl_outclk\) & ((data_time_count(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101110001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_tmp(0),
	datab => \key2~clkctrl_outclk\,
	datad => data_time_count(0),
	combout => data_time_tmp(0));

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

-- Location: PIN_89,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\key2~I\ : cycloneii_io
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
	padio => ww_key2,
	combout => \key2~combout\);

-- Location: CLKCTRL_G0
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

-- Location: CLKCTRL_G1
\div|Q_ms~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \div|Q_ms~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \div|Q_ms~clkctrl_outclk\);

-- Location: CLKCTRL_G6
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

-- Location: CLKCTRL_G7
\key2~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \key2~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \key2~clkctrl_outclk\);

-- Location: LCCOMB_X9_Y9_N12
\Add0~40\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~40_combout\ = (COUNT1(16) & (\Add0~39\ $ (GND))) # (!COUNT1(16) & (!\Add0~39\ & VCC))
-- \Add0~41\ = CARRY((COUNT1(16) & !\Add0~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(16),
	datad => VCC,
	cin => \Add0~39\,
	combout => \Add0~40_combout\,
	cout => \Add0~41\);

-- Location: LCCOMB_X9_Y9_N14
\Add0~42\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~42_combout\ = (COUNT1(17) & (!\Add0~41\)) # (!COUNT1(17) & ((\Add0~41\) # (GND)))
-- \Add0~43\ = CARRY((!\Add0~41\) # (!COUNT1(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(17),
	datad => VCC,
	cin => \Add0~41\,
	combout => \Add0~42_combout\,
	cout => \Add0~43\);

-- Location: LCCOMB_X8_Y10_N28
\Add0~65\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~65_combout\ = (\Add0~42_combout\) # ((COUNT1(16) & (!\LessThan0~4_combout\ & COUNT1(17))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(16),
	datab => \LessThan0~4_combout\,
	datac => COUNT1(17),
	datad => \Add0~42_combout\,
	combout => \Add0~65_combout\);

-- Location: PIN_88,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\key1~I\ : cycloneii_io
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
	padio => ww_key1,
	combout => \key1~combout\);

-- Location: CLKCTRL_G5
\key1~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \key1~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \key1~clkctrl_outclk\);

-- Location: LCFF_X8_Y10_N29
\COUNT1[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~65_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(17));

-- Location: LCCOMB_X8_Y10_N20
\LessThan0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~0_combout\ = (!COUNT1(17)) # (!COUNT1(16))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(16),
	datad => COUNT1(17),
	combout => \LessThan0~0_combout\);

-- Location: LCCOMB_X10_Y10_N30
\Add0~49\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~49_combout\ = (\LessThan0~4_combout\ & (\Add0~18_combout\)) # (!\LessThan0~4_combout\ & ((\LessThan0~0_combout\ & (\Add0~18_combout\)) # (!\LessThan0~0_combout\ & ((COUNT1(5))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101010101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~18_combout\,
	datab => COUNT1(5),
	datac => \LessThan0~4_combout\,
	datad => \LessThan0~0_combout\,
	combout => \Add0~49_combout\);

-- Location: LCFF_X9_Y10_N17
\COUNT1[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~49_combout\,
	aclr => \key1~clkctrl_outclk\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(5));

-- Location: LCCOMB_X9_Y10_N2
\Add0~52\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~52_combout\ = (\LessThan0~0_combout\ & (\Add0~12_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~12_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(2))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101010111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~12_combout\,
	datab => \LessThan0~0_combout\,
	datac => COUNT1(2),
	datad => \LessThan0~4_combout\,
	combout => \Add0~52_combout\);

-- Location: LCFF_X9_Y10_N3
\COUNT1[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~52_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(2));

-- Location: LCCOMB_X9_Y10_N14
\Add0~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~10_combout\ = (COUNT1(1) & (!\Add0~9\)) # (!COUNT1(1) & ((\Add0~9\) # (GND)))
-- \Add0~11\ = CARRY((!\Add0~9\) # (!COUNT1(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(1),
	datad => VCC,
	cin => \Add0~9\,
	combout => \Add0~10_combout\,
	cout => \Add0~11\);

-- Location: LCCOMB_X9_Y10_N4
\Add0~51\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~51_combout\ = (\LessThan0~0_combout\ & (\Add0~10_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~10_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(1))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~10_combout\,
	datac => COUNT1(1),
	datad => \LessThan0~4_combout\,
	combout => \Add0~51_combout\);

-- Location: LCFF_X9_Y10_N5
\COUNT1[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~51_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(1));

-- Location: LCCOMB_X9_Y10_N18
\Add0~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~14_combout\ = (COUNT1(3) & (!\Add0~13\)) # (!COUNT1(3) & ((\Add0~13\) # (GND)))
-- \Add0~15\ = CARRY((!\Add0~13\) # (!COUNT1(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(3),
	datad => VCC,
	cin => \Add0~13\,
	combout => \Add0~14_combout\,
	cout => \Add0~15\);

-- Location: LCCOMB_X9_Y10_N8
\Add0~53\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~53_combout\ = (\LessThan0~0_combout\ & (\Add0~14_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~14_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(3))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~14_combout\,
	datac => COUNT1(3),
	datad => \LessThan0~4_combout\,
	combout => \Add0~53_combout\);

-- Location: LCFF_X9_Y10_N9
\COUNT1[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~53_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(3));

-- Location: LCCOMB_X9_Y10_N20
\Add0~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~16_combout\ = (COUNT1(4) & (\Add0~15\ $ (GND))) # (!COUNT1(4) & (!\Add0~15\ & VCC))
-- \Add0~17\ = CARRY((COUNT1(4) & !\Add0~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(4),
	datad => VCC,
	cin => \Add0~15\,
	combout => \Add0~16_combout\,
	cout => \Add0~17\);

-- Location: LCCOMB_X10_Y10_N8
\Add0~48\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~48_combout\ = (\LessThan0~0_combout\ & (((\Add0~16_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~16_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(4)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(4),
	datab => \LessThan0~0_combout\,
	datac => \LessThan0~4_combout\,
	datad => \Add0~16_combout\,
	combout => \Add0~48_combout\);

-- Location: LCFF_X9_Y10_N15
\COUNT1[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~48_combout\,
	aclr => \key1~clkctrl_outclk\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(4));

-- Location: LCCOMB_X9_Y10_N26
\Add0~22\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~22_combout\ = (COUNT1(7) & (!\Add0~21\)) # (!COUNT1(7) & ((\Add0~21\) # (GND)))
-- \Add0~23\ = CARRY((!\Add0~21\) # (!COUNT1(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(7),
	datad => VCC,
	cin => \Add0~21\,
	combout => \Add0~22_combout\,
	cout => \Add0~23\);

-- Location: LCCOMB_X9_Y10_N0
\Add0~55\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~55_combout\ = (\LessThan0~0_combout\ & (\Add0~22_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~22_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(7))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~22_combout\,
	datac => COUNT1(7),
	datad => \LessThan0~4_combout\,
	combout => \Add0~55_combout\);

-- Location: LCFF_X9_Y10_N1
\COUNT1[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~55_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(7));

-- Location: LCCOMB_X9_Y10_N28
\Add0~24\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~24_combout\ = (COUNT1(8) & (\Add0~23\ $ (GND))) # (!COUNT1(8) & (!\Add0~23\ & VCC))
-- \Add0~25\ = CARRY((COUNT1(8) & !\Add0~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(8),
	datad => VCC,
	cin => \Add0~23\,
	combout => \Add0~24_combout\,
	cout => \Add0~25\);

-- Location: LCCOMB_X10_Y10_N10
\Add0~57\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~57_combout\ = (\LessThan0~0_combout\ & (((\Add0~24_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~24_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(8)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(8),
	datab => \LessThan0~0_combout\,
	datac => \LessThan0~4_combout\,
	datad => \Add0~24_combout\,
	combout => \Add0~57_combout\);

-- Location: LCCOMB_X10_Y10_N24
\COUNT1[8]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \COUNT1[8]~feeder_combout\ = \Add0~57_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~57_combout\,
	combout => \COUNT1[8]~feeder_combout\);

-- Location: LCFF_X10_Y10_N25
\COUNT1[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \COUNT1[8]~feeder_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(8));

-- Location: LCCOMB_X9_Y10_N30
\Add0~26\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~26_combout\ = (COUNT1(9) & (!\Add0~25\)) # (!COUNT1(9) & ((\Add0~25\) # (GND)))
-- \Add0~27\ = CARRY((!\Add0~25\) # (!COUNT1(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(9),
	datad => VCC,
	cin => \Add0~25\,
	combout => \Add0~26_combout\,
	cout => \Add0~27\);

-- Location: LCCOMB_X8_Y10_N26
\Add0~56\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~56_combout\ = (\LessThan0~0_combout\ & (((\Add0~26_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~26_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(9)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => COUNT1(9),
	datac => \LessThan0~4_combout\,
	datad => \Add0~26_combout\,
	combout => \Add0~56_combout\);

-- Location: LCFF_X9_Y10_N13
\COUNT1[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~56_combout\,
	aclr => \key1~clkctrl_outclk\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(9));

-- Location: LCCOMB_X9_Y9_N0
\Add0~28\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~28_combout\ = (COUNT1(10) & (\Add0~27\ $ (GND))) # (!COUNT1(10) & (!\Add0~27\ & VCC))
-- \Add0~29\ = CARRY((COUNT1(10) & !\Add0~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(10),
	datad => VCC,
	cin => \Add0~27\,
	combout => \Add0~28_combout\,
	cout => \Add0~29\);

-- Location: LCCOMB_X8_Y10_N6
\Add0~58\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~58_combout\ = (\LessThan0~0_combout\ & (((\Add0~28_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~28_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(10)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(10),
	datad => \Add0~28_combout\,
	combout => \Add0~58_combout\);

-- Location: LCFF_X8_Y10_N7
\COUNT1[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~58_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(10));

-- Location: LCCOMB_X9_Y9_N4
\Add0~32\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~32_combout\ = (COUNT1(12) & (\Add0~31\ $ (GND))) # (!COUNT1(12) & (!\Add0~31\ & VCC))
-- \Add0~33\ = CARRY((COUNT1(12) & !\Add0~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(12),
	datad => VCC,
	cin => \Add0~31\,
	combout => \Add0~32_combout\,
	cout => \Add0~33\);

-- Location: LCCOMB_X9_Y9_N26
\Add0~61\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~61_combout\ = (\LessThan0~0_combout\ & (\Add0~32_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~32_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(12))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~32_combout\,
	datac => COUNT1(12),
	datad => \LessThan0~4_combout\,
	combout => \Add0~61_combout\);

-- Location: LCFF_X9_Y9_N27
\COUNT1[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~61_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(12));

-- Location: LCCOMB_X9_Y9_N6
\Add0~34\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~34_combout\ = (COUNT1(13) & (!\Add0~33\)) # (!COUNT1(13) & ((\Add0~33\) # (GND)))
-- \Add0~35\ = CARRY((!\Add0~33\) # (!COUNT1(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(13),
	datad => VCC,
	cin => \Add0~33\,
	combout => \Add0~34_combout\,
	cout => \Add0~35\);

-- Location: LCCOMB_X9_Y9_N8
\Add0~36\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~36_combout\ = (COUNT1(14) & (\Add0~35\ $ (GND))) # (!COUNT1(14) & (!\Add0~35\ & VCC))
-- \Add0~37\ = CARRY((COUNT1(14) & !\Add0~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(14),
	datad => VCC,
	cin => \Add0~35\,
	combout => \Add0~36_combout\,
	cout => \Add0~37\);

-- Location: LCCOMB_X9_Y9_N10
\Add0~38\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~38_combout\ = (COUNT1(15) & (!\Add0~37\)) # (!COUNT1(15) & ((\Add0~37\) # (GND)))
-- \Add0~39\ = CARRY((!\Add0~37\) # (!COUNT1(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(15),
	datad => VCC,
	cin => \Add0~37\,
	combout => \Add0~38_combout\,
	cout => \Add0~39\);

-- Location: LCCOMB_X8_Y10_N12
\Add0~63\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~63_combout\ = (\LessThan0~0_combout\ & (((\Add0~38_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~38_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(15))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000111100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => \Add0~38_combout\,
	datad => COUNT1(15),
	combout => \Add0~63_combout\);

-- Location: LCFF_X8_Y10_N21
\COUNT1[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~63_combout\,
	aclr => \key1~clkctrl_outclk\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(15));

-- Location: LCCOMB_X8_Y10_N4
\Add0~64\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~64_combout\ = (\Add0~40_combout\) # ((COUNT1(17) & (!\LessThan0~4_combout\ & COUNT1(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(17),
	datab => \LessThan0~4_combout\,
	datac => COUNT1(16),
	datad => \Add0~40_combout\,
	combout => \Add0~64_combout\);

-- Location: LCFF_X8_Y10_N5
\COUNT1[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~64_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(16));

-- Location: LCCOMB_X9_Y9_N16
\Add0~44\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~44_combout\ = (COUNT1(18) & (\Add0~43\ $ (GND))) # (!COUNT1(18) & (!\Add0~43\ & VCC))
-- \Add0~45\ = CARRY((COUNT1(18) & !\Add0~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(18),
	datad => VCC,
	cin => \Add0~43\,
	combout => \Add0~44_combout\,
	cout => \Add0~45\);

-- Location: LCCOMB_X8_Y10_N24
\Add0~66\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~66_combout\ = (\Add0~44_combout\) # ((COUNT1(17) & (!\LessThan0~4_combout\ & COUNT1(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(17),
	datab => \LessThan0~4_combout\,
	datac => COUNT1(16),
	datad => \Add0~44_combout\,
	combout => \Add0~66_combout\);

-- Location: LCFF_X8_Y10_N25
\COUNT1[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~66_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(18));

-- Location: LCCOMB_X8_Y10_N16
\Add0~60\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~60_combout\ = (\LessThan0~0_combout\ & (((\Add0~36_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~36_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(14)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(14),
	datad => \Add0~36_combout\,
	combout => \Add0~60_combout\);

-- Location: LCFF_X8_Y10_N17
\COUNT1[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~60_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(14));

-- Location: LCCOMB_X8_Y10_N18
\LessThan0~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~1_combout\ = (((!COUNT1(15) & !COUNT1(14))) # (!COUNT1(18))) # (!COUNT1(19))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111011101111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(19),
	datab => COUNT1(18),
	datac => COUNT1(15),
	datad => COUNT1(14),
	combout => \LessThan0~1_combout\);

-- Location: LCCOMB_X9_Y9_N22
\Add0~62\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~62_combout\ = (\LessThan0~0_combout\ & (((\Add0~34_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~34_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(13)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(13),
	datab => \LessThan0~0_combout\,
	datac => \LessThan0~4_combout\,
	datad => \Add0~34_combout\,
	combout => \Add0~62_combout\);

-- Location: LCCOMB_X9_Y9_N28
\COUNT1[13]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \COUNT1[13]~feeder_combout\ = \Add0~62_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~62_combout\,
	combout => \COUNT1[13]~feeder_combout\);

-- Location: LCFF_X9_Y9_N29
\COUNT1[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \COUNT1[13]~feeder_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(13));

-- Location: LCCOMB_X9_Y9_N30
\LessThan0~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~3_combout\ = (!COUNT1(11) & (!COUNT1(12) & (!COUNT1(13) & !COUNT1(15))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(11),
	datab => COUNT1(12),
	datac => COUNT1(13),
	datad => COUNT1(15),
	combout => \LessThan0~3_combout\);

-- Location: LCCOMB_X9_Y10_N10
\Add0~54\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~54_combout\ = (\LessThan0~0_combout\ & (\Add0~20_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~20_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(6))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101010111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~20_combout\,
	datab => \LessThan0~0_combout\,
	datac => COUNT1(6),
	datad => \LessThan0~4_combout\,
	combout => \Add0~54_combout\);

-- Location: LCFF_X9_Y10_N11
\COUNT1[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~54_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(6));

-- Location: LCCOMB_X10_Y10_N22
\LessThan0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~2_combout\ = ((!COUNT1(8) & (!COUNT1(6) & !COUNT1(7)))) # (!COUNT1(9))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(8),
	datab => COUNT1(6),
	datac => COUNT1(7),
	datad => COUNT1(9),
	combout => \LessThan0~2_combout\);

-- Location: LCCOMB_X8_Y10_N14
\LessThan0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~4_combout\ = (\LessThan0~1_combout\) # ((!COUNT1(10) & (\LessThan0~3_combout\ & \LessThan0~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(10),
	datab => \LessThan0~1_combout\,
	datac => \LessThan0~3_combout\,
	datad => \LessThan0~2_combout\,
	combout => \LessThan0~4_combout\);

-- Location: LCCOMB_X8_Y10_N0
\COUNT1[19]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \COUNT1[19]~feeder_combout\ = \Add0~67_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~67_combout\,
	combout => \COUNT1[19]~feeder_combout\);

-- Location: LCFF_X8_Y10_N1
\COUNT1[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \COUNT1[19]~feeder_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(19));

-- Location: LCCOMB_X9_Y9_N18
\Add0~46\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~46_combout\ = \Add0~45\ $ (COUNT1(19))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => COUNT1(19),
	cin => \Add0~45\,
	combout => \Add0~46_combout\);

-- Location: LCCOMB_X8_Y10_N2
\Add0~67\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~67_combout\ = (\Add0~46_combout\) # ((COUNT1(17) & (!\LessThan0~4_combout\ & COUNT1(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(17),
	datab => \LessThan0~4_combout\,
	datac => COUNT1(16),
	datad => \Add0~46_combout\,
	combout => \Add0~67_combout\);

-- Location: LCCOMB_X8_Y10_N22
\Equal0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~0_combout\ = (\Add0~66_combout\ & (\Add0~67_combout\ & (\Add0~64_combout\ & \Add0~65_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~66_combout\,
	datab => \Add0~67_combout\,
	datac => \Add0~64_combout\,
	datad => \Add0~65_combout\,
	combout => \Equal0~0_combout\);

-- Location: LCCOMB_X8_Y10_N8
\Equal0~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~5_combout\ = (\Add0~60_combout\ & (!\Add0~61_combout\ & (!\Add0~62_combout\ & !\Add0~63_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~60_combout\,
	datab => \Add0~61_combout\,
	datac => \Add0~62_combout\,
	datad => \Add0~63_combout\,
	combout => \Equal0~5_combout\);

-- Location: LCCOMB_X10_Y10_N14
\Equal0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~2_combout\ = (!\Add0~55_combout\ & !\Add0~54_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \Add0~55_combout\,
	datad => \Add0~54_combout\,
	combout => \Equal0~2_combout\);

-- Location: LCFF_X9_Y10_N7
\COUNT1[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~50_combout\,
	aclr => \key1~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(0));

-- Location: LCCOMB_X9_Y10_N6
\Add0~50\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~50_combout\ = (\LessThan0~0_combout\ & (\Add0~8_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~8_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(0))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101010111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~8_combout\,
	datab => \LessThan0~0_combout\,
	datac => COUNT1(0),
	datad => \LessThan0~4_combout\,
	combout => \Add0~50_combout\);

-- Location: LCCOMB_X10_Y10_N0
\Equal0~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~1_combout\ = (\Add0~52_combout\ & (\Add0~50_combout\ & (\Add0~51_combout\ & \Add0~53_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~52_combout\,
	datab => \Add0~50_combout\,
	datac => \Add0~51_combout\,
	datad => \Add0~53_combout\,
	combout => \Equal0~1_combout\);

-- Location: LCCOMB_X10_Y10_N28
\Equal0~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~3_combout\ = (\Add0~48_combout\ & (\Add0~49_combout\ & (\Equal0~2_combout\ & \Equal0~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~48_combout\,
	datab => \Add0~49_combout\,
	datac => \Equal0~2_combout\,
	datad => \Equal0~1_combout\,
	combout => \Equal0~3_combout\);

-- Location: LCCOMB_X8_Y10_N10
\Equal0~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal0~6_combout\ = (\Equal0~4_combout\ & (\Equal0~0_combout\ & (\Equal0~5_combout\ & \Equal0~3_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal0~4_combout\,
	datab => \Equal0~0_combout\,
	datac => \Equal0~5_combout\,
	datad => \Equal0~3_combout\,
	combout => \Equal0~6_combout\);

-- Location: LCFF_X8_Y10_N11
\key_signal[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Equal0~6_combout\,
	ena => \ALT_INV_key1~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => key_signal(2));

-- Location: CLKCTRL_G3
\key_signal[2]~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \key_signal[2]~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \key_signal[2]~clkctrl_outclk\);

-- Location: LCCOMB_X12_Y10_N4
\Add1~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add1~1_combout\ = data_mode(2) $ (((data_mode(1) & \data_mode[0]~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datac => data_mode(2),
	datad => \data_mode[0]~0_combout\,
	combout => \Add1~1_combout\);

-- Location: LCCOMB_X12_Y10_N20
\data_mode[2]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_mode(2) = (!\Equal1~0_combout\ & ((GLOBAL(\key_signal[2]~clkctrl_outclk\) & ((\Add1~1_combout\))) # (!GLOBAL(\key_signal[2]~clkctrl_outclk\) & (data_mode(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011100010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(2),
	datab => \key_signal[2]~clkctrl_outclk\,
	datac => \Add1~1_combout\,
	datad => \Equal1~0_combout\,
	combout => data_mode(2));

-- Location: LCCOMB_X12_Y10_N30
\Equal1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal1~0_combout\ = (data_mode(1) & (\data_mode[0]~0_combout\ & (!data_mode(2) & !data_mode(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datab => \data_mode[0]~0_combout\,
	datac => data_mode(2),
	datad => data_mode(3),
	combout => \Equal1~0_combout\);

-- Location: LCCOMB_X12_Y10_N12
\data_mode[0]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[0]~0_combout\ = (!\Equal1~0_combout\ & (\data_mode[0]~0_combout\ $ (key_signal(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001100110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal1~0_combout\,
	datac => \data_mode[0]~0_combout\,
	datad => key_signal(2),
	combout => \data_mode[0]~0_combout\);

-- Location: LCCOMB_X12_Y10_N24
\Add1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add1~0_combout\ = data_mode(1) $ (\data_mode[0]~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_mode(1),
	datad => \data_mode[0]~0_combout\,
	combout => \Add1~0_combout\);

-- Location: LCCOMB_X12_Y10_N6
\data_mode[1]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_mode(1) = (!\Equal1~0_combout\ & ((GLOBAL(\key_signal[2]~clkctrl_outclk\) & ((\Add1~0_combout\))) # (!GLOBAL(\key_signal[2]~clkctrl_outclk\) & (data_mode(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011100010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datab => \key_signal[2]~clkctrl_outclk\,
	datac => \Add1~0_combout\,
	datad => \Equal1~0_combout\,
	combout => data_mode(1));

-- Location: LCCOMB_X12_Y10_N14
\Add1~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add1~2_combout\ = data_mode(3) $ (((data_mode(2) & (data_mode(1) & \data_mode[0]~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(2),
	datab => data_mode(3),
	datac => data_mode(1),
	datad => \data_mode[0]~0_combout\,
	combout => \Add1~2_combout\);

-- Location: LCCOMB_X12_Y10_N26
\data_mode[3]\ : cycloneii_lcell_comb
-- Equation(s):
-- data_mode(3) = (!\Equal1~0_combout\ & ((GLOBAL(\key_signal[2]~clkctrl_outclk\) & ((\Add1~2_combout\))) # (!GLOBAL(\key_signal[2]~clkctrl_outclk\) & (data_mode(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key_signal[2]~clkctrl_outclk\,
	datab => data_mode(3),
	datac => \Add1~2_combout\,
	datad => \Equal1~0_combout\,
	combout => data_mode(3));

-- Location: LCCOMB_X13_Y10_N16
\tmp_seg7data[0]~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~10_combout\ = (!data_mode(1) & (!data_mode(3) & (!data_mode(2) & \data_mode[0]~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datab => data_mode(3),
	datac => data_mode(2),
	datad => \data_mode[0]~0_combout\,
	combout => \tmp_seg7data[0]~10_combout\);

-- Location: LCCOMB_X13_Y10_N18
\Equal7~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal7~0_combout\ = (!data_mode(1) & (!data_mode(3) & (!data_mode(2) & !\data_mode[0]~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datab => data_mode(3),
	datac => data_mode(2),
	datad => \data_mode[0]~0_combout\,
	combout => \Equal7~0_combout\);

-- Location: LCCOMB_X26_Y6_N0
\data_min_high[0]~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high[0]~4_combout\ = !data_min_high(0)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_min_high(0),
	combout => \data_min_high[0]~4_combout\);

-- Location: LCCOMB_X25_Y6_N0
\Add7~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add7~0_combout\ = data_h_low(0) $ (VCC)
-- \Add7~1\ = CARRY(data_h_low(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(0),
	datad => VCC,
	combout => \Add7~0_combout\,
	cout => \Add7~1\);

-- Location: LCCOMB_X26_Y6_N16
\Add5~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add5~0_combout\ = data_min_low(0) $ (VCC)
-- \Add5~1\ = CARRY(data_min_low(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(0),
	datad => VCC,
	combout => \Add5~0_combout\,
	cout => \Add5~1\);

-- Location: LCFF_X26_Y6_N17
\data_min_low[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add5~0_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(0));

-- Location: LCCOMB_X26_Y6_N18
\Add5~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add5~2_combout\ = (data_min_low(1) & (!\Add5~1\)) # (!data_min_low(1) & ((\Add5~1\) # (GND)))
-- \Add5~3\ = CARRY((!\Add5~1\) # (!data_min_low(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(1),
	datad => VCC,
	cin => \Add5~1\,
	combout => \Add5~2_combout\,
	cout => \Add5~3\);

-- Location: LCCOMB_X26_Y6_N26
\data_min_low~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_low~0_combout\ = (\Add5~2_combout\ & ((!data_min_low(0)) # (!\Equal12~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal12~0_combout\,
	datac => data_min_low(0),
	datad => \Add5~2_combout\,
	combout => \data_min_low~0_combout\);

-- Location: LCFF_X26_Y6_N27
\data_min_low[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_low~0_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(1));

-- Location: LCCOMB_X26_Y6_N20
\Add5~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add5~4_combout\ = (data_min_low(2) & (\Add5~3\ $ (GND))) # (!data_min_low(2) & (!\Add5~3\ & VCC))
-- \Add5~5\ = CARRY((data_min_low(2) & !\Add5~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(2),
	datad => VCC,
	cin => \Add5~3\,
	combout => \Add5~4_combout\,
	cout => \Add5~5\);

-- Location: LCCOMB_X26_Y6_N28
\data_min_low~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_low~1_combout\ = (\Add5~6_combout\ & ((!data_min_low(0)) # (!\Equal12~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal12~0_combout\,
	datac => data_min_low(0),
	datad => \Add5~6_combout\,
	combout => \data_min_low~1_combout\);

-- Location: LCFF_X26_Y6_N29
\data_min_low[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_low~1_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(3));

-- Location: LCFF_X26_Y6_N21
\data_min_low[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add5~4_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(2));

-- Location: LCCOMB_X26_Y6_N12
\Equal12~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal12~0_combout\ = (!data_min_low(4) & (data_min_low(3) & (!data_min_low(2) & !data_min_low(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(4),
	datab => data_min_low(3),
	datac => data_min_low(2),
	datad => data_min_low(1),
	combout => \Equal12~0_combout\);

-- Location: LCCOMB_X26_Y6_N2
\data_min_high[3]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high[3]~2_combout\ = (data_min_high(0) & (data_min_high(2) & data_min_high(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(0),
	datab => data_min_high(2),
	datad => data_min_high(1),
	combout => \data_min_high[3]~2_combout\);

-- Location: LCCOMB_X26_Y6_N6
\data_min_high[3]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high[3]~3_combout\ = data_min_high(3) $ (((data_min_low(0) & (\Equal12~0_combout\ & \data_min_high[3]~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(0),
	datab => \Equal12~0_combout\,
	datac => data_min_high(3),
	datad => \data_min_high[3]~2_combout\,
	combout => \data_min_high[3]~3_combout\);

-- Location: LCFF_X26_Y6_N7
\data_min_high[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high[3]~3_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(3));

-- Location: LCCOMB_X26_Y6_N10
\data_min_high~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high~1_combout\ = (data_min_high(0) & ((data_min_high(2) & (data_min_high(3) & !data_min_high(1))) # (!data_min_high(2) & ((data_min_high(1)))))) # (!data_min_high(0) & (((data_min_high(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101011010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(0),
	datab => data_min_high(3),
	datac => data_min_high(2),
	datad => data_min_high(1),
	combout => \data_min_high~1_combout\);

-- Location: LCCOMB_X26_Y6_N4
\Equal12~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal12~1_combout\ = (data_min_low(0) & \Equal12~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_min_low(0),
	datad => \Equal12~0_combout\,
	combout => \Equal12~1_combout\);

-- Location: LCFF_X26_Y6_N11
\data_min_high[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high~1_combout\,
	aclr => \Equal15~1_combout\,
	ena => \Equal12~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(2));

-- Location: LCCOMB_X26_Y6_N8
\data_min_high~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high~0_combout\ = (data_min_high(0) & (!data_min_high(1) & ((data_min_high(3)) # (!data_min_high(2))))) # (!data_min_high(0) & (((data_min_high(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001010010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(0),
	datab => data_min_high(2),
	datac => data_min_high(1),
	datad => data_min_high(3),
	combout => \data_min_high~0_combout\);

-- Location: LCFF_X26_Y6_N9
\data_min_high[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high~0_combout\,
	aclr => \Equal15~1_combout\,
	ena => \Equal12~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(1));

-- Location: LCCOMB_X26_Y6_N14
\Equal13~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal13~0_combout\ = (data_min_high(2) & (data_min_high(0) & (!data_min_high(1) & !data_min_high(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(2),
	datab => data_min_high(0),
	datac => data_min_high(1),
	datad => data_min_high(3),
	combout => \Equal13~0_combout\);

-- Location: LCCOMB_X26_Y6_N30
\data_h_high[0]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[0]~2_combout\ = (data_min_low(0) & (\Equal13~0_combout\ & \Equal12~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(0),
	datac => \Equal13~0_combout\,
	datad => \Equal12~0_combout\,
	combout => \data_h_high[0]~2_combout\);

-- Location: LCFF_X25_Y6_N1
\data_h_low[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add7~0_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(0));

-- Location: LCCOMB_X25_Y6_N18
\data_h[1]~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[1]~6_combout\ = (data_h(1) & (data_h_low(0) $ (VCC))) # (!data_h(1) & (data_h_low(0) & VCC))
-- \data_h[1]~7\ = CARRY((data_h(1) & data_h_low(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110011010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h(1),
	datab => data_h_low(0),
	datad => VCC,
	combout => \data_h[1]~6_combout\,
	cout => \data_h[1]~7\);

-- Location: LCCOMB_X25_Y6_N20
\data_h[2]~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[2]~8_combout\ = (data_h(2) & (!\data_h[1]~7\)) # (!data_h(2) & ((\data_h[1]~7\) # (GND)))
-- \data_h[2]~9\ = CARRY((!\data_h[1]~7\) # (!data_h(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_h(2),
	datad => VCC,
	cin => \data_h[1]~7\,
	combout => \data_h[2]~8_combout\,
	cout => \data_h[2]~9\);

-- Location: LCCOMB_X25_Y6_N22
\data_h[3]~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[3]~10_combout\ = (data_h(3) & (\data_h[2]~9\ $ (GND))) # (!data_h(3) & (!\data_h[2]~9\ & VCC))
-- \data_h[3]~11\ = CARRY((data_h(3) & !\data_h[2]~9\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_h(3),
	datad => VCC,
	cin => \data_h[2]~9\,
	combout => \data_h[3]~10_combout\,
	cout => \data_h[3]~11\);

-- Location: LCCOMB_X25_Y6_N24
\data_h[4]~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[4]~12_combout\ = (data_h(4) & (!\data_h[3]~11\)) # (!data_h(4) & ((\data_h[3]~11\) # (GND)))
-- \data_h[4]~13\ = CARRY((!\data_h[3]~11\) # (!data_h(4)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_h(4),
	datad => VCC,
	cin => \data_h[3]~11\,
	combout => \data_h[4]~12_combout\,
	cout => \data_h[4]~13\);

-- Location: LCFF_X25_Y6_N27
\data_h[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[5]~14_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(5));

-- Location: LCFF_X25_Y6_N25
\data_h[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[4]~12_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(4));

-- Location: LCFF_X25_Y6_N19
\data_h[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[1]~6_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(1));

-- Location: LCFF_X25_Y6_N21
\data_h[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[2]~8_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(2));

-- Location: LCFF_X25_Y6_N23
\data_h[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[3]~10_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(3));

-- Location: LCCOMB_X25_Y6_N12
\Equal15~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal15~0_combout\ = (!data_h_low(0) & (!data_h(1) & (!data_h(2) & data_h(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(0),
	datab => data_h(1),
	datac => data_h(2),
	datad => data_h(3),
	combout => \Equal15~0_combout\);

-- Location: LCCOMB_X25_Y6_N14
\Equal15~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal15~1_combout\ = (!data_h(6) & (!data_h(5) & (data_h(4) & \Equal15~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h(6),
	datab => data_h(5),
	datac => data_h(4),
	datad => \Equal15~0_combout\,
	combout => \Equal15~1_combout\);

-- Location: LCFF_X26_Y6_N1
\data_min_high[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high[0]~4_combout\,
	aclr => \Equal15~1_combout\,
	ena => \Equal12~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(0));

-- Location: LCCOMB_X22_Y6_N0
\data_count_seg~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg~2_combout\ = (data_count_seg(1) & ((data_count_seg(2) $ (data_count_seg(0))))) # (!data_count_seg(1) & (data_count_seg(2) & ((data_count_seg(3)) # (data_count_seg(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(3),
	datac => data_count_seg(2),
	datad => data_count_seg(0),
	combout => \data_count_seg~2_combout\);

-- Location: LCFF_X22_Y6_N1
\data_count_seg[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(2));

-- Location: LCCOMB_X22_Y6_N14
\data_count_seg[3]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg[3]~3_combout\ = data_count_seg(3) $ (((data_count_seg(1) & (data_count_seg(2) & data_count_seg(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(2),
	datac => data_count_seg(3),
	datad => data_count_seg(0),
	combout => \data_count_seg[3]~3_combout\);

-- Location: LCFF_X22_Y6_N15
\data_count_seg[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg[3]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(3));

-- Location: LCCOMB_X22_Y6_N18
\data_count_seg~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg~1_combout\ = (!data_count_seg(0) & ((data_count_seg(1)) # ((data_count_seg(3)) # (!data_count_seg(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111000001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(3),
	datac => data_count_seg(0),
	datad => data_count_seg(2),
	combout => \data_count_seg~1_combout\);

-- Location: LCFF_X22_Y6_N19
\data_count_seg[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(0));

-- Location: LCCOMB_X22_Y6_N30
\Equal10~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal10~0_combout\ = (data_count_seg(1)) # (((data_count_seg(3)) # (data_count_seg(2))) # (!data_count_seg(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(0),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \Equal10~0_combout\);

-- Location: LCCOMB_X22_Y6_N6
\tmp_seg7data[0]~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~7_combout\ = (!\Equal9~0_combout\ & (\Equal7~0_combout\ & (data_min_high(0) & !\Equal10~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => \Equal7~0_combout\,
	datac => data_min_high(0),
	datad => \Equal10~0_combout\,
	combout => \tmp_seg7data[0]~7_combout\);

-- Location: LCCOMB_X22_Y6_N28
\tmp_seg7data[0]~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~8_combout\ = (\tmp_seg7data[0]~7_combout\) # ((\Equal9~0_combout\ & (\Equal7~0_combout\ & data_min_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => \Equal7~0_combout\,
	datac => \tmp_seg7data[0]~7_combout\,
	datad => data_min_low(0),
	combout => \tmp_seg7data[0]~8_combout\);

-- Location: LCCOMB_X22_Y6_N26
\tmp_seg7data~9\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data~9_combout\ = (!data_count_seg(3) & (!data_count_seg(2) & ((!data_count_seg(0)) # (!data_count_seg(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(0),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \tmp_seg7data~9_combout\);

-- Location: LCCOMB_X22_Y6_N4
\tmp_seg7data[0]~11\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~11_combout\ = (\tmp_seg7data[0]~6_combout\) # ((\tmp_seg7data[0]~8_combout\) # ((\tmp_seg7data[0]~10_combout\ & \tmp_seg7data~9_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111011111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~6_combout\,
	datab => \tmp_seg7data[0]~10_combout\,
	datac => \tmp_seg7data[0]~8_combout\,
	datad => \tmp_seg7data~9_combout\,
	combout => \tmp_seg7data[0]~11_combout\);

-- Location: LCCOMB_X22_Y6_N12
\tmp_seg7data[2]~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~18_combout\ = (\Equal9~0_combout\ & (((data_min_low(2))))) # (!\Equal9~0_combout\ & (data_min_high(2) & ((!\Equal10~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000011100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => data_min_high(2),
	datac => data_min_low(2),
	datad => \Equal10~0_combout\,
	combout => \tmp_seg7data[2]~18_combout\);

-- Location: LCCOMB_X22_Y6_N22
\tmp_seg7data[2]~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~16_combout\ = (\tmp_seg7data[0]~10_combout\ & \Equal10~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \tmp_seg7data[0]~10_combout\,
	datad => \Equal10~0_combout\,
	combout => \tmp_seg7data[2]~16_combout\);

-- Location: LCCOMB_X22_Y6_N10
\tmp_seg7data[2]~19\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~19_combout\ = (\tmp_seg7data[2]~17_combout\) # ((\tmp_seg7data[2]~16_combout\) # ((\Equal7~0_combout\ & \tmp_seg7data[2]~18_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[2]~17_combout\,
	datab => \Equal7~0_combout\,
	datac => \tmp_seg7data[2]~18_combout\,
	datad => \tmp_seg7data[2]~16_combout\,
	combout => \tmp_seg7data[2]~19_combout\);

-- Location: LCCOMB_X24_Y6_N2
\tmp_seg7data[1]~13\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~13_combout\ = (\Equal9~0_combout\ & (data_min_low(1))) # (!\Equal9~0_combout\ & (((data_min_high(1) & !\Equal10~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => data_min_low(1),
	datac => data_min_high(1),
	datad => \Equal10~0_combout\,
	combout => \tmp_seg7data[1]~13_combout\);

-- Location: LCCOMB_X24_Y6_N22
\tmp_seg7data[3]~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~5_combout\ = (!\Equal9~0_combout\ & (\Equal7~0_combout\ & \Equal10~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datac => \Equal7~0_combout\,
	datad => \Equal10~0_combout\,
	combout => \tmp_seg7data[3]~5_combout\);

-- Location: LCCOMB_X24_Y6_N8
\tmp_seg7data[1]~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~14_combout\ = (\tmp_seg7data[1]~12_combout\ & ((\tmp_seg7data[3]~5_combout\) # ((\tmp_seg7data[1]~13_combout\ & \Equal7~0_combout\)))) # (!\tmp_seg7data[1]~12_combout\ & (\tmp_seg7data[1]~13_combout\ & (\Equal7~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110101011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[1]~12_combout\,
	datab => \tmp_seg7data[1]~13_combout\,
	datac => \Equal7~0_combout\,
	datad => \tmp_seg7data[3]~5_combout\,
	combout => \tmp_seg7data[1]~14_combout\);

-- Location: LCCOMB_X13_Y10_N4
\tmp_seg7data[0]~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~4_combout\ = (data_mode(1)) # ((data_mode(2)) # (data_mode(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datac => data_mode(2),
	datad => data_mode(3),
	combout => \tmp_seg7data[0]~4_combout\);

-- Location: LCCOMB_X22_Y6_N24
\data_count_seg[1]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg[1]~0_combout\ = data_count_seg(1) $ (data_count_seg(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_count_seg(1),
	datad => data_count_seg(0),
	combout => \data_count_seg[1]~0_combout\);

-- Location: LCFF_X22_Y6_N25
\data_count_seg[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg[1]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(1));

-- Location: LCCOMB_X21_Y6_N4
\tmp_seg7data[0]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~2_combout\ = (data_count_seg(3)) # ((data_count_seg(2)) # ((data_count_seg(0) & data_count_seg(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(0),
	datab => data_count_seg(3),
	datac => data_count_seg(1),
	datad => data_count_seg(2),
	combout => \tmp_seg7data[0]~2_combout\);

-- Location: LCCOMB_X20_Y6_N16
\tmp_seg7data[1]~15\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~15_combout\ = (\tmp_seg7data[1]~14_combout\) # ((led_c(1) & (\tmp_seg7data[0]~4_combout\ & \tmp_seg7data[0]~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => led_c(1),
	datab => \tmp_seg7data[1]~14_combout\,
	datac => \tmp_seg7data[0]~4_combout\,
	datad => \tmp_seg7data[0]~2_combout\,
	combout => \tmp_seg7data[1]~15_combout\);

-- Location: LCCOMB_X25_Y6_N4
\Add7~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add7~4_combout\ = (data_h_low(2) & (\Add7~3\ $ (GND))) # (!data_h_low(2) & (!\Add7~3\ & VCC))
-- \Add7~5\ = CARRY((data_h_low(2) & !\Add7~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(2),
	datad => VCC,
	cin => \Add7~3\,
	combout => \Add7~4_combout\,
	cout => \Add7~5\);

-- Location: LCFF_X25_Y6_N5
\data_h_low[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add7~4_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(2));

-- Location: LCCOMB_X25_Y6_N6
\Add7~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add7~6_combout\ = (data_h_low(3) & (!\Add7~5\)) # (!data_h_low(3) & ((\Add7~5\) # (GND)))
-- \Add7~7\ = CARRY((!\Add7~5\) # (!data_h_low(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(3),
	datad => VCC,
	cin => \Add7~5\,
	combout => \Add7~6_combout\,
	cout => \Add7~7\);

-- Location: LCCOMB_X24_Y6_N18
\data_h_low~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_low~1_combout\ = (\Add7~6_combout\ & ((!data_h_low(0)) # (!\Equal14~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal14~0_combout\,
	datac => data_h_low(0),
	datad => \Add7~6_combout\,
	combout => \data_h_low~1_combout\);

-- Location: LCFF_X24_Y6_N19
\data_h_low[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_low~1_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(3));

-- Location: LCCOMB_X25_Y6_N8
\Add7~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add7~8_combout\ = \Add7~7\ $ (!data_h_low(4))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => data_h_low(4),
	cin => \Add7~7\,
	combout => \Add7~8_combout\);

-- Location: LCFF_X25_Y6_N9
\data_h_low[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add7~8_combout\,
	aclr => \Equal15~1_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(4));

-- Location: LCCOMB_X24_Y6_N0
\Equal14~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal14~0_combout\ = (!data_h_low(1) & (data_h_low(3) & (!data_h_low(4) & !data_h_low(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(1),
	datab => data_h_low(3),
	datac => data_h_low(4),
	datad => data_h_low(2),
	combout => \Equal14~0_combout\);

-- Location: LCCOMB_X25_Y6_N30
\data_h_high[0]~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[0]~7_combout\ = data_h_high(0) $ (((data_h_low(0) & (\Equal14~0_combout\ & \data_h_high[0]~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(0),
	datab => \Equal14~0_combout\,
	datac => data_h_high(0),
	datad => \data_h_high[0]~2_combout\,
	combout => \data_h_high[0]~7_combout\);

-- Location: LCFF_X25_Y6_N31
\data_h_high[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[0]~7_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(0));

-- Location: LCCOMB_X24_Y6_N14
\Equal14~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal14~1_combout\ = (data_h_low(0) & \Equal14~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_h_low(0),
	datad => \Equal14~0_combout\,
	combout => \Equal14~1_combout\);

-- Location: LCCOMB_X24_Y6_N12
\data_h_high[2]~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[2]~4_combout\ = (data_h_high(1) & (data_h_high(0) & (\Equal14~1_combout\ & \data_h_high[0]~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(1),
	datab => data_h_high(0),
	datac => \Equal14~1_combout\,
	datad => \data_h_high[0]~2_combout\,
	combout => \data_h_high[2]~4_combout\);

-- Location: LCCOMB_X24_Y6_N30
\data_h_high[2]~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[2]~5_combout\ = data_h_high(2) $ (\data_h_high[2]~4_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_h_high(2),
	datad => \data_h_high[2]~4_combout\,
	combout => \data_h_high[2]~5_combout\);

-- Location: LCFF_X24_Y6_N31
\data_h_high[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[2]~5_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(2));

-- Location: LCCOMB_X24_Y6_N4
\data_h_high[3]~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[3]~6_combout\ = data_h_high(3) $ (((data_h_high(2) & \data_h_high[2]~4_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_h_high(2),
	datac => data_h_high(3),
	datad => \data_h_high[2]~4_combout\,
	combout => \data_h_high[3]~6_combout\);

-- Location: LCFF_X24_Y6_N5
\data_h_high[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[3]~6_combout\,
	aclr => \Equal15~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(3));

-- Location: LCCOMB_X24_Y6_N26
\tmp_seg7data[3]~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~20_combout\ = (\tmp_seg7data[3]~5_combout\ & ((\tmp_seg7data[0]~0_combout\ & ((data_h_low(3)))) # (!\tmp_seg7data[0]~0_combout\ & (data_h_high(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100100001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~0_combout\,
	datab => \tmp_seg7data[3]~5_combout\,
	datac => data_h_high(3),
	datad => data_h_low(3),
	combout => \tmp_seg7data[3]~20_combout\);

-- Location: LCCOMB_X24_Y6_N10
\tmp_seg7data[3]~22\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~22_combout\ = (\tmp_seg7data[3]~20_combout\) # ((\tmp_seg7data[3]~21_combout\ & \Equal7~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110110011101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[3]~21_combout\,
	datab => \tmp_seg7data[3]~20_combout\,
	datac => \Equal7~0_combout\,
	combout => \tmp_seg7data[3]~22_combout\);

-- Location: LCCOMB_X17_Y3_N12
\dis|Mux6~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux6~0_combout\ = (\tmp_seg7data[2]~19_combout\ & (!\tmp_seg7data[1]~15_combout\ & ((\tmp_seg7data[3]~22_combout\) # (!\tmp_seg7data[0]~11_combout\)))) # (!\tmp_seg7data[2]~19_combout\ & (\tmp_seg7data[0]~11_combout\ & (\tmp_seg7data[1]~15_combout\ $ 
-- (!\tmp_seg7data[3]~22_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010110000000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux6~0_combout\);

-- Location: LCCOMB_X17_Y3_N10
\dis|Mux5~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux5~0_combout\ = (\tmp_seg7data[1]~15_combout\ & ((\tmp_seg7data[0]~11_combout\ & ((\tmp_seg7data[3]~22_combout\))) # (!\tmp_seg7data[0]~11_combout\ & (\tmp_seg7data[2]~19_combout\)))) # (!\tmp_seg7data[1]~15_combout\ & (\tmp_seg7data[2]~19_combout\ 
-- & (\tmp_seg7data[0]~11_combout\ $ (\tmp_seg7data[3]~22_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110010001001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux5~0_combout\);

-- Location: LCCOMB_X17_Y3_N4
\dis|Mux4~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux4~0_combout\ = (\tmp_seg7data[2]~19_combout\ & (\tmp_seg7data[3]~22_combout\ & ((\tmp_seg7data[1]~15_combout\) # (!\tmp_seg7data[0]~11_combout\)))) # (!\tmp_seg7data[2]~19_combout\ & (!\tmp_seg7data[0]~11_combout\ & (\tmp_seg7data[1]~15_combout\ & 
-- !\tmp_seg7data[3]~22_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100010000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux4~0_combout\);

-- Location: LCCOMB_X17_Y3_N2
\dis|Mux3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux3~0_combout\ = (\tmp_seg7data[1]~15_combout\ & ((\tmp_seg7data[0]~11_combout\ & (\tmp_seg7data[2]~19_combout\)) # (!\tmp_seg7data[0]~11_combout\ & (!\tmp_seg7data[2]~19_combout\ & \tmp_seg7data[3]~22_combout\)))) # (!\tmp_seg7data[1]~15_combout\ & 
-- (!\tmp_seg7data[3]~22_combout\ & (\tmp_seg7data[0]~11_combout\ $ (\tmp_seg7data[2]~19_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001000010000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux3~0_combout\);

-- Location: LCCOMB_X17_Y3_N8
\dis|Mux2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux2~0_combout\ = (\tmp_seg7data[1]~15_combout\ & (\tmp_seg7data[0]~11_combout\ & ((!\tmp_seg7data[3]~22_combout\)))) # (!\tmp_seg7data[1]~15_combout\ & ((\tmp_seg7data[2]~19_combout\ & ((!\tmp_seg7data[3]~22_combout\))) # 
-- (!\tmp_seg7data[2]~19_combout\ & (\tmp_seg7data[0]~11_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001010101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux2~0_combout\);

-- Location: LCCOMB_X17_Y3_N26
\dis|Mux1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux1~0_combout\ = (\tmp_seg7data[2]~19_combout\ & ((\tmp_seg7data[1]~15_combout\ & (\tmp_seg7data[0]~11_combout\ & !\tmp_seg7data[3]~22_combout\)) # (!\tmp_seg7data[1]~15_combout\ & ((\tmp_seg7data[3]~22_combout\))))) # (!\tmp_seg7data[2]~19_combout\ 
-- & (!\tmp_seg7data[3]~22_combout\ & ((\tmp_seg7data[0]~11_combout\) # (\tmp_seg7data[1]~15_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110010110010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux1~0_combout\);

-- Location: LCCOMB_X17_Y3_N20
\dis|Mux0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux0~0_combout\ = (\tmp_seg7data[3]~22_combout\) # ((\tmp_seg7data[2]~19_combout\ & ((!\tmp_seg7data[1]~15_combout\) # (!\tmp_seg7data[0]~11_combout\))) # (!\tmp_seg7data[2]~19_combout\ & ((\tmp_seg7data[1]~15_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111101111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~11_combout\,
	datab => \tmp_seg7data[2]~19_combout\,
	datac => \tmp_seg7data[1]~15_combout\,
	datad => \tmp_seg7data[3]~22_combout\,
	combout => \dis|Mux0~0_combout\);

-- Location: LCCOMB_X22_Y6_N20
\seg7com~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \seg7com~0_combout\ = ((data_count_seg(0)) # ((data_count_seg(3)) # (data_count_seg(2)))) # (!data_count_seg(1))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(0),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \seg7com~0_combout\);

-- Location: LCCOMB_X22_Y6_N8
\Equal9~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal9~0_combout\ = (!data_count_seg(1) & (!data_count_seg(0) & (!data_count_seg(3) & !data_count_seg(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(0),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \Equal9~0_combout\);

-- Location: PIN_90,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\key3~I\ : cycloneii_io
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
	padio => ww_key3);

-- Location: PIN_91,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\key4~I\ : cycloneii_io
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
	padio => ww_key4);

-- Location: PIN_72,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\key5~I\ : cycloneii_io
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
	padio => ww_key5);

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
	datain => \dis|ALT_INV_Mux0~0_combout\,
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
	datain => \tmp_seg7data~9_combout\,
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
	datain => \seg7com~0_combout\,
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
	datain => \Equal10~0_combout\,
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
	datain => \ALT_INV_Equal9~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7com(3));
END structure;


