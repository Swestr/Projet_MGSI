#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>

class Obstacle
{
  public:
    std::vector<double> normer(double, double, double);
    virtual std::vector<double> getTangente(std::vector<double>, std::vector<double>)=0;
    virtual bool dedans(float, float, float)=0;
    virtual void draw(float, float, float)=0;
};
#endif
