#include <stdio.h>


double average(double *, int);
double minima(double *, int);
double maxima(double *, int);
double variance(double *, int);


int main(void){
	
	
	double values[] = {0.9501, 0.2311, 0.6068, 0.4860, 0.8913, 0.7621, 0.4565, 0.0185, 0.8214, 0.4447, 0.6154, 0.7919, 0.9218, 0.7382, 0.1763, 0.4057, 0.9355,
	0.9169, 0.4103, 0.8936, 0.0579, 0.3529, 0.8132, 0.0099, 0.1389, 0.2028, 0.1987, 0.6038, 0.2722, 0.1988, 0.0153, 0.7468, 0.4451, 0.9318,
	0.4660, 0.4186, 0.8462, 0.5252, 0.2026, 0.6721, 0.8381, 0.0196, 0.6813, 0.3795, 0.8318, 0.5028, 0.7095, 0.4289, 0.3046, 0.1897, 0.1934,
	0.6822, 0.3028, 0.5417, 0.1509, 0.6979, 0.3784, 0.8600, 0.8537, 0.5936, 0.4966, 0.8998, 0.8216, 0.6449, 0.8180, 0.6602, 0.3420, 0.2897,
	0.3412, 0.5341, 0.7271, 0.3093, 0.8385, 0.5681, 0.3704, 0.7027, 0.5466, 0.4449, 0.6946, 0.6213, 0.7948, 0.9568, 0.5226, 0.8801, 0.1730,
	0.9797, 0.2714, 0.2523, 0.8757, 0.7373, 0.1365, 0.0118, 0.8939, 0.1991, 0.2987, 0.6614, 0.2844, 0.4692, 0.0648, 
	0.9883};
	
	
	//Determines the size of the vector
	const int SIZE = sizeof(values)/sizeof(values[0]);
	
	double returAvg = average(&values[0],SIZE);
	double returMin = minima(&values[0],SIZE);
	double returMax = maxima(&values[0],SIZE);
	double returVar = variance(&values[0],SIZE);
	
	printf("\n");
	
	printf("\nThe average value is: %f",returAvg);
	printf("\nThe minimal value is: %f",returMin);
	printf("\nThe maximum value is: %f",returMax);
	printf("\nThe variance value is: %f",returVar);
	
	printf("\nKlart...\n");
	
	return 0;
	
	
}


double average(double *dVec, int nVals){
	
	double avgSum = 0.0;
	int i=0;
	
	for(; i < nVals; i++){
		
		avgSum = avgSum + *dVec;
		*dVec++;
		
	}
	
	avgSum = avgSum / nVals;
	
	return avgSum;
	
}


double minima(double *dVec, int nVals){
	
	double minimalVal = *dVec;
	int i=0;
	
	for(; i < (nVals-1); i++){
		
		if(minimalVal > *(dVec+1)){
			
			minimalVal = *(dVec+1);
			
		}
		
		*dVec++;
		
	}
	
	return minimalVal;
	
}


double maxima(double *dVec, int nVals){
	
	double maxVal = *dVec;
	int i=0;
	
	for(; i < (nVals-1); i++){
		
		if(maxVal < *(dVec+1)){
			
			maxVal = *(dVec+1);
			
		}
		
		*dVec++;
		
	}
	
	return maxVal;
	
}


double variance(double *dVec, int nVals){
	
	if(nVals == 0) return -1.0;
	
	double avgSum = average(&dVec[0],nVals);
	double varSum = 0.0;
	int i=0;
	
	
	for(; i < nVals; i++){
		
		varSum = varSum + ((*dVec - avgSum)*(*dVec - avgSum));
		*dVec++;
		
	}
	
	varSum = varSum / nVals;
	
	return varSum;
	
}