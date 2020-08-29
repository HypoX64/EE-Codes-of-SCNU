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

-- DATE "05/20/2017 14:57:51"

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
	key6 : IN std_logic;
	sysclk : IN std_logic;
	led_c_r : OUT std_logic;
	led_c_y : OUT std_logic;
	led_c_g : OUT std_logic;
	led_p_r : OUT std_logic;
	led_p_g : OUT std_logic;
	seg7data : OUT std_logic_vector(7 DOWNTO 0);
	seg7com : OUT std_logic_vector(3 DOWNTO 0)
	);
END test;

-- Design Ports Information
-- key1	=>  Location: PIN_88,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key2	=>  Location: PIN_89,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key3	=>  Location: PIN_90,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key4	=>  Location: PIN_91,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- led_c_r	=>  Location: PIN_25,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- led_c_y	=>  Location: PIN_24,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- led_c_g	=>  Location: PIN_28,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- led_p_r	=>  Location: PIN_30,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
-- led_p_g	=>  Location: PIN_27,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
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
-- key5	=>  Location: PIN_72,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- sysclk	=>  Location: PIN_17,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- key6	=>  Location: PIN_26,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default


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
SIGNAL ww_key6 : std_logic;
SIGNAL ww_sysclk : std_logic;
SIGNAL ww_led_c_r : std_logic;
SIGNAL ww_led_c_y : std_logic;
SIGNAL ww_led_c_g : std_logic;
SIGNAL ww_led_p_r : std_logic;
SIGNAL ww_led_p_g : std_logic;
SIGNAL ww_seg7data : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_seg7com : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_s~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_ms~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \div|Q_min~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \sysclk~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \Add0~8_combout\ : std_logic;
SIGNAL \Add0~12_combout\ : std_logic;
SIGNAL \Add6~6_combout\ : std_logic;
SIGNAL \data_time_count[8]~28\ : std_logic;
SIGNAL \data_time_count[9]~29_combout\ : std_logic;
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
SIGNAL \tmp_seg7data[0]~3_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~4_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~5_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~12_combout\ : std_logic;
SIGNAL \Add0~48_combout\ : std_logic;
SIGNAL \Equal1~1_combout\ : std_logic;
SIGNAL \div|Q_ms~regout\ : std_logic;
SIGNAL \div|Q_min~regout\ : std_logic;
SIGNAL \data_h_high[2]~5_combout\ : std_logic;
SIGNAL \data_h_low~1_combout\ : std_logic;
SIGNAL \div|Equal2~0_combout\ : std_logic;
SIGNAL \div|Equal2~1_combout\ : std_logic;
SIGNAL \div|Equal2~2_combout\ : std_logic;
SIGNAL \div|Equal2~3_combout\ : std_logic;
SIGNAL \div|Equal2~4_combout\ : std_logic;
SIGNAL \div|Equal2~5_combout\ : std_logic;
SIGNAL \div|Equal2~6_combout\ : std_logic;
SIGNAL \div|Equal2~7_combout\ : std_logic;
SIGNAL \div|Equal2~8_combout\ : std_logic;
SIGNAL \div|Equal0~0_combout\ : std_logic;
SIGNAL \div|Equal0~1_combout\ : std_logic;
SIGNAL \div|Equal0~2_combout\ : std_logic;
SIGNAL \div|Equal0~3_combout\ : std_logic;
SIGNAL \div|Equal0~4_combout\ : std_logic;
SIGNAL \div|Equal0~5_combout\ : std_logic;
SIGNAL \div|Equal0~6_combout\ : std_logic;
SIGNAL \div|Q_ms~0_combout\ : std_logic;
SIGNAL \div|Equal3~0_combout\ : std_logic;
SIGNAL \div|Equal3~1_combout\ : std_logic;
SIGNAL \div|Q_min~0_combout\ : std_logic;
SIGNAL \div|data_s~0_combout\ : std_logic;
SIGNAL \div|data_s~1_combout\ : std_logic;
SIGNAL \div|data_s~2_combout\ : std_logic;
SIGNAL \div|data_s~3_combout\ : std_logic;
SIGNAL \div|data_s~4_combout\ : std_logic;
SIGNAL \div|data_s~5_combout\ : std_logic;
SIGNAL \div|data_s~6_combout\ : std_logic;
SIGNAL \div|data_s~7_combout\ : std_logic;
SIGNAL \div|data_s~8_combout\ : std_logic;
SIGNAL \div|data_ms~0_combout\ : std_logic;
SIGNAL \div|data_ms~1_combout\ : std_logic;
SIGNAL \div|data_ms~2_combout\ : std_logic;
SIGNAL \div|data_ms~3_combout\ : std_logic;
SIGNAL \div|data_ms~4_combout\ : std_logic;
SIGNAL \div|data_ms~5_combout\ : std_logic;
SIGNAL \div|data_ms~6_combout\ : std_logic;
SIGNAL \div|data_min~0_combout\ : std_logic;
SIGNAL \div|data_min~1_combout\ : std_logic;
SIGNAL \div|data_min~2_combout\ : std_logic;
SIGNAL \div|data_min~3_combout\ : std_logic;
SIGNAL \div|data_min~4_combout\ : std_logic;
SIGNAL \data_h_high[0]~7_combout\ : std_logic;
SIGNAL \sysclk~combout\ : std_logic;
SIGNAL \div|Q_ms~clkctrl_outclk\ : std_logic;
SIGNAL \div|Q_min~clkctrl_outclk\ : std_logic;
SIGNAL \sysclk~clkctrl_outclk\ : std_logic;
SIGNAL \data_time_count[0]~11\ : std_logic;
SIGNAL \data_time_count[1]~13\ : std_logic;
SIGNAL \data_time_count[2]~15\ : std_logic;
SIGNAL \data_time_count[3]~16_combout\ : std_logic;
SIGNAL \key6~combout\ : std_logic;
SIGNAL \Add6~0_combout\ : std_logic;
SIGNAL \data_h[1]~6_combout\ : std_logic;
SIGNAL \Add4~0_combout\ : std_logic;
SIGNAL \Add4~1\ : std_logic;
SIGNAL \Add4~3\ : std_logic;
SIGNAL \Add4~4_combout\ : std_logic;
SIGNAL \Add4~5\ : std_logic;
SIGNAL \Add4~6_combout\ : std_logic;
SIGNAL \data_min_low~1_combout\ : std_logic;
SIGNAL \Add4~2_combout\ : std_logic;
SIGNAL \data_min_low~0_combout\ : std_logic;
SIGNAL \Add4~7\ : std_logic;
SIGNAL \Add4~8_combout\ : std_logic;
SIGNAL \Equal14~0_combout\ : std_logic;
SIGNAL \data_min_high[0]~4_combout\ : std_logic;
SIGNAL \Equal14~1_combout\ : std_logic;
SIGNAL \data_min_high[3]~2_combout\ : std_logic;
SIGNAL \data_min_high[3]~3_combout\ : std_logic;
SIGNAL \data_min_high~0_combout\ : std_logic;
SIGNAL \data_min_high~1_combout\ : std_logic;
SIGNAL \Equal15~0_combout\ : std_logic;
SIGNAL \data_h_high[0]~2_combout\ : std_logic;
SIGNAL \data_h[3]~10_combout\ : std_logic;
SIGNAL \data_h[4]~12_combout\ : std_logic;
SIGNAL \Equal17~1_combout\ : std_logic;
SIGNAL \Equal17~2_combout\ : std_logic;
SIGNAL \data_h[1]~7\ : std_logic;
SIGNAL \data_h[2]~8_combout\ : std_logic;
SIGNAL \data_h[2]~9\ : std_logic;
SIGNAL \data_h[3]~11\ : std_logic;
SIGNAL \data_h[4]~13\ : std_logic;
SIGNAL \data_h[5]~14_combout\ : std_logic;
SIGNAL \night~2_combout\ : std_logic;
SIGNAL \night~3_combout\ : std_logic;
SIGNAL \key_flag~0_combout\ : std_logic;
SIGNAL \key_flag~regout\ : std_logic;
SIGNAL \process_2~0_combout\ : std_logic;
SIGNAL \data_time_count[0]~10_combout\ : std_logic;
SIGNAL \data_time_count[2]~14_combout\ : std_logic;
SIGNAL \Equal7~0_combout\ : std_logic;
SIGNAL \Equal7~1_combout\ : std_logic;
SIGNAL \data_time_count~20_combout\ : std_logic;
SIGNAL \data_time_count[3]~17\ : std_logic;
SIGNAL \data_time_count[4]~19\ : std_logic;
SIGNAL \data_time_count[5]~21_combout\ : std_logic;
SIGNAL \data_time_count[5]~22\ : std_logic;
SIGNAL \data_time_count[6]~23_combout\ : std_logic;
SIGNAL \data_time_count[6]~24\ : std_logic;
SIGNAL \data_time_count[7]~25_combout\ : std_logic;
SIGNAL \data_time_count[7]~26\ : std_logic;
SIGNAL \data_time_count[8]~27_combout\ : std_logic;
SIGNAL \Equal5~0_combout\ : std_logic;
SIGNAL \data_h[5]~15\ : std_logic;
SIGNAL \data_h[6]~16_combout\ : std_logic;
SIGNAL \Equal17~0_combout\ : std_logic;
SIGNAL \led_c~2_combout\ : std_logic;
SIGNAL \led_p~5_combout\ : std_logic;
SIGNAL \Equal6~0_combout\ : std_logic;
SIGNAL \data_time_count[1]~12_combout\ : std_logic;
SIGNAL \data_time_count[4]~18_combout\ : std_logic;
SIGNAL \Equal5~1_combout\ : std_logic;
SIGNAL \Equal5~2_combout\ : std_logic;
SIGNAL \led_c~4_combout\ : std_logic;
SIGNAL \led_c~5_combout\ : std_logic;
SIGNAL \LessThan1~0_combout\ : std_logic;
SIGNAL \led_c~0_combout\ : std_logic;
SIGNAL \led_c~1_combout\ : std_logic;
SIGNAL \led_c~3_combout\ : std_logic;
SIGNAL \led_p[1]~2_combout\ : std_logic;
SIGNAL \led_p[1]~3_combout\ : std_logic;
SIGNAL \Equal2~0_combout\ : std_logic;
SIGNAL \Equal3~0_combout\ : std_logic;
SIGNAL \div|Q_s~0_combout\ : std_logic;
SIGNAL \div|Q_s~regout\ : std_logic;
SIGNAL \div|Q_s~clkctrl_outclk\ : std_logic;
SIGNAL \led_p~4_combout\ : std_logic;
SIGNAL \data_count_seg[1]~3_combout\ : std_logic;
SIGNAL \data_count_seg~1_combout\ : std_logic;
SIGNAL \data_count_seg~0_combout\ : std_logic;
SIGNAL \Equal12~0_combout\ : std_logic;
SIGNAL \Add0~66_combout\ : std_logic;
SIGNAL \key5~combout\ : std_logic;
SIGNAL \Add0~67_combout\ : std_logic;
SIGNAL \LessThan0~0_combout\ : std_logic;
SIGNAL \Add0~50_combout\ : std_logic;
SIGNAL \Add0~9\ : std_logic;
SIGNAL \Add0~11\ : std_logic;
SIGNAL \Add0~13\ : std_logic;
SIGNAL \Add0~14_combout\ : std_logic;
SIGNAL \Add0~51_combout\ : std_logic;
SIGNAL \Add0~15\ : std_logic;
SIGNAL \Add0~16_combout\ : std_logic;
SIGNAL \Add0~52_combout\ : std_logic;
SIGNAL \Add0~17\ : std_logic;
SIGNAL \Add0~18_combout\ : std_logic;
SIGNAL \Add0~53_combout\ : std_logic;
SIGNAL \Add0~19\ : std_logic;
SIGNAL \Add0~21\ : std_logic;
SIGNAL \Add0~22_combout\ : std_logic;
SIGNAL \Add0~55_combout\ : std_logic;
SIGNAL \Add0~23\ : std_logic;
SIGNAL \Add0~24_combout\ : std_logic;
SIGNAL \Add0~57_combout\ : std_logic;
SIGNAL \Add0~25\ : std_logic;
SIGNAL \Add0~26_combout\ : std_logic;
SIGNAL \Add0~56_combout\ : std_logic;
SIGNAL \COUNT1[9]~feeder_combout\ : std_logic;
SIGNAL \Add0~27\ : std_logic;
SIGNAL \Add0~29\ : std_logic;
SIGNAL \Add0~30_combout\ : std_logic;
SIGNAL \Add0~59_combout\ : std_logic;
SIGNAL \Add0~31\ : std_logic;
SIGNAL \Add0~32_combout\ : std_logic;
SIGNAL \Add0~61_combout\ : std_logic;
SIGNAL \Add0~33\ : std_logic;
SIGNAL \Add0~35\ : std_logic;
SIGNAL \Add0~37\ : std_logic;
SIGNAL \Add0~38_combout\ : std_logic;
SIGNAL \Add0~63_combout\ : std_logic;
SIGNAL \Add0~34_combout\ : std_logic;
SIGNAL \Add0~62_combout\ : std_logic;
SIGNAL \LessThan0~3_combout\ : std_logic;
SIGNAL \Add0~20_combout\ : std_logic;
SIGNAL \Add0~54_combout\ : std_logic;
SIGNAL \LessThan0~2_combout\ : std_logic;
SIGNAL \Add0~39\ : std_logic;
SIGNAL \Add0~41\ : std_logic;
SIGNAL \Add0~43\ : std_logic;
SIGNAL \Add0~45\ : std_logic;
SIGNAL \Add0~46_combout\ : std_logic;
SIGNAL \Add0~65_combout\ : std_logic;
SIGNAL \COUNT1[19]~feeder_combout\ : std_logic;
SIGNAL \LessThan0~1_combout\ : std_logic;
SIGNAL \LessThan0~4_combout\ : std_logic;
SIGNAL \Add0~44_combout\ : std_logic;
SIGNAL \Add0~64_combout\ : std_logic;
SIGNAL \Add0~42_combout\ : std_logic;
SIGNAL \Add0~40_combout\ : std_logic;
SIGNAL \data_mode[3]~0_combout\ : std_logic;
SIGNAL \data_mode[3]~8_combout\ : std_logic;
SIGNAL \Add0~10_combout\ : std_logic;
SIGNAL \Add0~49_combout\ : std_logic;
SIGNAL \data_mode[3]~2_combout\ : std_logic;
SIGNAL \Add0~28_combout\ : std_logic;
SIGNAL \Add0~58_combout\ : std_logic;
SIGNAL \data_mode[3]~4_combout\ : std_logic;
SIGNAL \Add0~36_combout\ : std_logic;
SIGNAL \Add0~60_combout\ : std_logic;
SIGNAL \data_mode[3]~5_combout\ : std_logic;
SIGNAL \data_mode[3]~6_combout\ : std_logic;
SIGNAL \data_mode[2]~13_combout\ : std_logic;
SIGNAL \data_mode[3]~1_combout\ : std_logic;
SIGNAL \data_mode[0]~7_combout\ : std_logic;
SIGNAL \data_mode[1]~9_combout\ : std_logic;
SIGNAL \Equal1~0_combout\ : std_logic;
SIGNAL \data_mode[3]~3_combout\ : std_logic;
SIGNAL \data_mode[3]~10_combout\ : std_logic;
SIGNAL \data_mode[3]~11_combout\ : std_logic;
SIGNAL \data_mode[3]~12_combout\ : std_logic;
SIGNAL \Equal9~0_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~0_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~1_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~2_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~6_combout\ : std_logic;
SIGNAL \tmp_seg7data[0]~7_combout\ : std_logic;
SIGNAL \Add6~5\ : std_logic;
SIGNAL \Add6~7\ : std_logic;
SIGNAL \Add6~8_combout\ : std_logic;
SIGNAL \Equal16~0_combout\ : std_logic;
SIGNAL \Add6~1\ : std_logic;
SIGNAL \Add6~2_combout\ : std_logic;
SIGNAL \data_h_low~0_combout\ : std_logic;
SIGNAL \Add6~3\ : std_logic;
SIGNAL \Add6~4_combout\ : std_logic;
SIGNAL \data_count_seg[3]~2_combout\ : std_logic;
SIGNAL \Equal13~0_combout\ : std_logic;
SIGNAL \Equal11~0_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~13_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~14_combout\ : std_logic;
SIGNAL \tmp_seg7data[2]~15_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~10_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~8_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~9_combout\ : std_logic;
SIGNAL \tmp_seg7data[1]~11_combout\ : std_logic;
SIGNAL \Equal16~1_combout\ : std_logic;
SIGNAL \data_h_high[1]~3_combout\ : std_logic;
SIGNAL \data_h_high[2]~4_combout\ : std_logic;
SIGNAL \data_h_high[3]~6_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~18_combout\ : std_logic;
SIGNAL \Equal12~1_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~16_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~17_combout\ : std_logic;
SIGNAL \tmp_seg7data[3]~19_combout\ : std_logic;
SIGNAL \dis|Mux6~0_combout\ : std_logic;
SIGNAL \dis|Mux5~0_combout\ : std_logic;
SIGNAL \dis|Mux4~0_combout\ : std_logic;
SIGNAL \dis|Mux3~0_combout\ : std_logic;
SIGNAL \dis|Mux2~0_combout\ : std_logic;
SIGNAL \dis|Mux1~0_combout\ : std_logic;
SIGNAL \dis|Mux0~0_combout\ : std_logic;
SIGNAL \seg7com~2_combout\ : std_logic;
SIGNAL \seg7com~3_combout\ : std_logic;
SIGNAL \seg7com~5_combout\ : std_logic;
SIGNAL \seg7com~4_combout\ : std_logic;
SIGNAL data_min_high : std_logic_vector(3 DOWNTO 0);
SIGNAL data_h_low : std_logic_vector(4 DOWNTO 0);
SIGNAL data_h_high : std_logic_vector(3 DOWNTO 0);
SIGNAL data_h : std_logic_vector(6 DOWNTO 0);
SIGNAL data_count_seg : std_logic_vector(3 DOWNTO 0);
SIGNAL COUNT1 : std_logic_vector(19 DOWNTO 0);
SIGNAL \div|data_s\ : std_logic_vector(26 DOWNTO 0);
SIGNAL \div|data_ms\ : std_logic_vector(19 DOWNTO 0);
SIGNAL \div|data_min\ : std_logic_vector(6 DOWNTO 0);
SIGNAL data_time_count : std_logic_vector(9 DOWNTO 0);
SIGNAL led_c : std_logic_vector(1 DOWNTO 0);
SIGNAL led_p : std_logic_vector(1 DOWNTO 0);
SIGNAL data_mode : std_logic_vector(3 DOWNTO 0);
SIGNAL data_min_low : std_logic_vector(4 DOWNTO 0);
SIGNAL \ALT_INV_key6~combout\ : std_logic;
SIGNAL \dis|ALT_INV_Mux0~0_combout\ : std_logic;
SIGNAL \ALT_INV_Equal12~1_combout\ : std_logic;
SIGNAL ALT_INV_led_p : std_logic_vector(0 DOWNTO 0);
SIGNAL \ALT_INV_Equal2~0_combout\ : std_logic;

