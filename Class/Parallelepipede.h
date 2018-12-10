#ifndef PARALLELEPIPEDE_H
#define PARALLELEPIPEDE_H
class Parallelepipede : public Obstacle
{
  public:
    std::vector<double> translate;
    std::vector<double> rotation;
    std::vector<double> scale;

    Parallelepipede(std::vector<double>, std::vector<double>, std::vector<double>);
    void draw(float, float, float);
    std::vector<double> getTangente(std::vector<double>, std::vector<double>);

    bool dedans(float, float, float);
    bool translating(float, float, float);
    bool rotateX(float, float, float);
    bool rotateY(float, float, float);
    bool rotateZ(float, float, float);
    bool scaling(float, float, float);
    bool unitaire(float, float, float);

    std::vector<double> myCross(std::vector<double>, std::vector<double>);
    std::vector<double> getNormales(int);
};

#endif
