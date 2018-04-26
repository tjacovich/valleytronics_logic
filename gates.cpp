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

valley_volt c_valley :: vor(double V_G1, double V_G2, double V_S, double V_ref)
{
  valley_volt Vout(2);
  valley_volt Vt;
  Vt = vnot(V_G1,V_S);
  double Vtest = V_G2-V_ref;
  if(Vt[0]==0)
   {
     Vout[0]=10;
     if(Vtest==0) Vout[1]=0;
     else Vout[1]=-1;
   }

  else 
  {
    if(Vtest==0)
    {
      Vout[0]=10;
      Vout[1]=1;
    }
    else
    {
      Vout[0]=0;
      Vout[1]=0;
    }
  }
  return Vout;
}

valley_volt c_valley :: vxor(double V_G1, double V_G2, double V_S, double V_ref)
{
  valley_volt v1(2);
  v1 = vnand(V_G1, V_G2, V_S, V_ref);
  double temp = v1[0];
  
  valley_volt v2(2);
  valley_volt v3(2);
  v2 = vnand(V_G1,temp,V_S,V_ref); 
  v3 = vnand(temp,V_G2,V_S,V_ref);
  double temp1 = v2[0];
  double temp2 = v3[0];

  valley_volt Vout(2);
  Vout = vnand(temp1,temp2,V_S,V_ref);
  return Vout;
}

c_valley :: ~c_valley(){}


