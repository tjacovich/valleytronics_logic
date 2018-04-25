#include<stdlib.h>
#include<stdio.h>

c_valley :: c_valley()
{
  V_G1 = 0;
  V_G2 = 0;
  V_S = 0;
  V_in = 0;
  V_out= 0;
}

void* c_valley :: vnot(double V_in, double V_S, double V_G2, double V_out)
{
  if(V_in!=0) V_out = 0;

  else V_out = V_S;
}

void* c_valley :: vand()
{

}

void* c_valley :: vnand()
{

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


