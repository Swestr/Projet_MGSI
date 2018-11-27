#include "header.h"

Parallelepipede::Parallelepipede(std::vector<double> c, std::vector<double> r, double lon, double larg, double h)
{
  centre = c;
  rotation = r;
  longueur = lon;
  largeur = larg;
  hauteur = h;
}

std::vector<double> Parallelepipede::getTangente(std::vector<double> part, std::vector<double> I)
{
  std::vector<double> v{0, 1, 0};
  return v;
}

bool Parallelepipede::dedans_noRotate(float x, float y, float z)
{
  //Sans rotation :
  float minX = centre[0] - (longueur / 2.);
  float maxX = centre[0] + (longueur / 2.);
  float minY = centre[1] - (hauteur / 2.);
  float maxY = centre[1] + (hauteur / 2.);
  float minZ = centre[2] - (largeur / 2.);
  float maxZ = centre[2] + (largeur / 2.);


  return (minX <= x) && (x <= maxX) && (minY <= y) && (y <= maxY) && (minZ <= z) && (z <= maxZ);
}

bool Parallelepipede::dedans(float x, float y, float z)
{
  return dedans_noRotate(
    x + x*cos(rotation[1]) + z*sin(rotation[1]) + x*cos(rotation[2]) - y*sin(rotation[2]),
    y*cos(rotation[0]) - z*sin(rotation[0]) + y + x*sin(rotation[2]) + y*cos(rotation[2]),
    y*sin(rotation[0]) + z*cos(rotation[0]) - x*sin(rotation[1]) + z*cos(rotation[1]) + z
  );
}

void Parallelepipede::draw(float r, float g, float b)
{
  glPushMatrix();
    glTranslatef(centre[0], centre[1], centre[2]);
    glRotatef(rotation[0], 1, 0, 0);
    glRotatef(rotation[1], 0, 1, 0);
    glRotatef(rotation[2], 0, 0, 1);
    glScalef(longueur, hauteur, largeur);
    glColor3f(r, g, b);
      glutSolidCube(1);
    glEnd();
  glPopMatrix();
}
