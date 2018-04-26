#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include"number_ops.h"

#define Vref_ 10

typedef std::vector<double> valley_volt;
typedef std::vector<double> dec_ray;

c_num_ops :: c_num_ops(){}

c_num_ops :: ~c_num_ops(){}

double c_num_ops :: bin_to_dec(valley_volt N1)
{
  double ntemp = 0;
  for(int i =0; i< 8; i++)
  {
    double tempn = N1[i];
    ntemp += tempn*pow(2,7-i);
  }
  return ntemp;
}

dec_ray c_num_ops :: recover_input(valley_volt Nout)
{
  valley_volt n1(8);
  valley_volt n2(8);
  valley_volt n3(8);

  //decoding the truth table of a full-adder and writing the original value back
  for(int j = 0; j < 8; j++)
  {
    double temp;
    temp = Nout[2*j]/Vref_+Nout[2*j+1]+Nout[16+j]/Vref_;
     
    if(temp == 0)
    {
      if(Nout[2*j]==0)
      {
        if(Nout[16+j]!=0)
	{
	  n1[j] = 0;
          n2[j] = 1;
          n3[j] = 1;
	}

        else
        {
          n1[j] = 0;
          n2[j] = 0;
          n3[j] = 0;
        }
      }
      
      else
      {
        n1[j] = 0;
        n2[j] = 1;
        n3[j] = 0;
      }
    }

    else if(temp==3)
    {
      n1[j] = 1;
      n2[j] = 1;
      n3[j] = 1;
    }

    else if(temp == 2)
    {
      if(Nout[2*j]!=0)
      {
        n1[j] = 1;
        n2[j] = 0;
        n3[j] = 0;
      }

      else 
      {
        n1[j] = 1;
        n2[j] = 0;
        n3[j] = 1;
      }

    }
   
    else if(temp == 1)
    {
      if(Nout[2*j]!=0)
      {
        n1[j] = 0;
        n2[j] = 0;
        n3[j] = 1;
      }

      else 
      {
        n1[j] = 1;
        n2[j] = 1;
        n3[j] = 0;
      }

    }

  }
  std::cout<<"\nN1 = ";
  for(int i = 0; i < 8; i++)std::cout<<n1[i];
  std::cout<<"\n"; 
  
  std::cout<<"\nN2 = ";
  for(int i = 0; i < 8; i++)std::cout<<n2[i];
  std::cout<<"\n"; 
  
  dec_ray ori(2); 
  ori[0] = bin_to_dec(n1);
  ori[1] = bin_to_dec(n2);
  return ori;
}
