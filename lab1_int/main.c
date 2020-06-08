#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "core_cm3.h"

void SysTick_Handler(void);


void main(void){

   SystemInit();

  *((volatile unsigned int *) 0x400E0610U) = 0xFFFFFFF0;
  *((volatile unsigned int *) 0x400E1400U) = 0x8;
  *((volatile unsigned int *) 0x400E1460U) = 0x8;
  *((volatile unsigned int *) 0x400E1410U) = 0x8;
  //*((volatile unsigned int *) 0x400E1430U) = 0x8;//SODR
  
  
  NVIC_ClearPendingIRQ(16384);
  NVIC_SetPriority(16384, 0);
  NVIC_EnableIRQ(16384);
  
  //*((volatile unsigned int *) 0xE000E010U) = 0x7;//systick_clr
  
  *((volatile unsigned int *) 0x400E1440U) = 0x8;//PIOD_IER
  
 
  unsigned int hej = (int)0xFFFFFF;
  unsigned int tal = SysTick_Config(hej);
  
 while(1){

   
 // to do

 }// while(1)
} // main() 


void SysTick_Handler(void){
  
  *((volatile unsigned int *) 0x400E144CU) = 0x8;//PIOD_ISR
  
  static unsigned int tal = 0;
  
  if((tal%4)==0){
  
  unsigned int *var = (int*)0x400E143C;//PIOD_PDSR, läser av led
  
      if((int)0x8 & *var){
      
      *((volatile unsigned int*) 0x400E1434U) = 0x8;//CODR
      
    }
    else{
      
      *((volatile unsigned int*) 0x400E1430U) = 0x8;//SODR
      
    }
    
  }
  tal++;
}