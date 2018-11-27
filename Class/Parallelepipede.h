#ifndef PARALLELEPIPEDE_H
#define PARALLELEPIPEDE_H
class Parallelepipede : public Obstacle
{
  public:
    std::vector<double> centre;
    std::vector<double> rotation;
    double longueur;
    double largeur;
    double hauteur;
    //Rotation en x, y, et z (vecteur 3D)

    Parallelepipede(std::vector<double>, std::vector<double>, double, double, double);
    bool dedans_noRotate(float, float, float);
    std::vector<double> getTangente(std::vector<double>, std::vector<double>);
    bool dedans(float, float, float);
    void draw(float, float, float);
};

#endif
