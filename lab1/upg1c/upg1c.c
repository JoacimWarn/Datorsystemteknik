#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int comparePi(double PI_est);


int main(void){
	
	system("color 3");
	system("cls");
	
	//printf("%1.5f",PI);
	
	int nMembers = 0;
	
	while(1){
		
		double PI_est = 0.0;
		double PosSum = 0.0;
		double NegSum = 0.0;
		
		//Negativa summa
		int i=1;
		for(; i < nMembers; i++){
			
			NegSum = NegSum + (1.0)/(4*i-1);
			
		}
		
		//Positiva summa
		int j=1;
		for(; j < nMembers; j++){
			
			PosSum = PosSum + (1.0)/(4*j+1);
			
		}
		
		PI_est = 4.0*(1.0 + (PosSum - NegSum));
		
		//3.14159
		
		if(comparePi(PI_est)==1) break;
		
		nMembers++;
		
	}
	
	printf("Number of members: %d\n",nMembers);
	return 0;
	
}


int comparePi(double PI_est){
	
	if(3.141599 >= PI_est) return 1;
	
	return 0;
	
}
