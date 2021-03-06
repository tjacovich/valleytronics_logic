#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

#include "gates.h"
#include "logic.h"
#include "number_ops.h"
#include "parameters.h"

//Defines vector objects in a safe and efficient way.
typedef std::vector<double> valley_volt;
typedef std::vector<double> dec_ray;

//variables to access all our logic circuits and valley gates.
c_vlogic vlogic;
c_valley valley_t;
c_num_ops n_ops;
int main(int argc, char *argv[])
{
  //initiation guard
  if(argc!= 3) 
  {
    std::cout<<"Need to 8b capable numbers to demonstrate.\n";
    exit(EXIT_FAILURE);
  }
  
  for(int t = 0; t<5; t++) std::cout<<"\n"; 
  std::cout<<"First we demonstrate a 2b Full adder\n";
  
  //Bit value setting
  double n1;
  double n2;
  double n3;
  
  std::cout<<"A | B | Cin | Cout | S | V \n";
  
  for(int i = 0; i < 2; i++)
  { 
    n1=i;
    for(int j = 0; j<2; j++)
    { 
      n2=j;
      for(int k = 0; k<2; k++)
      { 
	n3=k;
        //Converting to voltage levels
        double inputs0 = n1*Vref_;
        double inputs1 = n2*Vref_; 
        double inputs2 = n3*Vref_;
  
  	valley_volt fullout(3);//full_adder returns a 3 entry valley_vector
  
  	fullout = vlogic.vnand_full_adder(inputs0, inputs1, inputs2);
        std::cout<<n1<<" | "<<n2<<" |  "<<n3<<"  |  "<<fullout[2]/Vref_<<"   | "<<fullout[0]/Vref_<<" | "<<fullout[1]<<"\n"; 
      }
    }
  }  

  for(int t = 0; t<3; t++) std::cout<<"\n"; 
  std::cout<<"And the half-adder\n";
  
  std::cout<<"A | B | C | S | V \n";
  
  for(int i = 0; i < 2; i++)
  { 
    n1=i;
    for(int j = 0; j<2; j++)
    { 
      n2=j;
        //Converting to voltage levels
        double inputs0 = n1*Vref_;
        double inputs1 = n2*Vref_; 
  
  	valley_volt fullout(3);//full_adder returns a 3 entry valley_vector
  
  	fullout = vlogic.vnand_half_adder(inputs0, inputs1);
        std::cout<<n1<<" | "<<n2<<" | "<<fullout[2]/Vref_<<" | "<<fullout[0]/Vref_<<" | "<<fullout[1]<<"\n"; 
      }
  }  
  std::cout<<"\n";
  std::cout<<"\n Now we perform a Full 8b add of your specified numbers and reverse it\n";
    
  valley_volt N1(2*arch_);//Vector for Binary A
  valley_volt N2(2*arch_);//Vector for Binary B
  valley_volt Nout(3*arch_);//Return Vector, needs 8b for C_out to maintain reversibility
 
  //Set Valley Polarization to the Null state 
  for(int i = 0; i<arch_; i++)
  {
    N1[2*i+1]=0;
    N2[2*i+1]=0;
  }
  
  //read in arguments from command line
  int in1 = atoi(argv[1]);
  int in2 = atoi(argv[2]);
  
  //converting args to binary
  for(int i = 0; i<arch_; i++)
  {
    int bin=in1%2;	  
    in1/=2;	  
    N1[14-2*i] = Vref_ * (double) bin;
    
    bin=in2%2;
    in2/=2;
    N2[14-2*i] = Vref_ * (double) bin;
  }
  
  //writing binary and dec numbers to std out
  std::cout<<"N1   "; 
  for(int i = 0; i<8; i++) std::cout<<N1[2*i]/10<<" ";
  std::cout<<argv[1];
  std::cout<<"\n";

  std::cout<<"N2   "; 
  for(int i = 0; i<8; i++) std::cout<<N2[2*i]/10<<" ";
  std::cout<<argv[2];
  std::cout<<"\n";

  //24 entry output of the sum, the valley polarization and the carry bits
  Nout = vlogic.vnand_8bit_adder(N1, N2);
  
  //dec version Nout
  double nout = 0;

  //binary to dec conversion
  for(int i = 0; i<8; i++)
  {	  
    double temp =Nout[2*i];
    nout += temp*pow(2,7-i)/Vref_;  
  }

  //writing Nout to std out
  std::cout<<"Nout "; 
  for(int i = 0; i<8; i++) std::cout<<Nout[2*i]/Vref_<<" ";
  std::cout<<nout;
  std::cout<<"\n";

  std::cout<<"Cout "; 
  for(int i = 0; i<8; i++) std::cout<<Nout[2*arch_+i]/Vref_<<" ";
  std::cout<<"\n";
  std::cout<<"Sout "; 
  for(int i = 0; i<8; i++) std::cout<<Nout[2*i+1]<<" ";
  std::cout<<"\n";

  std::cout<<" \n";

  std::cout<<"Now to verify the calculation is reversible.\n";

  dec_ray ori(2);
  ori = n_ops.recover_input(Nout);
  
  std::cout<<"A = "<<ori[0]<<" and B = "<<ori[1]<<"\n";

  return 0;

}
