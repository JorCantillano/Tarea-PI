#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>


double calcularPi(int UT){
	//UT: Unidad de trabajo
	int count=50*UT;
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
}

int main(){
	double countt=calcularPi(10000);
	
	std:: cout<< std::setprecision(15)<<(4*countt) << std::endl;
	return 0;

}


