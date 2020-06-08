#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "core_cm3.h"
#include "screen.h"


//PMC_PCER0 0x400E0610

//PIOD_PDR 0x400E1004
//PIOB_PER 0x400E1000
//PIOB_ODR 0x400E1014
//PIOB_OER 0x400E1010
//PIOB_CODR 0x400E1034
//PIOB_PDSR 0x400E103C
//PIOB_SODR 0x400E1030
//PIOB_PSR 0x400E1008

//PIOD_SODR 0x400E1430

//TC_CCR0 0x40080000
//TC_CMR0 0x40080004
//TC_IER0 0x40080024
//TC_IDR 0x40080028

//TC_RA0 0x40080014
//TC_RB0 0x40080018

//counter value0 0x40080010


void init_temp(void);
void start_measuring(void);
void delay(int);
void TC0_Handler(void);
void TC1_Handler(void);
void SysTick_Handler(void);


int systick_counter = 0;


void main(void){
  
  *((volatile unsigned int *) 0x400E1430U) = 0x4;        //Set OE key bus bit 2 PIOD_SODR - Stänger av keypad
  
  *((volatile unsigned int *) 0x400E0610U) = 1 << 13;       //PMC_PCER0 - PIOC
  
  *((volatile unsigned int *) 0x400E0610U) = 1 << 14;       //PMC_PCER0 - PIOD
  
  SystemInit();
  
  init();
  
  init_temp();
  
  start_measuring();
  /*
  SysTick_Config(0xFFFFFF);
  
  *((volatile unsigned int *) 0x400E1010U) = 0x20000;              //PIOB_OER
  *((volatile unsigned int *) 0x400E1004U) = 0x20000;              //PIOB_PDR
  */
  
  while(1){
    
    delay(30000000);
    
    start_measuring();
    
  }
  
}


void SysTick_Handler(void){
  
  systick_counter++;
  
}


void start_measuring(void){
  
    *AT91C_TC0_IER = 1 << 6;             // interrupt LDRBS 

    // create a startpuls with a Delay(25); sw_reset in TC0_CCR0.

    *AT91C_PIOB_OER   = AT91C_PIO_PB25;
    *AT91C_PIOB_CODR  = AT91C_PIO_PB25;
    
    delay(250);
    
    *AT91C_PIOB_ODR = AT91C_PIO_PB25;

    *AT91C_TC0_IDR = 1 << 6;    // disable interrupt
    *AT91C_TC0_CCR = 1 << 2;
  
  /*
  *((volatile unsigned int *) 0x40080024U) = 0x40;                //TC_IER0 - LDRBS
  
  
  *((volatile unsigned int *) 0x400E1010U) = 0x20000;              //PIOB_OER
  *((volatile unsigned int *) 0x400E1034U) = 0x20000;              //PIOB_CODR
  
  delay(25);
  
  *((volatile unsigned int *) 0x400E1014U) = 0x20000;               //PIOB_ODR
  
  
  *((volatile unsigned int *) 0x40080000U) = 0x4;               //TC_CCR0 - sw_reset
  */
  
}


