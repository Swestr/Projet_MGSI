#include "header.h"

Vent::Vent(std::vector<double> pt1, std::vector<double> pt2, std::vector<double> vdir, double speed)
{
  point1 = pt1;
  point2 = pt2;
  vecDir = vdir;
  vitesse = speed;
}
std::vector<double> Vent::getVec()
{
  return vecDir;
}
double Vent::getVitesse()
{
  return vitesse;
}
bool Vent::dedans(float x, float y, float z)
{

  double minX = min(point1[0], point2[0]);
  double maxX = max(point1[0], point2[0]);

  double minY = min(point1[1], point2[1]);
  double maxY = max(point1[1], point2[1]);

  double minZ = min(point1[2], point2[2]);
  double maxZ = max(point1[2], point2[2]);

  return (minX <= x) && (x <= maxX) && (minY <= y) && (y <= maxY) && (minZ <= z) && (z <= maxZ);
}
double Vent::max(double i, double j)
{
  return i < j ? j : i;
}
double Vent::min(double i, double j)
{
  return i > j ? j : i;
}
void Vent::draw(float r, float g, float b)
{
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
