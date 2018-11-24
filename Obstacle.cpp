#include "header.h"
std::vector<double> Obstacle::normer(double x, double y, double z)
{
  double norme = sqrt(x*x + y*y + z*z);
  std::vector<double> res;
  res.push_back(x / norme);
  res.push_back(y / norme);
  res.push_back(z / norme);
  return res;
}
