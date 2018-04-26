#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#include "gates.h"
#include "logic.h"

#define Vref_ 10.
#define arch_ 8

typedef std::vector<double> valley_volt;
typedef std::vector<double> input_val;

c_vlogic vlogic;

int main()
{

  // input_val n1(arch_) = 1;
  // input_val n2(arch_) = 0;
  double n1 = 0;
  double n2 = 0; 
  
  valley_volt inputs(2);
  double inputs0 = n1*10;
  double inputs1 = n2*10; 
  
  valley_volt output(4);
  output = vlogic.vnand_half_adder(inputs0,inputs1);

  for(int i=0; i<2; i++) std::cout<<output[i]<<"\n"; 
  for(int j=2; j<4; j++) std::cout<<output[j]<<"\n"; 
  return 0;
}
