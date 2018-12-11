#include "header.h"

Sphere::Sphere(std::vector<double> c, double r)
{
  centre = c;
  rayon = r;
}
std::vector<double> Sphere::getTangente(std::vector<double> particule, std::vector<double> I)
{
  // I[0] *= 1000;
  // I[1] *= 1000;
  // I[2] *= 1000;

  I = normer(I[0], I[1], I[2]);

  double a  = centre[0] - particule[0];
  double b  = centre[1] - particule[1];
  double c  = centre[2] - particule[2];

  std::vector<double> N = normer(a, b, c);

  // double d = -(N[0] * particule[0] + N[1] * particule[1] + N[2] * particule[2]);
  // N.push_back(d);

  //R⃗=2(N⃗ .⃗I)N⃗ +⃗I
  std::vector<double> R;
  double NI = N[0]*I[0] + N[1]*I[1] + N[2]*I[2];
  R.push_back(2 * (NI) * N[0] + I[0]);
  R.push_back(2 * (NI) * N[1] + I[1]);
  R.push_back(2 * (NI) * N[2] + I[2]);

  //R = normer(R[0], R[1], R[2]);

  //T⃗=⃗R−(⃗R. N⃗ )N
  double RN = N[0]*R[0] + N[1]*R[1] + N[2]*R[2];
  std::vector<double> T;
  T.push_back(R[0] - RN * N[0]);
  T.push_back(R[1] - RN * N[1]);
  T.push_back(R[2] - RN * N[2]);

  return T;//normer(T[0], T[1], T[2]);
}
bool Sphere::dedans(float x, float y, float z)
{
  double newX = x - centre[0];
  double newY = y - centre[1];
  double newZ = z - centre[2];
  return (newX*newX + newY*newY + newZ*newZ - rayon*rayon <= 0);
}
void Sphere::draw(float r, float g, float b)
{
  glPushMatrix();
    glTranslatef(centre[0], centre[1], centre[2]);
    glColor3f(r, g, b);
      glutSolidSphere(rayon, 30, 30);
    glEnd();
  glPopMatrix();
}
