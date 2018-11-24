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

    Vent(std::vector<double> pt1, std::vector<double> pt2, std::vector<double> vdir, double speed);
    std::vector<double> getVec();
    double getVitesse();
    bool dedans(float x, float y, float z);
    double max(double i, double j);
    double min(double i, double j);
    void draw(int r, int g, int b);
};
#endif