void init_temp(void){
  
    *AT91C_PMC_PCER= 1 << 27;           // init TC0

    // Enable counter and make a sw_reset in TC0_CCR0
    *AT91C_TC0_CCR = 0x5;               // SWTRG | CLKEN

    *AT91C_TC0_CMR = 0x60000;           // TIOA (A - falling - 10b), (B - rising - 01b) and TCCLK1

    //Enable the pin
    *AT91C_PIOB_PER = AT91C_PIO_PB25;
    *AT91C_PIOB_ODR = AT91C_PIO_PB25;

    NVIC_ClearPendingIRQ(TC0_IRQn);
    NVIC_SetPriority(TC0_IRQn, 1);
    NVIC_EnableIRQ(TC0_IRQn);
    
    //SysTick_Config(84000);
    
    //int t_reset = systick_counter;
    
    //while((systick_counter - t_reset) < 520);
    printf("hey\n");
  
  /*
  *((volatile unsigned int *) 0x400E0610U) = 0xFFFFFFFC;                //pmc_pcer0
  
  //*((volatile unsigned int *) 0x40080004U) = 0x60000;           //TIOA0, A - falling, B - rising, Timer_Clock1
  *((volatile unsigned int *) 0x40080004U) = 0x60000;           //TIOA0, A - falling, B - rising, Timer_Clock1, waveform = 1
  
  *((volatile unsigned int *) 0x40080000U) = 0x5;               //TC_CCR0 - sw_reset - enable counter
  
  //Enable pin
  *((volatile unsigned int *) 0x400E1000U) = 0x20000;               //PIOB_PER
  *((volatile unsigned int *) 0x400E1014U) = 0x20000;               //PIOB_ODR
  
  NVIC_ClearPendingIRQ(28);
  NVIC_SetPriority(28, 1);
  NVIC_EnableIRQ(28);
  
  NVIC_ClearPendingIRQ(27);
  NVIC_SetPriority(27, 1);
  NVIC_EnableIRQ(27);
  
  //NVIC_SetPendingIRQ(28);
  */
  
}


void delay(int value){
  
  int i = 0;
  
  for(; i < value; i++){
    
    asm("nop");
    
  }
  
}


void TC0_Handler(void){
  
      // global_variable = REG_TC0_RB0 - REG_TC0_RA0 or use a flag
    int32_t rb = (*AT91C_TC0_RB); //Register B
    int32_t ra = (*AT91C_TC0_RA); //Register A 

    // printf("%d      %d\n", ra, rb);

    *AT91C_TC0_SR;  // status register
    *AT91C_TC0_SR;  // status register

    float temp = ((rb - ra) / (5.0f * 42.0f)) - 273.15f; // divide by 42
    
    
    //(int)pekare;
    
    int32_t temperatur = temp * 100;
    
    //hej = hej & 0x5;
    
    //pekare = pekare + 1;
    
    //(*pekare++);
    
  
    printf("Temperature:%f\n",temp);
    printTemperature(temperatur);
    
    
  /*
  *((volatile unsigned int *) 0x40080028U) = 0x40;              //TC_IDR0_LDRBS
  double global_variable = 0.0;
  
  volatile unsigned int *tc_ra = &(*((volatile unsigned int *)0x40080014U));            //TC_RA0
  volatile unsigned int *tc_rb = &(*((volatile unsigned int *)0x40080018U));            //TC_RB0
  
  unsigned int ra = *tc_ra;
  unsigned int rb = *tc_rb;
  
  global_variable = ((rb - ra) / 5.0) - 273.15;
  
  printf("Temperature is:%f\n",global_variable);
  */
  
}

/*

void TC1_Handler(void){
  
    // global_variable = REG_TC0_RB0 - REG_TC0_RA0 or use a flag
    int32_t rb = (*AT91C_TC0_RB); //Register B
    int32_t ra = (*AT91C_TC0_RA); //Register A 

    // printf("%d      %d\n", ra, rb);

    *AT91C_TC0_SR;  // status register

    float temp = ((rb - ra) / (5.0f * 42.0f)) - 273.15f; // divide by 42
  
    //printf("Temperature:%f\n",temp);
    
  /*
  *((volatile unsigned int *) 0x40080028U) = 0x40;              //TC_IDR0_LDRBS
  double global_variable = 0.0;
  
  volatile unsigned int *tc_ra = &(*((volatile unsigned int *)0x40080014U));            //TC_RA0
  volatile unsigned int *tc_rb = &(*((volatile unsigned int *)0x40080018U));            //TC_RB0
  
  unsigned int ra = *tc_ra;
  unsigned int rb = *tc_rb;
  
  global_variable = ((rb - ra) / 5.0) - 273.15;
  
  printf("Temperature is:%f\n",global_variable);
  
}

*/