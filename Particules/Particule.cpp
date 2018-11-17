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

  vitesse.push_back(frand(0.25, 1));
  vitesse.push_back(frand(0.25, 1));
  vitesse.push_back(frand(0.25, 1));

  direction.push_back(0);
  direction.push_back(0.001);
  direction.push_back(0);

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

  //Pourcentage d'attenuation
  int attPourc = 99;

  //Nouvelle direction = (proportions de la direction initiale * direction initiale) +
  //                     (proportion du vecteur directeur * vecteur directeur attenué * vitesse du vent)
  direction[0] = ((attPourc * direction[0] / 100) + ((100-attPourc) * vect_dir[0] * speedCoeff * 0.001 / 100));
  direction[1] = ((attPourc * direction[1] / 100) + ((100-attPourc) * vect_dir[1] * speedCoeff * 0.001 / 100));
  direction[2] = ((attPourc * direction[2] / 100) + ((100-attPourc) * vect_dir[2] * speedCoeff * 0.001 / 100));

  //nouvelle position = direction * vitesse de particule + position + bruit
  position[0] = direction[0] * (float)(vitesse[0]) + x + bruitX;
  position[1] = direction[1] * (float)(vitesse[1]) + y + bruitY;
  position[2] = direction[2] * (float)(vitesse[2]) + z + bruitZ;
}
