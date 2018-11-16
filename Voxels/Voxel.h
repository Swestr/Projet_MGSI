  #include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>
class Voxel
{
  public:
    //La translation
    std::vector<double> translation;
    //Les dimensions
    std::vector<double> scale;
    //vecteur directeur dans le voxel
    std::vector<double> vecDir;

    Voxel(std::vector<double> trans, std::vector<double> sca, std::vector<double> vdir)
    {
      translation = trans;
      scale = sca;
      vecDir = vdir;
    }

    std::vector<double> getVec()
    {
      return vecDir;
    }

    bool dedans(float x, float y, float z)
    {
    float newX = x, newY = y, newZ = z;

    //On effectue la translation

    newX -= translation[0];
    newY -= translation[1];
    newZ -= translation[2];

    //Puis le scale

    newX -= scale[0];
    newY -= scale[1];
    newZ -= scale[2];

    return (x >= 0) && (x <= 1) && (y >= 0) && (y <= 1) && (z >= 0) && (z <= 1);

    }
};
