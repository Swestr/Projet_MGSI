#ifndef SPHERE_H
#define SPHERE_H
class Sphere : public Obstacle
{
  public:
    std::vector<double> centre;
    double rayon;
    Sphere(std::vector<double>, double);
    std::vector<double> getTangente(std::vector<double>, std::vector<double>);
    bool dedans(float, float, float);
    void draw(float, float, float);
};

#endif
