@====================================================================
@ File Name : 2410addr.a
@ Function  : S3C2410 Define Address Register (Assembly)
@ Program   : Shin, On Pil (SOP)
@ Date      : March 27, 2002
@ Version   : 0.0
@ History
@   1.0 : Programming start (February 18,2002) -> SOP
@         INTERRUPT rPRIORITY 0x4a00000a -> 0x4a00000c       (May 06, 2002 SOP)
@         RTC BCD DAY and DATE Register Name Correction      (May 06, 2002 SOP) 
@====================================================================


@=================
@ Memory control 
@=================
.EQU    BWSCON      ,  0x48000000     @Bus width & wait status
.EQU    BANKCON0    ,  0x48000004     @Boot ROM control
.EQU    BANKCON1    ,  0x48000008     @BANK1 control
.EQU    BANKCON2    ,  0x4800000c     @BANK2 cControl
.EQU    BANKCON3    ,  0x48000010     @BANK3 control
.EQU    BANKCON4    ,  0x48000014     @BANK4 control
.EQU    BANKCON5    ,  0x48000018     @BANK5 control
.EQU    BANKCON6    ,  0x4800001c     @BANK6 control
.EQU    BANKCON7    ,  0x48000020     @BANK7 control
.EQU    REFRESH     ,  0x48000024     @DRAM/SDRAM refresh
.EQU    BANKSIZE    ,  0x48000028     @Flexible Bank Size
.EQU    MRSRB6      ,  0x4800002c     @Mode register set for SDRAM
.EQU    MRSRB7      ,  0x48000030     @Mode register set for SDRAM

@=================
@ USB Host
@=================

@=================
@ INTERRUPT
@=================
.EQU    SRCPND       ,  0x4a000000    @Interrupt request status
.EQU    INTMOD       ,  0x4a000004    @Interrupt mode control
.EQU    INTMSK       ,  0x4a000008    @Interrupt mask control
.EQU    PRIORITY     ,  0x4a00000a    @IRQ priority control
.EQU    INTPND       ,  0x4a000010    @Interrupt request status
.EQU    INTOFFSET    ,  0x4a000014    @Interruot request source offset
.EQU    SUSSRCPND    ,  0x4a000018    @Sub source pending
.EQU    INTSUBMSK    ,  0x4a00001c    @Interrupt sub mask


@=================
@ DMA
@=================
.EQU    DISRC0       ,  0x4b000000    @DMA 0 Initial source
.EQU    DISRCC0      ,  0x4b000004    @DMA 0 Initial source control
.EQU    DIDST0       ,  0x4b000008    @DMA 0 Initial Destination
.EQU    DIDSTC0      ,  0x4b00000c    @DMA 0 Initial Destination control
.EQU    DCON0        ,  0x4b000010    @DMA 0 Control
.EQU    DSTAT0       ,  0x4b000014    @DMA 0 Status
.EQU    DCSRC0       ,  0x4b000018    @DMA 0 Current source
.EQU    DCDST0       ,  0x4b00001c    @DMA 0 Current destination
.EQU    DMASKTRIG0   ,  0x4b000020    @DMA 0 Mask trigger

.EQU    DISRC1       ,  0x4b000040    @DMA 1 Initial source
.EQU    DISRCC1      ,  0x4b000044    @DMA 1 Initial source control
.EQU    DIDST1       ,  0x4b000048    @DMA 1 Initial Destination
.EQU    DIDSTC1      ,  0x4b00004c    @DMA 1 Initial Destination control
.EQU    DCON1        ,  0x4b000050    @DMA 1 Control
.EQU    DSTAT1       ,  0x4b000054    @DMA 1 Status
.EQU    DCSRC1       ,  0x4b000058    @DMA 1 Current source
.EQU    DCDST1       ,  0x4b00005c    @DMA 1 Current destination
.EQU    DMASKTRIG1   ,  0x4b000060    @DMA 1 Mask trigger

.EQU    DISRC2       ,  0x4b000080    @DMA 2 Initial source
.EQU    DISRCC2      ,  0x4b000084    @DMA 2 Initial source control
.EQU    DIDST2       ,  0x4b000088    @DMA 2 Initial Destination
.EQU    DIDSTC2      ,  0x4b00008c    @DMA 2 Initial Destination control
.EQU    DCON2        ,  0x4b000090    @DMA 2 Control
.EQU    DSTAT2       ,  0x4b000094    @DMA 2 Status
.EQU    DCSRC2       ,  0x4b000098    @DMA 2 Current source
.EQU    DCDST2       ,  0x4b00009c    @DMA 2 Current destination
.EQU    DMASKTRIG2   ,  0x4b0000a0    @DMA 2 Mask trigger

