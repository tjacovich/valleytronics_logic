#ifndef NUM_OPS_H_
#define NUM_OPS_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>


typedef std::vector<double> valley_volt;
typedef std::vector<double> dec_ray;

class c_num_ops
{
  public:
  c_num_ops();
  ~c_num_ops();

  double bin_to_dec(valley_volt N1);
  dec_ray recover_input(valley_volt Nout);
};

#endif //NUM_OPS_H_
