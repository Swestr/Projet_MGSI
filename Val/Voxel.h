#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>
class Voxel
{
  public:
    //un voxel est un cube donc on a seulement besoin de sa taille
    float size;
    //vecteur directeur dans le voxel
    std::vector<double> v;
    Voxel(float s, double x, double y, double z)
    {
      size = s;
      v.push_back(x);
      v.push_back(y);
      v.push_back(z);
    }

    std::vector<double> getVec()
    {
      return v;
    }
    bool dedans(float x, float y, float z)
    {
      return (x >= 0) && (x <= size) && (y >= 0) && (y <= size) && (z >= 0) && (z <= size);
    }
};