.EQU    DISRC3       ,  0x4b0000c0    @DMA 3 Initial source
.EQU    DISRCC3      ,  0x4b0000c4    @DMA 3 Initial source control
.EQU    DIDST3       ,  0x4b0000c8    @DMA 3 Initial Destination
.EQU    DIDSTC3      ,  0x4b0000cc    @DMA 3 Initial Destination control
.EQU    DCON3        ,  0x4b0000d0    @DMA 3 Control
.EQU    DSTAT3       ,  0x4b0000d4    @DMA 3 Status
.EQU    DCSRC3       ,  0x4b0000d8    @DMA 3 Current source
.EQU    DCDST3       ,  0x4b0000dc    @DMA 3 Current destination
.EQU    DMASKTRIG3   ,  0x4b0000e0    @DMA 3 Mask trigger


@==========================
@ CLOCK & POWER MANAGEMENT
@==========================
.EQU    LOCKTIME    ,  0x4c000000     @PLL lock time counter
.EQU    MPLLCON     ,  0x4c000004     @MPLL Control
.EQU    UPLLCON     ,  0x4c000008     @UPLL Control
.EQU    CLKCON      ,  0x4c00000c     @Clock generator control
.EQU    CLKSLOW     ,  0x4c000010     @Slow clock control
.EQU    CLKDIVN     ,  0x4c000014     @Clock divider control


@=================
@ LCD CONTROLLER
@=================
.EQU    LCDCON1     ,  0x4d000000     @LCD control 1
.EQU    LCDCON2     ,  0x4d000004     @LCD control 2
.EQU    LCDCON3     ,  0x4d000008     @LCD control 3
.EQU    LCDCON4     ,  0x4d00000c     @LCD control 4
.EQU    LCDCON5     ,  0x4d000010     @LCD control 5
.EQU    LCDSADDR1   ,  0x4d000014     @STN/TFT Frame buffer start address 1
.EQU    LCDSADDR2   ,  0x4d000018     @STN/TFT Frame buffer start address 2
.EQU    LCDSADDR3   ,  0x4d00001c     @STN/TFT Virtual screen address set
.EQU    REDLUT      ,  0x4d000020     @STN Red lookup table
.EQU    GREENLUT    ,  0x4d000024     @STN Green lookup table 
.EQU    BLUELUT     ,  0x4d000028     @STN Blue lookup table
.EQU    DITHMODE    ,  0x4d00004c     @STN Dithering mode
.EQU    TPAL        ,  0x4d000050     @TFT Temporary palette
.EQU    LCDINTPND   ,  0x4d000054     @LCD Interrupt pending
.EQU    LCDSRCPND   ,  0x4d000058     @LCD Interrupt source
.EQU    LCDINTMSK   ,  0x4d00005c     @LCD Interrupt mask
.EQU    LPCSEL      ,  0x4d000060     @LPC3600 Control


@=================
@ NAND flash
@=================
.EQU    NFCONF      ,  0x4e000000     @NAND Flash configuration
.EQU    NFCMD       ,  0x4e000004     @NADD Flash command
.EQU    NFADDR      ,  0x4e000008     @NAND Flash address
.EQU    NFDATA      ,  0x4e00000c     @NAND Flash data
.EQU    NFSTAT      ,  0x4e000010     @NAND Flash operation status
.EQU    NFECC       ,  0x4e000014     @NAND Flash ECC


@=================
@ UART
@=================
.EQU    ULCON0       ,  0x50000000    @UART 0 Line control
.EQU    UCON0        ,  0x50000004    @UART 0 Control
.EQU    UFCON0       ,  0x50000008    @UART 0 FIFO control
.EQU    UMCON0       ,  0x5000000c    @UART 0 Modem control
.EQU    UTRSTAT0     ,  0x50000010    @UART 0 Tx/Rx status
.EQU    UERSTAT0     ,  0x50000014    @UART 0 Rx error status
.EQU    UFSTAT0      ,  0x50000018    @UART 0 FIFO status
.EQU    UMSTAT0      ,  0x5000001c    @UART 0 Modem status
.EQU    UBRDIV0      ,  0x50000028    @UART 0 Baud rate divisor

.EQU    ULCON1       ,  0x50004000    @UART 1 Line control
.EQU    UCON1        ,  0x50004004    @UART 1 Control
.EQU    UFCON1       ,  0x50004008    @UART 1 FIFO control
.EQU    UMCON1       ,  0x5000400c    @UART 1 Modem control
.EQU    UTRSTAT1     ,  0x50004010    @UART 1 Tx/Rx status
.EQU    UERSTAT1     ,  0x50004014    @UART 1 Rx error status
.EQU    UFSTAT1      ,  0x50004018    @UART 1 FIFO status
.EQU    UMSTAT1      ,  0x5000401c    @UART 1 Modem status
.EQU    UBRDIV1      ,  0x50004028    @UART 1 Baud rate divisor

