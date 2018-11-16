#include "../header.h"
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
  position.push_back(frand(0, 0.1));
  position.push_back(frand(0, 1));

  vitesse.push_back(frand(15, 50));
  vitesse.push_back(frand(15, 50));
  vitesse.push_back(frand(15, 50));

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
void Particule::print()
{
  cout << "hello";
  //cout << "Vie: " << vie << "\nVitesse: " << vitesse << "\nPosition: " << position << "\nMasse: " << masse << "\nRouge: " << couleur[0] << "\nVert: " << couleur[1] << "\nBleu: " << couleur[2] << "\nTrans: " << couleur[3] << "\nDensite: " << densite << "\n";
}
void Particule::draw()
{
  glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(position[0], position[1], position[2]);
    glutSolidCube(1.0/(n*4));
  glPopMatrix();

}
void Particule::move(std::vector<double> vect_dir, double speedCoeff)
{
  double x = position[0];
  double y = position[1];
  double z = position[2];

  //Il faudra ajouter le bruit de Perlin
  double bruitX = frand(-0.001, 0.001);
  double bruitY = frand(-0.001, 0.001);
  double bruitZ = frand(-0.001, 0.001);

  position[0] = vect_dir[0]*(float)(vitesse[0]/35)*speedCoeff + x + bruitX;
  position[1] = vect_dir[1]*(float)(vitesse[1]/35)*speedCoeff + y + bruitY;
  position[2] = vect_dir[2]*(float)(vitesse[2]/35)*speedCoeff + z + bruitZ;
}
