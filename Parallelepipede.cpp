#include "header.h"

Parallelepipede::Parallelepipede(std::vector<double> t, std::vector<double> r, std::vector<double> s)
{
  translate = t;
  rotation = r;
  scale = s;
}

std::vector<double> Parallelepipede::getTangente(std::vector<double> part, std::vector<double> I)
{
  std::vector<double> normales[6];
  double valeur[6];

  for (int i = 0; i < 6; i++) {
    normales[i] = getNormales(i);
    // printf("normale[%d] : (%f, %f, %f)\n", i, normales[i][0], normales[i][1], normales[i][2]);
    // normales[i] = normer(normales[i][0], normales[i][1], normales[i][2]);
  }
  for (int i = 0; i < 6; i++) {
    valeur[i] = abs(part[0] * normales[i][0] + part[1] * normales[i][1] + part[2] * normales[i][2] + normales[i][3]);
    printf("%d : %f,\t %f\n", i, valeur[i], part[0] * normales[i][0] + part[1] * normales[i][1] + part[2] * normales[i][2]);
  }

  int indice = 0;
  double value = valeur[0];
  for (int i = 1; i < 6; i++) {
    if(value > valeur[i])
    {
      value = valeur[i];
      indice = i;
    }
  }

  printf("indice : %d\n",indice);

  std::vector<double> N = normales[indice];

  N = normer(N[0], N[1], N[2]);
  I = normer(I[0], I[1], I[2]);

  //R⃗=2(N⃗ .⃗I)N⃗ +⃗I
  std::vector<double> R;
  double NI = N[0]*I[0] + N[1]*I[1] + N[2]*I[2];
  R.push_back(2 * (NI) * N[0] + I[0]);
  R.push_back(2 * (NI) * N[1] + I[1]);
  R.push_back(2 * (NI) * N[2] + I[2]);

  //T⃗=⃗R−(⃗R. N⃗ )N
  double RN = N[0]*R[0] + N[1]*R[1] + N[2]*R[2];
  std::vector<double> T;
  T.push_back(R[0] - RN * N[0]);
  T.push_back(R[1] - RN * N[1]);
  T.push_back(R[2] - RN * N[2]);

  // printf("N : (%f, %f, %f)\n", N[0], N[1], N[2]);
  // printf("T : (%f, %f, %f)\n", T[0], T[1], T[2]);
  // printf("part : (%f, %f, %f)\n", part[0], part[1], part[2]);

  return T;
}

std::vector<double> Parallelepipede::getNormales(int indice)
{
  std::vector<double> normales[6];
  std::vector<double> point[6];
  normales[0].push_back(0);   normales[0].push_back(1);   normales[0].push_back(0);
  normales[1].push_back(0);   normales[1].push_back(-1);  normales[1].push_back(0);
  normales[2].push_back(1);   normales[2].push_back(0);   normales[2].push_back(0);
  normales[3].push_back(-1);  normales[3].push_back(0);   normales[3].push_back(0);
  normales[4].push_back(0);   normales[4].push_back(0);   normales[4].push_back(1);
  normales[5].push_back(0);   normales[5].push_back(0);   normales[5].push_back(-1);
  point[0].push_back(0);      point[0].push_back(-0.5);   point[0].push_back(0);
  point[1].push_back(0);      point[1].push_back(0.5);    point[1].push_back(0);
  point[2].push_back(-0.5);   point[2].push_back(0);      point[2].push_back(0);
  point[3].push_back(0.5);    point[3].push_back(0);      point[3].push_back(0);
  point[4].push_back(0);      point[4].push_back(0);      point[4].push_back(-0.5);
  point[5].push_back(0);      point[5].push_back(0);      point[5].push_back(0.5);

  double x, y, z;

  point[indice][0] += translate[0];
  point[indice][1] += translate[1];
  point[indice][2] += translate[2];

  point[indice][0] *= scale[0];
  point[indice][1] *= scale[1];
  point[indice][2] *= scale[2];

  normales[indice][0] *= scale[0];
  normales[indice][1] *= scale[1];
  normales[indice][2] *= scale[2];



  double rX = (rotation[0]) * (M_PI/180.);
  x = normales[indice][0];
  y = normales[indice][1];
  z = normales[indice][2];
  normales[indice][0] = x;
  normales[indice][1] = cos(rX)*y - sin(rX)*z;
  normales[indice][2] = sin(rX)*y + cos(rX)*z;
  x = point[indice][0];
  y = point[indice][1];
  z = point[indice][2];
  point[indice][0] = x;
  point[indice][1] = cos(rX)*y - sin(rX)*z;
  point[indice][2] = sin(rX)*y + cos(rX)*z;

  double rY = (rotation[1]) * (M_PI/180.);
  x = normales[indice][0];
  y = normales[indice][1];
  z = normales[indice][2];
  normales[indice][0] = cos(rY)*x + sin(rY)*z;
  normales[indice][1] = y;
  normales[indice][2] = -sin(rY)*x + cos(rY)*z;
  x = point[indice][0];
  y = point[indice][1];
  z = point[indice][2];
  point[indice][0] = cos(rY)*x + sin(rY)*z;
  point[indice][1] = y;
  point[indice][2] = -sin(rY)*x + cos(rY)*z;

  double rZ = (rotation[2]) * (M_PI/180.);
  x = normales[indice][0];
  y = normales[indice][1];
  z = normales[indice][2];
  normales[indice][0] = cos(rZ)*x - sin(rZ)*y;
  normales[indice][1] = sin(rZ)*x + cos(rZ)*y;
  normales[indice][2] = z;
  x = point[indice][0];
  y = point[indice][1];
  z = point[indice][2];
  point[indice][0] = cos(rZ)*x - sin(rZ)*y;
  point[indice][1] = sin(rZ)*x + cos(rZ)*y;
  point[indice][2] = z;

  // normales[indice][0] += translate[0];
  // normales[indice][1] += translate[1];
  // normales[indice][2] += translate[2];

  double a = normales[indice][0];
  double b = normales[indice][1];
  double c = normales[indice][2];
  x = point[indice][0];
  y = point[indice][1];
  z = point[indice][2];


  normales[indice].push_back(-(a*x+b*y+c*z));
  return normales[indice];
}

bool Parallelepipede::dedans(float x, float y, float z)
{
  return rotateX(x, y, z);
}
bool Parallelepipede::rotateX(float x, float y, float z)
{
  double rX = (-rotation[0]) * (M_PI/180.);
  return rotateY(x, cos(rX)*y - sin(rX)*z, sin(rX)*y + cos(rX)*z);
}
bool Parallelepipede::rotateY(float x, float y, float z)
{
  double rY = (-rotation[1]) * (M_PI/180.);
  return rotateZ(cos(rY)*x + sin(rY)*z, y, -sin(rY)*x + cos(rY)*z);
}
bool Parallelepipede::rotateZ(float x, float y, float z)
{
  double rZ = (-rotation[2]) * (M_PI/180.);
  return scaling(cos(rZ)*x - sin(rZ)*y, sin(rZ)*x + cos(rZ)*y, z);
}
bool Parallelepipede::scaling(float x, float y, float z)
{
  return translating(x/scale[0], y/scale[1], z/scale[2]);
}
bool Parallelepipede::translating(float x, float y, float z)
{
  return unitaire(x-translate[0], y-translate[1], z-translate[2]);
}
bool Parallelepipede::unitaire(float x, float y, float z)
{
  return (-0.5<=x) && (x<=0.5) && (-0.5<=y) && (y<=0.5) && (-0.5<=z) && (z<=0.5);
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
