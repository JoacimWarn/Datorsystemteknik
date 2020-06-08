#include <stdio.h>

double PI_estimator(int nMbembers);

int main(void){
	
	double retur_1 = PI_estimator(30);
	double retur_2 = PI_estimator(300);
	double retur_3 = PI_estimator(3000);
	double retur_4 = PI_estimator(78786);
	
	printf("summing 30...\n");
	printf("%f\n",retur_1);
	
	printf("summing 300...\n");
	printf("%f\n",retur_2);
	
	printf("summing 3000...\n");
	printf("%f\n",retur_3);
	
	printf("summing 78786...\n");
	printf("%f\n",retur_4);
	
	return 0;
	
}

double PI_estimator(int nMbembers){
	
	double PI_est = 0.0;
	double PosSum = 0.0;
	double NegSum = 0.0;
	
	
	//Summerar alla negativa nummer
	int i=1;
	for(; i < nMbembers; i++){
		
		NegSum = NegSum + (1.0)/(4*i-1);
		
	}
	
	int j=1;
	for(; j < nMbembers; j++){
		
		PosSum = PosSum + (1.0)/(4*j+1);
		
	}
	
	PI_est = 4*(1 + (PosSum - NegSum));
	
	return PI_est;
	
}