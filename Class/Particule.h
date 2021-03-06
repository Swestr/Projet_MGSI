#ifndef PATRICULE_H
#define PATRICULE_H

#include <vector>

class Particule
{
  public:
    const int n = 32;
    double vie;
    double masse;
    double densite;
    double r;
    double g;
    double b;
    std::vector<double> position;
    std::vector<double> vitesse;
    std::vector<double> direction;
    std::vector<double> couleur;
    Particule();
    void print();
    void draw();
    bool dedans(float, float, float);
    void move(std::vector<double>, double);
    std::vector<double> nextPosition(std::vector<double>, double);
    void force_move(std::vector<double>);
};

#endif