BEGIN

ww_key1 <= key1;
ww_key2 <= key2;
ww_key3 <= key3;
ww_key4 <= key4;
ww_key5 <= key5;
ww_key6 <= key6;
ww_sysclk <= sysclk;
led_c_r <= ww_led_c_r;
led_c_y <= ww_led_c_y;
led_c_g <= ww_led_c_g;
led_p_r <= ww_led_p_r;
led_p_g <= ww_led_p_g;
seg7data <= ww_seg7data;
seg7com <= ww_seg7com;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\div|Q_s~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_s~regout\);

\div|Q_ms~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_ms~regout\);

\div|Q_min~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \div|Q_min~regout\);

\sysclk~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \sysclk~combout\);
\ALT_INV_key6~combout\ <= NOT \key6~combout\;
\dis|ALT_INV_Mux0~0_combout\ <= NOT \dis|Mux0~0_combout\;
\ALT_INV_Equal12~1_combout\ <= NOT \Equal12~1_combout\;
ALT_INV_led_p(0) <= NOT led_p(0);
\ALT_INV_Equal2~0_combout\ <= NOT \Equal2~0_combout\;

-- Location: LCFF_X15_Y8_N29
\data_time_count[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[9]~29_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(9));

-- Location: LCCOMB_X21_Y6_N12
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

-- Location: LCCOMB_X21_Y6_N16
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

-- Location: LCCOMB_X18_Y8_N28
\Add6~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add6~6_combout\ = (data_h_low(3) & (!\Add6~5\)) # (!data_h_low(3) & ((\Add6~5\) # (GND)))
-- \Add6~7\ = CARRY((!\Add6~5\) # (!data_h_low(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(3),
	datad => VCC,
	cin => \Add6~5\,
	combout => \Add6~6_combout\,
	cout => \Add6~7\);

