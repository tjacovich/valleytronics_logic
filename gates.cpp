#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include"gates.h"

typedef std::vector<double> valley_volt;

c_valley :: c_valley(){}

valley_volt c_valley :: vnot(double V_G1, double V_S)
{
  valley_volt V_out(2);

  if(V_G1!=0) 
   {
     V_out[0]=0;
     V_out[1]=0;
     return V_out;
   }

  else 
  { 
    V_out[0] = V_S;
    V_out[1] = 1;
    return V_out;
  }
}

void* c_valley :: vand()
{

}

valley_volt c_valley :: vnand(double V_G1, double V_G2, double V_S, double V_ref)
{
  
  valley_volt V_out(2);
  valley_volt  V_t(2); 
  V_t = vnot(V_G1, V_S);
  double V_test = V_t[0]-V_ref;

  if(V_test!=0)
    {
      if(V_G2>0) 
      {
        V_out[0]=0;
	V_out[1]=0;
	return V_out;
      }
      else
      {
        V_out[0] = V_S;
	V_out[1] = -1;
      }
    }

  else
    {
       V_out[0] = V_S;

      if(V_G2==0) 
      { 
	V_out[1]=0;
        return V_out;
      }
      else V_out[1] = 1;
    }

  return V_out;
}

void* c_valley :: vor()
{

}

void* c_valley :: vxor()
{

}

void* c_valley :: vxnor()
{

}

c_valley :: ~c_valley(){}