.EQU    ULCON2       ,  0x50008000    @UART 2 Line control
.EQU    UCON2        ,  0x50008004    @UART 2 Control
.EQU    UFCON2       ,  0x50008008    @UART 2 FIFO control
.EQU    UMCON2       ,  0x5000800c    @UART 2 Modem control
.EQU    UTRSTAT2     ,  0x50008010    @UART 2 Tx/Rx status
.EQU    UERSTAT2     ,  0x50008014    @UART 2 Rx error status
.EQU    UFSTAT2      ,  0x50008018    @UART 2 FIFO status
.EQU    UMSTAT2      ,  0x5000801c    @UART 2 Modem status
.EQU    UBRDIV2      ,  0x50008028    @UART 2 Baud rate divisor

.IFDEF BIG_ENDIAN__
.EQU    UTXH0        ,  0x50000023    @UART 0 Transmission Hold
.EQU    URXH0        ,  0x50000027    @UART 0 Receive buffer
.EQU    UTXH1        ,  0x50004023    @UART 1 Transmission Hold
.EQU    URXH1        ,  0x50004027    @UART 1 Receive buffer
.EQU    UTXH2        ,  0x50008023    @UART 2 Transmission Hold
.EQU    URXH2        ,  0x50008027    @UART 2 Receive buffer

.ELSE                               @Little Endian
.EQU    UTXH0        ,  0x50000020    @UART 0 Transmission Hold
.EQU    URXH0        ,  0x50000024    @UART 0 Receive buffer
.EQU    UTXH1        ,  0x50004020    @UART 1 Transmission Hold
.EQU    URXH1        ,  0x50004024    @UART 1 Receive buffer
.EQU    UTXH2        ,  0x50008020    @UART 2 Transmission Hold
.EQU    URXH2        ,  0x50008024    @UART 2 Receive buffer
.ENDIF


@=================
@ PWM TIMER
@=================
.EQU    TCFG0    ,  0x51000000        @Timer 0 configuration
.EQU    TCFG1    ,  0x51000004        @Timer 1 configuration
.EQU    TCON     ,  0x51000008        @Timer control
.EQU    TCNTB0   ,  0x5100000c        @Timer count buffer 0
.EQU    TCMPB0   ,  0x51000010        @Timer compare buffer 0
.EQU    TCNTO0   ,  0x51000014        @Timer count observation 0
.EQU    TCNTB1   ,  0x51000018        @Timer count buffer 1
.EQU    TCMPB1   ,  0x5100001c        @Timer compare buffer 1
.EQU    TCNTO1   ,  0x51000020        @Timer count observation 1
.EQU    TCNTB2   ,  0x51000024        @Timer count buffer 2
.EQU    TCMPB2   ,  0x51000028        @Timer compare buffer 2
.EQU    TCNTO2   ,  0x5100002c        @Timer count observation 2
.EQU    TCNTB3   ,  0x51000030        @Timer count buffer 3
.EQU    TCMPB3   ,  0x51000034        @Timer compare buffer 3
.EQU    TCNTO3   ,  0x51000038        @Timer count observation 3
.EQU    TCNTB4   ,  0x5100003c        @Timer count buffer 4
.EQU    TCNTO4   ,  0x51000040        @Timer count observation 4


