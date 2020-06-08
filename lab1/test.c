#include <stdio.h>


void changeVal(int*);


int main(void){
	
	system("echo off");
	system("color 2");
	system("cls");
	
	
	int A[100];
	int i;
	
	
	for(i=0; i < 100; i++){
		
		A[i] = 5*i;
		
	}
	
	changeVal(&A[0]);
	
	return 0;
	
}


void changeVal(int *x){
	
	int i=0;
	
	for(; i < 100; i++){
		
		*x = *x+1;
		
		printf("\n%d",*x++);
		
	}
	
}