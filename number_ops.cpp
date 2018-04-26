#include <iostream>
#include <stdlib.h>
#include <math.h>

typedef std::vector<double> valley_volt;

c_num_ops :: c_num_ops(){}

c_num_ops :: ~c_num_ops(){}

double c_num_ops :: bin_to_dec(valley_volt N1)
{
  for(int i = 0; i<7; i++)
  {
    double nout;
    double temp = Nout[2*i]/10;
    nout += temp*pow(2, 7-i);
    return nout;
  }
}

double c_num_ops :: recover_input(valley_volt Nout)
{
  valley_volt n1(8);
  valley_volt n2(8);

  for(int j = 0; j < 8; j++)
  {
    if(Nout[2*i]==0)
    {
      if(Nout[2*i+1]==0)    
    }   

  }

}