@=================
@ USB DEVICE
@=================
.IFDEF         BIG_ENDIAN__
.EQU    FUNC_ADDR_REG       ,  0x52000143     @Function address
.EQU    PWR_REG             ,  0x52000147     @Power management
.EQU    EP_INT_REG          ,  0x5200014b     @EP Interrupt pending and clear
.EQU    USB_INT_REG         ,  0x5200015b     @USB Interrupt pending and clear
.EQU    EP_INT_EN_REG       ,  0x5200015f     @Interrupt enable
.EQU    USB_INT_EN_REG      ,  0x5200016f
.EQU    FRAME_NUM1_REG      ,  0x52000173     @Frame number lower byte
.EQU    FRAME_NUM2_REG      ,  0x52000177     @Frame number lower byte
.EQU    INDEX_REG           ,  0x5200017b     @Register index
.EQU    MAXP_REG            ,  0x52000183     @Endpoint max packet
.EQU    EP0_CSR             ,  0x52000187     @Endpoint 0 status
.EQU    IN_CSR1_REG         ,  0x52000187     @In endpoint control status
.EQU    IN_CSR2_REG         ,  0x5200018b
.EQU    OUT_CSR1_REG        ,  0x52000193     @Out endpoint control status
.EQU    OUT_CSR2_REG        ,  0x52000197
.EQU    OUT_FIFO_CNT1_REG   ,  0x5200019b     @Endpoint out write count
.EQU    OUT_FIFO_CNT2_REG   ,  0x5200019f
.EQU    EP0_FIFO            ,  0x520001c3     @Endpoint 0 FIFO
.EQU    EP1_FIFO            ,  0x520001c7     @Endpoint 1 FIFO
.EQU    EP2_FIFO            ,  0x520001cb     @Endpoint 2 FIFO
.EQU    EP3_FIFO            ,  0x520001cf     @Endpoint 3 FIFO
.EQU    EP4_FIFO            ,  0x520001d3     @Endpoint 4 FIFO
.EQU    EP1_DMA_CON         ,  0x52000203     @EP1 DMA interface control
.EQU    EP1_DMA_UNIT        ,  0x52000207     @EP1 DMA Tx unit counter
.EQU    EP1_DMA_FIFO        ,  0x5200020b     @EP1 DMA Tx FIFO counter
.EQU    EP1_DMA_TTC_L       ,  0x5200020f     @EP1 DMA total Tx counter
.EQU    EP1_DMA_TTC_M       ,  0x52000213
.EQU    EP1_DMA_TTC_H       ,  0x52000217
.EQU    EP2_DMA_CON         ,  0x5200021b     @EP2 DMA interface control
.EQU    EP2_DMA_UNIT        ,  0x5200021f     @EP2 DMA Tx unit counter
.EQU    EP2_DMA_FIFO        ,  0x52000223     @EP2 DMA Tx FIFO counter
.EQU    EP2_DMA_TTC_L       ,  0x52000227     @EP2 DMA total Tx counter
.EQU    EP2_DMA_TTC_M       ,  0x5200022b
.EQU    EP2_DMA_TTC_H       ,  0x5200022f
.EQU    EP3_DMA_CON         ,  0x52000243     @EP3 DMA interface control
.EQU    EP3_DMA_UNIT        ,  0x52000247     @EP3 DMA Tx unit counter
.EQU    EP3_DMA_FIFO        ,  0x5200024b     @EP3 DMA Tx FIFO counter
.EQU    EP3_DMA_TTC_L       ,  0x5200024f     @EP3 DMA total Tx counter
.EQU    EP3_DMA_TTC_M       ,  0x52000253
.EQU    EP3_DMA_TTC_H       ,  0x52000257
.EQU    EP4_DMA_CON         ,  0x5200025b     @EP4 DMA interface control
.EQU    EP4_DMA_UNIT        ,  0x5200025f     @EP4 DMA Tx unit counter
.EQU    EP4_DMA_FIFO        ,  0x52000263     @EP4 DMA Tx FIFO counter
.EQU    EP4_DMA_TTC_L       ,  0x52000267     @EP4 DMA total Tx counter
.EQU    EP4_DMA_TTC_M       ,  0x5200026b
.EQU    EP4_DMA_TTC_H       ,  0x5200026f

