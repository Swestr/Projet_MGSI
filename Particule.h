#ifndef PATRICULE_H
#define PATRICULE_H
#include <vector>
#include <string>
#include <time.h>

class Particule
{
  public:
    const int n = 32;
    double vie;
    std::vector <double>position;
    std::vector <double> vitesse;
    std::vector<double> direction;
    double masse;
    std::vector<double> couleur;
    double densite;
    Particule();
    void print();
    void draw();
    bool dedans(float, float, float);
};

#endif