-- Location: LCCOMB_X15_Y8_N26
\data_time_count[8]~27\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[8]~27_combout\ = (data_time_count(8) & (\data_time_count[7]~26\ $ (GND))) # (!data_time_count(8) & (!\data_time_count[7]~26\ & VCC))
-- \data_time_count[8]~28\ = CARRY((data_time_count(8) & !\data_time_count[7]~26\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(8),
	datad => VCC,
	cin => \data_time_count[7]~26\,
	combout => \data_time_count[8]~27_combout\,
	cout => \data_time_count[8]~28\);

-- Location: LCCOMB_X15_Y8_N28
\data_time_count[9]~29\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[9]~29_combout\ = data_time_count(9) $ (\data_time_count[8]~28\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(9),
	cin => \data_time_count[8]~28\,
	combout => \data_time_count[9]~29_combout\);

-- Location: LCCOMB_X2_Y2_N6
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

-- Location: LCCOMB_X2_Y2_N8
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

-- Location: LCCOMB_X2_Y2_N10
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

-- Location: LCCOMB_X2_Y2_N12
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

-- Location: LCCOMB_X2_Y2_N14
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

-- Location: LCCOMB_X2_Y2_N16
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

-- Location: LCCOMB_X2_Y2_N18
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

-- Location: LCCOMB_X2_Y2_N20
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

-- Location: LCCOMB_X2_Y2_N22
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

-- Location: LCCOMB_X2_Y2_N24
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

-- Location: LCCOMB_X2_Y2_N26
\div|Add2~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~20_combout\ = (\div|data_s\(10) & (\div|Add2~19\ $ (GND))) # (!\div|data_s\(10) & (!\div|Add2~19\ & VCC))
-- \div|Add2~21\ = CARRY((\div|data_s\(10) & !\div|Add2~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(10),
	datad => VCC,
	cin => \div|Add2~19\,
	combout => \div|Add2~20_combout\,
	cout => \div|Add2~21\);

-- Location: LCCOMB_X2_Y2_N28
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

-- Location: LCCOMB_X2_Y2_N30
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

-- Location: LCCOMB_X2_Y1_N0
\div|Add2~26\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~26_combout\ = (\div|data_s\(13) & (!\div|Add2~25\)) # (!\div|data_s\(13) & ((\div|Add2~25\) # (GND)))
-- \div|Add2~27\ = CARRY((!\div|Add2~25\) # (!\div|data_s\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(13),
	datad => VCC,
	cin => \div|Add2~25\,
	combout => \div|Add2~26_combout\,
	cout => \div|Add2~27\);

-- Location: LCCOMB_X2_Y1_N2
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

-- Location: LCCOMB_X2_Y1_N4
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

-- Location: LCCOMB_X2_Y1_N6
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

-- Location: LCCOMB_X2_Y1_N8
\div|Add2~34\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add2~34_combout\ = (\div|data_s\(17) & (!\div|Add2~33\)) # (!\div|data_s\(17) & ((\div|Add2~33\) # (GND)))
-- \div|Add2~35\ = CARRY((!\div|Add2~33\) # (!\div|data_s\(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(17),
	datad => VCC,
	cin => \div|Add2~33\,
	combout => \div|Add2~34_combout\,
	cout => \div|Add2~35\);

-- Location: LCCOMB_X2_Y1_N10
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

-- Location: LCCOMB_X2_Y1_N12
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

-- Location: LCCOMB_X2_Y1_N14
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

-- Location: LCCOMB_X2_Y1_N16
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

-- Location: LCCOMB_X2_Y1_N18
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

-- Location: LCCOMB_X2_Y1_N20
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

-- Location: LCCOMB_X2_Y1_N22
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

-- Location: LCCOMB_X2_Y1_N24
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

-- Location: LCCOMB_X2_Y1_N26
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

-- Location: LCCOMB_X24_Y8_N12
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

-- Location: LCCOMB_X24_Y8_N14
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

-- Location: LCCOMB_X24_Y8_N16
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

-- Location: LCCOMB_X24_Y8_N18
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

-- Location: LCCOMB_X24_Y8_N20
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

-- Location: LCCOMB_X24_Y8_N22
\div|Add0~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~10_combout\ = (\div|data_ms\(5) & (!\div|Add0~9\)) # (!\div|data_ms\(5) & ((\div|Add0~9\) # (GND)))
-- \div|Add0~11\ = CARRY((!\div|Add0~9\) # (!\div|data_ms\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_ms\(5),
	datad => VCC,
	cin => \div|Add0~9\,
	combout => \div|Add0~10_combout\,
	cout => \div|Add0~11\);

-- Location: LCCOMB_X24_Y8_N24
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

-- Location: LCCOMB_X24_Y8_N26
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

-- Location: LCCOMB_X24_Y8_N28
\div|Add0~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add0~16_combout\ = (\div|data_ms\(8) & (\div|Add0~15\ $ (GND))) # (!\div|data_ms\(8) & (!\div|Add0~15\ & VCC))
-- \div|Add0~17\ = CARRY((\div|data_ms\(8) & !\div|Add0~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(8),
	datad => VCC,
	cin => \div|Add0~15\,
	combout => \div|Add0~16_combout\,
	cout => \div|Add0~17\);

-- Location: LCCOMB_X24_Y8_N30
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

-- Location: LCCOMB_X24_Y7_N0
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

-- Location: LCCOMB_X24_Y7_N2
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

-- Location: LCCOMB_X24_Y7_N4
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

-- Location: LCCOMB_X24_Y7_N6
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

-- Location: LCCOMB_X24_Y7_N8
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

-- Location: LCCOMB_X24_Y7_N10
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

-- Location: LCCOMB_X24_Y7_N12
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

-- Location: LCCOMB_X24_Y7_N14
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

-- Location: LCCOMB_X24_Y7_N16
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

-- Location: LCCOMB_X24_Y7_N18
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

-- Location: LCCOMB_X27_Y7_N0
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

-- Location: LCCOMB_X27_Y7_N2
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

-- Location: LCCOMB_X27_Y7_N4
\div|Add3~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~4_combout\ = (\div|data_min\(2) & (\div|Add3~3\ $ (GND))) # (!\div|data_min\(2) & (!\div|Add3~3\ & VCC))
-- \div|Add3~5\ = CARRY((\div|data_min\(2) & !\div|Add3~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(2),
	datad => VCC,
	cin => \div|Add3~3\,
	combout => \div|Add3~4_combout\,
	cout => \div|Add3~5\);

-- Location: LCCOMB_X27_Y7_N6
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

-- Location: LCCOMB_X27_Y7_N8
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

-- Location: LCCOMB_X27_Y7_N10
\div|Add3~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Add3~10_combout\ = (\div|data_min\(5) & (!\div|Add3~9\)) # (!\div|data_min\(5) & ((\div|Add3~9\) # (GND)))
-- \div|Add3~11\ = CARRY((!\div|Add3~9\) # (!\div|data_min\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(5),
	datad => VCC,
	cin => \div|Add3~9\,
	combout => \div|Add3~10_combout\,
	cout => \div|Add3~11\);

-- Location: LCCOMB_X27_Y7_N12
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

-- Location: LCCOMB_X19_Y4_N28
\tmp_seg7data[0]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~3_combout\ = (\Equal9~0_combout\ & (!data_mode(0) & ((data_count_seg(1)) # (!\Equal12~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000100010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => data_mode(0),
	datac => data_count_seg(1),
	datad => \Equal12~0_combout\,
	combout => \tmp_seg7data[0]~3_combout\);

-- Location: LCFF_X18_Y8_N21
\data_h_high[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	sdata => \data_h_high[0]~7_combout\,
	aclr => \Equal17~2_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(0));

-- Location: LCCOMB_X19_Y8_N8
\tmp_seg7data[0]~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~4_combout\ = (\Equal11~0_combout\ & ((\Equal13~0_combout\ & (data_h_high(0))) # (!\Equal13~0_combout\ & ((data_h_low(0))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(0),
	datab => data_h_low(0),
	datac => \Equal13~0_combout\,
	datad => \Equal11~0_combout\,
	combout => \tmp_seg7data[0]~4_combout\);

-- Location: LCCOMB_X19_Y8_N10
\tmp_seg7data[0]~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~5_combout\ = (\tmp_seg7data[0]~3_combout\ & ((\tmp_seg7data[0]~4_combout\) # ((data_min_high(0) & !\Equal11~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100010101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~3_combout\,
	datab => \tmp_seg7data[0]~4_combout\,
	datac => data_min_high(0),
	datad => \Equal11~0_combout\,
	combout => \tmp_seg7data[0]~5_combout\);

-- Location: LCCOMB_X19_Y4_N26
\tmp_seg7data[2]~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~12_combout\ = (\Equal9~0_combout\ & (data_mode(0) & \Equal11~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => data_mode(0),
	datac => \Equal11~0_combout\,
	combout => \tmp_seg7data[2]~12_combout\);

-- Location: LCFF_X19_Y8_N21
\data_h_high[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[2]~5_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(2));

-- Location: LCFF_X19_Y8_N7
\data_h_low[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_low~1_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(3));

-- Location: LCFF_X21_Y6_N25
\COUNT1[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~48_combout\,
	aclr => \key5~combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(0));

-- Location: LCCOMB_X20_Y6_N20
\Add0~48\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~48_combout\ = (\LessThan0~0_combout\ & (((\Add0~8_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~8_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(0),
	datab => \LessThan0~0_combout\,
	datac => \LessThan0~4_combout\,
	datad => \Add0~8_combout\,
	combout => \Add0~48_combout\);

-- Location: LCCOMB_X20_Y6_N16
\Equal1~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal1~1_combout\ = (data_mode(1) & data_mode(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datad => data_mode(0),
	combout => \Equal1~1_combout\);

-- Location: LCFF_X25_Y7_N23
\div|Q_ms\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Q_ms~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_ms~regout\);

-- Location: LCFF_X27_Y7_N31
\div|Q_min\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|Q_min~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_min~regout\);

-- Location: LCCOMB_X19_Y8_N20
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

-- Location: LCCOMB_X19_Y8_N6
\data_h_low~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_low~1_combout\ = (\Add6~6_combout\ & ((!\Equal16~0_combout\) # (!data_h_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(0),
	datac => \Equal16~0_combout\,
	datad => \Add6~6_combout\,
	combout => \data_h_low~1_combout\);

-- Location: LCFF_X2_Y2_N1
\div|data_s[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(5));

-- Location: LCFF_X2_Y2_N15
\div|data_s[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(4));

-- Location: LCFF_X2_Y2_N13
\div|data_s[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(3));

-- Location: LCFF_X2_Y2_N11
\div|data_s[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(2));

-- Location: LCCOMB_X1_Y1_N4
\div|Equal2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~0_combout\ = (!\div|data_s\(3) & (\div|data_s\(5) & (!\div|data_s\(4) & !\div|data_s\(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(3),
	datab => \div|data_s\(5),
	datac => \div|data_s\(4),
	datad => \div|data_s\(2),
	combout => \div|Equal2~0_combout\);

-- Location: LCFF_X2_Y2_N3
\div|data_s[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(7));

-- Location: LCFF_X2_Y2_N9
\div|data_s[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(1));

-- Location: LCFF_X2_Y2_N5
\div|data_s[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(0));

-- Location: LCFF_X2_Y2_N19
\div|data_s[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(6));

-- Location: LCCOMB_X1_Y1_N16
\div|Equal2~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~1_combout\ = (!\div|data_s\(1) & (!\div|data_s\(6) & (\div|data_s\(7) & !\div|data_s\(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(1),
	datab => \div|data_s\(6),
	datac => \div|data_s\(7),
	datad => \div|data_s\(0),
	combout => \div|Equal2~1_combout\);

-- Location: LCFF_X1_Y1_N1
\div|data_s[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(8));

-- Location: LCFF_X1_Y1_N21
\div|data_s[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(10));

-- Location: LCFF_X2_Y2_N25
\div|data_s[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(9));

-- Location: LCFF_X2_Y2_N29
\div|data_s[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~22_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(11));

-- Location: LCCOMB_X1_Y1_N26
\div|Equal2~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~2_combout\ = (\div|data_s\(10) & (\div|data_s\(8) & (!\div|data_s\(9) & !\div|data_s\(11))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(10),
	datab => \div|data_s\(8),
	datac => \div|data_s\(9),
	datad => \div|data_s\(11),
	combout => \div|Equal2~2_combout\);

-- Location: LCFF_X1_Y1_N15
\div|data_s[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(13));

-- Location: LCFF_X2_Y2_N31
\div|data_s[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~24_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(12));

-- Location: LCFF_X2_Y1_N3
\div|data_s[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~28_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(14));

-- Location: LCFF_X2_Y1_N5
\div|data_s[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~30_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(15));

-- Location: LCCOMB_X1_Y1_N22
\div|Equal2~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~3_combout\ = (!\div|data_s\(14) & (\div|data_s\(13) & (!\div|data_s\(15) & !\div|data_s\(12))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(14),
	datab => \div|data_s\(13),
	datac => \div|data_s\(15),
	datad => \div|data_s\(12),
	combout => \div|Equal2~3_combout\);

-- Location: LCCOMB_X1_Y1_N28
\div|Equal2~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~4_combout\ = (\div|Equal2~1_combout\ & (\div|Equal2~2_combout\ & (\div|Equal2~0_combout\ & \div|Equal2~3_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~1_combout\,
	datab => \div|Equal2~2_combout\,
	datac => \div|Equal2~0_combout\,
	datad => \div|Equal2~3_combout\,
	combout => \div|Equal2~4_combout\);

-- Location: LCFF_X1_Y1_N31
\div|data_s[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(17));

-- Location: LCFF_X1_Y1_N19
\div|data_s[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~7_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(18));

-- Location: LCFF_X2_Y1_N7
\div|data_s[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~32_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(16));

-- Location: LCFF_X2_Y1_N13
\div|data_s[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~38_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(19));

-- Location: LCCOMB_X1_Y1_N8
\div|Equal2~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~5_combout\ = (!\div|data_s\(16) & (\div|data_s\(17) & (!\div|data_s\(19) & \div|data_s\(18))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(16),
	datab => \div|data_s\(17),
	datac => \div|data_s\(19),
	datad => \div|data_s\(18),
	combout => \div|Equal2~5_combout\);

-- Location: LCFF_X1_Y1_N3
\div|data_s[21]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_s~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(21));

-- Location: LCFF_X2_Y1_N15
\div|data_s[20]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~40_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(20));

-- Location: LCFF_X2_Y1_N19
\div|data_s[22]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~44_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(22));

-- Location: LCFF_X2_Y1_N21
\div|data_s[23]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~46_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(23));

-- Location: LCCOMB_X2_Y1_N28
\div|Equal2~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~6_combout\ = (\div|data_s\(21) & (!\div|data_s\(20) & (!\div|data_s\(23) & !\div|data_s\(22))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_s\(21),
	datab => \div|data_s\(20),
	datac => \div|data_s\(23),
	datad => \div|data_s\(22),
	combout => \div|Equal2~6_combout\);

-- Location: LCFF_X2_Y1_N23
\div|data_s[24]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~48_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(24));

-- Location: LCFF_X2_Y1_N25
\div|data_s[25]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~50_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(25));

-- Location: LCFF_X2_Y1_N27
\div|data_s[26]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add2~52_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_s\(26));

-- Location: LCCOMB_X2_Y1_N30
\div|Equal2~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~7_combout\ = (!\div|data_s\(26) & (!\div|data_s\(25) & !\div|data_s\(24)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_s\(26),
	datac => \div|data_s\(25),
	datad => \div|data_s\(24),
	combout => \div|Equal2~7_combout\);

-- Location: LCCOMB_X1_Y1_N24
\div|Equal2~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal2~8_combout\ = (\div|Equal2~7_combout\ & (\div|Equal2~6_combout\ & (\div|Equal2~5_combout\ & \div|Equal2~4_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~7_combout\,
	datab => \div|Equal2~6_combout\,
	datac => \div|Equal2~5_combout\,
	datad => \div|Equal2~4_combout\,
	combout => \div|Equal2~8_combout\);

-- Location: LCFF_X24_Y7_N13
\div|data_ms[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~32_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(16));

-- Location: LCFF_X24_Y7_N15
\div|data_ms[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~34_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(17));

-- Location: LCFF_X24_Y7_N17
\div|data_ms[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~36_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(18));

-- Location: LCFF_X24_Y7_N19
\div|data_ms[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~38_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(19));

-- Location: LCCOMB_X24_Y7_N24
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

-- Location: LCFF_X24_Y8_N9
\div|data_ms[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(0));

-- Location: LCFF_X24_Y8_N15
\div|data_ms[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(1));

-- Location: LCCOMB_X25_Y7_N8
\div|Equal0~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~1_combout\ = (!\div|data_ms\(1) & !\div|data_ms\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|data_ms\(1),
	datad => \div|data_ms\(0),
	combout => \div|Equal0~1_combout\);

-- Location: LCFF_X24_Y8_N3
\div|data_ms[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(3));

-- Location: LCFF_X24_Y8_N1
\div|data_ms[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(5));

-- Location: LCFF_X24_Y8_N7
\div|data_ms[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(7));

-- Location: LCFF_X24_Y8_N21
\div|data_ms[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~8_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(4));

-- Location: LCFF_X24_Y8_N25
\div|data_ms[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(6));

-- Location: LCCOMB_X24_Y8_N4
\div|Equal0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~2_combout\ = (!\div|data_ms\(6) & (\div|data_ms\(5) & (!\div|data_ms\(4) & \div|data_ms\(7))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(6),
	datab => \div|data_ms\(5),
	datac => \div|data_ms\(4),
	datad => \div|data_ms\(7),
	combout => \div|Equal0~2_combout\);

-- Location: LCFF_X24_Y8_N17
\div|data_ms[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(2));

-- Location: LCCOMB_X25_Y7_N18
\div|Equal0~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~3_combout\ = (!\div|data_ms\(2) & (\div|data_ms\(3) & (\div|Equal0~1_combout\ & \div|Equal0~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(2),
	datab => \div|data_ms\(3),
	datac => \div|Equal0~1_combout\,
	datad => \div|Equal0~2_combout\,
	combout => \div|Equal0~3_combout\);

-- Location: LCFF_X24_Y8_N11
\div|data_ms[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(8));

-- Location: LCFF_X24_Y8_N31
\div|data_ms[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(9));

-- Location: LCFF_X24_Y7_N1
\div|data_ms[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(10));

-- Location: LCFF_X24_Y7_N3
\div|data_ms[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~22_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(11));

-- Location: LCCOMB_X25_Y7_N24
\div|Equal0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~4_combout\ = (!\div|data_ms\(11) & (!\div|data_ms\(10) & (!\div|data_ms\(9) & \div|data_ms\(8))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(11),
	datab => \div|data_ms\(10),
	datac => \div|data_ms\(9),
	datad => \div|data_ms\(8),
	combout => \div|Equal0~4_combout\);

-- Location: LCFF_X25_Y7_N31
\div|data_ms[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(13));

-- Location: LCFF_X25_Y7_N27
\div|data_ms[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|data_ms~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(14));

-- Location: LCFF_X24_Y7_N5
\div|data_ms[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~24_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(12));

-- Location: LCFF_X24_Y7_N11
\div|data_ms[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Add0~30_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_ms\(15));

-- Location: LCCOMB_X25_Y7_N20
\div|Equal0~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~5_combout\ = (!\div|data_ms\(15) & (\div|data_ms\(14) & (!\div|data_ms\(12) & \div|data_ms\(13))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_ms\(15),
	datab => \div|data_ms\(14),
	datac => \div|data_ms\(12),
	datad => \div|data_ms\(13),
	combout => \div|Equal0~5_combout\);

-- Location: LCCOMB_X25_Y7_N4
\div|Equal0~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal0~6_combout\ = (\div|Equal0~5_combout\ & (\div|Equal0~0_combout\ & (\div|Equal0~4_combout\ & \div|Equal0~3_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal0~5_combout\,
	datab => \div|Equal0~0_combout\,
	datac => \div|Equal0~4_combout\,
	datad => \div|Equal0~3_combout\,
	combout => \div|Equal0~6_combout\);

-- Location: LCCOMB_X25_Y7_N22
\div|Q_ms~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_ms~0_combout\ = \div|Equal0~6_combout\ $ (\div|Q_ms~regout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal0~6_combout\,
	datac => \div|Q_ms~regout\,
	combout => \div|Q_ms~0_combout\);

-- Location: LCFF_X27_Y7_N27
\div|data_min[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|data_min~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(4));

-- Location: LCFF_X27_Y7_N29
\div|data_min[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|data_min~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(3));

-- Location: LCFF_X27_Y7_N13
\div|data_min[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|Add3~12_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(6));

-- Location: LCFF_X27_Y7_N11
\div|data_min[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|Add3~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(5));

-- Location: LCCOMB_X27_Y7_N16
\div|Equal3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal3~0_combout\ = (!\div|data_min\(5) & (\div|data_min\(4) & (\div|data_min\(3) & !\div|data_min\(6))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|data_min\(5),
	datab => \div|data_min\(4),
	datac => \div|data_min\(3),
	datad => \div|data_min\(6),
	combout => \div|Equal3~0_combout\);

-- Location: LCFF_X27_Y7_N23
\div|data_min[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|data_min~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(2));

-- Location: LCFF_X27_Y7_N25
\div|data_min[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|data_min~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(1));

-- Location: LCFF_X27_Y7_N19
\div|data_min[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \div|data_min~4_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|data_min\(0));

-- Location: LCCOMB_X27_Y7_N20
\div|Equal3~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Equal3~1_combout\ = (!\div|data_min\(0) & (\div|data_min\(1) & \div|data_min\(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|data_min\(0),
	datac => \div|data_min\(1),
	datad => \div|data_min\(2),
	combout => \div|Equal3~1_combout\);

-- Location: LCCOMB_X27_Y7_N30
\div|Q_min~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|Q_min~0_combout\ = \div|Q_min~regout\ $ (((\div|Equal3~0_combout\ & \div|Equal3~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal3~0_combout\,
	datac => \div|Q_min~regout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|Q_min~0_combout\);

-- Location: LCCOMB_X2_Y2_N0
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

-- Location: LCCOMB_X2_Y2_N2
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

-- Location: LCCOMB_X2_Y2_N4
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

-- Location: LCCOMB_X1_Y1_N0
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

-- Location: LCCOMB_X1_Y1_N20
\div|data_s~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~4_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~20_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal2~8_combout\,
	datad => \div|Add2~20_combout\,
	combout => \div|data_s~4_combout\);

-- Location: LCCOMB_X1_Y1_N14
\div|data_s~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~5_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~26_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~8_combout\,
	datac => \div|Add2~26_combout\,
	combout => \div|data_s~5_combout\);

-- Location: LCCOMB_X1_Y1_N30
\div|data_s~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~6_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~34_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~8_combout\,
	datac => \div|Add2~34_combout\,
	combout => \div|data_s~6_combout\);

-- Location: LCCOMB_X1_Y1_N18
\div|data_s~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~7_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~36_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~8_combout\,
	datac => \div|Add2~36_combout\,
	combout => \div|data_s~7_combout\);

-- Location: LCCOMB_X1_Y1_N2
\div|data_s~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_s~8_combout\ = (!\div|Equal2~8_combout\ & \div|Add2~42_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal2~8_combout\,
	datac => \div|Add2~42_combout\,
	combout => \div|data_s~8_combout\);

-- Location: LCCOMB_X24_Y8_N8
\div|data_ms~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~0_combout\ = (\div|Add0~0_combout\ & !\div|Equal0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Add0~0_combout\,
	datad => \div|Equal0~6_combout\,
	combout => \div|data_ms~0_combout\);

-- Location: LCCOMB_X24_Y8_N2
\div|data_ms~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~1_combout\ = (\div|Add0~6_combout\ & !\div|Equal0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Add0~6_combout\,
	datad => \div|Equal0~6_combout\,
	combout => \div|data_ms~1_combout\);

-- Location: LCCOMB_X24_Y8_N0
\div|data_ms~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~2_combout\ = (\div|Add0~10_combout\ & !\div|Equal0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Add0~10_combout\,
	datad => \div|Equal0~6_combout\,
	combout => \div|data_ms~2_combout\);

-- Location: LCCOMB_X24_Y8_N6
\div|data_ms~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~3_combout\ = (\div|Add0~14_combout\ & !\div|Equal0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Add0~14_combout\,
	datad => \div|Equal0~6_combout\,
	combout => \div|data_ms~3_combout\);

-- Location: LCCOMB_X24_Y8_N10
\div|data_ms~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~4_combout\ = (\div|Add0~16_combout\ & !\div|Equal0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Add0~16_combout\,
	datad => \div|Equal0~6_combout\,
	combout => \div|data_ms~4_combout\);

-- Location: LCCOMB_X25_Y7_N30
\div|data_ms~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~5_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~26_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000000110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \div|Equal0~6_combout\,
	datac => \div|Add0~26_combout\,
	combout => \div|data_ms~5_combout\);

-- Location: LCCOMB_X25_Y7_N26
\div|data_ms~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_ms~6_combout\ = (!\div|Equal0~6_combout\ & \div|Add0~28_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \div|Equal0~6_combout\,
	datad => \div|Add0~28_combout\,
	combout => \div|data_ms~6_combout\);

-- Location: LCCOMB_X27_Y7_N26
\div|data_min~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~0_combout\ = (\div|Add3~8_combout\ & ((!\div|Equal3~1_combout\) # (!\div|Equal3~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal3~0_combout\,
	datac => \div|Add3~8_combout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|data_min~0_combout\);

-- Location: LCCOMB_X27_Y7_N28
\div|data_min~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~1_combout\ = (\div|Add3~6_combout\ & ((!\div|Equal3~0_combout\) # (!\div|Equal3~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal3~1_combout\,
	datac => \div|Equal3~0_combout\,
	datad => \div|Add3~6_combout\,
	combout => \div|data_min~1_combout\);

-- Location: LCCOMB_X27_Y7_N22
\div|data_min~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~2_combout\ = (\div|Add3~4_combout\ & ((!\div|Equal3~1_combout\) # (!\div|Equal3~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal3~0_combout\,
	datac => \div|Add3~4_combout\,
	datad => \div|Equal3~1_combout\,
	combout => \div|data_min~2_combout\);

-- Location: LCCOMB_X27_Y7_N24
\div|data_min~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~3_combout\ = (\div|Add3~2_combout\ & ((!\div|Equal3~0_combout\) # (!\div|Equal3~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal3~1_combout\,
	datac => \div|Equal3~0_combout\,
	datad => \div|Add3~2_combout\,
	combout => \div|data_min~3_combout\);

-- Location: LCCOMB_X27_Y7_N18
\div|data_min~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \div|data_min~4_combout\ = (\div|Add3~0_combout\ & ((!\div|Equal3~0_combout\) # (!\div|Equal3~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \div|Equal3~1_combout\,
	datac => \div|Equal3~0_combout\,
	datad => \div|Add3~0_combout\,
	combout => \div|data_min~4_combout\);

-- Location: LCCOMB_X17_Y8_N30
\data_h_high[0]~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[0]~7_combout\ = data_h_high(0) $ (((data_h_low(0) & (\Equal16~0_combout\ & \data_h_high[0]~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110101010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(0),
	datab => data_h_low(0),
	datac => \Equal16~0_combout\,
	datad => \data_h_high[0]~2_combout\,
	combout => \data_h_high[0]~7_combout\);

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

-- Location: CLKCTRL_G4
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

-- Location: LCCOMB_X15_Y8_N10
\data_time_count[0]~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[0]~10_combout\ = data_time_count(0) $ (VCC)
-- \data_time_count[0]~11\ = CARRY(data_time_count(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(0),
	datad => VCC,
	combout => \data_time_count[0]~10_combout\,
	cout => \data_time_count[0]~11\);

-- Location: LCCOMB_X15_Y8_N12
\data_time_count[1]~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[1]~12_combout\ = (data_time_count(1) & (!\data_time_count[0]~11\)) # (!data_time_count(1) & ((\data_time_count[0]~11\) # (GND)))
-- \data_time_count[1]~13\ = CARRY((!\data_time_count[0]~11\) # (!data_time_count(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(1),
	datad => VCC,
	cin => \data_time_count[0]~11\,
	combout => \data_time_count[1]~12_combout\,
	cout => \data_time_count[1]~13\);

-- Location: LCCOMB_X15_Y8_N14
\data_time_count[2]~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[2]~14_combout\ = (data_time_count(2) & (\data_time_count[1]~13\ $ (GND))) # (!data_time_count(2) & (!\data_time_count[1]~13\ & VCC))
-- \data_time_count[2]~15\ = CARRY((data_time_count(2) & !\data_time_count[1]~13\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(2),
	datad => VCC,
	cin => \data_time_count[1]~13\,
	combout => \data_time_count[2]~14_combout\,
	cout => \data_time_count[2]~15\);

-- Location: LCCOMB_X15_Y8_N16
\data_time_count[3]~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[3]~16_combout\ = (data_time_count(3) & (!\data_time_count[2]~15\)) # (!data_time_count(3) & ((\data_time_count[2]~15\) # (GND)))
-- \data_time_count[3]~17\ = CARRY((!\data_time_count[2]~15\) # (!data_time_count(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(3),
	datad => VCC,
	cin => \data_time_count[2]~15\,
	combout => \data_time_count[3]~16_combout\,
	cout => \data_time_count[3]~17\);

-- Location: PIN_26,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\key6~I\ : cycloneii_io
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
	padio => ww_key6,
	combout => \key6~combout\);

-- Location: LCCOMB_X18_Y8_N22
\Add6~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add6~0_combout\ = data_h_low(0) $ (VCC)
-- \Add6~1\ = CARRY(data_h_low(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(0),
	datad => VCC,
	combout => \Add6~0_combout\,
	cout => \Add6~1\);

-- Location: LCCOMB_X18_Y8_N0
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

-- Location: LCCOMB_X17_Y8_N18
\Add4~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add4~0_combout\ = data_min_low(0) $ (VCC)
-- \Add4~1\ = CARRY(data_min_low(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(0),
	datad => VCC,
	combout => \Add4~0_combout\,
	cout => \Add4~1\);

-- Location: LCFF_X17_Y8_N19
\data_min_low[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add4~0_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(0));

-- Location: LCCOMB_X17_Y8_N20
\Add4~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add4~2_combout\ = (data_min_low(1) & (!\Add4~1\)) # (!data_min_low(1) & ((\Add4~1\) # (GND)))
-- \Add4~3\ = CARRY((!\Add4~1\) # (!data_min_low(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(1),
	datad => VCC,
	cin => \Add4~1\,
	combout => \Add4~2_combout\,
	cout => \Add4~3\);

-- Location: LCCOMB_X17_Y8_N22
\Add4~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add4~4_combout\ = (data_min_low(2) & (\Add4~3\ $ (GND))) # (!data_min_low(2) & (!\Add4~3\ & VCC))
-- \Add4~5\ = CARRY((data_min_low(2) & !\Add4~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(2),
	datad => VCC,
	cin => \Add4~3\,
	combout => \Add4~4_combout\,
	cout => \Add4~5\);

-- Location: LCFF_X17_Y8_N23
\data_min_low[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add4~4_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(2));

-- Location: LCCOMB_X17_Y8_N24
\Add4~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add4~6_combout\ = (data_min_low(3) & (!\Add4~5\)) # (!data_min_low(3) & ((\Add4~5\) # (GND)))
-- \Add4~7\ = CARRY((!\Add4~5\) # (!data_min_low(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(3),
	datad => VCC,
	cin => \Add4~5\,
	combout => \Add4~6_combout\,
	cout => \Add4~7\);

-- Location: LCCOMB_X17_Y8_N4
\data_min_low~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_low~1_combout\ = (\Add4~6_combout\ & ((!\Equal14~0_combout\) # (!data_min_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(0),
	datac => \Add4~6_combout\,
	datad => \Equal14~0_combout\,
	combout => \data_min_low~1_combout\);

-- Location: LCFF_X17_Y8_N5
\data_min_low[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_low~1_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(3));

-- Location: LCCOMB_X17_Y8_N16
\data_min_low~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_low~0_combout\ = (\Add4~2_combout\ & ((!\Equal14~0_combout\) # (!data_min_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(0),
	datac => \Add4~2_combout\,
	datad => \Equal14~0_combout\,
	combout => \data_min_low~0_combout\);

-- Location: LCFF_X17_Y8_N17
\data_min_low[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_low~0_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(1));

-- Location: LCCOMB_X17_Y8_N26
\Add4~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add4~8_combout\ = \Add4~7\ $ (!data_min_low(4))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => data_min_low(4),
	cin => \Add4~7\,
	combout => \Add4~8_combout\);

-- Location: LCFF_X17_Y8_N27
\data_min_low[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add4~8_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_low(4));

-- Location: LCCOMB_X17_Y8_N14
\Equal14~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal14~0_combout\ = (!data_min_low(2) & (data_min_low(3) & (!data_min_low(1) & !data_min_low(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(2),
	datab => data_min_low(3),
	datac => data_min_low(1),
	datad => data_min_low(4),
	combout => \Equal14~0_combout\);

-- Location: LCCOMB_X17_Y8_N8
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

-- Location: LCCOMB_X17_Y8_N12
\Equal14~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal14~1_combout\ = (data_min_low(0) & \Equal14~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(0),
	datac => \Equal14~0_combout\,
	combout => \Equal14~1_combout\);

-- Location: LCFF_X17_Y8_N9
\data_min_high[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high[0]~4_combout\,
	aclr => \Equal17~2_combout\,
	ena => \Equal14~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(0));

-- Location: LCCOMB_X17_Y8_N28
\data_min_high[3]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high[3]~2_combout\ = (data_min_high(1) & (data_min_high(2) & data_min_high(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(1),
	datab => data_min_high(2),
	datad => data_min_high(0),
	combout => \data_min_high[3]~2_combout\);

-- Location: LCCOMB_X18_Y8_N18
\data_min_high[3]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high[3]~3_combout\ = data_min_high(3) $ (((\Equal14~0_combout\ & (\data_min_high[3]~2_combout\ & data_min_low(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal14~0_combout\,
	datab => \data_min_high[3]~2_combout\,
	datac => data_min_high(3),
	datad => data_min_low(0),
	combout => \data_min_high[3]~3_combout\);

-- Location: LCFF_X18_Y8_N19
\data_min_high[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high[3]~3_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(3));

-- Location: LCCOMB_X17_Y8_N10
\data_min_high~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high~0_combout\ = (data_min_high(1) & (((!data_min_high(0))))) # (!data_min_high(1) & (data_min_high(0) & ((data_min_high(3)) # (!data_min_high(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(2),
	datab => data_min_high(3),
	datac => data_min_high(1),
	datad => data_min_high(0),
	combout => \data_min_high~0_combout\);

-- Location: LCFF_X17_Y8_N11
\data_min_high[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high~0_combout\,
	aclr => \Equal17~2_combout\,
	ena => \Equal14~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(1));

-- Location: LCCOMB_X17_Y8_N2
\data_min_high~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_min_high~1_combout\ = (data_min_high(1) & ((data_min_high(2) $ (data_min_high(0))))) # (!data_min_high(1) & (data_min_high(2) & ((data_min_high(3)) # (!data_min_high(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(3),
	datab => data_min_high(1),
	datac => data_min_high(2),
	datad => data_min_high(0),
	combout => \data_min_high~1_combout\);

-- Location: LCFF_X17_Y8_N3
\data_min_high[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_min_high~1_combout\,
	aclr => \Equal17~2_combout\,
	ena => \Equal14~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_min_high(2));

-- Location: LCCOMB_X17_Y8_N0
\Equal15~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal15~0_combout\ = (!data_min_high(1) & (data_min_high(2) & (data_min_high(0) & !data_min_high(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_high(1),
	datab => data_min_high(2),
	datac => data_min_high(0),
	datad => data_min_high(3),
	combout => \Equal15~0_combout\);

-- Location: LCCOMB_X17_Y8_N6
\data_h_high[0]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[0]~2_combout\ = (data_min_low(0) & (\Equal14~0_combout\ & \Equal15~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min_low(0),
	datac => \Equal14~0_combout\,
	datad => \Equal15~0_combout\,
	combout => \data_h_high[0]~2_combout\);

-- Location: LCFF_X18_Y8_N1
\data_h[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[1]~6_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(1));

-- Location: LCCOMB_X18_Y8_N4
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

-- Location: LCFF_X18_Y8_N5
\data_h[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[3]~10_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(3));

-- Location: LCCOMB_X18_Y8_N6
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

-- Location: LCFF_X18_Y8_N7
\data_h[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[4]~12_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(4));

-- Location: LCCOMB_X18_Y8_N14
\Equal17~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal17~1_combout\ = (!data_h(6) & (data_h(3) & (!data_h(5) & data_h(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h(6),
	datab => data_h(3),
	datac => data_h(5),
	datad => data_h(4),
	combout => \Equal17~1_combout\);

-- Location: LCCOMB_X18_Y8_N16
\Equal17~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal17~2_combout\ = (!data_h_low(0) & (!data_h(1) & (\Equal17~1_combout\ & !data_h(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(0),
	datab => data_h(1),
	datac => \Equal17~1_combout\,
	datad => data_h(2),
	combout => \Equal17~2_combout\);

-- Location: LCFF_X18_Y8_N23
\data_h_low[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add6~0_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(0));

-- Location: LCCOMB_X18_Y8_N2
\data_h[2]~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[2]~8_combout\ = (data_h(2) & (!\data_h[1]~7\)) # (!data_h(2) & ((\data_h[1]~7\) # (GND)))
-- \data_h[2]~9\ = CARRY((!\data_h[1]~7\) # (!data_h(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_h(2),
	datad => VCC,
	cin => \data_h[1]~7\,
	combout => \data_h[2]~8_combout\,
	cout => \data_h[2]~9\);

-- Location: LCFF_X18_Y8_N3
\data_h[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[2]~8_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(2));

-- Location: LCCOMB_X18_Y8_N8
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

-- Location: LCFF_X18_Y8_N9
\data_h[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[5]~14_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(5));

-- Location: LCCOMB_X18_Y8_N12
\night~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \night~2_combout\ = (data_h(4) & ((data_h(3)) # ((data_h(2) & data_h(1))))) # (!data_h(4) & (((!data_h(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010110110100101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h(4),
	datab => data_h(2),
	datac => data_h(3),
	datad => data_h(1),
	combout => \night~2_combout\);

-- Location: LCCOMB_X14_Y8_N14
\night~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \night~3_combout\ = (data_h(6)) # ((data_h(5)) # (\night~2_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h(6),
	datac => data_h(5),
	datad => \night~2_combout\,
	combout => \night~3_combout\);

-- Location: LCCOMB_X15_Y8_N6
\key_flag~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \key_flag~0_combout\ = (\key_flag~regout\) # ((\Equal7~1_combout\ & \night~3_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal7~1_combout\,
	datac => \key_flag~regout\,
	datad => \night~3_combout\,
	combout => \key_flag~0_combout\);

-- Location: LCFF_X15_Y8_N7
key_flag : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \key_flag~0_combout\,
	aclr => \ALT_INV_key6~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \key_flag~regout\);

-- Location: LCCOMB_X15_Y8_N4
\process_2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \process_2~0_combout\ = (!\key6~combout\ & \key_flag~regout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \key6~combout\,
	datad => \key_flag~regout\,
	combout => \process_2~0_combout\);

-- Location: LCFF_X15_Y8_N11
\data_time_count[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[0]~10_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(0));

-- Location: LCFF_X15_Y8_N15
\data_time_count[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[2]~14_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(2));

-- Location: LCCOMB_X15_Y8_N30
\Equal7~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal7~0_combout\ = (!data_time_count(1) & (!data_time_count(2) & (!data_time_count(3) & data_time_count(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(1),
	datab => data_time_count(2),
	datac => data_time_count(3),
	datad => data_time_count(5),
	combout => \Equal7~0_combout\);

-- Location: LCCOMB_X14_Y8_N30
\Equal7~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal7~1_combout\ = (data_time_count(4) & (!data_time_count(0) & (\Equal5~0_combout\ & \Equal7~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(4),
	datab => data_time_count(0),
	datac => \Equal5~0_combout\,
	datad => \Equal7~0_combout\,
	combout => \Equal7~1_combout\);

-- Location: LCCOMB_X15_Y8_N2
\data_time_count~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count~20_combout\ = (!\led_c~2_combout\ & (((!\key_flag~regout\ & \Equal7~1_combout\)) # (!\night~3_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001000000110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key_flag~regout\,
	datab => \led_c~2_combout\,
	datac => \Equal7~1_combout\,
	datad => \night~3_combout\,
	combout => \data_time_count~20_combout\);

-- Location: LCFF_X15_Y8_N17
\data_time_count[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[3]~16_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(3));

-- Location: LCCOMB_X15_Y8_N18
\data_time_count[4]~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[4]~18_combout\ = (data_time_count(4) & (\data_time_count[3]~17\ $ (GND))) # (!data_time_count(4) & (!\data_time_count[3]~17\ & VCC))
-- \data_time_count[4]~19\ = CARRY((data_time_count(4) & !\data_time_count[3]~17\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(4),
	datad => VCC,
	cin => \data_time_count[3]~17\,
	combout => \data_time_count[4]~18_combout\,
	cout => \data_time_count[4]~19\);

-- Location: LCCOMB_X15_Y8_N20
\data_time_count[5]~21\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[5]~21_combout\ = (data_time_count(5) & (!\data_time_count[4]~19\)) # (!data_time_count(5) & ((\data_time_count[4]~19\) # (GND)))
-- \data_time_count[5]~22\ = CARRY((!\data_time_count[4]~19\) # (!data_time_count(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(5),
	datad => VCC,
	cin => \data_time_count[4]~19\,
	combout => \data_time_count[5]~21_combout\,
	cout => \data_time_count[5]~22\);

-- Location: LCFF_X15_Y8_N21
\data_time_count[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[5]~21_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(5));

-- Location: LCCOMB_X15_Y8_N22
\data_time_count[6]~23\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[6]~23_combout\ = (data_time_count(6) & (\data_time_count[5]~22\ $ (GND))) # (!data_time_count(6) & (!\data_time_count[5]~22\ & VCC))
-- \data_time_count[6]~24\ = CARRY((data_time_count(6) & !\data_time_count[5]~22\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(6),
	datad => VCC,
	cin => \data_time_count[5]~22\,
	combout => \data_time_count[6]~23_combout\,
	cout => \data_time_count[6]~24\);

-- Location: LCFF_X15_Y8_N23
\data_time_count[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[6]~23_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(6));

-- Location: LCCOMB_X15_Y8_N24
\data_time_count[7]~25\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_time_count[7]~25_combout\ = (data_time_count(7) & (!\data_time_count[6]~24\)) # (!data_time_count(7) & ((\data_time_count[6]~24\) # (GND)))
-- \data_time_count[7]~26\ = CARRY((!\data_time_count[6]~24\) # (!data_time_count(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_time_count(7),
	datad => VCC,
	cin => \data_time_count[6]~24\,
	combout => \data_time_count[7]~25_combout\,
	cout => \data_time_count[7]~26\);

-- Location: LCFF_X15_Y8_N25
\data_time_count[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[7]~25_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(7));

-- Location: LCFF_X15_Y8_N27
\data_time_count[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[8]~27_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(8));

-- Location: LCCOMB_X15_Y8_N8
\Equal5~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal5~0_combout\ = (!data_time_count(9) & (!data_time_count(6) & (!data_time_count(7) & !data_time_count(8))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(9),
	datab => data_time_count(6),
	datac => data_time_count(7),
	datad => data_time_count(8),
	combout => \Equal5~0_combout\);

-- Location: LCCOMB_X18_Y8_N10
\data_h[6]~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h[6]~16_combout\ = data_h(6) $ (\data_h[5]~15\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_h(6),
	cin => \data_h[5]~15\,
	combout => \data_h[6]~16_combout\);

-- Location: LCFF_X18_Y8_N11
\data_h[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h[6]~16_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h(6));

-- Location: LCCOMB_X18_Y8_N20
\Equal17~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal17~0_combout\ = (!data_h(5) & !data_h(6))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_h(5),
	datad => data_h(6),
	combout => \Equal17~0_combout\);

-- Location: LCCOMB_X14_Y8_N18
\led_c~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~2_combout\ = (\LessThan1~0_combout\ & (\Equal5~0_combout\ & (\Equal17~0_combout\ & !\night~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan1~0_combout\,
	datab => \Equal5~0_combout\,
	datac => \Equal17~0_combout\,
	datad => \night~2_combout\,
	combout => \led_c~2_combout\);

-- Location: LCCOMB_X14_Y8_N24
\led_p~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_p~5_combout\ = (!\key_flag~regout\ & ((\night~2_combout\) # ((data_h(5)) # (data_h(6)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100110010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \night~2_combout\,
	datab => \key_flag~regout\,
	datac => data_h(5),
	datad => data_h(6),
	combout => \led_p~5_combout\);

-- Location: LCCOMB_X14_Y8_N26
\Equal6~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal6~0_combout\ = (data_time_count(4)) # (((!\Equal7~0_combout\) # (!\Equal5~0_combout\)) # (!data_time_count(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(4),
	datab => data_time_count(0),
	datac => \Equal5~0_combout\,
	datad => \Equal7~0_combout\,
	combout => \Equal6~0_combout\);

-- Location: LCFF_X15_Y8_N13
\data_time_count[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[1]~12_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(1));

-- Location: LCFF_X15_Y8_N19
\data_time_count[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \data_time_count[4]~18_combout\,
	aclr => \process_2~0_combout\,
	sclr => \data_time_count~20_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_time_count(4));

-- Location: LCCOMB_X14_Y8_N12
\Equal5~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal5~1_combout\ = (!data_time_count(5) & (data_time_count(1) & (!data_time_count(0) & data_time_count(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(5),
	datab => data_time_count(1),
	datac => data_time_count(0),
	datad => data_time_count(4),
	combout => \Equal5~1_combout\);

-- Location: LCCOMB_X14_Y8_N2
\Equal5~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal5~2_combout\ = (data_time_count(3) & (data_time_count(2) & (\Equal5~0_combout\ & \Equal5~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_time_count(3),
	datab => data_time_count(2),
	datac => \Equal5~0_combout\,
	datad => \Equal5~1_combout\,
	combout => \Equal5~2_combout\);

-- Location: LCCOMB_X14_Y8_N28
\led_c~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~4_combout\ = (\Equal6~0_combout\ & ((\Equal5~2_combout\ & ((!\night~3_combout\))) # (!\Equal5~2_combout\ & (!led_c(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110001000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => led_c(0),
	datab => \Equal6~0_combout\,
	datac => \night~3_combout\,
	datad => \Equal5~2_combout\,
	combout => \led_c~4_combout\);

-- Location: LCCOMB_X14_Y8_N22
\led_c~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~5_combout\ = (!\led_c~4_combout\ & ((\led_c~2_combout\) # ((!\Equal7~1_combout\ & \led_p~5_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011011100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal7~1_combout\,
	datab => \led_c~2_combout\,
	datac => \led_p~5_combout\,
	datad => \led_c~4_combout\,
	combout => \led_c~5_combout\);

-- Location: LCFF_X14_Y8_N23
\led_c[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \led_c~5_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => led_c(0));

-- Location: LCCOMB_X15_Y8_N0
\LessThan1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan1~0_combout\ = (!data_time_count(4)) # (!data_time_count(5))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_time_count(5),
	datad => data_time_count(4),
	combout => \LessThan1~0_combout\);

-- Location: LCCOMB_X14_Y8_N20
\led_c~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~0_combout\ = ((\night~2_combout\) # ((\Equal5~0_combout\ & \LessThan1~0_combout\))) # (!\Equal17~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111010101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal17~0_combout\,
	datab => \Equal5~0_combout\,
	datac => \LessThan1~0_combout\,
	datad => \night~2_combout\,
	combout => \led_c~0_combout\);

-- Location: LCCOMB_X14_Y8_N4
\led_c~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~1_combout\ = (!\key_flag~regout\ & (\led_c~0_combout\ & !\Equal7~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key_flag~regout\,
	datac => \led_c~0_combout\,
	datad => \Equal7~1_combout\,
	combout => \led_c~1_combout\);

-- Location: LCCOMB_X14_Y8_N8
\led_c~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_c~3_combout\ = (\Equal6~0_combout\ & ((\led_c~1_combout\) # ((\Equal5~2_combout\ & \led_c~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010100010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal6~0_combout\,
	datab => \Equal5~2_combout\,
	datac => \led_c~1_combout\,
	datad => \led_c~2_combout\,
	combout => \led_c~3_combout\);

-- Location: LCCOMB_X14_Y8_N0
\led_p[1]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_p[1]~2_combout\ = (\night~3_combout\ & (!\Equal7~1_combout\ & ((\led_c~2_combout\) # (!\key_flag~regout\)))) # (!\night~3_combout\ & (((\led_c~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key_flag~regout\,
	datab => \Equal7~1_combout\,
	datac => \night~3_combout\,
	datad => \led_c~2_combout\,
	combout => \led_p[1]~2_combout\);

-- Location: LCCOMB_X14_Y8_N6
\led_p[1]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_p[1]~3_combout\ = ((\Equal5~2_combout\) # (!\led_p[1]~2_combout\)) # (!\Equal6~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111001111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal6~0_combout\,
	datac => \Equal5~2_combout\,
	datad => \led_p[1]~2_combout\,
	combout => \led_p[1]~3_combout\);

-- Location: LCFF_X14_Y8_N9
\led_c[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \led_c~3_combout\,
	ena => \led_p[1]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => led_c(1));

-- Location: LCCOMB_X1_Y5_N20
\Equal2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal2~0_combout\ = (led_c(1)) # (!led_c(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111001111110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => led_c(0),
	datac => led_c(1),
	combout => \Equal2~0_combout\);

-- Location: LCCOMB_X1_Y5_N6
\Equal3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal3~0_combout\ = (!led_c(0) & !led_c(1))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001100000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => led_c(0),
	datac => led_c(1),
	combout => \Equal3~0_combout\);

-- Location: LCCOMB_X1_Y1_N12
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

-- Location: LCFF_X1_Y1_N13
\div|Q_s\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \div|Q_s~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => \div|Q_s~regout\);

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

-- Location: LCCOMB_X14_Y8_N16
\led_p~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \led_p~4_combout\ = (!\Equal6~0_combout\ & ((\led_p~5_combout\) # (\led_c~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal6~0_combout\,
	datac => \led_p~5_combout\,
	datad => \led_c~2_combout\,
	combout => \led_p~4_combout\);

-- Location: LCFF_X14_Y8_N17
\led_p[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_s~clkctrl_outclk\,
	datain => \led_p~4_combout\,
	ena => \led_p[1]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => led_p(0));

-- Location: LCCOMB_X20_Y4_N12
\data_count_seg[1]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg[1]~3_combout\ = data_count_seg(1) $ (data_count_seg(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => data_count_seg(1),
	datad => data_count_seg(0),
	combout => \data_count_seg[1]~3_combout\);

-- Location: LCFF_X20_Y4_N13
\data_count_seg[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg[1]~3_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(1));

-- Location: LCCOMB_X20_Y4_N28
\data_count_seg~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg~1_combout\ = (data_count_seg(0) & ((data_count_seg(2) $ (data_count_seg(1))))) # (!data_count_seg(0) & (data_count_seg(2) & ((data_count_seg(3)) # (data_count_seg(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(3),
	datab => data_count_seg(0),
	datac => data_count_seg(2),
	datad => data_count_seg(1),
	combout => \data_count_seg~1_combout\);

-- Location: LCFF_X20_Y4_N29
\data_count_seg[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(2));

-- Location: LCCOMB_X20_Y4_N30
\data_count_seg~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg~0_combout\ = (!data_count_seg(0) & ((data_count_seg(3)) # ((data_count_seg(1)) # (!data_count_seg(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(3),
	datab => data_count_seg(2),
	datac => data_count_seg(0),
	datad => data_count_seg(1),
	combout => \data_count_seg~0_combout\);

-- Location: LCFF_X20_Y4_N31
\data_count_seg[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(0));

-- Location: LCCOMB_X19_Y4_N24
\Equal12~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal12~0_combout\ = (!data_count_seg(3) & (!data_count_seg(0) & !data_count_seg(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(3),
	datab => data_count_seg(0),
	datad => data_count_seg(2),
	combout => \Equal12~0_combout\);

-- Location: LCCOMB_X21_Y5_N28
\Add0~66\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~66_combout\ = (\Add0~40_combout\) # ((!\LessThan0~4_combout\ & (COUNT1(16) & COUNT1(17))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~40_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(16),
	datad => COUNT1(17),
	combout => \Add0~66_combout\);

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
	padio => ww_key5,
	combout => \key5~combout\);

-- Location: LCFF_X21_Y5_N29
\COUNT1[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~66_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(16));

-- Location: LCCOMB_X21_Y5_N26
\Add0~67\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~67_combout\ = (\Add0~42_combout\) # ((!\LessThan0~4_combout\ & (COUNT1(17) & COUNT1(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~42_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(17),
	datad => COUNT1(16),
	combout => \Add0~67_combout\);

-- Location: LCFF_X21_Y5_N27
\COUNT1[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~67_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(17));

-- Location: LCCOMB_X21_Y5_N24
\LessThan0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~0_combout\ = (!COUNT1(16)) # (!COUNT1(17))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(17),
	datad => COUNT1(16),
	combout => \LessThan0~0_combout\);

-- Location: LCCOMB_X21_Y6_N8
\Add0~50\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~50_combout\ = (\LessThan0~0_combout\ & (\Add0~12_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~12_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(2))))))

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
	combout => \Add0~50_combout\);

-- Location: LCFF_X21_Y6_N9
\COUNT1[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~50_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(2));

-- Location: LCCOMB_X21_Y6_N14
\Add0~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~10_combout\ = (COUNT1(1) & (!\Add0~9\)) # (!COUNT1(1) & ((\Add0~9\) # (GND)))
-- \Add0~11\ = CARRY((!\Add0~9\) # (!COUNT1(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(1),
	datad => VCC,
	cin => \Add0~9\,
	combout => \Add0~10_combout\,
	cout => \Add0~11\);

-- Location: LCCOMB_X21_Y6_N18
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

-- Location: LCCOMB_X21_Y6_N2
\Add0~51\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~51_combout\ = (\LessThan0~0_combout\ & (\Add0~14_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~14_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(3))))))

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
	combout => \Add0~51_combout\);

-- Location: LCFF_X21_Y6_N3
\COUNT1[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~51_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(3));

-- Location: LCCOMB_X21_Y6_N20
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

-- Location: LCCOMB_X21_Y6_N4
\Add0~52\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~52_combout\ = (\LessThan0~0_combout\ & (\Add0~16_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~16_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(4))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~16_combout\,
	datac => COUNT1(4),
	datad => \LessThan0~4_combout\,
	combout => \Add0~52_combout\);

-- Location: LCFF_X21_Y6_N5
\COUNT1[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~52_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(4));

-- Location: LCCOMB_X21_Y6_N22
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

-- Location: LCCOMB_X20_Y6_N8
\Add0~53\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~53_combout\ = (\LessThan0~4_combout\ & (((\Add0~18_combout\)))) # (!\LessThan0~4_combout\ & ((\LessThan0~0_combout\ & ((\Add0~18_combout\))) # (!\LessThan0~0_combout\ & (COUNT1(5)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(5),
	datab => \Add0~18_combout\,
	datac => \LessThan0~4_combout\,
	datad => \LessThan0~0_combout\,
	combout => \Add0~53_combout\);

-- Location: LCFF_X20_Y6_N17
\COUNT1[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	sdata => \Add0~53_combout\,
	aclr => \key5~combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(5));

-- Location: LCCOMB_X21_Y6_N24
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

-- Location: LCCOMB_X21_Y6_N26
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

-- Location: LCCOMB_X21_Y6_N0
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

-- Location: LCFF_X21_Y6_N1
\COUNT1[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~55_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(7));

-- Location: LCCOMB_X21_Y6_N28
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

-- Location: LCCOMB_X20_Y5_N10
\Add0~57\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~57_combout\ = (\LessThan0~0_combout\ & (((\Add0~24_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~24_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(8)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(8),
	datad => \Add0~24_combout\,
	combout => \Add0~57_combout\);

-- Location: LCFF_X20_Y5_N11
\COUNT1[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~57_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(8));

-- Location: LCCOMB_X21_Y6_N30
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

-- Location: LCCOMB_X20_Y5_N2
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

-- Location: LCCOMB_X20_Y5_N8
\COUNT1[9]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \COUNT1[9]~feeder_combout\ = \Add0~56_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~56_combout\,
	combout => \COUNT1[9]~feeder_combout\);

-- Location: LCFF_X20_Y5_N9
\COUNT1[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \COUNT1[9]~feeder_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(9));

-- Location: LCCOMB_X21_Y5_N0
\Add0~28\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~28_combout\ = (COUNT1(10) & (\Add0~27\ $ (GND))) # (!COUNT1(10) & (!\Add0~27\ & VCC))
-- \Add0~29\ = CARRY((COUNT1(10) & !\Add0~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(10),
	datad => VCC,
	cin => \Add0~27\,
	combout => \Add0~28_combout\,
	cout => \Add0~29\);

-- Location: LCCOMB_X21_Y5_N2
\Add0~30\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~30_combout\ = (COUNT1(11) & (!\Add0~29\)) # (!COUNT1(11) & ((\Add0~29\) # (GND)))
-- \Add0~31\ = CARRY((!\Add0~29\) # (!COUNT1(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(11),
	datad => VCC,
	cin => \Add0~29\,
	combout => \Add0~30_combout\,
	cout => \Add0~31\);

-- Location: LCCOMB_X20_Y5_N28
\Add0~59\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~59_combout\ = (\LessThan0~0_combout\ & (((\Add0~30_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~30_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(11)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(11),
	datad => \Add0~30_combout\,
	combout => \Add0~59_combout\);

-- Location: LCFF_X20_Y5_N29
\COUNT1[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~59_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(11));

-- Location: LCCOMB_X21_Y5_N4
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

-- Location: LCCOMB_X20_Y5_N18
\Add0~61\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~61_combout\ = (\LessThan0~0_combout\ & (((\Add0~32_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~32_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(12)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(12),
	datad => \Add0~32_combout\,
	combout => \Add0~61_combout\);

-- Location: LCFF_X20_Y5_N19
\COUNT1[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~61_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(12));

-- Location: LCCOMB_X21_Y5_N6
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

-- Location: LCCOMB_X21_Y5_N8
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

-- Location: LCCOMB_X21_Y5_N10
\Add0~38\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~38_combout\ = (COUNT1(15) & (!\Add0~37\)) # (!COUNT1(15) & ((\Add0~37\) # (GND)))
-- \Add0~39\ = CARRY((!\Add0~37\) # (!COUNT1(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(15),
	datad => VCC,
	cin => \Add0~37\,
	combout => \Add0~38_combout\,
	cout => \Add0~39\);

-- Location: LCCOMB_X20_Y5_N12
\Add0~63\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~63_combout\ = (\LessThan0~0_combout\ & (((\Add0~38_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~38_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(15)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(15),
	datad => \Add0~38_combout\,
	combout => \Add0~63_combout\);

-- Location: LCFF_X20_Y5_N13
\COUNT1[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~63_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(15));

-- Location: LCCOMB_X20_Y5_N20
\Add0~62\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~62_combout\ = (\LessThan0~0_combout\ & (((\Add0~34_combout\)))) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & ((\Add0~34_combout\))) # (!\LessThan0~4_combout\ & (COUNT1(13)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => COUNT1(13),
	datad => \Add0~34_combout\,
	combout => \Add0~62_combout\);

-- Location: LCFF_X20_Y5_N21
\COUNT1[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~62_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(13));

-- Location: LCCOMB_X20_Y5_N22
\LessThan0~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~3_combout\ = (!COUNT1(12) & (!COUNT1(11) & (!COUNT1(15) & !COUNT1(13))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(12),
	datab => COUNT1(11),
	datac => COUNT1(15),
	datad => COUNT1(13),
	combout => \LessThan0~3_combout\);

-- Location: LCCOMB_X21_Y6_N6
\Add0~54\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~54_combout\ = (\LessThan0~0_combout\ & (\Add0~20_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~20_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(6))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~20_combout\,
	datac => COUNT1(6),
	datad => \LessThan0~4_combout\,
	combout => \Add0~54_combout\);

-- Location: LCFF_X21_Y6_N7
\COUNT1[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~54_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(6));

-- Location: LCCOMB_X20_Y5_N4
\LessThan0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~2_combout\ = ((!COUNT1(8) & (!COUNT1(6) & !COUNT1(7)))) # (!COUNT1(9))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010101010111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(9),
	datab => COUNT1(8),
	datac => COUNT1(6),
	datad => COUNT1(7),
	combout => \LessThan0~2_combout\);

-- Location: LCFF_X20_Y5_N1
\COUNT1[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~64_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(18));

-- Location: LCCOMB_X21_Y5_N12
\Add0~40\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~40_combout\ = (COUNT1(16) & (\Add0~39\ $ (GND))) # (!COUNT1(16) & (!\Add0~39\ & VCC))
-- \Add0~41\ = CARRY((COUNT1(16) & !\Add0~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(16),
	datad => VCC,
	cin => \Add0~39\,
	combout => \Add0~40_combout\,
	cout => \Add0~41\);

-- Location: LCCOMB_X21_Y5_N14
\Add0~42\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~42_combout\ = (COUNT1(17) & (!\Add0~41\)) # (!COUNT1(17) & ((\Add0~41\) # (GND)))
-- \Add0~43\ = CARRY((!\Add0~41\) # (!COUNT1(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => COUNT1(17),
	datad => VCC,
	cin => \Add0~41\,
	combout => \Add0~42_combout\,
	cout => \Add0~43\);

-- Location: LCCOMB_X21_Y5_N16
\Add0~44\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~44_combout\ = (COUNT1(18) & (\Add0~43\ $ (GND))) # (!COUNT1(18) & (!\Add0~43\ & VCC))
-- \Add0~45\ = CARRY((COUNT1(18) & !\Add0~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(18),
	datad => VCC,
	cin => \Add0~43\,
	combout => \Add0~44_combout\,
	cout => \Add0~45\);

-- Location: LCCOMB_X21_Y5_N18
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

-- Location: LCCOMB_X21_Y5_N30
\Add0~65\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~65_combout\ = (\Add0~46_combout\) # ((COUNT1(17) & (!\LessThan0~4_combout\ & COUNT1(16))))

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
	combout => \Add0~65_combout\);

-- Location: LCCOMB_X21_Y5_N22
\COUNT1[19]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \COUNT1[19]~feeder_combout\ = \Add0~65_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~65_combout\,
	combout => \COUNT1[19]~feeder_combout\);

-- Location: LCFF_X21_Y5_N23
\COUNT1[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \COUNT1[19]~feeder_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(19));

-- Location: LCCOMB_X20_Y5_N26
\LessThan0~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~1_combout\ = (((!COUNT1(14) & !COUNT1(15))) # (!COUNT1(19))) # (!COUNT1(18))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011011111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(14),
	datab => COUNT1(18),
	datac => COUNT1(15),
	datad => COUNT1(19),
	combout => \LessThan0~1_combout\);

-- Location: LCCOMB_X20_Y5_N24
\LessThan0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \LessThan0~4_combout\ = (\LessThan0~1_combout\) # ((!COUNT1(10) & (\LessThan0~3_combout\ & \LessThan0~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111101000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(10),
	datab => \LessThan0~3_combout\,
	datac => \LessThan0~2_combout\,
	datad => \LessThan0~1_combout\,
	combout => \LessThan0~4_combout\);

-- Location: LCCOMB_X20_Y5_N0
\Add0~64\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~64_combout\ = (\Add0~44_combout\) # ((COUNT1(17) & (!\LessThan0~4_combout\ & COUNT1(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111001011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => COUNT1(17),
	datab => \LessThan0~4_combout\,
	datac => \Add0~44_combout\,
	datad => COUNT1(16),
	combout => \Add0~64_combout\);

-- Location: LCCOMB_X21_Y5_N20
\data_mode[3]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~0_combout\ = (\LessThan0~0_combout\ & (((\Add0~42_combout\ & \Add0~40_combout\)))) # (!\LessThan0~0_combout\ & (((\Add0~42_combout\ & \Add0~40_combout\)) # (!\LessThan0~4_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000100010001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \LessThan0~4_combout\,
	datac => \Add0~42_combout\,
	datad => \Add0~40_combout\,
	combout => \data_mode[3]~0_combout\);

-- Location: LCCOMB_X20_Y6_N4
\data_mode[3]~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~8_combout\ = (!\key5~combout\ & (\Add0~64_combout\ & (\Add0~65_combout\ & \data_mode[3]~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key5~combout\,
	datab => \Add0~64_combout\,
	datac => \Add0~65_combout\,
	datad => \data_mode[3]~0_combout\,
	combout => \data_mode[3]~8_combout\);

-- Location: LCFF_X21_Y6_N11
\COUNT1[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~49_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(1));

-- Location: LCCOMB_X21_Y6_N10
\Add0~49\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~49_combout\ = (\LessThan0~0_combout\ & (\Add0~10_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~10_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(1))))))

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
	combout => \Add0~49_combout\);

-- Location: LCCOMB_X20_Y6_N22
\data_mode[3]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~2_combout\ = (\Add0~48_combout\ & (\Add0~49_combout\ & (\Add0~50_combout\ & \Add0~51_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~48_combout\,
	datab => \Add0~49_combout\,
	datac => \Add0~50_combout\,
	datad => \Add0~51_combout\,
	combout => \data_mode[3]~2_combout\);

-- Location: LCFF_X20_Y5_N31
\COUNT1[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~58_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(10));

-- Location: LCCOMB_X20_Y5_N30
\Add0~58\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~58_combout\ = (\LessThan0~0_combout\ & (\Add0~28_combout\)) # (!\LessThan0~0_combout\ & ((\LessThan0~4_combout\ & (\Add0~28_combout\)) # (!\LessThan0~4_combout\ & ((COUNT1(10))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \LessThan0~0_combout\,
	datab => \Add0~28_combout\,
	datac => COUNT1(10),
	datad => \LessThan0~4_combout\,
	combout => \Add0~58_combout\);

-- Location: LCCOMB_X20_Y5_N16
\data_mode[3]~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~4_combout\ = (!\Add0~57_combout\ & (!\Add0~58_combout\ & (!\Add0~59_combout\ & \Add0~56_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~57_combout\,
	datab => \Add0~58_combout\,
	datac => \Add0~59_combout\,
	datad => \Add0~56_combout\,
	combout => \data_mode[3]~4_combout\);

-- Location: LCFF_X20_Y5_N15
\COUNT1[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \Add0~60_combout\,
	aclr => \key5~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => COUNT1(14));

-- Location: LCCOMB_X20_Y5_N14
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

-- Location: LCCOMB_X20_Y5_N6
\data_mode[3]~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~5_combout\ = (!\Add0~62_combout\ & (!\Add0~61_combout\ & (\Add0~60_combout\ & !\Add0~63_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~62_combout\,
	datab => \Add0~61_combout\,
	datac => \Add0~60_combout\,
	datad => \Add0~63_combout\,
	combout => \data_mode[3]~5_combout\);

-- Location: LCCOMB_X20_Y6_N0
\data_mode[3]~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~6_combout\ = (\data_mode[3]~3_combout\ & (\data_mode[3]~2_combout\ & (\data_mode[3]~4_combout\ & \data_mode[3]~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \data_mode[3]~3_combout\,
	datab => \data_mode[3]~2_combout\,
	datac => \data_mode[3]~4_combout\,
	datad => \data_mode[3]~5_combout\,
	combout => \data_mode[3]~6_combout\);

-- Location: LCCOMB_X20_Y6_N14
\data_mode[2]~13\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[2]~13_combout\ = data_mode(2) $ (((\Equal1~1_combout\ & (\data_mode[3]~8_combout\ & \data_mode[3]~6_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal1~1_combout\,
	datab => \data_mode[3]~8_combout\,
	datac => data_mode(2),
	datad => \data_mode[3]~6_combout\,
	combout => \data_mode[2]~13_combout\);

-- Location: LCCOMB_X20_Y6_N18
\data_mode[3]~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~1_combout\ = (!\key5~combout\ & (\Add0~65_combout\ & \Add0~64_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key5~combout\,
	datac => \Add0~65_combout\,
	datad => \Add0~64_combout\,
	combout => \data_mode[3]~1_combout\);

-- Location: LCCOMB_X20_Y6_N24
\data_mode[0]~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[0]~7_combout\ = data_mode(0) $ (((\data_mode[3]~0_combout\ & (\data_mode[3]~1_combout\ & \data_mode[3]~6_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \data_mode[3]~0_combout\,
	datab => \data_mode[3]~1_combout\,
	datac => data_mode(0),
	datad => \data_mode[3]~6_combout\,
	combout => \data_mode[0]~7_combout\);

-- Location: LCFF_X20_Y6_N25
\data_mode[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \data_mode[0]~7_combout\,
	aclr => \Equal1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_mode(0));

-- Location: LCCOMB_X20_Y6_N6
\data_mode[1]~9\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[1]~9_combout\ = data_mode(1) $ (((data_mode(0) & (\data_mode[3]~8_combout\ & \data_mode[3]~6_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(0),
	datab => \data_mode[3]~8_combout\,
	datac => data_mode(1),
	datad => \data_mode[3]~6_combout\,
	combout => \data_mode[1]~9_combout\);

-- Location: LCFF_X20_Y6_N7
\data_mode[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \data_mode[1]~9_combout\,
	aclr => \Equal1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_mode(1));

-- Location: LCCOMB_X20_Y6_N2
\Equal1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal1~0_combout\ = (!data_mode(2) & (!data_mode(3) & (data_mode(0) & data_mode(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(2),
	datab => data_mode(3),
	datac => data_mode(0),
	datad => data_mode(1),
	combout => \Equal1~0_combout\);

-- Location: LCFF_X20_Y6_N15
\data_mode[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \data_mode[2]~13_combout\,
	aclr => \Equal1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_mode(2));

-- Location: LCCOMB_X20_Y6_N30
\data_mode[3]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~3_combout\ = (!\Add0~54_combout\ & (\Add0~53_combout\ & (!\Add0~55_combout\ & \Add0~52_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~54_combout\,
	datab => \Add0~53_combout\,
	datac => \Add0~55_combout\,
	datad => \Add0~52_combout\,
	combout => \data_mode[3]~3_combout\);

-- Location: LCCOMB_X20_Y6_N10
\data_mode[3]~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~10_combout\ = (\data_mode[3]~2_combout\ & \data_mode[3]~3_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \data_mode[3]~2_combout\,
	datad => \data_mode[3]~3_combout\,
	combout => \data_mode[3]~10_combout\);

-- Location: LCCOMB_X20_Y6_N12
\data_mode[3]~11\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~11_combout\ = (\data_mode[3]~5_combout\ & (\data_mode[3]~8_combout\ & (\data_mode[3]~4_combout\ & \data_mode[3]~10_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \data_mode[3]~5_combout\,
	datab => \data_mode[3]~8_combout\,
	datac => \data_mode[3]~4_combout\,
	datad => \data_mode[3]~10_combout\,
	combout => \data_mode[3]~11_combout\);

-- Location: LCCOMB_X20_Y6_N28
\data_mode[3]~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_mode[3]~12_combout\ = data_mode(3) $ (((\Equal1~1_combout\ & (data_mode(2) & \data_mode[3]~11_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal1~1_combout\,
	datab => data_mode(2),
	datac => data_mode(3),
	datad => \data_mode[3]~11_combout\,
	combout => \data_mode[3]~12_combout\);

-- Location: LCFF_X20_Y6_N29
\data_mode[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \sysclk~clkctrl_outclk\,
	datain => \data_mode[3]~12_combout\,
	aclr => \Equal1~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_mode(3));

-- Location: LCCOMB_X20_Y4_N16
\Equal9~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal9~0_combout\ = (!data_mode(1) & (!data_mode(3) & !data_mode(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(1),
	datab => data_mode(3),
	datac => data_mode(2),
	combout => \Equal9~0_combout\);

-- Location: LCCOMB_X18_Y4_N0
\tmp_seg7data[0]~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~0_combout\ = (!\Equal12~0_combout\ & (!led_c(0) & ((!\Equal9~0_combout\) # (!data_mode(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(0),
	datab => \Equal12~0_combout\,
	datac => led_c(0),
	datad => \Equal9~0_combout\,
	combout => \tmp_seg7data[0]~0_combout\);

-- Location: LCCOMB_X19_Y4_N14
\tmp_seg7data[0]~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~1_combout\ = (!data_count_seg(3) & (!data_count_seg(2) & ((!data_count_seg(1)) # (!data_count_seg(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(3),
	datab => data_count_seg(0),
	datac => data_count_seg(1),
	datad => data_count_seg(2),
	combout => \tmp_seg7data[0]~1_combout\);

-- Location: LCCOMB_X18_Y4_N26
\tmp_seg7data[0]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~2_combout\ = (\Equal9~0_combout\ & (data_mode(0) & ((\tmp_seg7data[0]~0_combout\) # (\tmp_seg7data[0]~1_combout\)))) # (!\Equal9~0_combout\ & (((\tmp_seg7data[0]~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010100011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(0),
	datab => \tmp_seg7data[0]~0_combout\,
	datac => \tmp_seg7data[0]~1_combout\,
	datad => \Equal9~0_combout\,
	combout => \tmp_seg7data[0]~2_combout\);

-- Location: LCCOMB_X19_Y4_N8
\tmp_seg7data[0]~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~6_combout\ = (\Equal12~1_combout\ & (\Equal9~0_combout\ & !data_mode(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal12~1_combout\,
	datac => \Equal9~0_combout\,
	datad => data_mode(0),
	combout => \tmp_seg7data[0]~6_combout\);

-- Location: LCCOMB_X18_Y4_N12
\tmp_seg7data[0]~7\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[0]~7_combout\ = (\tmp_seg7data[0]~5_combout\) # ((\tmp_seg7data[0]~2_combout\) # ((\tmp_seg7data[0]~6_combout\ & data_min_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111011101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~5_combout\,
	datab => \tmp_seg7data[0]~2_combout\,
	datac => \tmp_seg7data[0]~6_combout\,
	datad => data_min_low(0),
	combout => \tmp_seg7data[0]~7_combout\);

-- Location: LCCOMB_X18_Y8_N26
\Add6~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add6~4_combout\ = (data_h_low(2) & (\Add6~3\ $ (GND))) # (!data_h_low(2) & (!\Add6~3\ & VCC))
-- \Add6~5\ = CARRY((data_h_low(2) & !\Add6~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(2),
	datad => VCC,
	cin => \Add6~3\,
	combout => \Add6~4_combout\,
	cout => \Add6~5\);

-- Location: LCCOMB_X18_Y8_N30
\Add6~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add6~8_combout\ = \Add6~7\ $ (!data_h_low(4))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => data_h_low(4),
	cin => \Add6~7\,
	combout => \Add6~8_combout\);

-- Location: LCFF_X18_Y8_N31
\data_h_low[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add6~8_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(4));

-- Location: LCCOMB_X19_Y8_N14
\Equal16~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal16~0_combout\ = (data_h_low(3) & (!data_h_low(1) & (!data_h_low(4) & !data_h_low(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(3),
	datab => data_h_low(1),
	datac => data_h_low(4),
	datad => data_h_low(2),
	combout => \Equal16~0_combout\);

-- Location: LCCOMB_X18_Y8_N24
\Add6~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add6~2_combout\ = (data_h_low(1) & (!\Add6~1\)) # (!data_h_low(1) & ((\Add6~1\) # (GND)))
-- \Add6~3\ = CARRY((!\Add6~1\) # (!data_h_low(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(1),
	datad => VCC,
	cin => \Add6~1\,
	combout => \Add6~2_combout\,
	cout => \Add6~3\);

-- Location: LCCOMB_X19_Y8_N30
\data_h_low~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_low~0_combout\ = (\Add6~2_combout\ & ((!\Equal16~0_combout\) # (!data_h_low(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_h_low(0),
	datac => \Equal16~0_combout\,
	datad => \Add6~2_combout\,
	combout => \data_h_low~0_combout\);

-- Location: LCFF_X19_Y8_N31
\data_h_low[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_low~0_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(1));

-- Location: LCFF_X18_Y8_N27
\data_h_low[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \Add6~4_combout\,
	aclr => \Equal17~2_combout\,
	ena => \data_h_high[0]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_low(2));

-- Location: LCCOMB_X20_Y4_N10
\data_count_seg[3]~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_count_seg[3]~2_combout\ = data_count_seg(3) $ (((data_count_seg(1) & (data_count_seg(0) & data_count_seg(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_count_seg(0),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \data_count_seg[3]~2_combout\);

-- Location: LCFF_X20_Y4_N11
\data_count_seg[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_ms~clkctrl_outclk\,
	datain => \data_count_seg[3]~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_count_seg(3));

-- Location: LCCOMB_X20_Y4_N8
\Equal13~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal13~0_combout\ = (data_count_seg(0)) # (((data_count_seg(2)) # (data_count_seg(3))) # (!data_count_seg(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(0),
	datab => data_count_seg(1),
	datac => data_count_seg(2),
	datad => data_count_seg(3),
	combout => \Equal13~0_combout\);

-- Location: LCCOMB_X20_Y4_N26
\Equal11~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal11~0_combout\ = ((data_count_seg(1)) # ((data_count_seg(3)) # (data_count_seg(2)))) # (!data_count_seg(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(0),
	datab => data_count_seg(1),
	datac => data_count_seg(3),
	datad => data_count_seg(2),
	combout => \Equal11~0_combout\);

-- Location: LCCOMB_X19_Y8_N18
\tmp_seg7data[2]~13\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~13_combout\ = (\Equal11~0_combout\ & ((\Equal13~0_combout\ & (data_h_high(2))) # (!\Equal13~0_combout\ & ((data_h_low(2))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(2),
	datab => data_h_low(2),
	datac => \Equal13~0_combout\,
	datad => \Equal11~0_combout\,
	combout => \tmp_seg7data[2]~13_combout\);

-- Location: LCCOMB_X19_Y8_N16
\tmp_seg7data[2]~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~14_combout\ = (\tmp_seg7data[0]~3_combout\ & ((\tmp_seg7data[2]~13_combout\) # ((data_min_high(2) & !\Equal11~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000100010101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~3_combout\,
	datab => \tmp_seg7data[2]~13_combout\,
	datac => data_min_high(2),
	datad => \Equal11~0_combout\,
	combout => \tmp_seg7data[2]~14_combout\);

-- Location: LCCOMB_X18_Y4_N30
\tmp_seg7data[2]~15\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[2]~15_combout\ = (\tmp_seg7data[2]~12_combout\) # ((\tmp_seg7data[2]~14_combout\) # ((\tmp_seg7data[0]~6_combout\ & data_min_low(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[2]~12_combout\,
	datab => \tmp_seg7data[0]~6_combout\,
	datac => data_min_low(2),
	datad => \tmp_seg7data[2]~14_combout\,
	combout => \tmp_seg7data[2]~15_combout\);

-- Location: LCCOMB_X18_Y4_N14
\tmp_seg7data[1]~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~10_combout\ = (!\Equal12~0_combout\ & (led_c(1) & !\Equal9~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Equal12~0_combout\,
	datac => led_c(1),
	datad => \Equal9~0_combout\,
	combout => \tmp_seg7data[1]~10_combout\);

-- Location: LCCOMB_X19_Y8_N12
\tmp_seg7data[1]~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~8_combout\ = (\Equal11~0_combout\ & ((\Equal13~0_combout\ & (data_h_high(1))) # (!\Equal13~0_combout\ & ((data_h_low(1))))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(1),
	datab => data_h_low(1),
	datac => \Equal13~0_combout\,
	datad => \Equal11~0_combout\,
	combout => \tmp_seg7data[1]~8_combout\);

-- Location: LCCOMB_X19_Y8_N26
\tmp_seg7data[1]~9\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~9_combout\ = (\tmp_seg7data[0]~3_combout\ & ((\tmp_seg7data[1]~8_combout\) # ((!\Equal11~0_combout\ & data_min_high(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101000100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~3_combout\,
	datab => \Equal11~0_combout\,
	datac => data_min_high(1),
	datad => \tmp_seg7data[1]~8_combout\,
	combout => \tmp_seg7data[1]~9_combout\);

-- Location: LCCOMB_X18_Y4_N16
\tmp_seg7data[1]~11\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[1]~11_combout\ = (\tmp_seg7data[1]~10_combout\) # ((\tmp_seg7data[1]~9_combout\) # ((data_min_low(1) & \tmp_seg7data[0]~6_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_min_low(1),
	datab => \tmp_seg7data[1]~10_combout\,
	datac => \tmp_seg7data[0]~6_combout\,
	datad => \tmp_seg7data[1]~9_combout\,
	combout => \tmp_seg7data[1]~11_combout\);

-- Location: LCCOMB_X19_Y8_N28
\Equal16~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal16~1_combout\ = (\Equal16~0_combout\ & data_h_low(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \Equal16~0_combout\,
	datad => data_h_low(0),
	combout => \Equal16~1_combout\);

-- Location: LCCOMB_X19_Y8_N24
\data_h_high[1]~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[1]~3_combout\ = data_h_high(1) $ (((data_h_high(0) & (\Equal16~1_combout\ & \data_h_high[0]~2_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(0),
	datab => \Equal16~1_combout\,
	datac => data_h_high(1),
	datad => \data_h_high[0]~2_combout\,
	combout => \data_h_high[1]~3_combout\);

-- Location: LCFF_X19_Y8_N25
\data_h_high[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[1]~3_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(1));

-- Location: LCCOMB_X19_Y8_N2
\data_h_high[2]~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[2]~4_combout\ = (data_h_high(0) & (\Equal16~1_combout\ & (data_h_high(1) & \data_h_high[0]~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(0),
	datab => \Equal16~1_combout\,
	datac => data_h_high(1),
	datad => \data_h_high[0]~2_combout\,
	combout => \data_h_high[2]~4_combout\);

-- Location: LCCOMB_X19_Y8_N0
\data_h_high[3]~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \data_h_high[3]~6_combout\ = data_h_high(3) $ (((data_h_high(2) & \data_h_high[2]~4_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_high(2),
	datac => data_h_high(3),
	datad => \data_h_high[2]~4_combout\,
	combout => \data_h_high[3]~6_combout\);

-- Location: LCFF_X19_Y8_N1
\data_h_high[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \div|Q_min~clkctrl_outclk\,
	datain => \data_h_high[3]~6_combout\,
	aclr => \Equal17~2_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => data_h_high(3));

-- Location: LCCOMB_X19_Y8_N4
\tmp_seg7data[3]~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~18_combout\ = (\Equal11~0_combout\ & ((\Equal13~0_combout\ & ((data_h_high(3)))) # (!\Equal13~0_combout\ & (data_h_low(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100100000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_h_low(3),
	datab => \Equal11~0_combout\,
	datac => \Equal13~0_combout\,
	datad => data_h_high(3),
	combout => \tmp_seg7data[3]~18_combout\);

-- Location: LCCOMB_X19_Y4_N22
\Equal12~1\ : cycloneii_lcell_comb
-- Equation(s):
-- \Equal12~1_combout\ = (!data_count_seg(3) & (!data_count_seg(0) & (!data_count_seg(1) & !data_count_seg(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(3),
	datab => data_count_seg(0),
	datac => data_count_seg(1),
	datad => data_count_seg(2),
	combout => \Equal12~1_combout\);

-- Location: LCCOMB_X19_Y4_N16
\tmp_seg7data[3]~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~16_combout\ = (\Equal9~0_combout\ & (!data_mode(0) & (data_min_low(3) & \Equal12~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal9~0_combout\,
	datab => data_mode(0),
	datac => data_min_low(3),
	datad => \Equal12~1_combout\,
	combout => \tmp_seg7data[3]~16_combout\);

-- Location: LCCOMB_X19_Y8_N22
\tmp_seg7data[3]~17\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~17_combout\ = (data_min_high(3) & !\Equal11~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => data_min_high(3),
	datad => \Equal11~0_combout\,
	combout => \tmp_seg7data[3]~17_combout\);

-- Location: LCCOMB_X19_Y4_N30
\tmp_seg7data[3]~19\ : cycloneii_lcell_comb
-- Equation(s):
-- \tmp_seg7data[3]~19_combout\ = (\tmp_seg7data[3]~16_combout\) # ((\tmp_seg7data[0]~3_combout\ & ((\tmp_seg7data[3]~18_combout\) # (\tmp_seg7data[3]~17_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101011111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~3_combout\,
	datab => \tmp_seg7data[3]~18_combout\,
	datac => \tmp_seg7data[3]~16_combout\,
	datad => \tmp_seg7data[3]~17_combout\,
	combout => \tmp_seg7data[3]~19_combout\);

-- Location: LCCOMB_X18_Y4_N8
\dis|Mux6~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux6~0_combout\ = (\tmp_seg7data[2]~15_combout\ & (!\tmp_seg7data[1]~11_combout\ & ((\tmp_seg7data[3]~19_combout\) # (!\tmp_seg7data[0]~7_combout\)))) # (!\tmp_seg7data[2]~15_combout\ & (\tmp_seg7data[0]~7_combout\ & (\tmp_seg7data[1]~11_combout\ $ 
-- (!\tmp_seg7data[3]~19_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010110000000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[2]~15_combout\,
	datac => \tmp_seg7data[1]~11_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux6~0_combout\);

-- Location: LCCOMB_X18_Y4_N22
\dis|Mux5~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux5~0_combout\ = (\tmp_seg7data[1]~11_combout\ & ((\tmp_seg7data[0]~7_combout\ & ((\tmp_seg7data[3]~19_combout\))) # (!\tmp_seg7data[0]~7_combout\ & (\tmp_seg7data[2]~15_combout\)))) # (!\tmp_seg7data[1]~11_combout\ & (\tmp_seg7data[2]~15_combout\ & 
-- (\tmp_seg7data[0]~7_combout\ $ (\tmp_seg7data[3]~19_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110010001001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[2]~15_combout\,
	datac => \tmp_seg7data[1]~11_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux5~0_combout\);

-- Location: LCCOMB_X18_Y4_N20
\dis|Mux4~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux4~0_combout\ = (\tmp_seg7data[2]~15_combout\ & (\tmp_seg7data[3]~19_combout\ & ((\tmp_seg7data[1]~11_combout\) # (!\tmp_seg7data[0]~7_combout\)))) # (!\tmp_seg7data[2]~15_combout\ & (!\tmp_seg7data[0]~7_combout\ & (\tmp_seg7data[1]~11_combout\ & 
-- !\tmp_seg7data[3]~19_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100010000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[2]~15_combout\,
	datac => \tmp_seg7data[1]~11_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux4~0_combout\);

-- Location: LCCOMB_X18_Y4_N18
\dis|Mux3~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux3~0_combout\ = (\tmp_seg7data[1]~11_combout\ & ((\tmp_seg7data[0]~7_combout\ & (\tmp_seg7data[2]~15_combout\)) # (!\tmp_seg7data[0]~7_combout\ & (!\tmp_seg7data[2]~15_combout\ & \tmp_seg7data[3]~19_combout\)))) # (!\tmp_seg7data[1]~11_combout\ & 
-- (!\tmp_seg7data[3]~19_combout\ & (\tmp_seg7data[0]~7_combout\ $ (\tmp_seg7data[2]~15_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001000010000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[2]~15_combout\,
	datac => \tmp_seg7data[1]~11_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux3~0_combout\);

-- Location: LCCOMB_X18_Y4_N28
\dis|Mux2~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux2~0_combout\ = (\tmp_seg7data[1]~11_combout\ & (\tmp_seg7data[0]~7_combout\ & ((!\tmp_seg7data[3]~19_combout\)))) # (!\tmp_seg7data[1]~11_combout\ & ((\tmp_seg7data[2]~15_combout\ & ((!\tmp_seg7data[3]~19_combout\))) # 
-- (!\tmp_seg7data[2]~15_combout\ & (\tmp_seg7data[0]~7_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001010101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[2]~15_combout\,
	datac => \tmp_seg7data[1]~11_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux2~0_combout\);

-- Location: LCCOMB_X18_Y4_N6
\dis|Mux1~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux1~0_combout\ = (\tmp_seg7data[2]~15_combout\ & ((\tmp_seg7data[1]~11_combout\ & (\tmp_seg7data[0]~7_combout\ & !\tmp_seg7data[3]~19_combout\)) # (!\tmp_seg7data[1]~11_combout\ & ((\tmp_seg7data[3]~19_combout\))))) # (!\tmp_seg7data[2]~15_combout\ 
-- & (!\tmp_seg7data[3]~19_combout\ & ((\tmp_seg7data[0]~7_combout\) # (\tmp_seg7data[1]~11_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110010110010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[2]~15_combout\,
	datac => \tmp_seg7data[1]~11_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux1~0_combout\);

-- Location: LCCOMB_X19_Y4_N4
\dis|Mux0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \dis|Mux0~0_combout\ = (\tmp_seg7data[3]~19_combout\) # ((\tmp_seg7data[1]~11_combout\ & ((!\tmp_seg7data[2]~15_combout\) # (!\tmp_seg7data[0]~7_combout\))) # (!\tmp_seg7data[1]~11_combout\ & ((\tmp_seg7data[2]~15_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111101111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \tmp_seg7data[0]~7_combout\,
	datab => \tmp_seg7data[1]~11_combout\,
	datac => \tmp_seg7data[2]~15_combout\,
	datad => \tmp_seg7data[3]~19_combout\,
	combout => \dis|Mux0~0_combout\);

-- Location: LCCOMB_X20_Y4_N22
\seg7com~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \seg7com~2_combout\ = (!data_count_seg(1) & (!data_mode(3) & (!data_mode(2) & !data_mode(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(1),
	datab => data_mode(3),
	datac => data_mode(2),
	datad => data_mode(1),
	combout => \seg7com~2_combout\);

-- Location: LCCOMB_X20_Y4_N20
\seg7com~3\ : cycloneii_lcell_comb
-- Equation(s):
-- \seg7com~3_combout\ = (!data_count_seg(3) & (!data_count_seg(2) & ((\seg7com~2_combout\) # (!data_count_seg(0)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001100000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_count_seg(0),
	datab => data_count_seg(3),
	datac => data_count_seg(2),
	datad => \seg7com~2_combout\,
	combout => \seg7com~3_combout\);

-- Location: LCCOMB_X20_Y4_N24
\seg7com~5\ : cycloneii_lcell_comb
-- Equation(s):
-- \seg7com~5_combout\ = (data_mode(2)) # ((data_mode(3)) # ((\Equal13~0_combout\) # (data_mode(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => data_mode(2),
	datab => data_mode(3),
	datac => \Equal13~0_combout\,
	datad => data_mode(1),
	combout => \seg7com~5_combout\);

-- Location: LCCOMB_X20_Y4_N2
\seg7com~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \seg7com~4_combout\ = (\Equal9~0_combout\ & ((\Equal11~0_combout\))) # (!\Equal9~0_combout\ & (\Equal13~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal13~0_combout\,
	datac => \Equal9~0_combout\,
	datad => \Equal11~0_combout\,
	combout => \seg7com~4_combout\);

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
	padio => ww_key1);

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
	padio => ww_key2);

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

-- Location: PIN_25,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\led_c_r~I\ : cycloneii_io
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
	datain => \ALT_INV_Equal2~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_led_c_r);

-- Location: PIN_24,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\led_c_y~I\ : cycloneii_io
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
	datain => led_c(1),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_led_c_y);

-- Location: PIN_28,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\led_c_g~I\ : cycloneii_io
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
	datain => \Equal3~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_led_c_g);

-- Location: PIN_30,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\led_p_r~I\ : cycloneii_io
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
	datain => ALT_INV_led_p(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_led_p_r);

-- Location: PIN_27,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 24mA
\led_p_g~I\ : cycloneii_io
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
	datain => led_p(0),
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_led_p_g);

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
	datain => \seg7com~3_combout\,
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
	datain => \seg7com~5_combout\,
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
	datain => \seg7com~4_combout\,
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
	datain => \ALT_INV_Equal12~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_seg7com(3));
END structure;


