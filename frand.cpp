#include "header.h"

double frand(double dmin, double dmax)
{
  double f = (double)rand() / RAND_MAX;
  return dmin + f * (dmax - dmin);
}
