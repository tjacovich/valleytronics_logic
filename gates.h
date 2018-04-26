#ifndef GATES_H
#define GATES_H
#include<stdlib.h>
#include<stdio.h>
#include<vector>

typedef std::vector<double> valley_volt;

class c_valley
{
  public:	
  	c_valley();
  	~c_valley();
  	valley_volt vnot(double V_G1, double V_S);
  	void* vand();
  	valley_volt vnand(double V_G1, double V_G2, double VS, double V_ref);
  	valley_volt vor(double V_G1, double V_G2, double VS, double V_ref);
  	void* vxor();
  	void* vxnor();
};


#endif //GATES_H
