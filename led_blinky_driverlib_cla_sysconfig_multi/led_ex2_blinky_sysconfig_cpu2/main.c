
//
// Included Files
//
// Make sure to include "board.h" to use SysConfig
//
#include <cla_ex4_pwm_control_shared.h>
#include "driverlib.h"
#include "device.h"
#include "board.h"
#pragma SET_DATA_SECTION("cla_shared")

volatile uint32_t u32CLAcnts = 0;

#pragma SET_DATA_SECTION()   // Reset section to default


volatile uint32_t u32C28cnts = 0;
//
// Function Prototypes
//
void initEPWM(void);
void initCLA(void);
//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize settings from SysConfig
    //
    Board_init();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Sync CPUs so the blinking starts at the same time, though the LEDs toggle at different frequency
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_SYNC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Turn on LED
        //
        GPIO_writePin(CPU2_LED, 1);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);

        //
        // Turn off LED
        //
        GPIO_writePin(CPU2_LED, 0);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);
    }
}

//
// End of File
//
