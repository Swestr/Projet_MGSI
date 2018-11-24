#include "header.h"

Sphere::Sphere(std::vector<double> c, double r)
{
  centre = c;
  rayon = r;
}

std::vector<double> Sphere::getTangente(std::vector<double> part, std::vector<double> I) 
{
  double a  = centre[0] - part[0];
  double b  = centre[1] - part[1];
  double c  = centre[2] - part[2];

  std::vector<double> N = normer(a, b, c);

  // double d = -(N[0] * part[0] + N[1] * part[1] + N[2] * part[2]);
  // N.push_back(d);

  //R⃗=2(N⃗ .⃗I)N⃗ +⃗I
  std::vector<double> R;
  double NI = N[0]*I[0] + N[1]*I[1] + N[2]*I[2];
  R.push_back(2 * (NI) * N[0] + I[0]);
  R.push_back(2 * (NI) * N[1] + I[1]);
  R.push_back(2 * (NI) * N[2] + I[2]);

  //R⃗=(⃗R. N⃗ )N⃗ +(R⃗−( ⃗R.N⃗ )N⃗ )
  double RN = N[0]*R[0] + N[1]*R[1] + N[2]*R[2];
  R[0] = RN * N[0] + (R[0] - RN * N[0]);
  R[1] = RN * N[1] + (R[1] - RN * N[1]);
  R[2] = RN * N[2] + (R[2] - RN * N[2]);

  //T⃗=⃗R−(⃗R. N⃗ )N
  RN = N[0]*R[0] + N[1]*R[1] + N[2]*R[2];
  std::vector<double> T;
  T.push_back(R[0] - RN * N[0]);
  T.push_back(R[1] - RN * N[1]);
  T.push_back(R[2] - RN * N[2]);

  return T;
}

bool Sphere::dedans(float x, float y, float z)
{
  double newX = x - centre[0];
  double newY = y - centre[1];
  double newZ = z - centre[2];
  return (newX*newX + newY*newY + newZ*newZ - rayon*rayon <= 0);
}

void Sphere::draw(int r, int g, int b)
{
    glPushMatrix();
      glTranslatef(centre[0], centre[1], centre[2]);
      glColor3f(r, g, b);
        glutSolidSphere(rayon-0.05, 30, 30);
      glEnd();
    glPopMatrix();
  }

// double angle = -M_PI/2;
// double x = N[0] * cos(angle) - N[1] * sin(angle);
// double z = N[0] * sin(angle) - N[1] * cos(angle);
// double y = - (N[0] * x + N[2] * z + N[3]) / (N[1]+0.001);
//
// std::vector<double> p1;
// p1.push_back(x);
// p1.push_back(y);
// p1.push_back(z);
//
// std::vector<double> v1 = normer(p1[0] - partX, p1[1] - partY, p1[2] - partZ);
//
// glColor3f(1, 0, 0);
// glBegin(GL_LINES);
//   glVertex3f(partX, partY, partZ);
//   glVertex3f(v1[0] + partX, v1[1] + partY, v1[2] + partZ);
// glEnd();
// printf("p1 :\t(%.1f, %.1f, %.1f)\n", p1[0], p1[1], p1[2]);
// printf("v1 :\t(%.1f, %.1f, %.1f)\n", v1[0], v1[1], v1[2]);
// printf("part :\t (%.1f, %.1f, %.1f)\n", partX, partY, partZ);
// printf("v1-pa :\t(%.1f, %.1f, %.1f)\n", v1[0] + partX, v1[1] + partY, v1[2] + partZ);

// double minX = centre[0]-rayon;
// double maxX = centre[0]+rayon;
// double minY = centre[1]-rayon;
// double maxY = centre[1]+rayon;
// double minZ = centre[2]-rayon;
// double maxZ = centre[2]+rayon;
// return (minX <= x) && (x <= maxX) && (minY <= y) && (y <= maxY) && (minZ <= z) && (z <= maxZ);
