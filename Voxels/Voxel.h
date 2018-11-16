#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>
class Voxel
{
  public:
    //On a besoin de deux point les plus distants du parallepipède pour le tracer
    std::vector<double> point1;
    std::vector<double> point2;

    //Coefficient de vitesse du vent
    double vitesse;

    //vecteur directeur dans le voxel
    std::vector<double> vecDir;

    Voxel(std::vector<double> pt1, std::vector<double> pt2, std::vector<double> vdir, double speed)
    {
      point1 = pt1;
      point2 = pt2;
      vecDir = vdir;
      vitesse = speed;
    }

    std::vector<double> getVec()
    {
      return vecDir;
    }

    double getVitesse()
    {
      return vitesse;
    }

    bool dedans(float x, float y, float z)
    {

      double minX = min(point1[0], point2[0]);
      double maxX = max(point1[0], point2[0]);

      double minY = min(point1[1], point2[1]);
      double maxY = max(point1[1], point2[1]);

      double minZ = min(point1[2], point2[2]);
      double maxZ = max(point1[2], point2[2]);

      return (minX <= x) && (x <= maxX) && (minY <= y) && (y <= maxY) && (minZ <= z) && (z <= maxZ);
    }

    double max(double i, double j)
    {
      return i < j ? j : i;
    }
    double min(double i, double j)
    {
      return i > j ? j : i;
    }

    void draw(int r, int g, int b){
      double minX = min(point1[0], point2[0]);
      double maxX = max(point1[0], point2[0]);

      double minY = min(point1[1], point2[1]);
      double maxY = max(point1[1], point2[1]);

      glColor3f(r, g, b);
      glBegin(GL_QUADS);
        glVertex3f(minX, minY, 1);
        glVertex3f(maxX, minY, 1);
        glVertex3f(maxX, maxY, 1);
        glVertex3f(minX, maxY, 1);
      glEnd();
    }
};
