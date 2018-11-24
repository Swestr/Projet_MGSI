#ifndef SPHERE_H
#define SPHERE_H
class Sphere : public Obstacle
{
  public:
    std::vector<double> centre;
    double rayon;
    Sphere(std::vector<double> c, double r);
    std::vector<double> getTangente(std::vector<double> part, std::vector<double> I);
    bool dedans(float x, float y, float z);
    void draw(int r, int g, int b);
};

#endif
