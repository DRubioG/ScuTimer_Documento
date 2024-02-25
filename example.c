#include <stdio.h>
#include "xscutimer.h"
#include "xparameters.h"

int main(){
    int Status;
    int timer_value;
    int counter = 0;
    XScuTimer my_Timer;
    XScuTimer_Config *Timer_Config;

    Timer_Config = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
    Status = XScuTimer_CfgInitialize(&my_Timer, Timer_Config, Timer_Config->BaseAddr);
    XScuTimer_LoadTimer(&my_Timer, XPAR_PS7_CORTEA9_0_CPU_CLK_FREQ_HZ/2);
    XScuTimer_Start(&my_Timer);
    while(1){
        timer_value = XScutimer_GetCounterValue(&my_Timer);
        if(timer_value == 0){
            XScuTimer_RestartTimer(&my_Timer);
            printf("Timer has reached zero %d times\n\r", counter++);
        } else {
            xil_printf("Timer is still running (Timer_value = %d)\n\r", timer_value);
        }
    }
    return 0;
}