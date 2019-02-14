#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>

int main(){
	int count=50*20000;
	double sum = 0;
	for (int i = 0; i < count; ++i){
		if (i & 0x1)
		{
			sum += -1.0/(2*i+1);
		}
		else{
			sum += 1.0/(2*i+1);
		}
	
	}
	std:: cout<< std::setprecision(15)<<(4*sum) << std::endl;
}