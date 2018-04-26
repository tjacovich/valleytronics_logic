#ifndef LOGIC_H
#define LOGIC_H

#include<stdlib.h>
#include <iostream>
#include <vector>
#include "gates.h"

typedef std::vector<double> valley_volt;

class c_vlogic 
{
  public:
   c_vlogic();  
   ~c_vlogic();
   valley_volt vnand_half_adder(double V1, double V2);
   valley_volt vnand_full_adder(double V1, double V2, double V3);
};

#endif //LOGIC_H