.ELSE           @ Little Endian
.EQU    FUNC_ADDR_REG       ,  0x52000140     @Function address
.EQU    PWR_REG             ,  0x52000144     @Power management
.EQU    EP_INT_REG          ,  0x52000148     @EP Interrupt pending and clear
.EQU    USB_INT_REG         ,  0x52000158     @USB Interrupt pending and clear
.EQU    EP_INT_EN_REG       ,  0x5200015c     @Interrupt enable
.EQU    USB_INT_EN_REG      ,  0x5200016c
.EQU    FRAME_NUM1_REG      ,  0x52000170     @Frame number lower byte
.EQU    FRAME_NUM2_REG      ,  0x52000174     @Frame number lower byte
.EQU    INDEX_REG           ,  0x52000178     @Register index
.EQU    MAXP_REG            ,  0x52000180     @Endpoint max packet
.EQU    EP0_CSR             ,  0x52000184     @Endpoint 0 status
.EQU    IN_CSR1_REG         ,  0x52000184     @In endpoint control status
.EQU    IN_CSR2_REG         ,  0x52000188
.EQU    OUT_CSR1_REG        ,  0x52000190     @Out endpoint control status
.EQU    OUT_CSR2_REG        ,  0x52000194
.EQU    OUT_FIFO_CNT1_REG   ,  0x52000198     @Endpoint out write count
.EQU    OUT_FIFO_CNT2_REG   ,  0x5200019c
.EQU    EP0_FIFO            ,  0x520001c0     @Endpoint 0 FIFO
.EQU    EP1_FIFO            ,  0x520001c4     @Endpoint 1 FIFO
.EQU    EP2_FIFO            ,  0x520001c8     @Endpoint 2 FIFO
.EQU    EP3_FIFO            ,  0x520001cc     @Endpoint 3 FIFO
.EQU    EP4_FIFO            ,  0x520001d0     @Endpoint 4 FIFO
.EQU    EP1_DMA_CON         ,  0x52000200     @EP1 DMA interface control
.EQU    EP1_DMA_UNIT        ,  0x52000204     @EP1 DMA Tx unit counter
.EQU    EP1_DMA_FIFO        ,  0x52000208     @EP1 DMA Tx FIFO counter
.EQU    EP1_DMA_TTC_L       ,  0x5200020c     @EP1 DMA total Tx counter
.EQU    EP1_DMA_TTC_M       ,  0x52000210
.EQU    EP1_DMA_TTC_H       ,  0x52000214
.EQU    EP2_DMA_CON         ,  0x52000218     @EP2 DMA interface control
.EQU    EP2_DMA_UNIT        ,  0x5200021c     @EP2 DMA Tx unit counter
.EQU    EP2_DMA_FIFO        ,  0x52000220     @EP2 DMA Tx FIFO counter
.EQU    EP2_DMA_TTC_L       ,  0x52000224     @EP2 DMA total Tx counter
.EQU    EP2_DMA_TTC_M       ,  0x52000228
.EQU    EP2_DMA_TTC_H       ,  0x5200022c
.EQU    EP3_DMA_CON         ,  0x52000240     @EP3 DMA interface control
.EQU    EP3_DMA_UNIT        ,  0x52000244     @EP3 DMA Tx unit counter
.EQU    EP3_DMA_FIFO        ,  0x52000248     @EP3 DMA Tx FIFO counter
.EQU    EP3_DMA_TTC_L       ,  0x5200024c     @EP3 DMA total Tx counter
.EQU    EP3_DMA_TTC_M       ,  0x52000250
.EQU    EP3_DMA_TTC_H       ,  0x52000254
.EQU    EP4_DMA_CON         ,  0x52000258     @EP4 DMA interface control
.EQU    EP4_DMA_UNIT        ,  0x5200025c     @EP4 DMA Tx unit counter
.EQU    EP4_DMA_FIFO        ,  0x52000260     @EP4 DMA Tx FIFO counter
.EQU    EP4_DMA_TTC_L       ,  0x52000264     @EP4 DMA total Tx counter
.EQU    EP4_DMA_TTC_M       ,  0x52000268
.EQU    EP4_DMA_TTC_H       ,  0x5200026c
.ENDIF        


@=================
@ WATCH DOG TIMER
@=================
.EQU    WTCON     ,  0x53000000       @Watch-dog timer mode
.EQU    WTDAT     ,  0x53000004       @Watch-dog timer data
.EQU    WTCNT     ,  0x53000008       @Eatch-dog timer count


@=================
@ IIC
@=================
.EQU    IICCON    ,  0x54000000       @IIC control
.EQU    IICSTAT   ,  0x54000004       @IIC status
.EQU    IICADD    ,  0x54000008       @IIC address
.EQU    IICDS     ,  0x5400000c       @IIC data shift


@=================
@ IIS
@=================
.EQU    IISCON    ,  0x55000000       @IIS Control
.EQU    IISMOD    ,  0x55000004       @IIS Mode
.EQU    IISPSR    ,  0x55000008       @IIS Prescaler
.EQU    IISFCON   ,  0x5500000c       @IIS FIFO control

.IFDEF         BIG_ENDIAN__
.EQU    IISFIFO    ,  0x55000012       @IIS FIFO entry
.ELSE                               @Little Endian
.EQU    IISFIFO    ,  0x55000010       @IIS FIFO entry
.ENDIF        


@=================
@ I/O PORT 
@=================
.EQU    GPACON      ,  0x56000000     @Port A control
.EQU    GPADAT      ,  0x56000004     @Port A data
                        
.EQU    GPBCON      ,  0x56000010     @Port B control
.EQU    GPBDAT      ,  0x56000014     @Port B data
.EQU    GPBUP       ,  0x56000018     @Pull-up control B
                        
.EQU    GPCCON      ,  0x56000020     @Port C control
.EQU    GPCDAT      ,  0x56000024     @Port C data
.EQU    GPCUP       ,  0x56000028     @Pull-up control C
                        
