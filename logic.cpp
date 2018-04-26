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
  std::cout<<S4[0]<<"\n"; 
  
  valley_volt S1(2);
  S1 = valley.vnand(V1, temp, V_ref, V_S);
  std::cout<<S1[0]<<"\n";
  double temp1 =S1[0];
  
  valley_volt S2(2);
  S2  = valley.vnand(V2, temp, V_ref, V_S);
  std::cout<<S2[0]<<"\n";
  double temp2 =S2[0];
  
  valley_volt S(2);
  S = valley.vnand(temp1, temp2, V_ref, V_S);
  std::cout<<S[0]<<"\n";
  
  valley_volt C(2);
  C = valley.vnand(temp, temp, V_ref, V_S); 
  std::cout<<C[0]<<"\n";
  valley_volt out(4);
  
  for(int i=0; i<2; i++) out[i]=C[i];
  for(int i=0; i<2; i++) out[i+2]=S[i];

  return out;
}

