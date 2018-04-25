#include<stdlib.h>
#include <iostream>
#include <vector>

#define V_ref = 10
#define V_S = 10

#include "gates.h"
#include "logic.h"

typedef std::vector<double> valley_volt;

c_vlogic :: c_vlogic()
{
  
}


valley_volt c_vlogic :: vnand_half_adder(double V1, double V2)
{
  valley_volt S4(2) = c_valley.vnand(V1, V2, V_ref, V_S);
  valley_volt S1(2) = c_valley.vnand(V1, S4[0], V_ref, V_S);
  valley_volt S2(2) = c_valley.vnand(V2, S4[0], V_ref, V_S);
  valley_volt S(2) = c_valley.vnand(S1[0], S2[0], V_ref, V_S);
  valley_volt C(2) = c_valley.vnand(S4[0], S4[0], V_ref, V_S); 

  valley_volt out(4);
  for(i=0; i<2; i++) out[i]=S[i];
  for(i=0; i<2; i++) out[i+2]=C[i];

  return out;
}

