#include "system_sam3x.h"
#include "at91sam3x8.h"
#include <stdio.h>


void ReadButton(unsigned int *);
void Set_Led(unsigned int);


void main(void){

  SystemInit();
  
  //Initiering av knapp
  *((volatile unsigned int *) 0x400E0610U) = 0xFFFFFFF0;
  *((volatile unsigned int *) 0x400E1400U) = 0x2;
  *((volatile unsigned int *) 0x400E1414U) = 0x2;
  *((volatile unsigned int *) 0x400E1460U) = 0x2;
  
  
  //Initiering av led
  *((volatile unsigned int*) 0x400E1400U) = 0x8;
  *((volatile unsigned int*) 0x400E1460U) = 0x8;
  *((volatile unsigned int*) 0x400E1410U) = 0x8;
  //0x10000000 = bit pid 28
  
  
  //unsigned int *var = (int*)0x400E143C;    Läser PIOD_PDSR
  
  unsigned int knappTryck = 0; //(int)0x2 & (int)0x7FFFFFFF;
  
  //PIOD_PER = 0x400E1400
  //PIOD_ODR = 0x400E1414
  //PIOD_OER = 0x400E1410
  //PIOD_PUER = 0x400E1464
  //PIOD_PDSR = 0x400E143C
  //PIOD_PUDR = 0x400E1460
  //PMC_PCER0 = 0x400E0610
  //PUDR = 0x400E1460
  //PIOD_IDR = 0x400E1444
 
 
 while(1){
   
   ReadButton(&knappTryck);
   Set_Led(knappTryck);
   
 // to d
   
 }// while(1)
} // main()


//Knapp ej nedtryckt = 1
//Knapp nedtryckt = 0
void ReadButton(unsigned int *nButton){
  
  unsigned int *var = (int*)0x400E143C;//PIOD_PDSR, läser av knapptryck
    
    if((int)0x2 & *var){
      
      *nButton = 1;
      
    }
    else{
      
      *nButton = 0;
      
    }
  
  //volatile unsigned int *var = (int*)0x400E143C;
  //nButton = (int*)0x400E143C;
  //printf("%d",nButton);
  
}



//Om nLed == 1: stäng på led
//Om nLed == 0: sätt av led
void Set_Led(unsigned int nLed){
  
  if(nLed == 0){
    
    *((volatile unsigned int*) 0x400E1430U) = 0x8;//SODR
    
  }
  else{
    
    *((volatile unsigned int*) 0x400E1434U) = 0x8;//CODR
    
  }
  
}


