#include<stdlib.h>
#include <iostream>
#include <vector>

#include "logic.h"
#include "gates.h"

#define V_ref   10 
#define V_S   10 

typedef std::vector<double> valley_volt;

c_vlogic :: c_vlogic(){}

c_vlogic :: ~c_vlogic(){}

c_valley valley;


valley_volt c_vlogic :: vnand_half_adder(double V1, double V2)
{
  valley_volt S4(2);
  S4 = valley.vnand(V1, V2, V_ref, V_S);
  double temp = S4[0];
  
  valley_volt S1(2);
  S1 = valley.vnand(V1, temp, V_ref, V_S);
  double temp1 = S1[0];
  
  valley_volt S2(2);
  S2  = valley.vnand(V2, temp, V_ref, V_S);
  double temp2 = S2[0];
  
  valley_volt S(2);
  S = valley.vnand(temp1, temp2, V_ref, V_S);
  
  valley_volt C(2);
  
  C = valley.vnand(temp, temp, V_ref, V_S);  
  
  for(int i = 0; i<2; i++) S.insert(S.end(),C[i]);
  
  return S;
}



valley_volt c_vlogic :: vnand_full_adder(double V1, double V2, double V3)
{
  valley_volt Vhalf(4);

  Vhalf = vnand_half_adder(V1, V2);
  
  double S = Vhalf[0];
  double  C1 = Vhalf[2];

  valley_volt Vfull(4);  
  Vfull = vnand_half_adder(S, V3);
  double C2 = Vfull[2];
  
  valley_volt Vcarry(2);
  Vcarry = valley.vor(C1, C2, V_ref, V_S);
  
  valley_volt Vreturn(3);
  
  Vreturn[0] = Vfull[0];
  Vreturn[1] = Vhalf[1];
  Vreturn[2] = Vcarry[0];
  
  return Vreturn; 
}



valley_volt c_vlogic :: vnand_8bit_adder(valley_volt N1, valley_volt N2)
{
  if(N1.size()!=16)
   {
     std::cout<<"Invalid number format N1. Should be valley 8b.";
     exit(EXIT_FAILURE);
   }
  
  if(N2.size()!=16)
   {
     std::cout<<"Invalid number format N2. Should be valley 8b.";
     exit(EXIT_FAILURE);
   }

  double temp;
  double temp1;
  double temp2;

  temp = N1[14];
  temp1 = N2[14];

  valley_volt Vhalf(4);
  Vhalf = vnand_half_adder(temp, temp1);
  temp2 = Vhalf[2];
  valley_volt Cout(8);
  Cout[7] = temp2; 
  valley_volt Nout(16);
  
  Nout[14] = Vhalf[0];
  Nout[15] = Vhalf[1];

  for(int i = 0; i< 7; i++)
  {
    temp = N1[12-2*i];
    temp1 = N2[12-2*i];

    valley_volt Vfull(3);
    
    Vfull = vnand_full_adder(temp, temp1, temp2);
    
    temp2 = Vfull[2];
    Cout[6-i]=temp2;
    Nout[12-2*i] = Vfull[0];
    Nout[13-2*i] = Vfull[1];
  }

 for(int i = 0; i< 8; i++) Nout.insert(Nout.end(),Cout[i]); 

 return Nout;
}

valley_volt c_vlogic :: VSR_nand_latch(double R, double S, valley_volt Q, valley_volt Qbar)
{
  valley_volt vout(4); 
  valley_volt v1(2);
  valley_volt v2(2);
 
  temp = Q[0];
  temp1 = Qbar[0];

  v1 = valley.vnand(Qbar, R, temp, temp);
  v2 = valley.vnand(Q, S, temp1, temp1);

  return vout;
}
