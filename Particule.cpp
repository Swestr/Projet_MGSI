#include "header.h"
#include <time.h>
#include <string>
#include <iostream>

using namespace std;


double frand(double dmin, double dmax)
{
  double f = (double)rand() / RAND_MAX;
  return dmin + f * (dmax - dmin);
}
Particule::Particule()
{
  vie = frand(0, 100);

  position.push_back(frand(0, 1));
  position.push_back(frand(0, 1));
  position.push_back(frand(0, 1));

  vitesse.push_back(frand(0, 100));
  vitesse.push_back(frand(0, 100));
  vitesse.push_back(frand(0, 100));

  //direction.push_back(frand(0, 100);
  //direction.push_back(frand(0, 100);
  //direction.push_back(frand(0, 100);
  masse = frand(0, 100);

  couleur.push_back(frand(0, 1));
  couleur.push_back(frand(0, 1));
  couleur.push_back(frand(0, 1));
  couleur.push_back(frand(0, 1));

  densite = frand(0, 100);
}
bool Particule::dedans(float x, float y, float z)
{
  return pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(0.05, 2) <= 0;
}
void Particule::print()
{
  cout << "hello";
  //cout << "Vie: " << vie << "\nVitesse: " << vitesse << "\nPosition: " << position << "\nMasse: " << masse << "\nRouge: " << couleur[0] << "\nVert: " << couleur[1] << "\nBleu: " << couleur[2] << "\nTrans: " << couleur[3] << "\nDensite: " << densite << "\n";
}
void Particule::draw()
{
    for (size_t i = 0; i < n; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        for(size_t k = 0; k < n ; k++)
        {
          float fi = (float)i / (float)n;
          float fj = (float)j / (float)n;
          float fk = (float)k / (float)n;
          if (dedans(fi - position[0], fj - position[1], fk - position[2]))
          {
            glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(fi, fj, fk);
            glutSolidCube(1.0/n);
            glPopMatrix();
          }
      }
    }
  }
}
