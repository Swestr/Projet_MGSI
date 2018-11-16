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
    double masse;
    double densite;
    std::vector<double> position;
    std::vector<double> vitesse;
    std::vector<double> direction;
    std::vector<double> couleur;
    Particule();
    void print();
    void draw();
    bool dedans(float, float, float);
    void move(std::vector<double> vect_dir);
};

#endif
