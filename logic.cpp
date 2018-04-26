#include<stdlib.h>
#include <iostream>
#include <vector>

#include "logic.h"
#include "gates.h"
#include "parameters.h"

/*These are all the available higher order logic functions.
 * currently, they cover integer arithmetic and some bitwise operations
 * but are currently being hindered by the difficulty of implementing a 
 * flip-flop that respects the valley polarization when holding a polarized
 * bit*/

//defines the valley current type
typedef std::vector<double> valley_volt;

c_vlogic :: c_vlogic(){}

c_vlogic :: ~c_vlogic(){}

//allows access to logic gates class
c_valley valley;

//2b  half adder
valley_volt c_vlogic :: vnand_half_adder(double V1, double V2)
{
  valley_volt S4(2);
  S4 = valley.vnand(V1, V2, Vref_, V_S);
  double temp = S4[0];
  
  valley_volt S1(2);
  S1 = valley.vnand(V1, temp, Vref_, V_S);
  double temp1 = S1[0];
  
  valley_volt S2(2);
  S2  = valley.vnand(V2, temp, Vref_, V_S);
  double temp2 = S2[0];
  
  valley_volt S(2);
  S = valley.vnand(temp1, temp2, Vref_, V_S);
  
  valley_volt C(2);
  
  C = valley.vnand(temp, temp, Vref_, V_S);  
  
  for(int i = 0; i<2; i++) S.insert(S.end(),C[i]);
  
  return S;
}

//2b full adder
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
  Vcarry = valley.vor(C1, C2, Vref_, V_S);
  
  valley_volt Vreturn(3);
  
  Vreturn[0] = Vfull[0];
  Vreturn[1] = Vhalf[1];
  Vreturn[2] = Vcarry[0];
  
  return Vreturn; 
}

//8bit adder currently, but could be easily converted to Nb as calls 
//depend on arch_, but the reverse check is currently 8b only.
valley_volt c_vlogic :: vnand_8bit_adder(valley_volt N1, valley_volt N2)
{
  if(N1.size()!=2*arch_)
   {
     std::cout<<"Invalid number format N1. Should be valley "<<arch_<<"b";
     exit(EXIT_FAILURE);
   }
  
  if(N2.size()!=2*arch_)
   {
     std::cout<<"Invalid number format N2. Should be valley "<<arch_<<"b";
     exit(EXIT_FAILURE);
   }

  double temp;
  double temp1;
  double temp2;

  temp = N1[2*arch_-2];
  temp1 = N2[2*arch_-2];

  valley_volt Vhalf(4);
  Vhalf = vnand_half_adder(temp, temp1);
  temp2 = Vhalf[2];
  valley_volt Cout(arch_);
  Cout[arch_-1] = temp2; 
  valley_volt Nout(2*arch_);
  
  Nout[2*arch_-2] = Vhalf[0];
  Nout[2*arch_-1] = Vhalf[1];

  for(int i = 0; i< arch_-1; i++)
  {
    temp = N1[2*arch_-4-2*i];
    temp1 = N2[2*arch_-4-2*i];

    valley_volt Vfull(3);
    
    Vfull = vnand_full_adder(temp, temp1, temp2);
    
    temp2 = Vfull[2];
    Cout[arch_-2-i]=temp2;
    Nout[2*arch_-4-2*i] = Vfull[0];
    Nout[2*arch_-3-2*i] = Vfull[1];
  }

 for(int i = 0; i< arch_; i++) Nout.insert(Nout.end(),Cout[i]); 

 return Nout;
}

valley_volt c_vlogic :: VSR_nand_latch(double R, double S, valley_volt Q, valley_volt Qbar)
{
  valley_volt vout(4); 
  valley_volt v1(2);
  valley_volt v2(2);
 
  double temp = Q[0];
  double temp1 = Qbar[0];

  v1 = valley.vnand(temp, R, temp, temp);
  v2 = valley.vnand(temp1, S, temp1, temp1);

  return vout;
}
