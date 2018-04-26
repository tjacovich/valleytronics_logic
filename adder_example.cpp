#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

#include "gates.h"
#include "logic.h"

#define Vref_ 10.
#define arch_ 8

typedef std::vector<double> valley_volt;
typedef std::vector<double> input_val;

c_vlogic vlogic;
c_valley valley_t;
int main(int argc, char *argv[])
{
  if(argc!= 3) 
  {
    std::cout<<"Need to 8b capable numbers to demonstrate.\n";
    exit(EXIT_FAILURE);
  }

  // input_val n1(arch_) = 1;
  // input_val n2(arch_) = 0;
  
  double n1 = 1;
  double n2 = 0;
  double n3 = 0; 
  
  valley_volt inputs(2);
  double inputs0 = n1*10;
  double inputs1 = n2*10; 
  double inputs2 = n3*10;

  valley_volt fullout(3);
  fullout = vlogic.vnand_full_adder(inputs0, inputs1, inputs2);
  
  std::cout<<fullout[0]/10<<"  "<<fullout[2]/10<<"\n"; 
  std::cout<<fullout[1]<<"\n"; 
  
  valley_volt N1(16);
  valley_volt N2(16);
  valley_volt Nout(16);
  
  for(int i = 0; i<8; i++)
  {
    N1[2*i+1]=0;
    N2[2*i+1]=0;
  }

  int in1 = atoi(argv[1]);
  int in2 = atoi(argv[2]);

  for(int i = 0; i<8; i++)
  {
    int bin=in1%2;	  
    in1/=2;	  
    N1[14-2*i] = Vref_ * (double) bin;
    
    bin=in2%2;
    in2/=2;
    N2[14-2*i] = Vref_ * (double) bin;
  }
  
  std::cout<<"N1 "; 
  for(int i = 0; i<8; i++) std::cout<<N1[2*i]/10<<" ";
  std::cout<<"\n";

  std::cout<<"N2 "; 
  for(int i = 0; i<8; i++) std::cout<<N2[2*i]/10<<" ";
  std::cout<<"\n";

  Nout = vlogic.vnand_8bit_adder(N1, N2);
  
  double nout = 0;

  for(int i = 0; i<8; i++)
  {	  
    double temp =Nout[2*i];
    nout += temp*pow(2,7-i)/10;  
  }

  std::cout<<"Nout "; 
  for(int i = 0; i<8; i++) std::cout<<Nout[2*i]/10<<" ";
  std::cout<<"\n";
  std::cout<<"Sout "; 

  for(int i = 0; i<8; i++) std::cout<<Nout[2*i+1]<<" ";

  std::cout<<"\n";

  std::cout<<"Nout is "<<nout;
 
  std::cout<<"\n";  
  return 0;

}
