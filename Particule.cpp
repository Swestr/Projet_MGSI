#include "header.h"

using namespace std;

Particule::Particule()
{
  vie = frand(150, 8000);

  position.push_back(frand(0, 1));
  position.push_back(0);
  position.push_back(0.5);
  // position.push_back(frand(0, 1));
  // position.push_back(frand(-0.1, 0.1));
  // position.push_back(frand(0, 1));

  vitesse.push_back(frand(0.25, 1));
  vitesse.push_back(frand(0.25, 1));
  vitesse.push_back(frand(0.25, 1));

  r = 1;

  direction.push_back(0);
  direction.push_back(0.001);
  direction.push_back(0);

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
    glColor3f(r, 1, 1);
    glTranslatef(position[0], position[1], position[2]);
    glutSolidCube(1.0/(n*4));
  glPopMatrix();

}
std::vector<double> Particule::nextPosition(std::vector<double> vect_dir, double speedCoeff)
{
  std::vector<double> newPosition;

  //Il faudra ajouter le bruit de Perlin
  double bruitX = 0;//frand(-0.001, 0.001);
  double bruitY = 0;//frand(-0.001, 0.001);
  double bruitZ = 0;//frand(-0.001, 0.001);

  //Pourcentage d'attenuation
  int attPourc = 99;

  //Nouvelle direction = (proportions de la direction initiale * direction initiale) +
  //                     (proportion du vecteur directeur * vecteur directeur attenué * vitesse du vent)
  direction[0] = ((attPourc * direction[0] / 100) + ((100-attPourc) * vect_dir[0] * speedCoeff * 0.001 / 100));
  direction[1] = ((attPourc * direction[1] / 100) + ((100-attPourc) * vect_dir[1] * speedCoeff * 0.001 / 100));
  direction[2] = ((attPourc * direction[2] / 100) + ((100-attPourc) * vect_dir[2] * speedCoeff * 0.001 / 100));

  //nouvelle position = position + direction * vitesse de particule + bruit
  newPosition.push_back(position[0] + direction[0] * (float)(vitesse[0]) + bruitX);
  newPosition.push_back(position[1] + direction[1] * (float)(vitesse[1]) + bruitY);
  newPosition.push_back(position[2] + direction[2] * (float)(vitesse[2]) + bruitZ);

  return newPosition;
}
void Particule::move(std::vector<double> vect_dir, double speedCoeff)
{
  vie--;
  std::vector<double> newPosition = nextPosition(vect_dir, speedCoeff);
  position[0] = newPosition[0];
  position[1] = newPosition[1];
  position[2] = newPosition[2];
}
void Particule::force_move(std::vector<double> vec_dir)
{
  position[0] += vec_dir[0] * 0.001;
  position[1] += vec_dir[1] * 0.001;
  position[2] += vec_dir[2] * 0.001;
}
