#include<stdlib.h>
#include <iostream>
#include <vector>
#include "gates.h"
#include "logic.h"

typedef std::vector<double> valley_volt;

c_vlogic 
{
  public:
   c_vlogic();  
   ~c_vlogic();
   valley_volt vnand_half_adder(double V1, double V2);
}

