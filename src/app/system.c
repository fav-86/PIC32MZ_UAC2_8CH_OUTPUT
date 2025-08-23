
#include "system.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************





// <editor-fold defaultstate="collapsed" desc="Configuration Bits">

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
//#pragma config BOOTISA =    MICROMIPS
#pragma config FECCCON =    ON //OFF_UNLOCKED // ON
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config EJTAGBEN =   NORMAL
#pragma config CP =         OFF

/*** DEVCFG1 ***/ 
#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       ON // OFF
#pragma config POSCMOD =    HS
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSECME
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     NORMAL
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF

/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_1           // FRC 8MHz/1 = 8MHz
#pragma config FPLLRNG =    RANGE_5_10_MHZ
#pragma config FPLLICLK =   PLL_FRC
#pragma config FPLLMULT =   MUL_46          // 8MHz x 46 = 368MHz (allowed range from 350 to 700 MHz)
#pragma config FPLLODIV =   DIV_2           // 368MHz/2 = 184MHz (60MHz - minimum frequecy when USB HS is ON )

    #if PRIMARY_CRYSTAL_FREQUENCY_Hz == 12000000u
#pragma config UPLLFSEL =   FREQ_12MHZ
    #elif PRIMARY_CRYSTAL_FREQUENCY_Hz == 24000000u
#pragma config UPLLFSEL =   FREQ_24MHZ
    #endif

    #ifdef PIC32MZxxxxEC
#pragma config UPLLEN =     ON
    #endif

/*** DEVCFG3 ***/
#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     OFF
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
#pragma config FUSBIDIO =   ON

/*** BF1SEQ0 ***/
#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xffff
// </editor-fold>

// Locate System Tasks bits
volatile uint32_t systemTasks;
// MCU system frequency in Hz
volatile int sysFreqHz = 0;




/*
 * Start MCU initialisation
 */
void sys_init (int sysfreq)
{  
    volatile uint32_t pfws, prefen;

    // Set flash frequency limits from errata
    if (DEVCFG0bits.FECCCON < 2) { // If Dynamic Flash ECC is enabled
        if (sysfreq <= 60000000) pfws = 0;
        else if (sysfreq <= 120000000) pfws = 1;
        else if (sysfreq <= 184000000) pfws = 2;
        else if (sysfreq <= 200000000) pfws = 3;
        else if (sysfreq <= 300000000) pfws = 4;
        else pfws = 5;
    }
    else {
        if (sysfreq <= 74000000) pfws = 0;
        else if (sysfreq <= 140000000) pfws = 1;
        else if (sysfreq <= 184000000) pfws = 2;
        else if (sysfreq <= 200000000) pfws = 3;
        else if (sysfreq <= 300000000) pfws = 4;
        else pfws = 5;
    }

    // Set prefetch only if flash clock divider is on
    prefen = (pfws) ? 0x3 : 0x0;

    PRECON = 0
            | (prefen << _PRECON_PREFEN_POSITION)   // Enable predictive prefetch for any address
            | (pfws << _PRECON_PFMWS_POSITION)      // Waite States PFM Access
            ;
    
    // Unlock peripheral bus clock control
    SYSKEY = 0x0; // Ensure OSCCON is locked
    SYSKEY = 0xAA996655; // Write Key1 to SYSKEY
    SYSKEY = 0x556699AA; // Write Key2 to SYSKEY

    if (sysfreq <= 100000000) { // if SYS frequency up to 100MHz
        PB1DIVbits.PBDIV = 0;
        PB2DIVbits.PBDIV = 0;
        PB3DIVbits.PBDIV = 0;
        PB4DIVbits.PBDIV = 0;
        PB5DIVbits.PBDIV = 0;
    }
    else if (sysfreq <= 200000000) { // if SYS frequency up to 200MHz
        PB1DIVbits.PBDIV = 1;
        PB2DIVbits.PBDIV = 1;
        PB3DIVbits.PBDIV = 1;
        PB4DIVbits.PBDIV = 1;
        PB5DIVbits.PBDIV = 1;
    }
    else if (sysfreq <= 300000000) {  // if SYS frequency up to 300MHz
        PB1DIVbits.PBDIV = 2;
        PB2DIVbits.PBDIV = 2;
        PB3DIVbits.PBDIV = 2;
        PB4DIVbits.PBDIV = 2;
        PB5DIVbits.PBDIV = 2;
    }
    else {  // if SYS frequency is more than 300MHz
        PB1DIVbits.PBDIV = 3;
        PB2DIVbits.PBDIV = 3;
        PB3DIVbits.PBDIV = 3;
        PB4DIVbits.PBDIV = 3;
        PB5DIVbits.PBDIV = 3;
    }
    PB8DIVbits.ON = 0; // Peripheral Bus 8 Output Clock Disable
    
    SYSKEY = 0x33333333; // Write any value other than Key1 or Key2
    
    /* Configure Shadow Register Set */
    PRISS = 0x76543210;
    while (PRISS != 0x76543210) {
        /* Wait for PRISS value to take effect */
    }
    INTCONbits.MVEC = 1;    // Set the CP0 registers for multi-vector interrupt
    
    // Disable all peripheral clocks
    PMD1SET = 0xffffffff;
    PMD2SET = 0xffffffff;
    PMD3SET = 0xffffffff;
    PMD4SET = 0xffffffff & ~(_PMD4_T1MD_MASK | _PMD4_T2MD_MASK | _PMD4_T3MD_MASK);
    PMD5SET = 0xffffffff & ~(_PMD5_SPI1MD_MASK | _PMD5_SPI2MD_MASK | _PMD5_SPI3MD_MASK | _PMD5_SPI4MD_MASK | _PMD5_USBMD_MASK | _PMD5_U1MD_MASK);
    PMD6SET = 0xffffffff & ~(_PMD6_REFO1MD_MASK);
    PMD7SET = 0xffffffff & ~(_PMD7_DMAMD_MASK);
}

