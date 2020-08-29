#Scnu_pins.tcl 
set_global_assignment -name RESERVE_ALL_UNUSED_PINS "AS INPUT TRI-STATED" 
set_global_assignment -name ENABLE_INIT_DONE_OUTPUT OFF 
set_location_assignment PIN_17 -to clk                                              
#led
set_location_assignment PIN_71 -to led 
#seg7
set_location_assignment PIN_65 -to seg7com\[0\]
set_location_assignment PIN_67 -to seg7com\[1\]
set_location_assignment PIN_69 -to seg7com\[2\]
set_location_assignment PIN_70 -to seg7com\[3\]

set_location_assignment PIN_53 -to seg7data\[0\]  
set_location_assignment PIN_55 -to seg7data\[1\] 
set_location_assignment PIN_57 -to seg7data\[2\] 
set_location_assignment PIN_58 -to seg7data\[3\] 
set_location_assignment PIN_59 -to seg7data\[4\] 
set_location_assignment PIN_60 -to seg7data\[5\] 
set_location_assignment PIN_63 -to seg7data\[6\] 
set_location_assignment PIN_64 -to seg7data\[7\] 
--set_location_assignment PIN_64 -to seg7dp

#SDRAM
set_location_assignment PIN_112 -to sd_data\[0\] 
set_location_assignment PIN_104 -to sd_data\[1\]
set_location_assignment PIN_103 -to sd_data\[2\] 
set_location_assignment PIN_101 -to sd_data\[3\]
set_location_assignment PIN_100 -to sd_data\[4\] 
set_location_assignment PIN_99 -to sd_data\[5\]
set_location_assignment PIN_97 -to sd_data\[6\] 
set_location_assignment PIN_96 -to sd_data\[7\]
set_location_assignment PIN_129 -to sd_data\[8\] 
set_location_assignment PIN_132 -to sd_data\[9\]
set_location_assignment PIN_133 -to sd_data\[10\] 
set_location_assignment PIN_134 -to sd_data\[11\]
set_location_assignment PIN_135 -to sd_data\[12\] 
set_location_assignment PIN_136 -to sd_data\[13\]
set_location_assignment PIN_139 -to sd_data\[14\] 
set_location_assignment PIN_137 -to sd_data\[15\]

set_location_assignment PIN_76 -to sd_addr\[0\] 
set_location_assignment PIN_75 -to sd_addr\[1\]
set_location_assignment PIN_74 -to sd_addr\[2\] 
set_location_assignment PIN_73 -to sd_addr\[3\]
set_location_assignment PIN_113 -to sd_addr\[4\] 
set_location_assignment PIN_114 -to sd_addr\[5\]
set_location_assignment PIN_115 -to sd_addr\[6\] 
set_location_assignment PIN_118 -to sd_addr\[7\]
set_location_assignment PIN_119 -to sd_addr\[8\] 
set_location_assignment PIN_120 -to sd_addr\[9\]
set_location_assignment PIN_79 -to sd_addr\[10\] 
set_location_assignment PIN_121 -to sd_addr\[11\]

set_location_assignment PIN_81 -to sd_ba\[0\] 
set_location_assignment PIN_80 -to sd_ba\[1\]

set_location_assignment PIN_94 -to sd_ldqm 
set_location_assignment PIN_126 -to sd_udqm

set_location_assignment PIN_86 -to sd_cs
set_location_assignment PIN_87 -to sd_ras
set_location_assignment PIN_92 -to sd_cas
set_location_assignment PIN_93 -to sd_we 
set_location_assignment PIN_122 -to sd_cke
set_location_assignment PIN_125 -to sd_clk

#key
set_location_assignment PIN_88 -to key1
set_location_assignment PIN_89 -to key2
set_location_assignment PIN_90 -to key3
set_location_assignment PIN_91 -to key4
set_location_assignment PIN_72 -to key5 