.EQU    GPDCON      ,  0x56000030     @Port D control
.EQU    GPDDAT      ,  0x56000034     @Port D data
.EQU    GPDUP       ,  0x56000038     @Pull-up control D
                        
.EQU    GPECON      ,  0x56000040     @Port E control
.EQU    GPEDAT      ,  0x56000044     @Port E data
.EQU    GPEUP       ,  0x56000048     @Pull-up control E
                        
.EQU    GPFCON      ,  0x56000050     @Port F control
.EQU    GPFDAT      ,  0x56000054     @Port F data
.EQU    GPFUP       ,  0x56000058     @Pull-up control F
                        
.EQU    GPGCON      ,  0x56000060     @Port G control
.EQU    GPGDAT      ,  0x56000064     @Port G data
.EQU    GPGUP       ,  0x56000068     @Pull-up control G
                        
.EQU    GPHCON      ,  0x56000070     @Port H control
.EQU    GPHDAT      ,  0x56000074     @Port H data
.EQU    GPHUP       ,  0x56000078     @Pull-up control H
                        
.EQU    MISCCR      ,  0x56000080     @Miscellaneous control
.EQU    DCKCON      ,  0x56000084     @DCLK0/1 control
.EQU    EXTINT0     ,  0x56000088     @External interrupt control register 0
.EQU    EXTINT1     ,  0x5600008c     @External interrupt control register 1
.EQU    EXTINT2     ,  0x56000090     @External interrupt control register 2
.EQU    EINTFLT0    ,  0x56000094     @Reserved
.EQU    EINTFLT1    ,  0x56000098     @Reserved
.EQU    EINTFLT2    ,  0x5600009c     @External interrupt filter control register 2
.EQU    EINTFLT3    ,  0x560000a0     @External interrupt filter control register 3
.EQU    EINTMASK    ,  0x560000a4     @External interrupt mask
.EQU    EINTPEND    ,  0x560000a8     @External interrupt pending
.EQU    GSTATUS0    ,  0x560000ac     @External pin status
.EQU    GSTATUS1    ,  0x560000b0     @Chip ID(0x32410000)
.EQU    GSTATUS2    ,  0x560000b4     @Reset type
.EQU    GSTATUS3    ,  0x560000b8     @Saved data0(32-bit) before entering POWER_OFF mode 
.EQU    GSTATUS4    ,  0x560000bc     @Saved data1(32-bit) before entering POWER_OFF mode


@=================
@ RTC
@=================
.IFDEF         BIG_ENDIAN__
.EQU    RTCCON    ,  0x57000043       @RTC control
.EQU    TICNT     ,  0x57000047       @Tick time count
.EQU    RTCALM    ,  0x57000053       @RTC alarm control
.EQU    ALMSEC    ,  0x57000057       @Alarm second
.EQU    ALMMIN    ,  0x5700005b       @Alarm minute
.EQU    ALMHOUR   ,  0x5700005f       @Alarm Hour
.EQU    ALMDAY    ,  0x57000063       @Alarm day
.EQU    ALMMON    ,  0x57000067       @Alarm month
.EQU    ALMYEAR   ,  0x5700006b       @Alarm year
.EQU    RTCRST    ,  0x5700006f       @RTC round reset
.EQU    BCDSEC    ,  0x57000073       @BCD second
.EQU    BCDMIN    ,  0x57000077       @BCD minute
.EQU    BCDHOUR   ,  0x5700007b       @BCD hour
.EQU    BCDDAY    ,  0x5700007f       @BCD day
.EQU    BCDDATE   ,  0x57000083       @BCD date
.EQU    BCDMON    ,  0x57000087       @BCD month
.EQU    BCDYEAR   ,  0x5700008b       @BCD year

.ELSE                               @Little Endian
.EQU    RTCCON    ,  0x57000040       @RTC control
.EQU    TICNT     ,  0x57000044       @Tick time count
.EQU    RTCALM    ,  0x57000050       @RTC alarm control
.EQU    ALMSEC    ,  0x57000054       @Alarm second
.EQU    ALMMIN    ,  0x57000058       @Alarm minute
.EQU    ALMHOUR   ,  0x5700005c       @Alarm Hour
.EQU    ALMDAY    ,  0x57000060       @Alarm day
.EQU    ALMMON    ,  0x57000064       @Alarm month
.EQU    ALMYEAR   ,  0x57000068       @Alarm year
.EQU    RTCRST    ,  0x5700006c       @RTC round reset
.EQU    BCDSEC    ,  0x57000070       @BCD second
.EQU    BCDMIN    ,  0x57000074       @BCD minute
.EQU    BCDHOUR   ,  0x57000078       @BCD hour
.EQU    BCDDAY    ,  0x5700007c       @BCD day
.EQU    BCDDATE   ,  0x57000080       @BCD date
.EQU    BCDMON    ,  0x57000084       @BCD month
.EQU    BCDYEAR   ,  0x57000088       @BCD year
.ENDIF                               @RTC


