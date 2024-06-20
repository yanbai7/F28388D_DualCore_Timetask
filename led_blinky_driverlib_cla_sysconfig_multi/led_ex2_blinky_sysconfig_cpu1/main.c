
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
    // Boot CPU2 core
    //

    Device_bootCPU2(BOOT_MODE_CPU2);


    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();
    
        //
    // GPIO0 is set to EPWM1A
    // GPIO1 is set to EPWM1B
    //
    GPIO_setControllerCore(0, GPIO_CORE_CPU1);
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setControllerCore(1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(1,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);



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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize EPWM module
    //
    initEPWM();
    
    //
    // Initialize settings from SysConfig
    //
    Board_init();
    
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Start ePWM1, enabling SOCA and putting the counter in up-count mode
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);


    //
    // Sync CPUs so the blinking starts at the same time, though the LEDs toggle at different frequency
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_SYNC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;


    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Turn on LED
        //
        GPIO_writePin(CPU1_LED, 0);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);

        //
        // Turn off LED
        //
        GPIO_writePin(CPU1_LED, 1);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);
    }
}


//
// EPWM Initialization
// EPWM1 : generates output of frequency EPWM1_FREQ (100 KHz)
// EPWM4 : Triggers CLA task at frequency EPWM4_FREQ (10 KHz)
//
void initEPWM(void)
{
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM1_PERIOD
    // - run in count up-down mode
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_PERIOD);
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM1_PERIOD/10U);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    //
    // Configuring action-qualifiers for EPWM1 to generate symmetric
    // and complementary outputs on channel A and B
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                         EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                             EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                             EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                             EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Enabling Counter Compare shadow mode
    //
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO);

    //
    // Set up EPWM4 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM4_PERIOD
    // - run in count up mode
    EPWM_setClockPrescaler(EPWM4_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM4_BASE, EPWM4_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM4_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM4_BASE, 0U);

    //
    // Enabling EPWM4 interrupt at TBCTR = 0 to trigger
    // CLA task
    //
    EPWM_setInterruptSource(EPWM4_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM4_BASE);
    EPWM_setInterruptEventCount(EPWM4_BASE, 1U);

    //
    // EPWM 1 and 4 should run freely in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    EPWM_setEmulationMode(EPWM4_BASE, EPWM_EMULATION_FREE_RUN);
}

__interrupt void INT_CPU1_ADCA_1_ISR (void)
{
    u32C28cnts++;

    // Clear the interrupt flag
    ADC_clearInterruptStatus(CPU1_ADCA_BASE, ADC_INT_NUMBER1);

    // Acknowledge the interrupt
    Interrupt_clearACKGroup(INT_CPU1_ADCA_1_INTERRUPT_ACK_GROUP);

//    RST_DEBUG_ADC_EOC();
}


//
// End of File
//
