#include<stdlib.h>
#include<stdio.h>
#include<vector>

#include"gates.h"

typedef std::vector<double> valley_volt;

class c_valley
{
  public:
	
  c_valley();
  ~c_valley();
  double vnot(double V_G1, double V_S);
  void* c_valley :: vand();
  valley_volt vnand(double V_G1, double V_G2, double V_S, double V_ref);
  void* vor();
  void* vxor();
  void* vxnor();
}

extern c_valley;
