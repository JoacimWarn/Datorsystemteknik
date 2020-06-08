#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "core_cm3.h"


void SysTick_Handler(void);
void PIOD_Handler(void);


void main(void){
  
  
   SystemInit();
   
   
   
  *((volatile unsigned int *) 0x400E0610U) = 0xFFFFFFF0;
  
  *((volatile unsigned int *) 0x400E14B0U) = 0x2; //PIOD_AIMER
  *((volatile unsigned int *) 0x400E1420U) = 0x2; //PIOD_IFER
  *((volatile unsigned int *) 0x400E1484U) = 0x2; //PIOD_DIFSR
  *((volatile unsigned int *) 0x400E148CU) = 0xFF; //PIOD_SCDR
  
  *((volatile unsigned int *) 0x400E144CU);//PIOD_ISR knapp och led
  
  //Initiering av knapp
  *((volatile unsigned int *) 0x400E1400U) = 0x2;
  *((volatile unsigned int *) 0x400E1414U) = 0x2;
  *((volatile unsigned int *) 0x400E1464U) = 0x2;       //pull up enable
  *((volatile unsigned int *) 0x400E14C0U) = 0x2; //PIOD_ESR
  *((volatile unsigned int *) 0x400E14D0U) = 0x2; //PIOD_FELLSR
  
  
  //Initiering av led
  *((volatile unsigned int *) 0x400E1400U) = 0x8;
  *((volatile unsigned int *) 0x400E1460U) = 0x8;
  *((volatile unsigned int *) 0x400E1410U) = 0x8;
  //*((volatile unsigned int *) 0x400E1430U) = 0x8;//SODR
  
  
  NVIC_ClearPendingIRQ(14);
  NVIC_SetPriority(14,1);
  NVIC_EnableIRQ(14);
  
  
  
  *((volatile unsigned int *) 0x400E1440U) = 0x2;//PIOD_IER knapp
  *((volatile unsigned int *) 0x400E144CU);//PIO_ISR
  
  
 while(1){
   
 // to do

 }// while(1)
} // main() 


void SysTick_Handler(void){
  
  *((volatile unsigned int *) 0x400E144CU);//PIOD_ISR
  
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
  //printf("led is blinking\n");
  
}


void PIOD_Handler(void){
  
  *((volatile unsigned int *) 0x400E144CU);//PIOD_ISR
  
  unsigned static val = 0;
  
  if((val%2)==0){
    
    *((volatile unsigned int*) 0x400E1400U) = 0x8;
    
      unsigned int hej = (int)0xFFFFFF;
      unsigned int tal = SysTick_Config(hej);
      
  }
  else{
    
    *((volatile unsigned int*) 0x400E1434U) = 0x8;//CODR
    *((volatile unsigned int *) 0x400E1404U) = 0x8;
      
  }
    
  val++;
  //printf("button was pressed\n");
  
  
}