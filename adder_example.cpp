#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define V_ref = 10

#include "logic.h"
#include "gates.h"
#define arch_ = 8
typedef std::vector<double> valley_volt;
typedef std::vector<double> input_val;

int main()
{
  // input_val n1(arch_) = 1;
  // input_val n2(arch_) = 0;
  int n1 = 1;
  int n2 = 0; 
  
  valley_volt inputs(2);
  
  inputs[0]=n1*V_ref;
  inputs[1]=n2*V_ref;
  
  valley_volt output(4) = c_vlogic.vnand_half_adder(inputs[0],inputs[1]);

  for(int i=0; i<4, i++) cout<<output[i]; 

  return 0;

}
