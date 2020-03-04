#include "Library/F2802x_Device.h"
#include "Library/gpio.h"
#include "Library/F2802x_Examples.h"
#include "Library/clk.h"

#define CLEAR_28 (GpioDataRegs.GPACLEAR.bit.GPIO28 = 1) // J1-3
#define CLEAR_29 (GpioDataRegs.GPACLEAR.bit.GPIO29 = 1) // J1-4
#define CLEAR_34 (GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1) // J1-5
#define CLEAR_16 (GpioDataRegs.GPACLEAR.bit.GPIO16 = 1) // J6-7
#define CLEAR_17 (GpioDataRegs.GPACLEAR.bit.GPIO17 = 1) // J6-8 shared with GPIO33
#define CLEAR_18 (GpioDataRegs.GPACLEAR.bit.GPIO18 = 1) // J1-7 shared with GPIO32
#define CLEAR_19 (GpioDataRegs.GPACLEAR.bit.GPIO19 = 1) // J2-2
#define CLEAR_0  (GpioDataRegs.GPACLEAR.bit.GPIO0 = 1)  // J6-1
#define CLEAR_1  (GpioDataRegs.GPACLEAR.bit.GPIO1 = 1)  // J6-2
#define CLEAR_2  (GpioDataRegs.GPACLEAR.bit.GPIO2 = 1)  // J6-3
#define CLEAR_3  (GpioDataRegs.GPACLEAR.bit.GPIO3 = 1)  // J6-4
#define CLEAR_4  (GpioDataRegs.GPACLEAR.bit.GPIO4 = 1)  // J6-5
#define CLEAR_5  (GpioDataRegs.GPACLEAR.bit.GPIO5 = 1)  // J6-6
#define CLEAR_6  (GpioDataRegs.GPACLEAR.bit.GPIO6 = 1)  // J2-8
#define CLEAR_7  (GpioDataRegs.GPACLEAR.bit.GPIO7 = 1)  // J2-9
#define CLEAR_12 (GpioDataRegs.GPACLEAR.bit.GPIO12 = 1) // J2-3
#define SET_28   (GpioDataRegs.GPASET.bit.GPIO28 = 1)
#define SET_29   (GpioDataRegs.GPASET.bit.GPIO29 = 1)
#define SET_34   (GpioDataRegs.GPBSET.bit.GPIO34 = 1)
#define SET_16   (GpioDataRegs.GPASET.bit.GPIO16 = 1)
#define SET_17   (GpioDataRegs.GPASET.bit.GPIO17 = 1)
#define SET_18   (GpioDataRegs.GPASET.bit.GPIO18 = 1)
#define SET_19   (GpioDataRegs.GPASET.bit.GPIO19 = 1)
#define SET_0    (GpioDataRegs.GPASET.bit.GPIO0 = 1)
#define SET_1    (GpioDataRegs.GPASET.bit.GPIO1 = 1)
#define SET_2    (GpioDataRegs.GPASET.bit.GPIO2 = 1)
#define SET_3    (GpioDataRegs.GPASET.bit.GPIO3 = 1)
#define SET_4    (GpioDataRegs.GPASET.bit.GPIO4 = 1)
#define SET_5    (GpioDataRegs.GPASET.bit.GPIO5 = 1)
#define SET_6    (GpioDataRegs.GPASET.bit.GPIO6 = 1)
#define SET_7    (GpioDataRegs.GPASET.bit.GPIO7 = 1)
#define SET_12   (GpioDataRegs.GPASET.bit.GPIO12 = 1)

#define ABOUT_1S_OF_BIG_NUMBER ((Uint32)1000000) // count ~ 1us, 1s = 1,000,000 counts
#define ABOUT_10MS_OF_BIG_NUMBER ((Uint32)10000) // count ~ 1us, 10ms = 10,000 counts
#define ABOUT_1US_OF_BIG_NUMBER ((Uint32)1)      // count ~ 1us, 1us = 1 count

void initTimer(void);
void initGPIO(void);
void setGpioAsOutput(GPIO_Number_e gpioNumber);
void delayMicroseconds(Uint32 delayTime);

GPIO_Handle myGpio;

/**
 * main.c
 */
int main(void)
{
    //Uint32 time = 0;
    // Think we need this to be able to run from flash, not during JTAG debugging

#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    initGPIO();
    initTimer();

    for (;;) {
        //time = CpuTimer1Regs.TIM.all;
        //delayMicroseconds(100);
        //while ((time - CpuTimer1Regs.TIM.all) < ABOUT_1US_OF_BIG_NUMBER) {};
    }
}

void delayMicroseconds(Uint32 delayTimeUS)
{
    Uint32 startTime = CpuTimer1Regs.TIM.all;
    while ((startTime - CpuTimer1Regs.TIM.all) < delayTimeUS) {};
}

void setGpioAsOutput(GPIO_Number_e gpioNumber)
{
    GPIO_setMode(myGpio, gpioNumber, GPIO_0_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, gpioNumber, GPIO_Direction_Output);
    GPIO_setPullUp(myGpio, gpioNumber, GPIO_PullUp_Disable);
}

void initGPIO(void)
{
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    setGpioAsOutput(GPIO_Number_28);
    setGpioAsOutput(GPIO_Number_29);
    setGpioAsOutput(GPIO_Number_34);
    setGpioAsOutput(GPIO_Number_16);
    setGpioAsOutput(GPIO_Number_17);
    setGpioAsOutput(GPIO_Number_18);
    setGpioAsOutput(GPIO_Number_19);
    setGpioAsOutput(GPIO_Number_0);
    setGpioAsOutput(GPIO_Number_1);
    setGpioAsOutput(GPIO_Number_2);
    setGpioAsOutput(GPIO_Number_3);
    setGpioAsOutput(GPIO_Number_4);
    setGpioAsOutput(GPIO_Number_5);
    setGpioAsOutput(GPIO_Number_6);
    setGpioAsOutput(GPIO_Number_7);
    setGpioAsOutput(GPIO_Number_12);
    CLEAR_28;
    CLEAR_29;
    CLEAR_34;
    CLEAR_16;
    CLEAR_17;
    CLEAR_18;
    CLEAR_19;
    CLEAR_0;
    CLEAR_1;
    CLEAR_2;
    CLEAR_3;
    CLEAR_4;
    CLEAR_5;
    CLEAR_6;
    CLEAR_7;
    CLEAR_12;
}

void initTimer(void)
{
    CpuTimer1Regs.TCR.bit.FREE = 1; // Free run mode
    CpuTimer1Regs.TCR.bit.SOFT = 1;
    CpuTimer1Regs.PRD.all = 0xFFFFFFFF; // Initialize CpuTimer1
    CpuTimer1Regs.TPR.bit.TDDR = 0x3C; // 60MHz / 3C = 1us I think
    CpuTimer1Regs.TPRH.bit.TDDRH = 0x00;
    CpuTimer1Regs.TCR.bit.TSS = 1; // Stop CpuTimer1
    CpuTimer1Regs.TCR.bit.TRB = 1; // Reload CpuTimer1 counter register
    CpuTimer1.InterruptCount = 0; // Reset CpuTimer1 interrupt counter
    CpuTimer1Regs.TCR.bit.TIF = 1; // Clear CpuTimer1 interrupt flag
    CpuTimer1Regs.TCR.bit.TIE = 0; // Disable CpuTimer1 interrupt
    CpuTimer1Regs.TIM.all = 0xFFFFFFFF;
    CpuTimer1Regs.TCR.bit.TSS = 0; // Start CpuTimer1
}
