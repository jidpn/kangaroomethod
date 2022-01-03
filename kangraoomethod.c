#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void kangaroomethod(double);
void simplemethod(double);

double x[360];
double y[360];
double max_diff;
int main(){
	int i;
	for(i=0;i<360;i++){
		x[i] = sin(M_PI*i /180);
		y[i] = cos(M_PI*i /180);
	}
	for(i=0;i<359;i++){
		max_diff = max_diff > fabs(y[i]	-y[i+1]) ? max_diff:fabs(y[i]-y[i+1]);
	}
	max_diff = max_diff > fabs(y[359]	-y[0]) ? max_diff:fabs(y[359]-y[0]);
	simplemethod(0.5);
	kangaroomethod(0.5);
}

void simplemethod(double intersection){
	int i;
	int counter = 0;
	printf("simple method\n");
	for(i=0;i<359;i++){
		counter++;
		if((y[i] < intersection && y[i+1] > intersection) || ((y[i] > intersection && y[i+1] < intersection))){
			printf("%d\n",i);		 	
		}
	}
	if((y[359] < intersection && y[0] > intersection) || ((y[359] > intersection && y[0] < intersection))){
			printf("359\n");		 
	}
	printf("counter %d\n",counter);
}
void kangaroomethod(double intersection){
	int i;
	int jump;
	int counter = 0;
	printf("kangaroo method\n");
	for(i=0;i<359;){
		counter++;
		if((y[i] < intersection && y[i+1] > intersection) || ((y[i] > intersection && y[i+1] < intersection))){
			printf("%d\n",i);		 }	

		jump = ((double)((double)fabs(y[i] - intersection)) / (double)max_diff) -1;
		if(jump < 1){
			i++;
		}else{
			i+=jump;
		}
	}
	if((y[359] < intersection && y[0] > intersection) || ((y[359] > intersection && y[0] < intersection))){
			printf("359\n");		 
	}

	printf("counter %d\n",counter);
}
