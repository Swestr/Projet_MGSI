#ifndef VENT_H
#define VENT_H

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>

class Vent
{
  public:
    //On a besoin de deux point les plus distants du parallepipède pour le tracer
    std::vector<double> point1;
    std::vector<double> point2;

    //Coefficient de vitesse du vent
    double vitesse;

    //vecteur directeur dans le voxel
    std::vector<double> vecDir;

    Vent(std::vector<double>, std::vector<double>, std::vector<double>, double);
    std::vector<double> getVec();
    double getVitesse();
    bool dedans(float, float, float);
    double max(double, double);
    double min(double, double);
    void draw(float, float, float);
};
#endif
