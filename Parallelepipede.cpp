#include "header.h"

Parallelepipede::Parallelepipede(std::vector<double> t, std::vector<double> r, std::vector<double> s)
{
  translate = t;
  rotation = r;
  scale = s;
}

std::vector<double> Parallelepipede::getTangente(std::vector<double> part, std::vector<double> I)
{
  std::vector<double> v{0, 1, 0};
  return v;
}

bool Parallelepipede::dedans(float x, float y, float z)
{
  return rotate(x, y, z);
}

bool Parallelepipede::rotate(float x, float y, float z)
{
  //Conversion des angles inverse en radians
  double rX = (-rotation[0]) * (double)(M_PI/180.);
  double rY = (-rotation[1]) * (double)(M_PI/180.);
  double rZ = (-rotation[2]) * (double)(M_PI/180.);

  std::vector<double> rotX;
  rotX.push_back(x);
  rotX.push_back(cos(rX)*y - sin(rX)*z);
  rotX.push_back(sin(rX)*y + cos(rX)*z);
  printf("rotX : (%f, %f, %f)\n", rotX[0], rotX[1], rotX[2]);

  std::vector<double> rotY;
  rotY.push_back(cos(rY)*x + sin(rY)*z);
  rotY.push_back(y);
  rotY.push_back(-sin(rY)*x + cos(rY)*z);
  printf("rotY : (%f, %f, %f)\n", rotY[0], rotY[1], rotY[2]);

  std::vector<double> rotZ;
  rotZ.push_back(cos(rZ)*x - sin(rZ)*y);
  rotZ.push_back(sin(rZ)*x + cos(rZ)*y);
  rotZ.push_back(z);
  printf("rotZ : (%f, %f, %f)\n", rotZ[0], rotZ[1], rotZ[2]);

  double newX = (rotX[0] + rotY[0] + rotZ[0]) / 3.;
  double newY = (rotX[1] + rotY[1] + rotZ[1]) / 3.;
  double newZ = (rotX[2] + rotY[2] + rotZ[2]) / 3.;

  printf("Anciennes coord : (%f, %f, %f)\n", x, y, z);
  printf("Nouvelles coord : (%f, %f, %f)\n\n", newX, newY, newZ);

  return translating(
          x + x*cos(-rotation[y]) + z*sin(-rotation[y]) + x*cos(-rotation[z]) - y*sin(-rotation[z]),
          y*cos(-rotation[x]) - z*sin(-rotation[x]) + y + x*sin(-rotation[z]) + y*cos(-rotation[z]),
          y*sin(-rotation[x]) + z*cos(-rotation[x]) - x*sin(-rotation[y]) + z*cos(-rotation[y]) + z
        );


  // return translating(newX, newY, newZ);
}

bool Parallelepipede::translating(float x, float y, float z)
{
  return scaling(x-translate[0], y-translate[1], z-translate[2]);
}

bool Parallelepipede::scaling(float x, float y, float z)
{
  return unitaire(x/scale[0], y/scale[1], z/scale[2]);
}

bool Parallelepipede::unitaire(float x, float y, float z)
{
  return (0<=x) && (x<=1) && (0<=y) && (y<=1) && (0<=z) && (z<=1);
}

void Parallelepipede::draw(float r, float g, float b)
{
  glPushMatrix();
    glRotatef(rotation[0], 1, 0, 0);
    glRotatef(rotation[1], 0, 1, 0);
    glRotatef(rotation[2], 0, 0, 1);
    glScalef(scale[0], scale[1], scale[2]);
    glTranslatef(translate[0], translate[1], translate[2]);
    glColor3f(r, g, b);
    glutSolidCube(1);
  glPopMatrix();
}
