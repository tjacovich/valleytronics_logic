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