@=================
@ ADC
@=================
.EQU    ADCCON      ,  0x58000000     @ADC control
.EQU    ADCTSC      ,  0x58000004     @ADC touch screen control
.EQU    ADCDLY      ,  0x58000008     @ADC start or Interval Delay
.EQU    ADCDAT0     ,  0x5800000c     @ADC conversion data 0
.EQU    ADCDAT1     ,  0x58000010     @ADC conversion data 1                     


@=================                      
@ SPI           
@=================
.EQU    SPCON0      ,  0x59000000     @SPI0 control
.EQU    SPSTA0      ,  0x59000004     @SPI0 status
.EQU    SPPIN0      ,  0x59000008     @SPI0 pin control
.EQU    SPPRE0      ,  0x5900000c     @SPI0 baud rate prescaler
.EQU    SPTDAT0     ,  0x59000010     @SPI0 Tx data
.EQU    SPRDAT0     ,  0x59000014     @SPI0 Rx data

.EQU    SPCON1      ,  0x59000020     @SPI1 control
.EQU    SPSTA1      ,  0x59000024     @SPI1 status
.EQU    SPPIN1      ,  0x59000028     @SPI1 pin control
.EQU    SPPRE1      ,  0x5900002c     @SPI1 baud rate prescaler
.EQU    SPTDAT1     ,  0x59000030     @SPI1 Tx data
.EQU    SPRDAT1     ,  0x59000034     @SPI1 Rx data

@=================
@ SD Interface
@=================
.EQU    SDICON      ,  0x5a000000     @SDI control
.EQU    SDIPRE      ,  0x5a000000     @SDI baud rate prescaler
.EQU    SDICmdArg   ,  0x5a000000     @SDI command argument
.EQU    SDICmdCon   ,  0x5a000000     @SDI command control
.EQU    SDICmdSta   ,  0x5a000000     @SDI command status
.EQU    SDIRSP0     ,  0x5a000000     @SDI response 0
.EQU    SDIRSP1     ,  0x5a000000     @SDI response 1
.EQU    SDIRSP2     ,  0x5a000000     @SDI response 2
.EQU    SDIRSP3     ,  0x5a000000     @SDI response 3
.EQU    SDIDTimer   ,  0x5a000000     @SDI data/busy timer
.EQU    SDIBSize    ,  0x5a000000     @SDI block size
.EQU    SDIDatCon   ,  0x5a000000     @SDI data control
.EQU    SDIDatCnt   ,  0x5a000000     @SDI data remain counter
.EQU    SDIDatSta   ,  0x5a000000     @SDI data status
.EQU    SDIFSTA     ,  0x5a000000     @SDI FIFO status
.EQU    SDIIntMsk   ,  0x5a000000     @SDI interrupt mask

.IFDEF         BIG_ENDIAN__
.EQU    SDIDAT      ,  0x5a00003f     @SDI data
.ELSE                               @Little Endian
.EQU    SDIDAT      ,  0x5a00003c     @SDI data
.ENDIF                               @SD Interface

             
@=================
@ ISR
@=================
.EQU    pISR_RESET     ,  (_ISR_STARTADDRESS+0x0)
.EQU    pISR_UNDEF     ,  (_ISR_STARTADDRESS+0x4)
.EQU    pISR_SWI       ,  (_ISR_STARTADDRESS+0x8)
.EQU    pISR_PABORT    ,  (_ISR_STARTADDRESS+0xc)
.EQU    pISR_DABORT    ,  (_ISR_STARTADDRESS+0x10)
.EQU    pISR_RESERVED  ,  (_ISR_STARTADDRESS+0x14)
.EQU    pISR_IRQ       ,  (_ISR_STARTADDRESS+0x18)
.EQU    pISR_FIQ       ,  (_ISR_STARTADDRESS+0x1c)

