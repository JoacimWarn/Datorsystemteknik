#include <stdio.h>


int main(void){
	
	//Rensar output
	//system("cls");
	
	
	double PI_est = 0.0;
	double NegPi=0.0;
	double PosPi=0.0;
	
	
	int i=1;
	//Summerar alla negativa nummer
	for(; i <=50; i++){
		
		NegPi = NegPi + (1.0/(4*i-1));
		
	}
	
	
	int j=1;
	//Summerar alla positiva nummer
	for(; j<=50; j++){
		
		PosPi = PosPi + (1.0/(4*j+1));
		
	}
	
	
	PI_est = 4*(1 + (PosPi - NegPi));
	printf("%f\n",PI_est);
	
	
	return(0);
	
}