.EQU    pISR_EINT0     ,  (_ISR_STARTADDRESS+0x20)
.EQU    pISR_EINT1     ,  (_ISR_STARTADDRESS+0x24)
.EQU    pISR_EINT2     ,  (_ISR_STARTADDRESS+0x28)
.EQU    pISR_EINT3     ,  (_ISR_STARTADDRESS+0x2c)
.EQU    pISR_EINT4_7   ,  (_ISR_STARTADDRESS+0x30)
.EQU    pISR_EINT8_23  ,  (_ISR_STARTADDRESS+0x34)
.EQU    pISR_NOTUSED6  ,  (_ISR_STARTADDRESS+0x38)
.EQU    pISR_BAT_FLT   ,  (_ISR_STARTADDRESS+0x3c)
.EQU    pISR_TICK      ,  (_ISR_STARTADDRESS+0x40)
.EQU    pISR_WDT       ,  (_ISR_STARTADDRESS+0x44)
.EQU    pISR_TIMER0    ,  (_ISR_STARTADDRESS+0x48)
.EQU    pISR_TIMER1    ,  (_ISR_STARTADDRESS+0x4c)
.EQU    pISR_TIMER2    ,  (_ISR_STARTADDRESS+0x50)
.EQU    pISR_TIMER3    ,  (_ISR_STARTADDRESS+0x54)
.EQU    pISR_TIMER4    ,  (_ISR_STARTADDRESS+0x58)
.EQU    pISR_UART2     ,  (_ISR_STARTADDRESS+0x5c)
.EQU    pISR_LCD       ,  (_ISR_STARTADDRESS+0x60)
.EQU    pISR_DMA0      ,  (_ISR_STARTADDRESS+0x64)
.EQU    pISR_DMA1      ,  (_ISR_STARTADDRESS+0x68)
.EQU    pISR_DMA2      ,  (_ISR_STARTADDRESS+0x6c)
.EQU    pISR_DMA3      ,  (_ISR_STARTADDRESS+0x70)
.EQU    pISR_SDI       ,  (_ISR_STARTADDRESS+0x74)
.EQU    pISR_SPI0      ,  (_ISR_STARTADDRESS+0x78)
.EQU    pISR_UART1     ,  (_ISR_STARTADDRESS+0x7c)
.EQU    pISR_NOTUSED24 ,  (_ISR_STARTADDRESS+0x80)
.EQU    pISR_USBD      ,  (_ISR_STARTADDRESS+0x84)
.EQU    pISR_USBH      ,  (_ISR_STARTADDRESS+0x88)
.EQU    pISR_IIC       ,  (_ISR_STARTADDRESS+0x8c)
.EQU    pISR_UART0     ,  (_ISR_STARTADDRESS+0x90)
.EQU    pISR_SPI1      ,  (_ISR_STARTADDRESS+0x94)
.EQU    pISR_RTC       ,  (_ISR_STARTADDRESS+0x98)
.EQU    pISR_ADC       ,  (_ISR_STARTADDRESS+0xa0)


@=================
@ PENDING BIT
@=================
.EQU    BIT_EINT0     ,  (0x1)
.EQU    BIT_EINT1     ,  (0x1<<1)
.EQU    BIT_EINT2     ,  (0x1<<2)
.EQU    BIT_EINT3     ,  (0x1<<3)
.EQU    BIT_EINT4_7   ,  (0x1<<4)
.EQU    BIT_EINT8_23  ,  (0x1<<5)
.EQU    BIT_NOTUSED6  ,  (0x1<<6)
.EQU    BIT_BAT_FLT   ,  (0x1<<7)
.EQU    BIT_TICK      ,  (0x1<<8)
.EQU    BIT_WDT       ,  (0x1<<9)
.EQU    BIT_TIMER0    ,  (0x1<<10)
.EQU    BIT_TIMER1    ,  (0x1<<11)
.EQU    BIT_TIMER2    ,  (0x1<<12)
.EQU    BIT_TIMER3    ,  (0x1<<13)
.EQU    BIT_TIMER4    ,  (0x1<<14)
.EQU    BIT_UART2     ,  (0x1<<15)
.EQU    BIT_LCD       ,  (0x1<<16)
.EQU    BIT_DMA0      ,  (0x1<<17)
.EQU    BIT_DMA1      ,  (0x1<<18)
.EQU    BIT_DMA2      ,  (0x1<<19)
.EQU    BIT_DMA3      ,  (0x1<<20)
.EQU    BIT_SDI       ,  (0x1<<21)
.EQU    BIT_SPI0      ,  (0x1<<22)
.EQU    BIT_UART1     ,  (0x1<<23)
.EQU    BIT_NOTUSED24 ,  (0x1<<24)
.EQU    BIT_USBD      ,  (0x1<<25)
.EQU    BIT_USBH      ,  (0x1<<26)
.EQU    BIT_IIC       ,  (0x1<<27)
.EQU    BIT_UART0     ,  (0x1<<28)
.EQU    BIT_SPI1      ,  (0x1<<29)
.EQU    BIT_RTC       ,  (0x1<<30)
.EQU    BIT_ADC       ,  (0x1<<31)
.EQU    BIT_ALLMSK    ,  (0xffffffff)

        
        
